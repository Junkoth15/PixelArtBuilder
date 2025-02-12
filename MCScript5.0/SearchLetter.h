#pragma once
#include<opencv2/opencv.hpp>
class SearchLetter
{
public:
	using Mat = cv::Mat;
	template<typename Type>
	using vector = std::vector<Type>;
public:
	//Ҫ��ͼƬΪ�Ҷ�ͼ��ͼƬΪ�����ַ���ͼƬ
	virtual bool searchLetter(const Mat& mat,char& ch)const =0;
	//��ȡ�����ַ��Ŀ�ȣ�˳��Ӱ������˳��
	virtual vector<int> getAllLetterWidth()const = 0;
	virtual int getLetterHeight()const = 0;
};

