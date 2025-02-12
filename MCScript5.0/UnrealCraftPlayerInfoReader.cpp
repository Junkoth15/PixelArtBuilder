#include "UnrealCraftPlayerInfoReader.h"
#include"VectorFontFactory.h"
#include"StringReader.h"
#include"UnrealCraftPerformerFile.h"
using namespace std;

Scalar UnrealCraftPlayerInfoReader::f3_font_color = Scalar(221, 221, 221);
Rect UnrealCraftPlayerInfoReader::player_pos_rect = Rect(3, 164, 500, 18);
Rect UnrealCraftPlayerInfoReader::player_facing_rect = Rect(3, 218, 600, 18);
Rect UnrealCraftPlayerInfoReader::looking_at_block_name_rect = Rect(1734, 308, 400, 18);//这里的坐标是右上角坐标
Rect UnrealCraftPlayerInfoReader::looking_at_block_pos_rect = Rect(1734, 290, 500, 18);//这里的坐标是右上角坐标

UnrealCraftPlayerInfoReader::UnrealCraftPlayerInfoReader():
	str_reader(make_shared<StringReader>(VectorFontFactory::getFont(UnrealCraftPerformerFile::getFontPath())))
{
}

bool UnrealCraftPlayerInfoReader::isLookingAtBlock(const Mat& f3_image)
{
	//如果没有指向方块，也肯定看不到方块
	if (!isPointingToBlock(f3_image)) {
		return false;
	}

	//若指向了方块，如果看向方块的距离和自身距离超过4.5，则也看不到
	BlockPos block_pos;
	getLookingAtBlockPos(f3_image,block_pos);
	PlayerPos player_pos;
	getPlayerPosition(f3_image, player_pos);
	if (fabs(player_pos.x - block_pos.x) * fabs(player_pos.x - block_pos.x) +
		fabs(player_pos.z - block_pos.z) * fabs(player_pos.z - block_pos.z) <
		4.5 * 4.5) {
		return true;
	}
	return false;
}

bool UnrealCraftPlayerInfoReader::getLookingAtBlock(const Mat& f3_image, BlockInfo& block_info)
{
	bool a = getLookingAtBlockName(f3_image, block_info.block_name);
	bool b = getLookingAtBlockPos(f3_image, block_info.block_pos);
	return a && b;
}

bool UnrealCraftPlayerInfoReader::getLookingAtBlockName(const Mat& f3_image,string& name)
{
	if (isPointingToBlock(f3_image)) {
		string str = readF3Line(f3_image, looking_at_block_name_rect, false);
		//cout << "UnrealCraftPlayerInfoReader::getLookingAtBlockName1:"+str << endl;

		int begin = str.find_first_of(":");
		//错误反馈
		if (begin < 0) {
			return false;
		}
		name.assign(str.begin() + begin + 1, str.end());
		return true;
	}
	return false;
}

bool UnrealCraftPlayerInfoReader::getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos)
{
	if (isPointingToBlock(f3_image)) {
		string str = readF3Line(f3_image, looking_at_block_pos_rect, false);

		//std::cout << "UnrealCraftImageHandler::getLookingAtBlockPos:" << str << std::endl;

		//提取字符串中的数字
		int num_begin, num_end;
		num_begin = str.find_first_of("-0123456789");
		num_end = str.find_first_of(",", num_begin);
		if (num_begin < 0 || num_end < 0) {
			return false;
			/*cout << "getLookingAtBlockPos:" << str << endl;
			test(f3_image);*/
		}

		block_pos.x = atoi(string(str.begin() + num_begin, str.begin() + num_end).c_str());

		num_begin = str.find_first_of("-0123456789", num_end);
		num_end = str.find_first_of(",", num_begin);
		if (num_begin < 0 || num_end < 0) {
			return false;
			/*cout << "getLookingAtBlockPos:" << str << endl;
			test(f3_image);*/
		}

		block_pos.y = atoi(string(str.begin() + num_begin, str.begin() + num_end).c_str());

		num_begin = str.find_first_of("-0123456789", num_end);
		if (num_begin < 0 || num_end < 0) {
			return false;
			/*cout << "getLookingAtBlockPos:" << str << endl;
			test(f3_image);*/
		}
		block_pos.z = atoi(string(str.begin() + num_begin, str.end()).c_str());
		return true;
	}
	return false;
}

bool UnrealCraftPlayerInfoReader::ifPosCanRead(const Mat& image)
{
	//窗口图片大小不为0，读取判断
	Rect rect = player_pos_rect;
	rect.width = 12;
	if (!readF3Line(image, rect).empty()) {
		return true;
	}
	return false;
}

bool UnrealCraftPlayerInfoReader::ifDirectionCanRead(const Mat& image)
{
	//窗口图片大小不为0，读取判断
	Rect rect = player_facing_rect;
	rect.width = 12;
	if (!readF3Line(image, rect).empty()) {
		return true;
	}
	return false;
}

bool UnrealCraftPlayerInfoReader::getPlayerPosition(const Mat& image,PlayerPos& player_pos)
{
	if (!ifPosCanRead(image)) {
		return false;
	}
	//读取字符串
	std::string str = readF3Line(image, player_pos_rect);
	//std::cout << "getPlayerPosition:" + str << std::endl;

	//提取字符串中的数字
	int num_begin, num_end;
	num_begin = str.find_first_of("-0123456789");
	num_end = str.find_first_of(" ", num_begin);
	if (num_begin < 0 || num_end < 0) {
		return false;
	}
	player_pos.x = atof(std::string(str.begin() + num_begin, str.begin() + num_end).c_str());

	num_begin = str.find_first_of("-0123456789", num_end);
	num_end = str.find_first_of(" ", num_begin);
	if (num_begin < 0 || num_end < 0) {
		return false;
	}
	player_pos.y = atof(std::string(str.begin() + num_begin, str.begin() + num_end).c_str());

	num_begin = str.find_first_of("-0123456789", num_end);
	if (num_begin < 0 || num_end < 0) {
		return false;
	}
	player_pos.z = atof(std::string(str.begin() + num_begin, str.end()).c_str());
	return true;
}

bool UnrealCraftPlayerInfoReader::getPlayerFacingDirection(const Mat& image,PlayerFacing& player_facing)
{
	if (!ifDirectionCanRead(image)) {
		return false;
	}
	//读取字符串
	std::string str = readF3Line(image, player_facing_rect);
	//std::cout <<"UnrealCraftImageHandler::getPlayerFacingDirection:" << str << std::endl;

	//获取其中的数字
	int begin, end;
	begin = str.find_first_of("-0123456789");
	end = str.find_first_of(" ", begin);
	if (begin < 0 || end < 0) {
		return false;
	}
	player_facing.x = stof(std::string(str.begin() + begin, str.begin() + end));

	begin = str.find_first_of("-0123456789", end);
	if (begin < 0 || end < 0) {
		return false;
	}
	player_facing.y = stof(std::string(str.begin() + begin, str.end()));
	return true;
}

bool UnrealCraftPlayerInfoReader::isPointingToBlock(const Mat& image)
{
	//判断f3是否开启且3,259位置是否为L，若不是则肯定没指向方块
	Rect rect = looking_at_block_pos_rect;
	rect.width = 12;
	if (!readF3Line(image, rect, false).empty()) {
		return true;
	}
	return false;
}

string UnrealCraftPlayerInfoReader::readF3Line(const Mat& img, Rect rect, bool from_left_top)
{
	//由于可能存在下划线，需要将图片的头两行染黑
	//cv::imshow("UnrealCraftPlayerInfoReader::readF3Line", mat);
	//cv::waitKey();
	if(!from_left_top)
		rect.x -= rect.width-1;
	Mat mat = img(rect).clone();
	mat.row(0).setTo(Scalar(0, 0, 0));
	mat.row(1).setTo(Scalar(0, 0, 0));
	return str_reader->readString(mat, f3_font_color, from_left_top);
}
