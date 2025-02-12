#pragma once
#include<opencv2/opencv.hpp>
#include<string>
/// <summary>
/// 输入的是原图
/// </summary>
class ReadString
{
public:
	using string = std::string;
	using Mat = cv::Mat;
	using Scalar = cv::Scalar;
public:
	virtual ~ReadString() = default;
	//图像为原图，只包含字符串，读取到空格两次后停止读取
	virtual string readString(const Mat& img, Scalar font_color, bool from_left_top = true)const =0;
};

