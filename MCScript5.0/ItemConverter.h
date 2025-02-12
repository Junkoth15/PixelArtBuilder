#pragma once
#include"NameSpace.h"
#include"MCItemMap.h"
class ItemConverter
{
private:
	map<string,string> convert_map;
	const MCItemMap* item_map;
public:
	ItemConverter(string convert_file_path, string mcitem_map_name);
	//根据名字获取对应的mc物品
	const MCItem& convert(string name)const;
private:
	void loadConvertMap(string convert_file_path);
	void loadMCItemMap(string mcitem_map_name);
};

