#pragma once
#include"NameSpace.h"
class Shower
{
public:
	template<typename Key,typename Value>
	static void showMap(map<Key, Value> map);
};


template<typename Key, typename Value>
inline void Shower::showMap(map<Key, Value> map)
{
	for (std::pair<Key, Value> pair : map) {
		std::cout << pair.first << ":" << pair.second << std::endl;
	}
}