#pragma once
#include"ColorItem.h"
class BuildLine
{
public:
	virtual ~BuildLine() = default;
public:
	//建造一列，需要指定建造的最远index，以提供优化的可能
	virtual void buildLine(const vector<ColorItem>& line,int max_index)=0;
};

