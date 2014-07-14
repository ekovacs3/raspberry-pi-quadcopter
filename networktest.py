import socket

s = socket.socket()
host = "10.0.0.17"
port = 4999
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
number = 1234567890

s.listen(5)
while True:
    (c, addr) = s.accept()
    print 'got connection from', addr
#    c.send("you have successfully connected")
    c.send(repr(number))
    c.close()
