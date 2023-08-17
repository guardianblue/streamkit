#include "pch.h"
#include "Notifier.h"


using namespace std;
using namespace websocketpp;

wsclient c;
string serverUri;
connection_hdl conn;
bool isConnected;
unsigned int msgIndex = 0;

void onMessage(connection_hdl, wsclient::message_ptr msg)
{
	LOG_INFO << "WS: " << msg->get_payload() << endl;
}

void onConnectionOpen(connection_hdl hdl)
{
	conn = hdl;
	isConnected = true;
	LOG_INFO << "Connection opened" << endl;
	identify();
}

void onConnectionClose(connection_hdl handle)
{
	isConnected = false;
	LOG_INFO << "Connection closed" << endl;
	wsRetryConnect();
}

void wsClientGetConnection(string uri)
{
	websocketpp::lib::error_code ec;
	wsclient::connection_ptr conn_ptr = c.get_connection(uri, ec);
	if (ec) {
		LOG_ERROR << "Connection error: " << ec.message() << std::endl;
	}

	c.connect(conn_ptr);
	c.run();
}

void wsClientSetCommonProperties()
{
	c.set_access_channels(log::alevel::all);
	c.clear_access_channels(log::alevel::frame_payload);
	c.set_error_channels(log::elevel::all);

	c.set_message_handler(onMessage);
	c.set_open_handler(onConnectionOpen);
	c.set_close_handler(onConnectionClose);
}

void identify()
{
	nlohmann::json jmain;
	jmain["op"] = 1;

	nlohmann::json j;
	j["rpcVersion"] = 1;
	// todo implement auth

	jmain["d"] = j;

	c.send(conn, jmain.dump(), frame::opcode::text);
}

void sendMessage(string sceneName)
{
	if (isConnected)
	{
		if (sceneName.compare("") != 0)
		{
			LOG_DEBUG << "Sending scene change to OBS: " << sceneName << endl;

			nlohmann::json js;
			js["op"] = 6;

			nlohmann::json jsreq;
			jsreq["requestType"] = "SetCurrentProgramScene";
			jsreq["requestId"] = std::to_string(++msgIndex);

			nlohmann::json jsreqdata;
			jsreqdata["sceneName"] = sceneName;

			jsreq["requestData"] = jsreqdata;
			js["d"] = jsreq;

			c.send(conn, js.dump(), frame::opcode::text);
		}
	}
}

void wsConnect(string uri)
{
	LOG_INFO << "Connecting to: " << uri << endl;

	serverUri = uri;

	try {
		wsClientSetCommonProperties();		
		c.init_asio();
		wsClientGetConnection(serverUri);
	}
	catch (websocketpp::exception const& e) {
		LOG_ERROR << e.what() << endl;
	}
}

void wsRetryConnect()
{
	LOG_INFO << "Reconnecting" << endl;
	c.reset();
	try {
		wsClientSetCommonProperties();
		wsClientGetConnection(serverUri);
	} 
	catch (websocketpp::exception const& e) {
		LOG_ERROR << e.what() << endl;
	}
}
