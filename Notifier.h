#pragma once

using namespace std;
using namespace websocketpp;

typedef client<config::asio_client> wsclient;

void onConnectionOpen(connection_hdl handle);
void onConnectionClose(connection_hdl handle);
void onMessage(connection_hdl, wsclient::message_ptr msg);
void identify();
void sendMessage(string sceneName);
void wsConnect(string uri);
void wsRetryConnect();
