#pragma once

#include <exception>

class SDLException : public std::exception {
public:
	char const* what() const noexcept override;
};

class MixException : public SDLException {
public:
	char const* what() const noexcept override;
};
