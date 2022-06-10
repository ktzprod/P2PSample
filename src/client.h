#pragma once

#include <memory>
#include <optional>
#include <string>

namespace Network {

    class Client final
    {
        public:

            Client(std::string host_name, int client_socket);
            virtual ~Client();

        public:

            /**
             * @brief Create a client instance based on the given host and port
             *
             * @param host_name
             * @param port
             *
             * @return A Client instance if everything went fine, nullptr otherwise
             */
            static std::unique_ptr<Client> create(const std::string& host_name, const std::string& port);

        public:

            /**
             * @brief Send the given message to the client
             *
             * @param data
             * @param data_size
             *
             * @return false if the client can't be reached, true if the message has been sent properly
             */
            bool send(const void* data, size_t data_size) const;

            /**
             * @brief Receive data from the client
             *
             * @return the message content
             */
            std::optional<std::string> recv() const;

            /**
             * @return the host name of the client
             */
            inline const std::string& host_name() { return _host_name; }

        private:

            std::string _host_name;
            int _socket;
    };

}
