#include "doctest.h"
#include "server.h"

TEST_SUITE_BEGIN("client <-> server");

TEST_CASE("create server")
{
    SUBCASE("valid information")
    {
        auto server = Network::Server::create("127.0.0.1", "8080");
        REQUIRE(server);
    }

    SUBCASE("invalid IP")
    {
        auto server = Network::Server::create("32187.9128392183.12231.31", "8080");
        REQUIRE_FALSE(server);
    }

    SUBCASE("invalid PORT")
    {
        auto server = Network::Server::create("127.0.0.1", "wrong");
        REQUIRE_FALSE(server);
    }
}

TEST_CASE("create client")
{
    auto server = Network::Server::create("127.0.0.1", "8080");

    SUBCASE("valid information")
    {
        auto client = Network::Client::create("127.0.0.1", "8080");
        REQUIRE(client);
    }

    SUBCASE("invalid IP")
    {
        auto client = Network::Client::create("32187.9128392183.12231.31", "8080");
        REQUIRE_FALSE(client);
    }

    SUBCASE("invalid PORT")
    {
        auto client = Network::Client::create("127.0.0.1", "wrong");
        REQUIRE_FALSE(client);
    }
}

TEST_SUITE_END();
