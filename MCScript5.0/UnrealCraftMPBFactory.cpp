#include "UnrealCraftMPBFactory.h"
#include"UnrealCraftPerformer.h"
#include"UnrealCraftMPBPerformer.h"
#include"TaskSpliter.h"
#include"LineBuilder.h"
#include"MapBuilder.h"
#include"UnrealCraftPerformerFile.h"
#include"FileLoader.h"
string UnrealCraftMPBFactory::color_item_set_file_path= "./config/虚幻世界/虚幻世界颜色物品集.txt";
string UnrealCraftMPBFactory::unreal_craft_mpb_info_path= "./config/虚幻世界/UnrealCraftMPBConfig.txt";

static UnrealCraftMPBInfo loadMPBInfo(string path);

shared_ptr<BuildMapPic> UnrealCraftMPBFactory::getUnrealCraftMPB(HWND window)
{
	shared_ptr<UnrealCraftPerformer> performer = make_shared<UnrealCraftPerformer>(window);
	shared_ptr<CanBuildMapPic> builder
		= make_shared<UnrealCraftMPBPerformer>(performer,loadMPBInfo(unreal_craft_mpb_info_path));
	shared_ptr<SplitTask> task_spliter = make_shared<TaskSpliter>();
	shared_ptr<BuildLine> line_builder = make_shared<LineBuilder>(builder);
	shared_ptr<MapBuilder> build
		= make_shared<MapBuilder>(builder, line_builder, task_spliter,color_item_set_file_path);
	return build;
}


static UnrealCraftMPBInfo loadMPBInfo(string path) {
	auto key_value = FileLoader::loadTXTMap(path);
	UnrealCraftMPBInfo result;
	result.board_first_line_x = std::stoi(key_value.at("画板第一列x"));
	result.item_map_path = UnrealCraftPerformerFile::getMCItemSetPath();
	result.convert_file_path = key_value.at("转换文件路径");
	result.getter_file_path = key_value.at("Getter文件路径");
	return result;
}