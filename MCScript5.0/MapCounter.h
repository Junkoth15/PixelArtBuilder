#pragma once
#include"NameSpace.h"
class MapCounter
{
public:
	template<typename Key,typename Value>
	static void addToMap(map<Key, Value>& map,const Key& k, const Value& v);
	template<typename K, typename V>
	static map<K, V> minusMap(const map<K, V>& bigger, const map<K, V>& smaller);
};

template<typename Key, typename Value>
inline void MapCounter::addToMap(map<Key, Value>& map, const Key& k, const Value& v)
{
	if (map.count(k)) map.at(k) += v;
	else map[k] = v;
}

template<typename K, typename V>
inline map<K, V> MapCounter::minusMap(const map<K, V>& bigger, const map<K, V>& smaller)
{
	map<K, V> result = bigger;
	for (std::pair<K,V> p : smaller) {
		if (result.count(p.first)) {
			V& value = result.at(p.first);
			value -= p.second;
			if (value <= 0) result.erase(p.first);
		}
	}
	return result;
}
