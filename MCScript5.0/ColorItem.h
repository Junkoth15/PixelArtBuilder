#pragma once
#include<opencv2/opencv.hpp>
#include"NameSpace.h"
class ColorItem
{
public:
	int ID;
	string name;
	Scalar color;
	ColorItem(int ID, string name, Scalar color);
	ColorItem();
};

