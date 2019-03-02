#pragma once

#include <string>

class ILoggable {
public:
	virtual ~ILoggable() = default;

	virtual std::string const& toString() const = 0;
};
