#ifndef NITRATE_SERVER_HPP
#define NITRATE_SERVER_HPP

#include <server/client.hpp>
#include <string>
#include <vector>

class Server {
public:
    Server(Network& network);
    ~Server();

    static Server* getInstance();
    bool init();
    void close();

    void run();

    std::string version;
    int protocolVersion;
    std::string motd;
    int maxPlayers;

private:
    static Server* instance;

    bool isRunning;

    std::vector<Client> clients;

    Network& network;
};

#endif // NITRATE_SERVER_HPP