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
		path = value["ͼƬ·��"].asString();
		begin_line = value["��ʼ��"].asInt();
		end_line = value["������"].asInt();
		Json::Value parts_array = value["��ѡ����"];
		//��json�ж����ѡ����
		for (int i = 0; i < parts_array.size(); i++) {
			parts.push_back(parts_array[i].asInt());
		}
		//��ȡͼƬ
		mat = FileLoader::loadMat(path, cv::ImreadModes::IMREAD_UNCHANGED);

		//����ͼ���С
		if (mat.rows % 128 != 0 || mat.cols % 128 != 0 || mat.rows == 0 || mat.cols == 0) {
			ThrowException::throwException(__FUNCTION__, "ͼƬ�ߴ��128����");
		}
		//�޸�Ϊ3ͨ��
		if (mat.channels() == 4) {
			cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
		}
		else if (mat.channels() != 3) {
			ThrowException::throwException(__FUNCTION__, "ͼƬͨ��������!channels:" + std::to_string(mat.channels()));
		}

		//����ѡ����Ϊ�գ���ֱ��������ͼƬ��Ϊ����
		if (!parts.empty()) {
			Mat tmp(parts.size()*128,128,CV_8UC3);
			int width = mat.cols / 128;
			for (int i = 0; i < parts.size();i++) {
				int index = parts[i] - 1;	//ת��Ϊ��0��ʼ
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
	str << "��ѡ����:";
	if (parts.empty()) {
		str << "�޽�ѡ";
	}
	else {
		for (auto i : parts) {
			str << i<<" ";
		}
	}
	LogInfo("ͼƬ·��:" + path);
	LogInfo("��ʼ��:" + std::to_string(begin_line));
	LogInfo("������" + std::to_string(end_line));
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
	LogInfo("��ɺ�ʱ(s):" + std::to_string(tc.end()));
}
