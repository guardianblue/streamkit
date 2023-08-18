#include "pch.h"
#include "Notifier.h"

using namespace CryptoPP;

wsclient c;

string serverUri = "ws://localhost:4455";
string serverPassword = "";

connection_hdl conn;
bool isConnected;
unsigned int msgIndex = 0;
unsigned int numRetry = 0;

string lastSceneName = "";

void handlePayload(json payload) {
	switch ((int) payload["op"]) {
	case 0: {
		// Hello
		json authObj = payload["d"]["authentication"];
		LOG_INFO << "WS: Hello (useAuth: " << !authObj.is_null() << ")" << endl;
		identify(authObj);
		break;
	}
	case 2:
		// Identified
		LOG_INFO << "WS: Identified" << endl;
		isConnected = true;
		break;
	default:
		LOG_DEBUG << "WS: " << payload << endl;
	}
}

void onMessage(connection_hdl, wsclient::message_ptr msg)
{
	string payload = msg->get_payload();

	try {
		handlePayload(json::parse(payload));
	}
	catch (std::exception const& e) {
		LOG_ERROR << "OBS Payload Parse Error: " << e.what() << endl;
	}
}

void onConnectionOpen(connection_hdl hdl)
{
	conn = hdl;
	LOG_INFO << "Connection opened" << endl;
}

void onConnectionClose(connection_hdl handle)
{
	isConnected = false;
	LOG_INFO << "Connection closed" << endl;
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
	c.set_access_channels(websocketpp::log::alevel::none);
	c.clear_access_channels(websocketpp::log::alevel::frame_payload);
	c.set_error_channels(websocketpp::log::elevel::rerror);

	c.set_message_handler(onMessage);
	c.set_open_handler(onConnectionOpen);
	c.set_close_handler(onConnectionClose);
}

string sha256base64(string ciper)
{
	string digest;
	SHA256 hash;

	StringSource ss(ciper, true,
		new HashFilter(hash,
			new Base64Encoder(
				new StringSink(digest), 
				false /* do not insert line break */
			)
		)
	);

	return digest;
}

string getAuthDigest(string salt, string challenge)
{
	string secret = sha256base64(serverPassword + salt);
	string authDigest = sha256base64(secret + challenge);

	return authDigest;
}

void identify(json authObj)
{
	json jmain;
	jmain["op"] = 1;

	json j;
	j["rpcVersion"] = 1;

	if (!authObj.is_null()) {
		j["authentication"] = getAuthDigest(authObj["salt"], authObj["challenge"]);
	}

	jmain["d"] = j;

	c.send(conn, jmain.dump(), frame::opcode::text);
}

void sendMessage(string sceneName)
{
	lastSceneName = sceneName;

	if (isConnected)
	{
		try {
			if (sceneName.compare("") != 0)
			{
				LOG_DEBUG << "Sending scene change to OBS: " << sceneName << endl;

				json js;
				js["op"] = 6;

				json jsreq;
				jsreq["requestType"] = "SetCurrentProgramScene";
				jsreq["requestId"] = std::to_string(++msgIndex);

				json jsreqdata;
				jsreqdata["sceneName"] = sceneName;

				jsreq["requestData"] = jsreqdata;
				js["d"] = jsreq;

				c.send(conn, js.dump(), frame::opcode::text);

			}
		}
		catch (std::exception const& e) {
			LOG_ERROR << "Error sending scene change to OBS: " << e.what() << endl;
		}
	}
	//else {
	//	wsRetryConnect();
	//}
}

void wsInit(boost::property_tree::ptree& ptree) {
	string ptreeServerUri = ptree.get<string>("MAIN.server");
	if (ptreeServerUri.compare("") != 0) {
		serverUri = ptreeServerUri;
	}

	serverPassword = ptree.get<string>("MAIN.password");
}

void wsConnect()
{
	LOG_INFO << "Connecting to: " << serverUri << endl;

	try {
		c.init_asio();
		wsClientSetCommonProperties();
		wsClientGetConnection(serverUri);
	}
	catch (websocketpp::exception const& e) {
		LOG_ERROR << e.what() << endl;
	}
}

// Do not attempt to reconnection as websocketpp has an open issue
// that memory would leak on every failed attemp.
// 
// https://github.com/zaphoyd/websocketpp/issues/754
// 
//void wsRetryConnect()
//{
//	LOG_INFO << "Reconnecting" << endl;
//	numRetry++;
//	try {
//		c.reset();
//		wsClientSetCommonProperties();
//		wsClientGetConnection(serverUri);
//	} 
//	catch (websocketpp::exception const& e) {
//		LOG_ERROR << e.what() << endl;
//	}
//}
