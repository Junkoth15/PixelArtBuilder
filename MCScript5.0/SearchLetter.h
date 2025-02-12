#pragma once
#include<opencv2/opencv.hpp>
class SearchLetter
{
public:
	using Mat = cv::Mat;
	template<typename Type>
	using vector = std::vector<Type>;
public:
	//要求图片为灰度图，图片为单个字符的图片
	virtual bool searchLetter(const Mat& mat,char& ch)const =0;
	//获取所有字符的宽度，顺序影响搜索顺序
	virtual vector<int> getAllLetterWidth()const = 0;
	virtual int getLetterHeight()const = 0;
};

