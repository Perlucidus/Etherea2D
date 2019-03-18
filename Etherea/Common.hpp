#pragma once

#include "Log.hpp"
#include "Exception.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_timer.h>
#include <memory>
#include <map>

using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;

const int LOOP_SOUND_FOREVER = -1;

inline SDL_Color Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = SDL_ALPHA_OPAQUE) {
	SDL_Color color;
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
	return color;
}

template<typename T, typename K, typename V>
inline T& GetUniqueValueRef(std::map<K, unique_ptr<V>> const& map, K const& key)
{
	static_assert(std::is_base_of<V, T>::value, "Invalid type argument");
	auto it = map.find(key);
	if (it == map.end())
		throw std::logic_error("Key not found: " + key);
	return dynamic_cast<T&>(*it->second);
}

template<typename T, typename K, typename V>
inline T& AddUniqueValueRef(std::map<K, unique_ptr<V>>& map, K const& key, unique_ptr<T>&& value)
{
	static_assert(std::is_base_of<V, T>::value, "Invalid type argument");
	auto lb = map.lower_bound(key);
	if (lb != map.end() && !(map.key_comp()(key, lb->first)))
		throw std::logic_error("Key already exists: " + key);
	auto it = map.insert(lb, std::map<K, unique_ptr<V>>::value_type(key, std::move(value)));
	return dynamic_cast<T&>(*it->second);
}

template<typename T, typename K, typename V>
inline T& AddUniqueValueRef(std::map<K, unique_ptr<V>>& map, K const& key)
{
	return AddUniqueValueRef(map, key, make_unique<T>());
}
