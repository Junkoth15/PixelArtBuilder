#pragma once
#include<opencv2/opencv.hpp>
#include"Letter.h"
#include"SearchLetter.h"
class Font:public SearchLetter
{
public:
	using string = std::string;
public:
	string name;
};