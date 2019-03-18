#pragma once

#define BETTER_ENUMS_NO_CONSTEXPR //Prevents some weird error
#include "Enum.hpp"

#include <string>
#include <cstddef>

using std::string;

BETTER_ENUM(CustomEvent, int32_t, SPLASH, ENTITY_COLLISION)

class CustomEventData
{
public:
	CustomEventData(const string& name);
	virtual ~CustomEventData() = default;
	const string type() const;
private:
	const string name;
};

class SplashEventData : public CustomEventData { public:	SplashEventData(); };

class CollisionEventData : public CustomEventData {};
class EntityCollisionEventData : public CustomEventData
{
public:
	EntityCollisionEventData(string const& id1, string const& id2);

	string getId1() const;
	string getId2() const;
private:
	string id1, id2;
};
