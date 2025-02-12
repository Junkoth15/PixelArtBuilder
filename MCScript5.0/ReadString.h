#pragma once
#include<opencv2/opencv.hpp>
#include<string>
/// <summary>
/// �������ԭͼ
/// </summary>
class ReadString
{
public:
	using string = std::string;
	using Mat = cv::Mat;
	using Scalar = cv::Scalar;
public:
	virtual ~ReadString() = default;
	//ͼ��Ϊԭͼ��ֻ�����ַ�������ȡ���ո����κ�ֹͣ��ȡ
	virtual string readString(const Mat& img, Scalar font_color, bool from_left_top = true)const =0;
};

