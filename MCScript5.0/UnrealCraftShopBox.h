#pragma once
#include"UnrealCraftBox.h"
class UnrealCraftShopBox:public UnrealCraftBox
{
public:
	UnrealCraftShopBox();
	virtual int getMaxRow()const;
	//���������˳���Ǵ��ϵ��£�������
	virtual vector<POINT> getAllLatticePOINT()const override;
	virtual shared_ptr<CloneAble> clone()const override;
};

