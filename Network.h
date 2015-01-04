//Network.h
#ifndef NETWORK_H
#define NETWORK_H

#include <cstdlib>
#include <iostream>
#include <array>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

class Network
{
public:
    Network();
    void startServer();
    //void session(boost::asio::ip::tcp::socket sock);
    void server(boost::asio::io_service& io_service, unsigned short port);
    void getData(std::array<float, 3> data);
    void sendData(std::array<float, 3> data);
private:
    std::array<float, 3> outypr;
    std::array<float, 3> inypr;
};


#endif
