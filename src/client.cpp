#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "client.h"

namespace Network {

    Client::Client(std::string host_name, int client_socket)
        : _host_name(host_name)
        , _socket(client_socket)
    {
        // nothing to do
    }

    Client::~Client()
    {
        close(_socket);
    }

    std::unique_ptr<Client> Client::create(const std::string& host_name, const std::string& port)
    {
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket < 0)
        {
            std::cerr << "Failed to create socket with error: " << strerror(errno) << std::endl;
            return nullptr;
        }

        struct sockaddr_in server;
        struct hostent *host = gethostbyname(host_name.c_str());
        if (host == NULL)
        {
            std::cerr << "Failed to get host by name: " << strerror(errno) << std::endl;
            return nullptr;
        }

        int server_port = atoi(port.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(server_port);

        memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);

        // Connect to the remote server
        int res = connect(client_socket, (struct sockaddr*) &server, sizeof(server));
        if (res < 0)
        {
            std::cerr << "Failed to connect with error: " << strerror(errno) << std::endl;
            return nullptr;
        }

        return std::unique_ptr<Client>(new Client(host_name, client_socket));
    }

    bool Client::send(const void* data, size_t data_size) const
    {
        const char* data_ptr = (const char*)data;
        while (data_size > 0)
        {
            auto bytes_sent = ::send(_socket, data_ptr, data_size, 0);
            if (bytes_sent < 0) {
                return false;
            }

            data_ptr += bytes_sent;
            data_size -= bytes_sent;
        }

        return true;
    }

    std::optional<std::string> Client::recv() const
    {
        char recv_data[2048];
        int bytes_recieved = ::recv(_socket, recv_data, 2048, 0); recv_data[bytes_recieved] = '\0';

        if (bytes_recieved == 0) { return std::nullopt; }
        if (bytes_recieved == -1) {
            if (errno != EWOULDBLOCK) {
                std::cerr << "Error while trying to receive data from client with error: " << strerror(errno) << std::endl;
            }
            return std::nullopt;
        }

        return std::string(recv_data);
    }
}
