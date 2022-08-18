#This code is for Python3:

#import required modules:
import sys
import socket
import ssl


#create socket:
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM) #AF_INET denotes IPv4 family and SOCK_stream denotes TCP.

#define server address and port:
srvr_add=('localhost',22002)

#Wrap-Up created socket with ssl key and certificate
ssl_sock=ssl.wrap_socket(sock,cert_reqs=1,ca_certs='cert')
print(sys.stderr,'connecting to %s port %s' % srvr_add)

#connect client with ssl secured socket:
ssl_sock.connect(srvr_add)

try:
    tosend ='this is the echo message'
    print(sys.stderr,'sending "%s"' % tosend)
    ssl_sock.sendall(tosend) # sending message to server

    bits_recv=0 #
    bits_expected = len(tosend)

    while bits_recv < bits_expected:
        data=ssl_sock.recv(20) # Receiving message from server
        bits_recv+=len(data)
        print(sys.stderr,'received: "%s"' %data)

finally:
    print(sys.stderr,'closing socket') 
    sock.close() #closing socket to free port.