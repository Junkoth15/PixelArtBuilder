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

//测试注释

HWND window;
string window_name;
shared_ptr<UnrealCraftPerformer> performer{};
string folder = "C:/Users/Junko/Desktop/images/测试图集";
string server_name = "UnrealCraft虚幻世界";
//string server_name = "失落世界";

TimeCounter tc(TimeCounterMode::MILISECOND);

int main()
{
	SetProcessDPIAware();
	cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	try
	{
	//UnrealCraft虚幻世界
	//失落世界
		if (searchWindow(server_name, window, window_name)) {
			performer = make_shared<UnrealCraftPerformer>(window);
			cout << window_name << endl;
		}
		else {
			cout << "未找到!" << endl;
		}
		char ch;
		while (true)
		{
			if (!_kbhit()) {
				continue;
			}
			ch = _getch();
			if (ch == '-') {

				/*while (true) {
					CImage cimg;
					getWindowPic(window, cimg, 0, 0, 1740, 945, 0, 0);
					Mat image = Cimage2Mat(cimg);
					cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
					imshow("", image);
					saveMat(folder + "/index2.png", image);
					waitKey(0);
					return 0;
				}*/
				performer->setWindowSize(1740, 945);
				Sleep(500);
				performer->backGame();
				Sleep(500);
				Mat img;
				tc.begin();
				for (int i = 0; i < 1000000; i++) {
					performer->getWindowPic(img);
					performer->analysisPic(img);

					PlayerStatus p;
					if (performer->ifF3CanRead()) {
						p = performer->getAllPlayerInfo();
						cout << p.to_string() << endl;
					}
					/*BlockInfo block;
					if (performer->getLookingAtBlock(block)) {
						cout << block.to_string() << endl;
					}*/
					usleep(100);
				}
				cout << tc.end();
				return 0;

				while (true) {
					performer->getWindowPic(img);
					performer->analysisPic(img);
					PlayerPos pos;
					performer->getPlayerPosition(pos);
					cout << pos.to_string() << endl;
					Sleep(100);
				}			
				imwrite(folder+"/F3_无index.png", img);
				
				/*performer->backGame();
				while (true) {
					CImage img;
					performer->getWindowPic(img);
					PlayerStatus s = performer->getAllPlayerInfo(img);
					if (s.is_looking_at_block) {
						performer->putBlock(false);
					}
					usleep(30);
				}*/
			}
			if (ch =='.') {
				MCScript script(performer.get());
				script.shouCai();
				//setClipbar("/pw 测试一下");
			}

			if (ch == ';') {
				cout << "测试" << endl;
				cout<<(int)ASCIIKeyCode2KeyBoardCode(ASCIIKeyCode::CTRL)<<endl;


				/*performer->backGame();
				performer->guaji(10000);*/

			}
			if (ch == ']') {
				performer->setWindowSize(1740, 945);
				Sleep(3000);
				shared_ptr<BuildMapPic> builder = UnrealCraftMPBFactory::getUnrealCraftMPB(window);
				MPBQuickStarter starter(builder.get(), performer.get());
				starter.start();
			}
			if (ch == '[') {
				performer->setWindowSize(1740, 945);
				Mat img;
				performer->backGame();
				Sleep(1000);
				performer->getWindowPic(img);
				saveMat(folder + "/有index2.png",img);
			}
			Sleep(1);
		}

	}
	catch (const std::exception& e)
	{
		LogError(e.what());
		return 0;
	}
}

/*performer->backGame();
Sleep(1000);
UnrealCraftMPBInfo info;
info.board_name = "Junko";
info.board_line_name = "Junko.ss";
info.board_first_line_x = 9648;
info.item_map_path = "./src/MCItemSet/虚幻世界物品集";
info.convert_file_path = "./config/item_convert.txt";
UnrealCraftMPBPerformer mpb(performer, info);
mpb.openPackage();
mpb.refreshPackage();
mpb.closePackage();

vector<ColorItem> vec;
vec.push_back(ColorItem(0, "白色粉", Scalar()));
mpb.getItemToHand(vec, 0);*/
