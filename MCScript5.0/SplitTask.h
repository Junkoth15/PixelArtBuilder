#pragma once
#include"CanBuildMapPic.h"
#include"NameSpace.h"
#include"ColorItemMat.h"
class SplitTask
{
public:
	//根据颜色物品矩阵，计算下一次应该从第几行建到第几行，并返回所需物品图
	virtual int getNextEndRow(const ColorItemMat& color_item_mat,int begin_row, int max_row,
		shared_ptr<const CanBuildMapPic> builder,map<string,int>& need_item_map)=0;
};

