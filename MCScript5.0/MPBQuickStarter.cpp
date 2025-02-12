#include "MPBQuickStarter.h"
#include"FileLoader.h"
#include"Logger.h"
#include"Tools.h"
string MPBQuickStarter::config_path="./config/MPBQuickStarter_config.txt";

MPBQuickStarter::MPBQuickStarter(BuildMapPic* builder, NoImagePerformer* performer):
	builder(builder),performer(performer)
{
}

void MPBQuickStarter::start()
{

	map<string,string> key_value= FileLoader::loadTXTMap(config_path);
	string path = key_value.at("图片路径");
	int begin_line = std::stoi(key_value.at("开始列"));
	int end_line = std::stoi(key_value.at("结束列"));
	Mat mat = imread(path, cv::ImreadModes::IMREAD_UNCHANGED);
	
	Logger::log("图片路径:" + path);
	Logger::log("开始列:" + std::to_string(begin_line));
	Logger::log("结束列" + std::to_string(end_line));

	performer->setWindowSize(1740, 945);
	performer->backGame();
	Sleep(1000);

	TimeCounter tc(TimeCounterMode::SECOND);
	tc.begin();
	builder->buildMapPic(mat, begin_line, end_line);
	Logger::log("完成耗时(s):"+std::to_string(tc.end()));
}
