#pragma once

#include "GameComponent.hpp"
#include "Entity.hpp"
#include "Geometry.hpp"
#include <map>
#include <unordered_set>

using ChunkId = std::pair<int, int>;
using ChunkMap = std::map<ChunkId, std::unordered_set<string>>;
using EntityMap = std::map<string, unique_ptr<Entity>>;

class World : public GameComponent {
public:
	World() = default;

	static ChunkId GetChunkMapping(Point const& point);

	// Inherited via GameComponent
	virtual void initialize() override;
	virtual void update() override;
	virtual void render(Renderer& renderer) override;
	virtual void clean() override;

	template<typename EntityT>
	EntityT& GetEntity(EntityMap::key_type const& key);
	template<typename EntityT, typename ...TArgs>
	EntityT& AddEntity(TArgs ...args);
	void EraseEntity(EntityMap::key_type const& key);
private:
	void updateLocation(string const& id, Rectangle const& old, Rectangle const& current);
	void registerCollisions();
	void registerCollisions(string const& id, Rectangle const& hitbox, ChunkId const& chunk);
private:
	static const int CHUNK_RATIO;

	ChunkMap chunks;
	EntityMap entities;
};

template<typename EntityT>
inline EntityT& World::GetEntity(EntityMap::key_type const & key)
{
	return GetUniqueValueRef<EntityT>(entities, key);
}

template<typename EntityT, typename ...TArgs>
inline EntityT & World::AddEntity(TArgs ...args)
{
	unique_ptr<EntityT> entity = make_unique<EntityT>(args...);
	return AddUniqueValueRef<EntityT>(entities, entity->getId(), std::move(entity));
}
