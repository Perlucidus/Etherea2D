#pragma once

#include "Renderable.hpp"
#include <map>

using ObjectMap = std::map<string, unique_ptr<Renderable>>;

class GameComponent {
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;
	GameComponent(GameComponent const&) = delete;
	void operator=(GameComponent const&) = delete;

	virtual void Init() = 0;

	void Update();
	void Render(Renderer& renderer);
	void Cleanup();

	template<typename RenderableT>
	RenderableT& GetObject(ObjectMap::key_type const& key);
	template<typename RenderableT>
	void AddObject(ObjectMap::key_type const& key, unique_ptr<RenderableT>&& value);
	void EraseObject(ObjectMap::key_type const& key);
private:
	ObjectMap objects;
};

template<typename RenderableT>
inline RenderableT& GameComponent::GetObject(ObjectMap::key_type const& key)
{
	static_assert(std::is_base_of<ObjectMap::mapped_type::element_type, RenderableT>::value, "Invalid type argument");
	auto it = objects.find(key);
	if (it == objects.end())
		throw std::logic_error("Key not found");
	return dynamic_cast<RenderableT&>(*it->second);
}

template<typename RenderableT>
inline void GameComponent::AddObject(ObjectMap::key_type const& key, unique_ptr<RenderableT>&& value)
{
	static_assert(std::is_base_of<ObjectMap::mapped_type::element_type, RenderableT>::value, "Invalid type argument");
	auto lb = objects.lower_bound(key);
	if (lb != objects.end() && !(objects.key_comp()(key, lb->first)))
		throw std::logic_error("Key already exists");
	objects.insert(lb, ObjectMap::value_type(key, std::move(value)));
}
