#include <iostream>

#include "peer_connection.h"

namespace Network {

    PeerConnection::PeerConnection(std::string name, const std::unique_ptr<Server>& server)
        : _server(server)
        , _name(name)
        , _loop(&PeerConnection::run_internal, this)
        , _keep_going(true)
    {
    }

    PeerConnection::~PeerConnection()
    {
        stop();
    }

    bool PeerConnection::connect(const std::string& host, const std::string& port)
    {
        auto client = Network::Client::create(host, port);
        if (client) {
            on_new_client(client);
            return true;
        }

        return false;
    }

    bool PeerConnection::send(const std::string& who, const std::string msg)
    {
        std::lock_guard<std::mutex> locker(_peers_lock);
        auto it = _peers.find(who);
        if (it == _peers.end()) {
            return false;
        }
        return it->second->send(msg.c_str(), msg.size());
    }

    void PeerConnection::stop()
    {
        _keep_going = false;
        if (_loop.joinable()) {
            _loop.join();
        }

        std::lock_guard<std::mutex> locker(_peers_lock);
        _peers.clear();
    }

    void PeerConnection::on_new_client(std::unique_ptr<Client>& client)
    {
        client->send(_name.c_str(), _name.size());
        auto client_name = client->recv();
        if (client_name) {
            std::cout << "[NEW] connection detected: " << *client_name << std::endl;
            std::lock_guard<std::mutex> locker(_peers_lock);
            _peers.insert(std::make_pair(*client_name, std::move(client)));
        }
    }

    void PeerConnection::run_internal()
    {
        while (_keep_going)
        {
            auto client = _server->accept_new_client();
            if (client) {
                on_new_client(client);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
