#pragma once

#include "ILoggable.hpp"
#include <sstream>

#define STDLOG Log(LogLevel::STANDARD)
#define WRNLOG Log(LogLevel::WARNING)
#define ERRLOG Log(LogLevel::ERROR)

using std::ostringstream;
using std::string;

enum class LogLevel {
	STANDARD,
	WARNING,
	ERROR
};

class Log {
public:
	Log() = delete;
	Log(Log const&) = delete;
	void operator=(Log&) = delete;

	Log(LogLevel);
	virtual ~Log();
	
	Log& operator<<(const char*);
	Log& operator<<(string const& msg);
private:
	ostringstream ss;
};
