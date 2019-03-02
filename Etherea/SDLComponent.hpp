#pragma once

#include <string>

using std::string;

class SDLComponent {
public:
	SDLComponent() noexcept = default;
	virtual ~SDLComponent() noexcept = default;
protected:
	void setError(bool s);
	string const& getError() const;
private:
	bool success;
	string error;
};
