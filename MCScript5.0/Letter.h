#pragma once
#include<opencv2/opencv.hpp>
/// <summary>
/// �ַ���
/// </summary>
class Letter
{
public:
	using Mat = cv::Mat;
public:
	Mat pic;
	char ch;
public:
	//���캯��
	Letter(char ch, const Mat& pic);
};

