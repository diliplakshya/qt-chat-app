require 'socket'      # Sockets are in standard library

hostname = 'localhost'
port = 1234

s = TCPSocket.open(hostname, port)

while
s.send('Hello World',0)
puts s.recv(100)
end


