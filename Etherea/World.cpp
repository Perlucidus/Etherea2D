#include "World.hpp"
#include "LocationComponent.hpp"
#include "PhysicsComponent.h"
#include "EventHandler.hpp"

const int World::CHUNK_RATIO = 64;

ChunkId World::GetChunkMapping(Point const & point)
{
	return ChunkId(static_cast<int>(point->x / CHUNK_RATIO), static_cast<int>(point->y / CHUNK_RATIO));
}

void World::initialize()
{
}

void World::update()
{
	for (auto&& entity : entities) {
		Entity& e = *entity.second;
		if (e.HasComponent<LocationComponent>() && e.HasComponent<PhysicsComponent>()) {
			LocationComponent& loc = e.GetComponent<LocationComponent>();
			PhysicsComponent& phy = e.GetComponent<PhysicsComponent>();
			Rectangle old(loc.getLocation(), phy.getHitbox());
			e.update();
			updateLocation(e.getId(), old, Rectangle(loc.getLocation(), phy.getHitbox()));
		}
		else
			e.update();
	}
	registerCollisions();
}

void World::render(Renderer& renderer)
{
	for (auto&& entity : entities) {
		Entity& e = *entity.second;
		e.draw(renderer);
		if (e.HasComponent<LocationComponent>() && e.HasComponent<PhysicsComponent>()) {
			renderer.SetDrawColor(Color(0, 127, 127));
			renderer.DrawRectangle(Rectangle(e.GetComponent<LocationComponent>().getLocation(),
				e.GetComponent<PhysicsComponent>().getHitbox())); //DEBUG
		}
	}
}

void World::clean()
{
	for (auto&& entity : entities)
		entity.second->clean();
	entities.clear();
}

void World::EraseEntity(EntityMap::key_type const& key)
{
	entities.erase(key);
}

void World::updateLocation(string const& id, Rectangle const& old, Rectangle const& current)
{
	for (float x = old.tl->x; x <= old.br->x; x += CHUNK_RATIO)
		for (float y = old.tl->y; y <= old.br->y; y += CHUNK_RATIO)
			chunks[GetChunkMapping(Point(x, y))].erase(id);
	for (float x = current.tl->x; x <= current.br->x; x += CHUNK_RATIO)
		for (float y = current.tl->y; y <= current.br->y; y += CHUNK_RATIO)
			chunks[GetChunkMapping(Point(x, y))].insert(id);
}

void World::registerCollisions()
{
	for (auto&& entity : entities) {
		Entity& e = *entity.second;
		if (!e.HasComponent<LocationComponent>() || !e.HasComponent<PhysicsComponent>())
			return;
		Rectangle hitbox(e.GetComponent<LocationComponent>().getLocation(), e.GetComponent<PhysicsComponent>().getHitbox());
		for (float x = hitbox.tl->x; x <= hitbox.br->x; x += CHUNK_RATIO)
			for (float y = hitbox.tl->y; y <= hitbox.br->y; y += CHUNK_RATIO)
				registerCollisions(e.getId(), hitbox, GetChunkMapping(Point(x, y)));
	}
}

void World::registerCollisions(string const& id, Rectangle const& hitbox, ChunkId const& chunk)
{
	for (string const& id2 : chunks[chunk]) {
		if (id == id2)
			continue;
		Entity& e = GetEntity<Entity>(id2);
		Rectangle hitbox2(e.GetComponent<LocationComponent>().getLocation(), e.GetComponent<PhysicsComponent>().getHitbox());
		if (hitbox.overlaps(hitbox2))
			EventHandler::PushCustomEvent<EntityCollisionEventData>(CustomEvent::ENTITY_COLLISION, id, id2);
	}
}
