#include "pch.h"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <fstream>
#include <string> 

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;

BOOST_LOG_GLOBAL_LOGGER_CTOR_ARGS(sysLogger,
	src::severity_channel_logger_mt<logging::trivial::severity_level>,
	(logging::keywords::channel = "SYSLF"));

#define LOG_FORMATTER \
    expr::stream \
    << expr::format_date_time(expr::attr<boost::posix_time::ptime>("TimeStamp"), "%Y-%m-%d %H:%M:%S") \
    << std::setw(6) << logging::trivial::severity \
    << " [" << expr::attr<std::string>("File") \
    << ":" << expr::attr<int>("Line") << "] " \
    << expr::smessage

void
Logger::init() {
    logging::core::get()->set_exception_handler(logging::make_exception_suppressor());
    logging::add_common_attributes();
    logging::register_simple_filter_factory<logging::trivial::severity_level, char>("Severity");
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    Logger::addConsoleLog();
    Logger::addFileLog("streamkit.log");
}

void Logger::addConsoleLog()
{
    auto sink = boost::make_shared<sinks::synchronous_sink<sinks::text_ostream_backend>>();
    boost::shared_ptr<std::ostream> stream(&std::cout, boost::null_deleter{});
    sink->locked_backend()->add_stream(stream);
    sink->set_formatter(LOG_FORMATTER);
    logging::core::get()->add_sink(sink);
}

void
Logger::addFileLog(const std::string& logFileName) {
    boost::shared_ptr<sinks::text_ostream_backend> backend(
        new sinks::text_ostream_backend());
    backend->add_stream(boost::shared_ptr<std::ostream>(new std::ofstream(logFileName)));
    backend->auto_flush(true);
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> sink_t;
    boost::shared_ptr<sink_t> sink(new sink_t(backend));
    sink->set_formatter(LOG_FORMATTER);
    logging::core::get()->add_sink(sink);
}