#include"UnrealCraftPlayerInfoReader.h"
#include"StringReader.h"
#include"VectorFontFactory.h"
#include"UnrealCraftPerformerFile.h"
#include"Tools.h"

Rect UnrealCraftPlayerInfoReader::index_pool_rect=Rect(1734,308,500,18);
Rect UnrealCraftPlayerInfoReader::block_name_rect_up=Rect(1734,416,500,18);
Rect UnrealCraftPlayerInfoReader::block_pos_rect_up=Rect(1734,398,500,18);
Rect UnrealCraftPlayerInfoReader::block_name_rect_down=Rect(1734,452,500,18);
Rect UnrealCraftPlayerInfoReader::block_pos_rect_down=Rect(1734,434,500,18);

UnrealCraftPlayerInfoReader::UnrealCraftPlayerInfoReader():
	PlayerInfoReader120(nullptr)
{
	clearData();
	_str_reader = make_shared<StringReader>(
		VectorFontFactory::getFont(UnrealCraftPerformerFile::getFontPath())
	);
}

bool UnrealCraftPlayerInfoReader::judgeOffset()
{
	switch (_offset_updated)
	{
	case PlayerInfoReader120::UpdatedStatus::NO:
	{
		//判断方块信息文字部分是否存在，若不是则肯定没指向方块
		Rect rect = block_pos_rect_up;
		int offset = 0;
		bool find = false;
		//最多有两个附加行
		for (int i = 0; i < 3; i++) {
			string str = readF3Line(*_img, rect, false);
			if (str.find("Targeted Block") != string::npos) {
				find = true;
				break;
			}
			rect.y += 18;
			offset += 18;
		}
		if (find) {
			_offset_updated = UpdatedStatus::YES;
			_offset = offset;
		}
		else {
			_offset_updated = UpdatedStatus::ERR;
		}
		return judgeOffset();
	}break;
	case PlayerInfoReader120::UpdatedStatus::YES:
	{
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

Rect UnrealCraftPlayerInfoReader::getBlockNameRect()
{
	if (judgeOffset()) {
		Rect result = block_name_rect_up;
		result.y += _offset;
		return result;
	}
	else {
		ThrowException::throwException(__FUNCTION__, "未找到name位置");
	}
}

Rect UnrealCraftPlayerInfoReader::getBlockPosRect()
{
	if (judgeOffset()) {
		Rect result = block_pos_rect_up;
		result.y += _offset;
		return result;
	}
	else {
		ThrowException::throwException(__FUNCTION__, "未找到pos位置");
	}
}

void UnrealCraftPlayerInfoReader::clearData()
{
	_offset_updated = UpdatedStatus::NO;
	_offset = 0;
	PlayerInfoReader120::clearData();
}

bool UnrealCraftPlayerInfoReader::isPointingToBlock()
{
	try
	{
		//若无异常，则可以正常判断
		getBlockPosRect();
		return PlayerInfoReader120::isPointingToBlock();
	}
	catch (const std::exception& e)
	{
		//否则无法判断，肯定是没有指向方块
		return false;
	}
}
