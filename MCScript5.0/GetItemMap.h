#pragma once
#include"NameSpace.h"
class GetItemMap
{
public:
	virtual ~GetItemMap() = default;
	//此处的物品图是mc物品图
	virtual void getItemMap(map<string,int> map)=0;
};

