#pragma once

#include "EntityComponent.hpp"
#include "Geometry.hpp"

class LocationComponent : public EntityComponent {
public:
	LocationComponent(Point const& location) : location(location) {}

	Point getLocation() const { return location; }
	void setLocation(Point const& loc) { location = loc; }
private:
	Point location;
};
