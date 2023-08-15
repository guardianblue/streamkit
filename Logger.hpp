#ifndef LOGGER_HPP
#define LOGGER_HPP
#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <string>

BOOST_LOG_GLOBAL_LOGGER(sysLogger,
    boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>);

class Logger
{
public:
    static void init();
    static void addFileLog(const std::string& logFileName);
    static void addConsoleLog();
};

#define LOG_LOG_LOCATION(LOGGER, LEVEL) \
  BOOST_LOG_SEV(LOGGER, boost::log::trivial::LEVEL) \
    << boost::log::add_value("Line", __LINE__) \
    << boost::log::add_value("File", __FILE__)

#define LOG_DEBUG LOG_LOG_LOCATION(sysLogger::get(), debug)
#define LOG_INFO LOG_LOG_LOCATION(sysLogger::get(), info)
#define LOG_WARN  LOG_LOG_LOCATION(sysLogger::get(), warn)
#define LOG_ERROR LOG_LOG_LOCATION(sysLogger::get(), error)
#define LOG_FATAL LOG_LOG_LOCATION(sysLogger::get(), fatal)

#endif LOGGER_HPP