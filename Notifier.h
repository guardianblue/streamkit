#pragma once

using namespace nlohmann;
using namespace std;
using namespace websocketpp;

typedef client<config::asio_client> wsclient;

void onConnectionOpen(connection_hdl handle);
void onConnectionClose(connection_hdl handle);
void onMessage(connection_hdl, wsclient::message_ptr msg);
void identify(json authObj);
void sendMessage(string sceneName);
void wsInit(boost::property_tree::ptree& ptree);
void wsConnect();
void wsRetryConnect();
