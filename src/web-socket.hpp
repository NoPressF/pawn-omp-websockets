#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::connection_hdl WebsocketConnection;

typedef websocketpp::client<websocketpp::config::asio> WebsocketClient;
typedef WebsocketClient::message_ptr WebsocketMessage;

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef WebsocketServer::message_ptr WebsocketMessage;
typedef WebsocketServer::connection_ptr WebsocketConnectionPtr;