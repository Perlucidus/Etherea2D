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
	
	template<typename T>
	Log& operator<<(T const& val);
	Log& operator<<(ILoggable const& val);
private:
	ostringstream ss;
};

template<typename T>
inline Log& Log::operator<<(T const& val)
{
	ss << val;
	return *this;
}
