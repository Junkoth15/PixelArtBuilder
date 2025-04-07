#include "ColorItemSetFactory.h"
#include"FileLoader.h"

map<string, shared_ptr<ColorItemSet>> ColorItemSetFactory::item_set_map;

shared_ptr<ColorItemSet> ColorItemSetFactory::createColorItemSet(string color_describe_file_path)
{
	shared_ptr<ColorItemSet> result = make_shared<ColorItemSet>();
	result->name = getColorItemSetName(color_describe_file_path);

	//Json::Value json_root = FileLoader::loadJson(color_describe_file_path);
	auto lines=FileLoader::loadLinesInTXT(color_describe_file_path);
	for (auto line : lines) {
		std::istringstream stream(line);
		int ID, B, G, R;
		string name;
		stream >> ID;
		stream >> name;
		stream >> B;
		stream >> G;
		stream >> R;
		result->item_set.emplace_back(ColorItem(ID, name, Scalar(B, G, R)));
	}
	return result;
}

string ColorItemSetFactory::getColorItemSetName(string color_describe_file_path)
{
	int begin = color_describe_file_path.find_last_of('/')+1;
	int end = color_describe_file_path.find_last_of('.');
	return string(color_describe_file_path.begin()+begin,color_describe_file_path.begin()+end);
}

shared_ptr<const ColorItemSet> ColorItemSetFactory::getColorItemSet(string item_set_path)
{
	string color_item_set_name = getColorItemSetName(item_set_path);
	auto iter = item_set_map.find(color_item_set_name);
	if (iter != item_set_map.end()) {
		return iter->second;
	}
	else {
		shared_ptr<ColorItemSet> new_item_set = createColorItemSet(item_set_path);
		item_set_map[color_item_set_name] = new_item_set;
		return item_set_map[color_item_set_name];
	}
}
