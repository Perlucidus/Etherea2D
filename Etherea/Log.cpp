#include "Log.hpp"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

#ifdef _WIN32
void* Log::hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

Log::Log(LogLevel ll) : level(ll)
{
	ss << ll._to_string() << ": ";
}

Log::~Log()
{
	ss << endl;
#ifdef _WIN32
	if (level == +LogLevel::WARN)
		SetConsoleTextAttribute(hStdout, 14);
	else if (level == +LogLevel::ERR)
		SetConsoleTextAttribute(hStdout, 4);
#endif
	cout << ss.str();
#ifdef _WIN32
	if (level != +LogLevel::INFO)
		SetConsoleTextAttribute(hStdout, 7);
#endif
}

Log& Log::operator<<(ILoggable const& val)
{
	*this << val.toString();
}
