#pragma once

#include "Common.hpp"
#include "Renderable.hpp"
#include <map>

using ObjectMap = std::map<string, unique_ptr<Renderable>>;

class GameComponent {
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;
	GameComponent(GameComponent const&) = delete;
	void operator=(GameComponent const&) = delete;

	void Update();
	void Render(Renderer& renderer);
	void Cleanup();

	template<typename Obj>
	Obj& GetObject(ObjectMap::key_type const& key);
	template<typename Obj>
	void AddObject(ObjectMap::key_type const& key, unique_ptr<Obj>&& value);
	void EraseObject(ObjectMap::key_type const& key);
private:
	ObjectMap objects;
};

template<typename Obj>
inline Obj& GameComponent::GetObject(ObjectMap::key_type const& key)
{
	static_assert(std::is_base_of<ObjectMap::mapped_type::element_type, Obj>::value, "Invalid type argument");
	auto it = objects.find(key);
	if (it == objects.end())
		throw std::runtime_error("Key not found");
	return dynamic_cast<T&>(*it->second);
}

template<typename Obj>
inline void GameComponent::AddObject(ObjectMap::key_type const& key, unique_ptr<Obj>&& value)
{
	static_assert(std::is_base_of<ObjectMap::mapped_type::element_type, Obj>::value, "Invalid type argument");
	auto lb = objects.lower_bound(key);
	if (lb != objects.end() && !(objects.key_comp()(key, lb->first)))
		throw std::runtime_error("Key already exists");
	objects.insert(lb, ObjectMap::value_type(key, std::move(value)));
}
