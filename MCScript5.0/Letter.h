#pragma once
#include<opencv2/opencv.hpp>
/// <summary>
/// 字符类
/// </summary>
class Letter
{
public:
	using Mat = cv::Mat;
public:
	Mat pic;
	char ch;
public:
	//构造函数
	Letter(char ch, const Mat& pic);
};

