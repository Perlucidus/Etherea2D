#include "World.hpp"

void World::serialize(BinaryWriter & writer) const
{
	writer.write<int>(1);
}

void World::deserialize(BinaryReader & reader)
{
	reader.read<int>();
}
