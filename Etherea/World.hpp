#pragma once

#include "ISerializable.hpp"

class World : public ISerializable
{
public:
	World() = default;
	virtual ~World() = default;
public:
	// Inherited via ISerializable
	virtual void serialize(BinaryWriter &) const override;
	virtual void deserialize(BinaryReader &) override;
};
