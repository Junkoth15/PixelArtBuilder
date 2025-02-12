#pragma once
#include"UnrealCraftBox.h"
class UnrealCraftShopBox:public UnrealCraftBox
{
public:
	UnrealCraftShopBox();
	virtual int getMaxRow()const;
	//格子坐标的顺序是从上到下，从左到右
	virtual vector<POINT> getAllLatticePOINT()const override;
	virtual shared_ptr<CloneAble> clone()const override;
};

