#include "ItemConverter.h"
#include"FileLoader.h"
#include"MCItemMapFactory.h"

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
	convert_map= FileLoader::loadTXTMap(convert_file_path);
}

void ItemConverter::loadMCItemMap(string mcitem_map_name)
{
	item_map = &MCItemMapFactory::getMCItemMap(mcitem_map_name);
}
