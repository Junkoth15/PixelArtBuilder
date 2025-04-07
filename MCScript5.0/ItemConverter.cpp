#include "ItemConverter.h"
#include"FileLoader.h"
#include"MCItemMapFactory.h"
#include"Tools.h"

ItemConverter::ItemConverter(string convert_file_path, string mcitem_map_name)
{
	loadConvertMap(convert_file_path);
	loadMCItemMap(mcitem_map_name);
}

const MCItem& ItemConverter::convert(string name)const
{
	auto& map = item_map->item_map;
	return map.at(convert_map.at(name));
}

void ItemConverter::loadConvertMap(string convert_file_path)
{
	Json::Value item= FileLoader::loadJson(convert_file_path);
	try
	{
		LogTrace("begin");
		for (int i = 0; i < item.size(); i++) {
			convert_map.insert(std::make_pair(
				item[i]["颜色物品"].asString(),
				item[i]["转换物品"].asString()
			));
		}
	}
	catch (const std::exception& e)
	{
		LogError("error");
		throw e;
	}

	//Json::Value::Members keys = item.getMemberNames();
	//for (int k = 0; k < keys.size(); ++k)
	//{
	//	convert_map.insert(std::make_pair<>(keys.at(k),item[keys[k]].asString()));
	//	//cout << keys.at(k) << ":" << item[keys[k]] << ", ";
	//}
}

void ItemConverter::loadMCItemMap(string mcitem_map_name)
{
	item_map = &MCItemMapFactory::getMCItemMap(mcitem_map_name);
}
