#include "CustomEventData.hpp"

CustomEventData::CustomEventData(const string& name) : name(name) {}
const string CustomEventData::type() const { return name; }

EntityCollisionEventData::EntityCollisionEventData(string const& id1, string const& id2) :
	CustomEventData("EntityCollision"), id1(id1), id2(id2) {}
string EntityCollisionEventData::getId1() const { return id1; }
string EntityCollisionEventData::getId2() const { return id2; }

SplashEventData::SplashEventData() : CustomEventData("Splash") {}
