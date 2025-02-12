#pragma once
#include"BuildMapPic.h"
#include"Windows.h"
class UnrealCraftMPBFactory
{
private:
	static string color_item_set_file_path;
	static string unreal_craft_mpb_info_path;
public:
	static shared_ptr<BuildMapPic> getUnrealCraftMPB(HWND window);
};

