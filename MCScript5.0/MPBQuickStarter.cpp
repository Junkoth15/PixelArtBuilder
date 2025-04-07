#include "MPBQuickStarter.h"
#include"FileLoader.h"
#include"Logger.h"
#include"Tools.h"
using namespace std;
using namespace cv;
string MPBQuickStarter::config_path="./config/MPBQuickStarter_config.json";

MPBQuickStarter::MPBQuickStarter(BuildMapPic* builder, NoImagePerformer* performer):
	builder(builder),performer(performer)
{
}

void MPBQuickStarter::startFromFile()
{

	auto value = FileLoader::loadJson(config_path);
	string path;
	int begin_line, end_line;
	vector<int> parts;
	Mat mat;
	try
	{
		LogTrace("begin");
		path = value["图片路径"].asString();
		begin_line = value["开始列"].asInt();
		end_line = value["结束列"].asInt();
		Json::Value parts_array = value["节选部分"];
		//从json中读入节选部分
		for (int i = 0; i < parts_array.size(); i++) {
			parts.push_back(parts_array[i].asInt());
		}
		//读取图片
		mat = FileLoader::loadMat(path, cv::ImreadModes::IMREAD_UNCHANGED);

		//处理图像大小
		if (mat.rows % 128 != 0 || mat.cols % 128 != 0 || mat.rows == 0 || mat.cols == 0) {
			ThrowException::throwException(__FUNCTION__, "图片尺寸非128倍数");
		}
		//修改为3通道
		if (mat.channels() == 4) {
			cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
		}
		else if (mat.channels() != 3) {
			ThrowException::throwException(__FUNCTION__, "图片通道数错误!channels:" + std::to_string(mat.channels()));
		}

		//若节选部分为空，则直接以整个图片作为输入
		if (!parts.empty()) {
			Mat tmp(parts.size()*128,128,CV_8UC3);
			int width = mat.cols / 128;
			for (int i = 0; i < parts.size();i++) {
				int index = parts[i] - 1;	//转换为从0开始
				Rect src(index % width * 128, index / width * 128, 128, 128);
				Rect des(0, 128 * i, 128, 128);
				mat(src).copyTo(tmp(des));
			}
			mat = tmp;
		}

	}
	catch (const std::exception& e)
	{
		LogError("error");
		throw e;
	}
	stringstream str;
	str << "节选部分:";
	if (parts.empty()) {
		str << "无节选";
	}
	else {
		for (auto i : parts) {
			str << i<<" ";
		}
	}
	LogInfo("图片路径:" + path);
	LogInfo("开始列:" + std::to_string(begin_line));
	LogInfo("结束列" + std::to_string(end_line));
	LogInfo(str.str());

	start(mat, begin_line, end_line);
}

void MPBQuickStarter::start(Mat mat, int begin_line, int end_line)
{
	performer->setWindowSize(1740, 945);
	performer->backGame();
	usleep(1000);

	TimeCounter tc(TimeCounterMode::SECOND);
	tc.begin();
	builder->buildMapPic(mat, begin_line, end_line);
	LogInfo("完成耗时(s):" + std::to_string(tc.end()));
}
