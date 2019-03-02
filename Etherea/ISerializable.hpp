#pragma once

#include "BinaryIO.hpp"

class ISerializable {
public:
	virtual ~ISerializable() = default;

	virtual void serialize(BinaryWriter&) const = 0;
	virtual void deserialize(BinaryReader&) = 0;
};
