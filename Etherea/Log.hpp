#pragma once

#include "ILoggable.hpp"
#include <sstream>

#define BETTER_ENUMS_NO_CONSTEXPR //Prevents some weird error
#include "Enum.hpp"

#define STDLOG Log(LogLevel::INFO)
#define WRNLOG Log(LogLevel::WARN)
#define ERRLOG Log(LogLevel::ERR)

using std::ostringstream;
using std::string;

BETTER_ENUM(LogLevel, unsigned, INFO, WARN, ERR)

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
#ifdef _WIN32
public:
	static void* hStdout;
#endif
private:
	ostringstream ss;
	LogLevel level;
};

template<typename T>
inline Log& Log::operator<<(T const& val)
{
	ss << val;
	return *this;
}
