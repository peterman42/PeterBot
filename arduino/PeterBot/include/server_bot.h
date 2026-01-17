#ifndef SERVER_BOT_H
#define SERVER_BOT_H

class ServerBot {
private:
    int port;
public:


    ServerBot(int port): port(port) {};
    ~ServerBot();

    void initialize();
    void start();

};
#endif // SERVER_BOT_H