require 'socket'               # Get sockets from stdlib

server = TCPServer.open(1234)
socket = server.accept
while
socket.puts 'Hello!' # Prints Hello! to the client
puts socket.recv(100)
end