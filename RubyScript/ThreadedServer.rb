require "socket"
 
gs = TCPServer.open(1234)
addr = gs.addr
addr.shift
printf("server is on %s\n", addr.join(":"))
 
loop do
  Thread.start(gs.accept) do |s|
    print(s, " is accepted\n")
    while true
    	socket.puts 'Hello!' # Prints Hello! to the client
    	puts socket.recv(100)
    end
    print(s, " is gone\n")
    s.close
  end
end