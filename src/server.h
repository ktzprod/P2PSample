#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include "client.h"

namespace Network {

    class Server final
    {
        public:

            virtual ~Server();

        private:

            Server(int socket);

        public:

            /**
             * @brief create a server based on the given arguments
             *
             * @param ip
             * @param port
             *
             * @return a Server instance
             */
            static std::unique_ptr<Server> create(const std::string& ip, const std::string& port);

            /**
             * @brief Check if a new client tries to connect
             *
             * @return a Client instance
             */
            std::unique_ptr<Client> accept_new_client();

        private:

            int server_socket;
    };
}
