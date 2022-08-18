#This code is for python3:

#importing required packages:
import socket
import sys
import ssl

KEY='<PATH TO KEY>'
CERT='<PATH TO CERT>'

#Creating socket:
#AF_INET denotes IPv4 family and SOCK_stream denotes TCP.
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

#server address and port:
srvr_addr=('<IP>',<port>)

print(sys.stderr,'setting up %s on port %s' % srvr_addr)

#Binding socket:
sock.bind(srvr_addr)

#listening on port:
sock.listen(1)

#Wrap-Up created socket with ssl key and certificate
s_ssl = ssl.wrap_socket(sock,keyfile=KEY,certfile=CERT,server_side=True)



while True:
    #waiting for connection
    print(sys.stderr,'waiting for connection')
    #accepting client connection
    connection, clnt_addr=s_ssl.accept()

    try:
        print(sys.stderr,'connection from',clnt_addr)
        while True:
            data = connection.recv(20)
            print(sys.stderr,'received "%s" ' % data)
            if data:
                print(sys.stderr,'Sending data back to client')
                connection.sendall(data)
            else:
                print(sys.stderr,'no more data from ',clnt_addr)
                break
    finally:2
        #closing connection to free the port:
        connection.close()