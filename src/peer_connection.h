#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "server.h"

namespace Network {

    class PeerConnection final
    {
        public:

            PeerConnection(std::string name, const std::unique_ptr<Server>& server);
            virtual ~PeerConnection();

        public:

            /**
             * @brief create a connection with an other peer
             *
             * @param host
             * @param port
             *
             * @return true if the connection is successful; false otherwise
             */
            bool connect(const std::string& host, const std::string& port);

            /**
             * @brief send a message to the given user
             *
             * @param who
             * @param msg
             *
             * @return true if the user exists and the message has been sent properly, false otherwise
             */
            bool send(const std::string& who, const std::string msg);

            /**
             * @brief stop the connection
             */
            void stop();

        private:

            void run_internal();
            void on_new_client(std::unique_ptr<Client>&);

        private:

            using PeersDatabase = std::unordered_map<std::string, std::unique_ptr<Client>>;

            const std::unique_ptr<Server>&  _server;
            std::string                     _name;
            std::thread                     _loop;
            PeersDatabase                   _peers;
            std::mutex                      _peers_lock;
            std::atomic_bool                _keep_going;
    };
}
