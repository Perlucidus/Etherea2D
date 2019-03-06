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

Log& Log::operator<<(ILoggable const& val)
{
	*this << val.toString();
}
