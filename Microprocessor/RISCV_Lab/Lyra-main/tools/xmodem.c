/*
 * Minimalistic implementation of the XModem/YModem protocol suite, including
 * a compact version of an CRC16 algorithm. The code is just enough to upload
 * an image to an MCU that bootstraps itself over an UART.
 *
 * Copyright (c) 2014 Daniel Mack <github@zonque.org>
 *
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define X_STX 0x01
#define X_ACK 0x06
#define X_NAK 0x15
#define X_EOF 0x04

#define X_SIZE_OVER 0x0f

#define min(a, b)       ((a) < (b) ? (a) : (b))

struct xmodem_chunk {
    uint8_t start;
    uint8_t block;
    uint8_t block_neg;
    uint8_t payload[128];
    uint16_t crc;
} __attribute__((packed));

#define CRC_POLY 0x1021

static uint16_t crc_update(uint16_t crc_in, int incr)
{
    uint16_t xor = crc_in >> 15;
    uint16_t out = crc_in << 1;

    if (incr)
        out++;

    if (xor)
        out ^= CRC_POLY;

    return out;
}

static uint16_t crc16(const uint8_t *data, uint16_t size)
{
    uint16_t crc, i;

    for (crc = 0; size > 0; size--, data++)
        for (i = 0x80; i; i >>= 1)
            crc = crc_update(crc, *data & i);

    for (i = 0; i < 16; i++)
        crc = crc_update(crc, 0);

    return crc;
}
static uint16_t swap16(uint16_t in)
{
    return (in >> 8) | ((in & 0xff) << 8);
}

enum {
    PROTOCOL_XMODEM,
    PROTOCOL_YMODEM,
};

static int xymodem_send(int serial_fd, const char *filename, int protocol, int wait)
{
    size_t len;
    int ret, fd;
    uint8_t answer,answer1,answer2;
    struct stat stat;
    const uint8_t *buf;
    uint8_t eof = X_EOF;
    struct xmodem_chunk chunk;
    int skip_payload = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -errno;
    }

    fstat(fd, &stat);
    len = stat.st_size;
    buf = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    if (!buf) {
        perror("mmap");
        return -errno;
    }

    if (wait) {
        fflush(stdout);

        do {
            ret = read(serial_fd, &answer, sizeof(answer));
            ret = read(serial_fd, &answer1, sizeof(answer1));
            ret = read(serial_fd, &answer2, sizeof(answer2));
            if (ret != sizeof(answer)) {
                perror("read");
                return -errno;
            }
            /*  printf("%c ",answer);
            printf("%c ",answer1);
            printf("%c ",answer2);*/
        } while (answer != 'C' || answer1 != 'C' || answer2 != 'C');
        

        printf("done.\n");
    }

    printf("Uploading %s ", filename);

    if (protocol == PROTOCOL_YMODEM) {
        strncpy((char *) chunk.payload, filename, sizeof(chunk.payload));
        chunk.block = 0;
        skip_payload = 1;
    } else {
        chunk.block = 1;
    }

    chunk.start = X_STX;

    while (len) {
        size_t z = 0;
        int next = 0;
        char status;

        if (!skip_payload) {
            z = min(len, sizeof(chunk.payload));
            memcpy(chunk.payload, buf, z);
            memset(chunk.payload + z, 0xff, sizeof(chunk.payload) - z);
        } else {
            skip_payload = 0;
        }

        chunk.crc = swap16(crc16(chunk.payload, sizeof(chunk.payload)));
        chunk.block_neg = 0xff - chunk.block;
        
        
        //unsigned char *tmp = ( unsigned char  *)(&chunk);
        //printf("size: %ld\n",sizeof(chunk));
        
        /*for(int i=0;i<sizeof(chunk);i++)
        {
            printf("%02X ",tmp[i]);    
            write(serial_fd, &tmp[i], 1);  
            usleep(10000);   	
        }*/

        ret = write(serial_fd, &chunk, sizeof(chunk));
        if (ret != sizeof(chunk))
            return -errno;
                
        

        ret = read(serial_fd, &answer, sizeof(answer));
        if (ret != sizeof(answer))
            return -errno;
                
        //printf("answer: %x\n",answer);
        switch (answer) {
        case X_NAK:
            status = 'N';
            break;
        case X_ACK:
            status = '.';
            next = 1;
            break;
        case X_SIZE_OVER:
            status = '?';
            printf("\n___________________________________________________\n\n!!! ERROR: File size is greater than 249KB! \nPlease reduce the program size and try again\n___________________________________________________\n\n");
            exit(0);
            break;
        default:
            status = '?';
            printf("\n___________________________________________________\n\n!!! Please RESET the ARIES Board and Try again\n___________________________________________________\n\n");
            exit(0);
            break;
        }

        printf("%c", status);
        fflush(stdout);

        if (next) {
            chunk.block++;
            len -= z;
            buf += z;
        }
    }

    ret = write(serial_fd, &eof, sizeof(eof));
    if (ret != sizeof(eof))
        return -errno;
            
    

    /* send EOT again for YMODEM */
    if (protocol == PROTOCOL_YMODEM) {
        ret = write(serial_fd, &eof, sizeof(eof));
        if (ret != sizeof(eof))
            return -errno;
    }

    printf("done.\n");
    
    ret = write(serial_fd, "\n", 1); //jump to program binary
    if (ret != sizeof(eof))
        return -errno;

    return 0;
}

static int open_serial(const char *path, int baud)
{
    int fd;
    struct termios tty;
    int RTS_flag;

    fd = open(path, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -errno;
    }

    
    
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return -errno;
    }

    //RTS_flag = TIOCM_RTS;
    //ioctl(fd,TIOCMBIC,&RTS_flag);//Set RTS pin
    //tty.c_cflag &= HUPCL; // disable hang-up-on-close to avoid reset

    cfsetospeed(&tty, baud);
    cfsetispeed(&tty, baud);
    
    tty.c_lflag &= ~(ICANON);
    tty.c_lflag &= ~(ECHO | ECHOE);
    tty.c_cc[VMIN] = 2;
    tty.c_cc[VTIME] = 10; 

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                         // disable break processing
    
                                        
    tty.c_oflag = 0;                                // no remapping, no delays
                    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);                // ignore modem controls,
                                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);              // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return -errno;
    }

    return fd;
}

static void dump_serial(int serial_fd)
{
    char in;

    for (;;) {
        read(serial_fd, &in, sizeof(in));
        //printf("%c", in);
        if(in==0x3c)
        {
            write(serial_fd, ">" , 1); //jump to program binary                 
            //printf("HANDSHAKE >>>>\n");
            break;				
        }
        fflush(stdout);
    }
}
static void dump_serial_bare(int serial_fd)
{
    char in;

    for (;;) {
        read(serial_fd, &in, sizeof(in));
        printf("%c", in);
        
        fflush(stdout);
    }
}

int main(int argc, char **argv)
{
    int a, ret, serial_fd;

    if (argc < 3) {
        printf("\nUsage : %s [device] <path/to/binary> \n",argv[0]);
        return -errno;
    }

    serial_fd = open_serial(argv[1], B115200);
    if (serial_fd < 0) {
        printf("\n___________________________________________________\n\n!!! Please connect the ARIES Board to your PC\n___________________________________________________\n\n");
        return -errno;
    }
    sleep(1);   
    printf("\nPress the Reset Button on Board\n"); 

    dump_serial(serial_fd);

    ret = xymodem_send(serial_fd, argv[2], PROTOCOL_XMODEM, 1);
    if (ret < 0)
            return ret;

    return 0;
}
