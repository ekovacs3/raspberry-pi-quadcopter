//Network.cpp
#include Network.h
#include map.h
#include <thread>

Network::Network()
{
    std::thread(startServer).detach();
}

void Network::startServer()
{
    try
    {

        boost::asio::io_service io_service;
        server(io_service, PORT);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void Network::session(tcp::socket sock)
{
    try
    {
        for (;;)
        {
            char indata[MAX_LENGTH];

            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(indata), error);
            if (error == boost::asio::error::eof)
            {
                break; // Connection closed cleanly by peer.
            }
            else if (error)
            {
                throw boost::system::system_error(error); // Some other error.
            }
            //PUT SPECIFIC CODE HERE
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void Network::server(boost::asio::io_service& io_service, unsigned short port)
{
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        tcp::socket sock(io_service);
        a.accept(sock);
        std::thread(session, std::move(sock)).detach();
    }
}

void getData(float& data)
{
    data[0] = inypr[0];
    data[1] = inypr[1];
    data[2] = inypr[2];
}

void sendData(float& data)
{
    outypr[0] = data[0];
    outypr[1] = data[1];
    outypr[2] = data[2];
}
