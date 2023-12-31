// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define BOOST_USE_WINAPI_VERSION BOOST_WINAPI_VERSION_WIN7

#include "framework.h"
#include "Psapi.h"

#include <iostream>
#include <thread>
#include <vector>

#include <atlstr.h>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <minhook.h>
#include <nlohmann/json.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

#include "Logger.hpp"
#include "Notifier.h"
#include "Decider.h"

#endif //PCH_H
