#pragma once
#include"VectorFont.h"
#include"NameSpace.h"
class VectorFontFactory
{
private:
	static map<string, shared_ptr<VectorFont>> font_map;
private:
	//读取指定文件夹下的字体文件并返回Font指针，若不能完整创建则报错
	static shared_ptr<VectorFont> createFont(string font_path);
	static string getFontName(string font_path);
public:
	//到指定文件夹去寻找Font文件并创建对应的Font，若不存在该字体则返回null
	static shared_ptr<const VectorFont> getFont(string font_path);
};



