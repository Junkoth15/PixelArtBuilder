#pragma once
#include"CanBuildMapPic.h"
#include"NameSpace.h"
#include"ColorItemMat.h"
class SplitTask
{
public:
	//������ɫ��Ʒ���󣬼�����һ��Ӧ�ôӵڼ��н����ڼ��У�������������Ʒͼ
	virtual int getNextEndRow(const ColorItemMat& color_item_mat,int begin_row, int max_row,
		shared_ptr<const CanBuildMapPic> builder,map<string,int>& need_item_map)=0;
};

