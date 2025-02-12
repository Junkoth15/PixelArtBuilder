#pragma once
#include"ColorItemSet.h"
class ColorItemSetFactory
{
private:
	static map<string, shared_ptr<ColorItemSet>> item_set_map;
private:
	//������ɫ��Ʒ��������Ʒ��Ϊ���򷵻�null
	static shared_ptr<ColorItemSet> createColorItemSet(string color_describe_file_path);
	static string getColorItemSetName(string color_describe_file_path);
public:
	static shared_ptr<const ColorItemSet> getColorItemSet(string item_set_path);
};