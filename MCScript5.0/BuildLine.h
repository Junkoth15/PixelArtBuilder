#pragma once
#include"ColorItem.h"
class BuildLine
{
public:
	virtual ~BuildLine() = default;
public:
	//����һ�У���Ҫָ���������Զindex�����ṩ�Ż��Ŀ���
	virtual void buildLine(const vector<ColorItem>& line,int max_index)=0;
};

