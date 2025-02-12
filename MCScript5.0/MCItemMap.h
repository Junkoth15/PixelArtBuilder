#pragma once
#include"MCItem.h"
class MCItemMap
{
public:
	template<typename Key,typename Value>
	using map = std::map<Key,Value>;
	using string = std::string;
public:
	map<string, MCItem> item_map;
	string name;
};

