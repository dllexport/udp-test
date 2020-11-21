#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
int main() {
    boost::asio::io_context io;
    boost::asio::ip::udp::socket socket(io);
    boost::asio::spawn(io, [&](boost::asio::yield_context context){
        socket.open(boost::asio::ip::udp::v4());
        const auto bind_ep = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("10.0.0.2"), 2222);
        boost::system::error_code ec;
        socket.bind(bind_ep, ec);
        char buff[1024];
        const auto send_ep = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("10.0.0.1"), 2222);
        boost::asio::steady_timer timer(io);
        uint32_t bytes_per_second = 2.5 * 1024 * 1024;
        if(setsockopt(socket.native_handle(), SOL_SOCKET, SO_MAX_PACING_RATE, &bytes_per_second, sizeof(bytes_per_second)) < 0) {
            std::cout << "Unable to set socket max pacing rate" << std::endl;
        }
        int i = 0;
        while(1) {
            boost::system::error_code ec;
            auto bytes_send = socket.async_send_to(boost::asio::buffer(buff, 1024), send_ep, context[ec]);
            printf("sending: %d\n", i++);
        }
    });
    io.run();
    return 0;
}
