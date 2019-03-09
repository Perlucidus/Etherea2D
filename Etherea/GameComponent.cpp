#include "GameComponent.hpp"

void GameComponent::Update()
{
	for (auto&& obj : objects)
		obj.second->update();
}

void GameComponent::Render(Renderer& renderer)
{
	for (auto&& obj : objects)
		obj.second->draw(renderer);
}

void GameComponent::Cleanup()
{
	for (auto&& obj : objects)
		obj.second->clean();
}

void GameComponent::EraseObject(ObjectMap::key_type const& key)
{
	objects.erase(key);
}
