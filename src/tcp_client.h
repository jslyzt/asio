#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include "asio.hpp"
#include "tcp_message.h"

using asio::ip::tcp;

typedef std::deque<tcpMessage> message_queue;

class tcpClient {
public:
    tcpClient(asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

    void write(const tcpMessage& msg);

    void close();

private:
    void do_connect(const tcp::resolver::results_type& endpoints);

    void do_read_header();

    void do_read_body();

    void do_write();

private:
    asio::io_context& io_context_;
    tcp::socket socket_;
    tcpMessage read_msg_;
    message_queue write_msgs_;
};
