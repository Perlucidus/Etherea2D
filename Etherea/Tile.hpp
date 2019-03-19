#pragma once

#include "IGameObject.hpp"
#include "Common.hpp"

using TileId = uint32_t;

class Tile : public IGameObject {
public:
	Tile() = delete;
	Tile(TileId id) : id(id) {}
private:
	TileId id;
};
