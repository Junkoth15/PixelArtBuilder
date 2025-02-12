#pragma once
#include"SplitTask.h"
#include"ColorItemMat.h"
class TaskSpliter:public SplitTask
{
public:
	// 通过 SplitTask 继承，row从0开始
	int getNextEndRow(const ColorItemMat& mat, int begin_row, int max_row, 
		shared_ptr<const CanBuildMapPic> builder,map<string,int>& needed_item_map) override;
protected:
	//将一行的物品添加到物品图中，行从0开始
	void addRowToItemMap(const ColorItemMat& mat,int row, map<string, int>& item_map);
	//将一行的物品从颜色物品图中移除，行从0开始
	void eraseRowFromItemMap(const ColorItemMat& mat,int row, map<string, int>& item_map);
	//尝试将颜色物品图添加到背包中
	bool testAddToPackage(shared_ptr<const CanBuildMapPic> builder,const map<string, int>& item_map);
	//根据一种材料的理想数量计算所需的真实数量
	int countActualNum(int ori_num);
	//将理想数量图转换为实际数量图
	map<string, int> idealMapToActualMap(const map<string, int>& item_map);
};

