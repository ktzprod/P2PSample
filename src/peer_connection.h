#pragma once

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

            bool connect(const std::string& host, const std::string& port);
            bool send(const std::string& who, const std::string msg);
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
