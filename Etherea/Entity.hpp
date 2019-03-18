#pragma once

#include "Renderer.hpp"
#include "EntityComponent.hpp"
#include <vector>

class Entity {
public:
	Entity() = delete;
	Entity(Entity const&) = delete;
	void operator=(Entity const&) = delete;
	virtual ~Entity() = default;

	explicit Entity(string const& id) : id(id) {}

	string getId() const { return id; }

	virtual void draw(Renderer & renderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	template<typename ComponentT, typename... TArgs>
	ComponentT& AddComponent(TArgs&&... args);
	template<typename ComponentT>
	ComponentT& GetComponent();
	template<typename ComponentT>
	bool HasComponent() const;
private:
	static size_t GenerateComponentId() {
		static size_t id = 0;
		return id++;
	}
	template<typename ComponentT>
	static size_t GetComponentId();
protected:
	string id;
	std::vector<unique_ptr<EntityComponent>> components;
};

template<typename ComponentT, typename... TArgs>
inline ComponentT & Entity::AddComponent(TArgs&&... args)
{
	if (HasComponent<ComponentT>())
		throw std::logic_error("Component already exists");
	unique_ptr<ComponentT> component = make_unique<ComponentT>(std::forward<TArgs>(args)...);
	size_t id = GetComponentId<ComponentT>();
	components.resize(id + 1);
	components[id] = std::move(component);
	return *component;
}

template<typename ComponentT>
inline ComponentT & Entity::GetComponent()
{
	if (!HasComponent<ComponentT>())
		throw std::logic_error("Component does not exist");
	return static_cast<ComponentT&>(*components[GetComponentId<ComponentT>()]);
}

template<typename ComponentT>
inline bool Entity::HasComponent() const
{
	size_t id = GetComponentId<ComponentT>();
	return id < components.size() && components[id] != nullptr;
}

template<typename ComponentT>
inline size_t Entity::GetComponentId()
{
	static size_t id = GenerateComponentId();
	return id;
}
