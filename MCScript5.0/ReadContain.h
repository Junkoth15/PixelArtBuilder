#pragma once
#include"Contain.h"
class ReadContain
{
public:
	using Mat = cv::Mat;
public:
	virtual void readContain(const Mat& mat,Contain& contain) = 0;
};

