#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"

//const short multicast_port = 10002;

class receiver
{
public:
  receiver(boost::asio::io_service& io_service,
      const boost::asio::ip::address& listen_address,
      const boost::asio::ip::address& multicast_address,
      const int& multicast_port)
    : socket_(io_service)
  {
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(
        listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // local ip
    const boost::asio::ip::address& local_address = boost::asio::ip::address::from_string("1.2.3.4");
    // Join the multicast group.
    socket_.set_option(
        boost::asio::ip::multicast::join_group(multicast_address));

    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&receiver::handle_receive_from, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive_from(const boost::system::error_code& error,
      size_t bytes_recvd)
  {
    if (!error)
    {
      std::cout.write(data_, bytes_recvd);
      std::cout << std::endl;

      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&receiver::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }

private:
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 4)
    {
      std::cerr << "Usage: receiver <listen_address> <multicast_address> <multicast_port>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 239.255.0.1 30001\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 ff31::8000:1234 30001\n";
      return 1;
    }

    boost::asio::io_service io_service;
    receiver r(io_service,
        boost::asio::ip::address::from_string(argv[1]),
        boost::asio::ip::address::from_string(argv[2]),
        atoi(argv[3]));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

