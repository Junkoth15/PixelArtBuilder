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
	// 读取文件夹中的文件,返回文件名：图片的键值对
	static map<string,Mat> loadPicsInFolder(string path,cv::ImreadModes mode);
	//读取txt文件中每行键值对
	static map<string, string> loadTXTMap(string path);
	//读取txt文件中的所有行
	static vector<string> loadLinesInTXT(string path);
	//读取图片
	static Mat loadMat(string path,cv::ImreadModes mode);
	static bool ifFilePathExist(string path);
};

