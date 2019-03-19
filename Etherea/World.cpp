#include "World.hpp"
#include "RenderComponent.hpp"
#include "LocationComponent.hpp"
#include "PhysicsComponent.h"
#include "FaceComponent.hpp"
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
		e.render(renderer);
		//DEBUG:
		if (e.HasComponent<LocationComponent>()) {
			Point loc = e.GetComponent<LocationComponent>().getLocation();
			if (e.HasComponent<RenderComponent>()) {
				renderer.SetDrawColor(Color(127, 127, 0, 200));
				Point center = loc + e.GetComponent<RenderComponent>().getRotationCenter();
				renderer.DrawPoint(center);
				float angle = static_cast<float>(e.GetComponent<RenderComponent>().getRenderAngle() * M_PI / 180);
				if (angle > 0)
					renderer.DrawLine(center, center + Point(15 * cosf(angle), 15 * sinf(angle)));
				else
					renderer.DrawLine(center, center + Point(10, 0));
				renderer.SetDrawColor(Color(127, 127, 255, 200));
				if (e.HasComponent<FaceComponent>()) {
					renderer.DrawLine(center, center + Point(Direction(5, 5) * e.GetComponent<FaceComponent>().getFacingDirection()));
				}
			}
			if (e.HasComponent<PhysicsComponent>()) {
				renderer.SetDrawColor(Color(0, 127, 127));
				renderer.DrawRectangle(Rectangle(loc, e.GetComponent<PhysicsComponent>().getHitbox()));
			}
		}
	}
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
			continue;
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
