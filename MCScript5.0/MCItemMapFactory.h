#pragma once
#include"MCItemMap.h"
#include<memory>
class MCItemMapFactory
{
public:
	template<typename Key, typename Value>
	using map = std::map<Key, Value>;  // 使用 using 定义模板类的别名
	using string = std::string;
public:
	static const MCItemMap& getMCItemMap(string item_set_path);

private:
	static map<string, MCItemMap> item_map_map;
private:
	//创建物品集，若创建的物品集为空则返回null
	static MCItemMap createMCItemMap(string item_set_path);
	static string getMCItemMapName(string item_set_path);
};

