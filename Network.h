//Network.h
#ifndef NETWORK_H
#define NETWORK_H

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

class Network
{
public:
    Network();
    void startServer();
    void session(tcp::socket sock)
    void server(boost::asio::io_service& io_service, unsigned short port);
    void getData(int& data);
    void sendData(int& data);
private:
    float outypr [3];
    float inypr [3];
}


#endif
