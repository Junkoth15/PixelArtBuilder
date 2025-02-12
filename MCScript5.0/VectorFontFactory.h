#pragma once
#include"VectorFont.h"
#include"NameSpace.h"
class VectorFontFactory
{
private:
	static map<string, shared_ptr<VectorFont>> font_map;
private:
	//��ȡָ���ļ����µ������ļ�������Fontָ�룬���������������򱨴�
	static shared_ptr<VectorFont> createFont(string font_path);
	static string getFontName(string font_path);
public:
	//��ָ���ļ���ȥѰ��Font�ļ���������Ӧ��Font���������ڸ������򷵻�null
	static shared_ptr<const VectorFont> getFont(string font_path);
};



