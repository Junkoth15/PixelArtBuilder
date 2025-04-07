#include "FileLoader.h"
#include"Tools.h"
#include<fstream>
#include<filesystem>
using namespace std;
using namespace cv;
using namespace Json;
namespace fs = std::filesystem;

map<string, Mat> FileLoader::loadPicsInFolder(string path,ImreadModes mode)
{
	map<string, Mat> result;
	std::string directory = path; // 替换为你的目录路径

	if (!ifFilePathExist(path)) {
		throw FileLoaderOpenException(path);
	}

	// 使用recursive_directory_iterator来遍历目录及其子目录
	for (const auto& entry : fs::recursive_directory_iterator(directory)) {
		if (fs::is_regular_file(entry.status())) {
			string file_path = entry.path().string();
			string file_name = entry.path().filename().string();
			int end = file_name.find_first_of(".");
			file_name = file_name.substr(0, end);
			result[file_name] = imread(file_path, mode);
		}
	}

	return result;
}

Value FileLoader::loadJson(string path)
{
	if (!ifFilePathExist(path)) {
		throw FileLoaderOpenException(path);
	}
	ifstream in(path);
	Value root;
	Reader reader;
	reader.parse(in, root);
	return root;


	/*vector<string> lines = loadLinesInTXT(path);
	map<string, string> result;
	for (auto line : lines) {
		std::istringstream stream(line);
		string key, value;
		stream >> key;
		stream >> value;
		result[key] = value;
	}
	return result;*/
}

vector<string> FileLoader::loadLinesInTXT(string path)
{
	vector<string> result;
	if (!ifFilePathExist(path)) {
		throw FileLoaderOpenException(path);
	}

	ifstream file(path);
	//if (!file.is_open()) {
	//	throw exception(("FileLoader::loadJson:" + path + "文件不存在!\n").c_str());
	//}

	string str;
	while (getline(file,str))
	{
		result.push_back(str);
	}
	file.close();
	return result;
}

map<string, string> FileLoader::loadKstringVstringMapFromJson(string path)
{
	Value v = loadJson(path);
	map<string, string> result;
	auto keys = v.getMemberNames();
	for (const auto& key : keys) {
		result.insert(make_pair<>(key, v[key].asString()));
	}
	return result;
}


Mat FileLoader::loadMat(string path,cv::ImreadModes mode)
{
	if (!ifFilePathExist(path))
		throw FileLoaderOpenException(path);
	return imread(path,mode);
}

bool FileLoader::ifFilePathExist(string path)
{
	return fs::exists(path);
}
