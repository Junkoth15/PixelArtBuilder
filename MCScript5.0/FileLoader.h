#pragma once
#include"FileLoaderOpenException.h"
#include<opencv2/opencv.hpp>
#include<json.h>
class FileLoader
{
public:
	template<typename Value>
	using vector = std::vector<Value>;
	template<typename Key,typename Value>
	using map = std::map<Key, Value>;
	using Mat = cv::Mat;
	using string = std::string;
	using Value = Json::Value;
public:
	// ��ȡ�ļ����е��ļ�,�����ļ�����ͼƬ�ļ�ֵ��
	static map<string,Mat> loadPicsInFolder(string path,cv::ImreadModes mode);
	//��ȡtxt�ļ���ÿ�м�ֵ��
	static Value loadJson(string path);
	//��ȡtxt�ļ��е�������
	static vector<string> loadLinesInTXT(string path);
	//��ȡ����ֵ����string��map
	static map<string, string> loadKstringVstringMapFromJson(string path);
	//��ȡͼƬ
	static Mat loadMat(string path,cv::ImreadModes mode);
	static bool ifFilePathExist(string path);
};

