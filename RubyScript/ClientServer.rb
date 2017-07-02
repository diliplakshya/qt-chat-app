require 'socket' # Provides TCPServer and TCPSocket classes

messageToBeSent = ""
port = 1234

printf "Enter User Type : server or client :"
userType = gets.chomp

printf "Enter Host name :"
hostname = gets.chomp
	
#Work as a server
if userType == "server"

	puts "********* Server is waiting for client connection *********"
	
	server = TCPServer.new(hostname, port) # Server bind to port 1234
	client = server.accept    # Wait for a client to connect
	
	puts "********* Server has accepted client connection *********"
	  
	while messageToBeSent!="bye" do
		printf "Server :"
		
		messageToBeSent = gets.chomp

		client.puts messageToBeSent
		
		puts client.recv(100)
	end	
	client.close
	puts "********* Server has lost connection with client *********"

#Work as a client
else
	clientThread = ""	
	puts "********* Waiting for client to be connected to server *********"
	client = TCPSocket.open(hostname, port)
	puts "********* Client is connected to server *********"
	
	clientThread = Thread.start do
		while true						
			printf "Client :"			
			
			messageToBeSent = gets.chomp
			client.puts messageToBeSent		
			
			puts client.recv(100)		
		end		
	end	
	clientThread.join
	puts "********* client is disconnected from server *********"
end