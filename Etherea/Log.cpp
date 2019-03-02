#include "Log.hpp"
#include <iostream>

using namespace std;

Log::Log(LogLevel ll)
{
	ss << static_cast<int>(ll);
}

Log::~Log()
{
	ss << endl;
	cout << ss.str();
}

Log& Log::operator<<(const char* msg)
{
	ss << msg;
	return *this;
}

Log& Log::operator<<(string const& msg)
{
	ss << msg;
	return *this;
}
