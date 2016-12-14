#include "serverBot.h"
#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ServerBot::Start()
{
	bool isStarted = true;
	try
	{	
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0)
		{
			std::cout << "Failed to create socket." << std::endl;
			throw;
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(port);

		int bindStatus = bind(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(bindStatus < 0)
		{ // If failed to bind address and port.
			std::cout << "Failed to bind address and port." << std::endl;
			throw;
		}
		std::cout << "Bind address and port successfully." << std::endl;

		listen(sockfd,5);
		clilen = sizeof(cli_addr);
	} 
	catch(std::exception& e)
	{
		isStarted = false;	
	}
	catch(...)
	{
		isStarted = false;
	}

	return isStarted;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerBot::Listen(HANDLE_FUNCTION_REF Handle)
{
	// Listen for a connection
	try
	{
	
	while(1)
	{
		std::cout << "Waiting for a new client..." << std::endl;
		newsockfd = accept(sockfd, (struct sockaddr* )&cli_addr, (socklen_t*)&clilen);
		
		// Check if we have a new connection.
		if(newsockfd < 0)
		{
			std::cout << "Error in 'accept' function." << std::endl;
			throw;				
		}

		std::cout << "Established new connection." << std::endl;

		while(1)
		{
			ClientMessage message = getData(newsockfd);
			std::cout << "Socket code :: " << newsockfd << std::endl;
			if(message.status)
			{
				std::cout << "Got data: " << std::to_string(message.data) << std::endl;
				// Execute the 'Handle' function in order to handle the client message.
				Handle(message.data);
				//break;				
			}
		}
		close(newsockfd);
	}

	}
	catch(std::exception& e)
	{
		std::cout << "Error on listening." << std::endl;	
	}
	catch(...)
	{
		std::cout << "Error on listening." << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientMessage ServerBot::getData(int sockfd)
{
        char buffer[32];
        int n;
	ClientMessage message;
	try
	{	
		if((n=read(sockfd,buffer,32)) < 0)
		{
			std::cout << "Failed to read data." << std::endl;
			throw;			
		}
		
		buffer[n] = '\0';
		message.data = atoi(buffer);	
		message.status = true;
	}
	catch(std::exception& e)
	{
		message.status = false;		
	}
	catch(...)
	{
		message.status = false;
	}

	return message;
}

