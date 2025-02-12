#include <iostream>
#include<opencv2/opencv.hpp>
#include<conio.h>
#include <opencv2/core/utils/logger.hpp>
#include"Tools.h"
#include"NameSpace.h"
using namespace std;
using namespace cv;
using namespace imageHandle;
#include"UnrealCraftPerformer.h"
#include"MCScript.h"

#include"UnrealCraftMPBFactory.h"
#include"MPBQuickStarter.h"
#include"UnrealCraftBox.h"

#pragma execution_character_set("gbk") 

//����ע��



HWND window;
string window_name;
shared_ptr<UnrealCraftPerformer> performer{};
string folder = "C:/Users/Junko/Desktop/ͼ��/";
TimeCounter tc(TimeCounterMode::MILISECOND);

int main()
{
	SetProcessDPIAware();
	try
	{
	//UnrealCraft�������
	//ʧ������
		cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
		if (searchWindow("UnrealCraft�������", window, window_name)) {
			performer = make_shared<UnrealCraftPerformer>(window);
			cout << window_name << endl;
		}
		else {
			cout << "δ�ҵ�!" << endl;
		}
		char ch;
		while (true)
		{
			if (!_kbhit()) {
				continue;
			}
			ch = _getch();
			if (ch == '-') {
				performer->setWindowSize(1740, 945);
				performer->backGame();
				while (true) {
					CImage img;
					performer->getWindowPic(img);
					PlayerStatus s = performer->getAllPlayerInfo(img);
					if (s.is_looking_at_block) {
						performer->putBlock(false);
					}
					usleep(30);
				}
			}
			if (ch =='.') {
				MCScript script(performer.get());
				script.shouCai();
				//setClipbar("/pw ����һ��");
			}

			if (ch == ';') {
				performer->backGame();
				performer->guaji(10000);

			}
			if (ch == ']') {
				/*string path = "C:/Users/Junko/Desktop/images/images/��������1_1_��ʯ_ʯӢ_ɰ��_���_����.png";
				int begin_line = 27;
				int end_line = 128;

				cout << "����·��:" << path << endl;
				cout << "��ʼ��:" << begin_line << endl;
				cout << "������:" << end_line << endl;
				performer->setWindowSize(1740, 945);
				Mat mat = imread(path, cv::ImreadModes::IMREAD_UNCHANGED);*/
				performer->setWindowSize(1740, 945);
				Sleep(10000);
				shared_ptr<BuildMapPic> builder = UnrealCraftMPBFactory::getUnrealCraftMPB(window);
				MPBQuickStarter starter(builder.get(), performer.get());
				starter.start();
			}
			if (ch == '[') {
				performer->setWindowSize(1740, 945);
				CImage img;
				performer->backGame();
				Sleep(1000);
				performer->getWindowPic(img);
				//imwrite(folder + "ȥ����.png", Cimage2Mat(img));
				UnrealCraftBox box(BoxType::BIG);
				performer->readContain(img, box);
				cout << box.getAllLatticeInfo();
				/*performer->readPackage(img);
				cout << performer->getPackageInfo();*/


				/*Mat package = imread("C:/Users/Junko/Desktop/��ľ��_����.png",cv::ImreadModes::IMREAD_UNCHANGED);
				Mat box = imread("C:/Users/Junko/Desktop/��ľ��_����.png", cv::ImreadModes::IMREAD_UNCHANGED);
				for (int y = 0; y < package.rows; y++) {
					for (int x = 0; x < package.cols; x++) {
						if (package.at<Vec4b>(y, x)[3] != 0) {
							if (getColor(package, y, x) != getColor(box, y, x)) {
								cout << y << " " << x << endl;
							}
						}
					}
				}*/


			}
			Sleep(1);
		}

	}
	catch (const std::exception& e)
	{
		Logger::log(e.what());
		return 0;
	}
}

/*performer->backGame();
Sleep(1000);
UnrealCraftMPBInfo info;
info.board_name = "Junko";
info.board_line_name = "Junko.ss";
info.board_first_line_x = 9648;
info.item_map_path = "./src/MCItemSet/���������Ʒ��";
info.convert_file_path = "./config/item_convert.txt";
UnrealCraftMPBPerformer mpb(performer, info);
mpb.openPackage();
mpb.refreshPackage();
mpb.closePackage();

vector<ColorItem> vec;
vec.push_back(ColorItem(0, "��ɫ��", Scalar()));
mpb.getItemToHand(vec, 0);*/
