#pragma once
#include"NameSpace.h"
class GetItemMap
{
public:
	virtual ~GetItemMap() = default;
	//�˴�����Ʒͼ��mc��Ʒͼ
	virtual void getItemMap(map<string,int> map)=0;
};

