#include "MCItemMapFactory.h"
#include"FileLoader.h"
using namespace std;

map<string, MCItemMap> MCItemMapFactory::item_map_map;

MCItemMap MCItemMapFactory::createMCItemMap(string item_set_path)
{
    MCItemMap result;
    result.name =getMCItemMapName(item_set_path);
    //方块名和方块图的键值对
    auto map = FileLoader::loadPicsInFolder(item_set_path,cv::IMREAD_UNCHANGED);
    if (map.empty()) {
        throw exception(("MCItemMapFactory::createMCItemMap:" + item_set_path + "加载失败!\n").c_str());
    }
    for (auto pair : map) {
        result.item_map[pair.first] = MCItem(pair.second, pair.first, 64);
    }
    return result;
}

string MCItemMapFactory::getMCItemMapName(string item_set_path)
{
    int begin = item_set_path.find_last_of('/')+1;
    return string(item_set_path.begin()+begin,item_set_path.end());
}

const MCItemMap& MCItemMapFactory::getMCItemMap(string item_set_path)
{
    string item_map_name = getMCItemMapName(item_set_path);
    auto iter=item_map_map.find(item_map_name);
    if (iter != item_map_map.end()) {
        return iter->second;
    }
    else
    {
        //若创建失败，create函数会抛出异常
        item_map_map[item_map_name] = createMCItemMap(item_set_path);
        return item_map_map[item_map_name];
    }
}
