#pragma once
#include"CanBuildMapPic.h"
#include"ImagePerformer.h"
#include"ItemConverter.h"
#include"UnrealCraftBox.h"
#include"MCItemMap.h"
#include"UnrealCraftItemMapWareGetter.h"
struct UnrealCraftMPBInfo
{
	int board_first_line_x;//画板第一列x
	string item_map_path;//mc物品集路径
	string convert_file_path;//转换文件路径
	string getter_file_path;//获取器文件路径
};

class UnrealCraftMPBPerformer:public CanBuildMapPic
{
protected:
	shared_ptr<ImagePerformer> performer;
	ItemConverter converter;//颜色物品转mc物品
	UnrealCraftBox ender_chest;
	UnrealCraftMPBInfo mpb_info;
	UnrealCraftItemMapWareGetter getter;

public:
	UnrealCraftMPBPerformer(shared_ptr<ImagePerformer> performer,UnrealCraftMPBInfo mpb_info);
	// 通过 CanBuildMapPic 继承，所有函数均附带延迟
	void getItemToHand(const vector<ColorItem>& line,int item_index) override;
	void putBlock() override;
	void move(MoveMode mode) override;
	PlayerStatus getPlayerStatus() override;
	bool testAddItemToPackage(map<string, int> item_map) const override;
	//line从0开始
	void goToLine(int line) override;
	void goToBoard() override;
	//打开背包并设置背包状态为末影箱
	void openPackage() override;
	void closePackage() override;
	void refreshPackage() override;
	void recycleItem() override;
	void getItemMap(map<string, int> map) override;
private:
	//颜色物品转mc物品
	const MCItem& convert(string name)const;
	void arrangePackage(const vector<ColorItem>& line,int index);
	//arrange的子函数，若口袋物品图有该物品则修改物品数量和index
	bool isPocketMapHas(map<string, int>& map, const string& item_name, int& index);
	//arrange的子函数，寻找可用的物品坐标
	POINT findUseAbleMCItemPOINT(const MCItem& item, const vector<bool>& is_used);
	//arrange的子函数，如果item的坐标在口袋中
	void ifMCItemInPocket(map<string, int>& pocket_map,POINT item_point , vector<bool>& is_used, int& pocket_used);
	//arrange的子函数，如果item的坐标不在口袋中
	void ifMCItemNotInPocket(map<string, int>& pocket_map, POINT item_point, vector<bool>& is_used, int& pocket_used);
	//根据所需物品，获取格子编号
	POINT findOneMCItem(const MCItem& item)const;
	vector<POINT> findAllMCItem(const MCItem& item)const;
	POINT getLatticeRelativeMidPos(int x, int y)const;
	Lattice& getLattice(int x, int y);
	const Lattice& getLattice(int x, int y) const;
	//去主城
	void goToSpawn();
	//去生存区
	void goToSurviveArea();
	//飞行
	void fly();
	//解除飞行
	void closeFly();
};

