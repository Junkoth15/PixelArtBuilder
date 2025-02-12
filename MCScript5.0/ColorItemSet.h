#pragma once
#include"ColorItem.h"
class ColorItemSet
{
public:
	vector<ColorItem> item_set;
	string name;
public:
	ColorItem getColorMCItem(Scalar color) const;
};

