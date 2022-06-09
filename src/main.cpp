#include <signal.h>

#include <atomic>
#include <functional>
#include <iostream>
#include <unordered_map>

#include "peer_connection.h"
#include "utils.hpp"

void print_help()
{
    std::cout << "This program must be used as follow:" << std::endl;
    std::cout << "\t" << "[PROGRAM] -user [NAME] -ip [IP] -port [PORT]" << std::endl;
}

static std::atomic_bool on_sig_int_flag = false;
static void on_signal_handler(int sig)
{
    if (sig == SIGINT) {
        on_sig_int_flag = true;
    }
}

int main(int argc, char** argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    if (argc != 7) {
        print_help();
        return -1;
    }

    std::string my_name = argv[2];
    std::string my_ip = argv[4];
    std::string my_port = argv[6];

    auto server = Network::Server::create(my_ip, my_port);
    Network::PeerConnection peer_connection(my_name, server);

    std::atomic_bool keep_going = true;

    const std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> command_map {
        { "exit", [&keep_going](const std::vector<std::string>&) { keep_going = false; } },
        { "connect", [&peer_connection](const std::vector<std::string>& args) { peer_connection.connect(args[1], args[2]); } },
        { "send", [&peer_connection](const std::vector<std::string>& args) { peer_connection.send(args[1], args[2]); } },
    };

    while (keep_going && !on_sig_int_flag)
    {
        std::string user_command;

        std::cout << ">> ";
        std::getline(std::cin, user_command);

        auto args = Utils::split(user_command, " ");
        auto it = command_map.find(args[0]);
        if (it != command_map.end()) {
            it->second(args);
        }

        std::cout << "\r";
        std::cout.flush();
    }

    peer_connection.stop();
    return 0;
}
