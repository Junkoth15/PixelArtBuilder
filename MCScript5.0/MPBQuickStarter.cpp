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
	string path = key_value.at("ͼƬ·��");
	int begin_line = std::stoi(key_value.at("��ʼ��"));
	int end_line = std::stoi(key_value.at("������"));
	Mat mat = imread(path, cv::ImreadModes::IMREAD_UNCHANGED);
	
	Logger::log("ͼƬ·��:" + path);
	Logger::log("��ʼ��:" + std::to_string(begin_line));
	Logger::log("������" + std::to_string(end_line));

	performer->setWindowSize(1740, 945);
	performer->backGame();
	Sleep(1000);

	TimeCounter tc(TimeCounterMode::SECOND);
	tc.begin();
	builder->buildMapPic(mat, begin_line, end_line);
	Logger::log("��ɺ�ʱ(s):"+std::to_string(tc.end()));
}
