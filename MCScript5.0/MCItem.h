#pragma once
#include<opencv2/opencv.hpp>
class MCItem
{
public:
	using Mat = cv::Mat;
	using string = std::string;
public:
	//物品图片
	Mat image;
	//物品名字
	string name;
	//堆叠上限
	int stacking_limit;
public:
	MCItem();
	MCItem(const Mat& image, string name, int stacking_limit);
	MCItem(const MCItem& item);
	MCItem& operator=(const MCItem& item);
	bool equal(const MCItem& item)const;
};
bool operator==(const MCItem& item_1, const MCItem& item_2);

