#include <vega/hal.h>

#include <stdio.h>

int _write(int file, char* ptr, int len) {
    (void)file;
    UART_Transmit(&huart0, ptr, len);
    return len;
}

int main()
{
    UART_Init(&huart0);

    while (1) {
        printf("This is a printf call\r\n");
        delayms(500);
    }
    
    return 0;
}



