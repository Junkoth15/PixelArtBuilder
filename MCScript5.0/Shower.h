#pragma once
#include"NameSpace.h"
#include<sstream>
class Shower
{
public:
	template<typename Key,typename Value>
	static void showMap(map<Key, Value> map);
	template<typename Key, typename Value>
	static string getMapStr(map<Key, Value> map);
};


template<typename Key, typename Value>
inline void Shower::showMap(map<Key, Value> map)
{
	for (const std::pair<Key, Value>& pair : map) {
		std::cout << pair.first << ":" << pair.second << std::endl;
	}
}

template<typename Key, typename Value>
inline string Shower::getMapStr(map<Key, Value> map)
{
	std::stringstream ss;
	for (const std::pair<Key, Value>& pair : map) {
		ss<< pair.first<< ":" << pair.second << std::endl;
	}
	return ss.str();
}
