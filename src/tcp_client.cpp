#include "tcp_client.h"

tcpClient::tcpClient(asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
    : io_context_(io_context),
      socket_(io_context) {
    do_connect(endpoints);
}

void tcpClient::write(const tcpMessage& msg) {
    asio::post(io_context_,
    [this, msg]() {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            do_write();
        }
    });
}

void tcpClient::close() {
    asio::post(io_context_, [this]() { socket_.close(); });
}

void tcpClient::do_connect(const tcp::resolver::results_type& endpoints) {
    asio::async_connect(socket_, endpoints,
    [this](std::error_code ec, tcp::endpoint) {
        if (!ec) {
            do_read_header();
        }
    });
}

void tcpClient::do_read_header() {
    asio::async_read(socket_,
                     asio::buffer(read_msg_.data(), tcpMessage::header_length),
    [this](std::error_code ec, std::size_t length) {
        if (!ec && read_msg_.decode_header()) {
            do_read_body();
        } else {
            socket_.close();
        }
    });
}

void tcpClient::do_read_body() {
    asio::async_read(socket_,
                     asio::buffer(read_msg_.body(), read_msg_.body_length()),
    [this](std::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            do_read_header();
        } else {
            socket_.close();
        }
    });
}

void tcpClient::do_write() {
    asio::async_write(socket_,
                      asio::buffer(write_msgs_.front().data(),
                                   write_msgs_.front().length()),
    [this](std::error_code ec, std::size_t length) {
        if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
                do_write();
            }
        } else {
            socket_.close();
        }
    });
}
