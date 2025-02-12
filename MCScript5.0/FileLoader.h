#pragma once
#include<opencv2/opencv.hpp>
#include"FileLoaderException.h"
class FileLoader
{
public:
	template<typename Value>
	using vector = std::vector<Value>;
	template<typename Key,typename Value>
	using map = std::map<Key, Value>;
	using Mat = cv::Mat;
	using string = std::string;
public:
	// ��ȡ�ļ����е��ļ�,�����ļ�����ͼƬ�ļ�ֵ��
	static map<string,Mat> loadPicsInFolder(string path,cv::ImreadModes mode);
	//��ȡtxt�ļ���ÿ�м�ֵ��
	static map<string, string> loadTXTMap(string path);
	//��ȡtxt�ļ��е�������
	static vector<string> loadLinesInTXT(string path);
	//��ȡͼƬ
	static Mat loadMat(string path,cv::ImreadModes mode);
	static bool ifFilePathExist(string path);
};

