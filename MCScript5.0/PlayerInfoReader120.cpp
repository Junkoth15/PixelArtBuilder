#include "PlayerInfoReader120.h"
#include"VectorFontFactory.h"
#include"StringReader.h"
#include"UnrealCraftPerformerFile.h"
using namespace std;

Scalar PlayerInfoReader120::f3_font_color = Scalar(221, 221, 221);
Rect PlayerInfoReader120::player_pos_rect = Rect(3, 164, 500, 18);
Rect PlayerInfoReader120::player_facing_rect = Rect(3, 218, 600, 18);
Rect PlayerInfoReader120::block_name_rect = Rect(1734, 308, 400, 18);//这里的坐标是右上角坐标
Rect PlayerInfoReader120::block_pos_rect = Rect(1734, 290, 500, 18);//这里的坐标是右上角坐标

//PlayerInfoReader120::PlayerInfoReader120():
//	_str_reader(make_shared<StringReader>(VectorFontFactory::getFont(UnrealCraftPerformerFile::getFontPath())))
//{
//}



PlayerInfoReader120::PlayerInfoReader120(shared_ptr<const ReadString> _str_reader)
{
	this->_str_reader = _str_reader;
	clearData();
}

bool PlayerInfoReader120::isLookingAtBlock()
{
	switch (_is_looking_at_block_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		//如果没有指向方块，也肯定看不到方块
		if (!isPointingToBlock()) {
			_is_looking_at_block_updated = UpdatedStatus::YES;
			_player_status.is_looking_at_block = false;
			return false;
		}

		//若指向了方块，如果看向方块的距离和自身距离超过4.5，则也看不到
		BlockPos block_pos;
		PlayerPos player_pos;
		//若成功识别
		if (getLookingAtBlockPos(block_pos) && getPlayerPosition(player_pos)) {
			bool result = false;
			if (fabs(player_pos.x - block_pos.x) * fabs(player_pos.x - block_pos.x) +
				fabs(player_pos.z - block_pos.z) * fabs(player_pos.z - block_pos.z) <
				4.5 * 4.5) {
				result = true;
			}
			_is_looking_at_block_updated = UpdatedStatus::YES;
			_player_status.is_looking_at_block = result;
			return result;
		}
		//若识别失败
		else {
			_is_looking_at_block_updated = UpdatedStatus::ERR;
			return false;
		}
		
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		//若数据已更新，则使用更新后的数据
		return _player_status.is_looking_at_block;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}
	return false;
}

bool PlayerInfoReader120::getLookingAtBlock(BlockInfo& block_info)
{
	bool a = getLookingAtBlockName(block_info.block_name);
	bool b = getLookingAtBlockPos(block_info.block_pos);
	return a && b;
}

bool PlayerInfoReader120::getLookingAtBlockName(string& name)
{
	switch (_block_name_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		bool result = false;
		if (isPointingToBlock()) {
			string str = readF3Line(*_img, getBlockNameRect(), false);
			//cout << "PlayerInfoReader120::getLookingAtBlockName1:"+str << endl;

			int begin = str.find_first_of(":");
			//错误反馈
			if (begin >= 0) {
				_player_status.block_info.block_name.assign(str.begin() + begin + 1, str.end());
				result = true;
			}
		}
		if (result) {
			_block_name_updated = UpdatedStatus::YES;
		}
		else {
			_block_name_updated = UpdatedStatus::ERR;
		}
		return getLookingAtBlockName(name);
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		name = _player_status.block_info.block_name;
		return true;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}

	return false;
}

bool PlayerInfoReader120::getLookingAtBlockPos(BlockPos& block_pos)
{
	switch (_block_pos_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		//若未指向方块,则无法读取
		if (!isPointingToBlock()) {
			_block_pos_updated = UpdatedStatus::ERR;
			return getLookingAtBlockPos(block_pos);
		}
		bool result = true;
		string str = readF3Line(*_img, getBlockPosRect(), false);
		int x, y, z;

		//std::cout << "UnrealCraftImageHandler::getLookingAtBlockPos:" << str << std::endl;

		//提取字符串中的数字
		do {
			int num_begin, num_end;
			num_begin = str.find_first_of("-0123456789");
			num_end = str.find_first_of(",", num_begin);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
				/*cout << "getLookingAtBlockPos:" << str << endl;
				test(f3_image);*/
			}
			x = atoi(string(str.begin() + num_begin, str.begin() + num_end).c_str());

			num_begin = str.find_first_of("-0123456789", num_end);
			num_end = str.find_first_of(",", num_begin);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
				/*cout << "getLookingAtBlockPos:" << str << endl;
				test(f3_image);*/
			}
			y = atoi(string(str.begin() + num_begin, str.begin() + num_end).c_str());

			num_begin = str.find_first_of("-0123456789", num_end);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
				/*cout << "getLookingAtBlockPos:" << str << endl;
				test(f3_image);*/
			}
			z = atoi(string(str.begin() + num_begin, str.end()).c_str());
		} while (false);

		if (result) {
			_player_status.block_info.block_pos.x = x;
			_player_status.block_info.block_pos.y = y;
			_player_status.block_info.block_pos.z = z;
			_block_pos_updated = UpdatedStatus::YES;
		}
		else {
			_block_pos_updated = UpdatedStatus::ERR;
		}
		
		return getLookingAtBlockPos(block_pos);
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		block_pos = _player_status.block_info.block_pos;
		return true;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}
	return false;
}

//bool PlayerInfoReader120::ifPosCanRead()
//{
//	switch (_F3_can_read_updated)
//	{
//	case PlayerInfoReader120::UpdatedStatus::NO:
//	{
//		//窗口图片大小不为0，读取判断
//		Rect rect = player_pos_rect;
//		rect.width = 12;
//		if (!readF3Line(*_img, rect).empty()) {
//			_F3_can_read_updated = UpdatedStatus::YES;
//			_player_status.is_F3_can_read = true;
//		}
//		else {
//			_F3_can_read_updated = UpdatedStatus::YES;
//			_player_status.is_F3_can_read = false;
//		}
//		return ifPosCanRead();
//	}break;
//	case PlayerInfoReader120::UpdatedStatus::YES:
//	{
//		return _player_status.is_F3_can_read;
//	}break;
//	case PlayerInfoReader120::UpdatedStatus::ERR:
//	{
//		return false;
//	}break;
//	default:
//		break;
//	}
//	
//	return false;
//}

//bool PlayerInfoReader120::ifDirectionCanRead()
//{
//	switch ()
//	{
//	default:
//		break;
//	}
//	//窗口图片大小不为0，读取判断
//	Rect rect = player_facing_rect;
//	rect.width = 12;
//	if (!readF3Line(image, rect).empty()) {
//		return true;
//	}
//	return false;
//}

bool PlayerInfoReader120::getPlayerPosition(PlayerPos& player_pos)
{
	switch (_player_pos_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		if (!ifF3CanRead()) {
			_player_pos_updated = UpdatedStatus::ERR;
			return getPlayerPosition(player_pos);
		}
		//读取字符串
		std::string str = readF3Line(*_img, getPlayerPosRect());
		//std::cout << "getPlayerPosition:" + str << std::endl;

		double x, y, z;
		bool result = true;
		//提取字符串中的数字
		do {
			int num_begin, num_end;
			num_begin = str.find_first_of("-0123456789");
			num_end = str.find_first_of(" ", num_begin);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
			}
			x = atof(std::string(str.begin() + num_begin, str.begin() + num_end).c_str());

			num_begin = str.find_first_of("-0123456789", num_end);
			num_end = str.find_first_of(" ", num_begin);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
			}
			y = atof(std::string(str.begin() + num_begin, str.begin() + num_end).c_str());

			num_begin = str.find_first_of("-0123456789", num_end);
			if (num_begin < 0 || num_end < 0) {
				result = false;
				break;
			}
			z = atof(std::string(str.begin() + num_begin, str.end()).c_str());
		} while (false);
		if (result) {
			_player_pos_updated = UpdatedStatus::YES;
			_player_status.player_pos.x = x;
			_player_status.player_pos.y = y;
			_player_status.player_pos.z = z;
		}
		else {
			_player_pos_updated = UpdatedStatus::ERR;
		}
		return getPlayerPosition(player_pos);
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		player_pos = _player_status.player_pos;
		return true;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}
	return false;
}

bool PlayerInfoReader120::getPlayerFacing(PlayerFacing& player_facing)
{
	switch (_player_facing_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		if (!ifF3CanRead()) {
			_player_facing_updated = UpdatedStatus::ERR;
			return getPlayerFacing(player_facing);
		}
		//读取字符串
		std::string str = readF3Line(*_img, getPlayerFacingRect());
		//std::cout <<"UnrealCraftImageHandler::getPlayerFacing:" << str << std::endl;

		float x, y;
		bool result = true;
		do {
			//获取其中的数字
			int begin, end;
			begin = str.find_first_of("-0123456789");
			end = str.find_first_of(" ", begin);
			if (begin < 0 || end < 0) {
				result = false;
				break;
			}
			x = stof(std::string(str.begin() + begin, str.begin() + end));

			begin = str.find_first_of("-0123456789", end);
			if (begin < 0 || end < 0) {
				result = false;
				break;
			}
			y = stof(std::string(str.begin() + begin, str.end()));
		} while (false);

		if (result) {
			_player_status.facing_direction.x = x;
			_player_status.facing_direction.y = y;
			_player_facing_updated = UpdatedStatus::YES;
		}
		else {
			_player_facing_updated = UpdatedStatus::ERR;
		}
		return getPlayerFacing(player_facing);

	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		player_facing = _player_status.facing_direction;
		return true;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}
	
	return false;
}

bool PlayerInfoReader120::isPointingToBlock()
{
	switch (_is_pointing_to_block_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		//判断方块信息文字部分是否存在，若不是则肯定没指向方块
		Rect rect = getBlockPosRect();
		rect.width = 12;
		_is_pointing_to_block_updated = UpdatedStatus::YES;
		_is_pointing_to_block = !readF3Line(*_img, rect, false).empty();
		return isPointingToBlock();
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		return _is_pointing_to_block;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}
	
	return false;
}

string PlayerInfoReader120::readF3Line(const Mat& img, Rect rect, bool from_left_top)
{
	//由于可能存在下划线，需要将图片的头两行染黑
	//cv::imshow("PlayerInfoReader120::readF3Line", mat);
	//cv::waitKey();
	if(!from_left_top)
		rect.x -= rect.width-1;
	Mat mat = img(rect).clone();
	mat.row(0).setTo(Scalar(0, 0, 0));
	mat.row(1).setTo(Scalar(0, 0, 0));
	return _str_reader->readString(mat, f3_font_color, from_left_top);
}

Rect PlayerInfoReader120::getPlayerPosRect()
{
	return player_pos_rect;
}

Rect PlayerInfoReader120::getPlayerFacingRect()
{
	return player_facing_rect;
}

Rect PlayerInfoReader120::getBlockNameRect()
{
	return block_name_rect;
}

Rect PlayerInfoReader120::getBlockPosRect()
{
	return block_pos_rect;
}

PlayerStatus PlayerInfoReader120::getAllPlayerInfo()
{
	PlayerStatus result;
	if (ifF3CanRead()) {
		result.is_F3_can_read = true;
		getPlayerPosition(result.player_pos);
		getPlayerFacing(result.facing_direction);
	}
	else {
		result.is_F3_can_read = false;
	}
	if (isLookingAtBlock()) {
		result.is_looking_at_block = true;
		getLookingAtBlock(result.block_info);
	}
	else {
		result.is_looking_at_block = false;
	}
	return result;
}

bool PlayerInfoReader120::ifF3CanRead()
{
	switch (_F3_can_read_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		//窗口图片大小不为0，读取判断
		Rect rect = getPlayerPosRect();
		rect.width = 12;
		_F3_can_read_updated = UpdatedStatus::YES;
		_player_status.is_F3_can_read = !readF3Line(*_img, rect).empty();
		/*if (!readF3Line(*_img, rect).empty()) {
			_F3_can_read_updated = UpdatedStatus::YES;
			_player_status.is_F3_can_read = true;
		}
		else {
			_F3_can_read_updated = UpdatedStatus::YES;
			_player_status.is_F3_can_read = false;
		}*/
		return ifF3CanRead();
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
		return _player_status.is_F3_can_read;
	}break;
	case PlayerInfoReader120::UpdatedStatus::ERR:
	{
		return false;
	}break;
	default:
		break;
	}

	return false;
}


void PlayerInfoReader120::analysisPic(const Mat& img)
{
	clearData();
	_img = &img;
}

void PlayerInfoReader120::clearData()
{
	_img = nullptr;
	_player_pos_updated=UpdatedStatus::NO;
	_player_facing_updated=UpdatedStatus::NO;
	_block_pos_updated=UpdatedStatus::NO;
	_block_name_updated=UpdatedStatus::NO;
	_F3_can_read_updated=UpdatedStatus::NO;
	_is_looking_at_block_updated=UpdatedStatus::NO;
	_is_pointing_to_block_updated = UpdatedStatus::NO;
	_is_pointing_to_block = false;
}
