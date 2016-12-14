#ifndef __SERVER_BOT_H__
#define __SERVER_BOT_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <exception>
#include <functional>

#define HANDLE_FUNCTION_REF const std::function<void(int) >&
#define DEFAULT_SERVER_PORT 8888
struct ClientMessage
{
	int data;
	bool status;

	ClientMessage()
	: data(0)
	, status(false)	
	{}
};

class ServerBot
{
public:
	int sockfd;
	int newsockfd;
	int port;
	int clilen;
	char* buffer;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	int n;
	int data;
	
	ServerBot()
	: port(DEFAULT_SERVER_PORT)
	{}

	ServerBot(int port)
	: port(port)
	{}

	~ServerBot()
	{}

	/////////////////////////////////////////////////
	bool Start();
	/////////////////////////////////////////////////
	void Listen(HANDLE_FUNCTION_REF Handle);
	////////////////////////////////////////////////
	ClientMessage getData(int sockfd);
};

#endif/*__SERVER_BOT_H*/
