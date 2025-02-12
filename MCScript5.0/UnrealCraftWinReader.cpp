#include "UnrealCraftWinReader.h"
#include"UnrealCraftContainReader.h"
#include"UnrealCraftPlayerInfoReader.h"

UnrealCraftWinReader::UnrealCraftWinReader():
	player_info_reader(make_shared<UnrealCraftPlayerInfoReader>()),
	contain_reader(make_shared<UnrealCraftContainReader>())
{
}

shared_ptr<ReadPlayerInfo> UnrealCraftWinReader::setPlayerInfoReader(shared_ptr<ReadPlayerInfo> reader)
{
	auto ori = player_info_reader;
	player_info_reader = reader;
	return ori;
}

shared_ptr<ReadPlayerInfo> UnrealCraftWinReader::getPlayerInfoReader()
{
	return player_info_reader;
}

shared_ptr<ReadContain> UnrealCraftWinReader::setContainReader(shared_ptr<ReadContain> reader)
{
	auto ori = contain_reader;
	contain_reader = reader;
	return ori;
}

shared_ptr<ReadContain> UnrealCraftWinReader::getContainReader()
{
	return contain_reader;
}

bool UnrealCraftWinReader::isLookingAtBlock(const Mat& f3_image)
{
	return player_info_reader->isLookingAtBlock(f3_image);
}

bool UnrealCraftWinReader::getLookingAtBlock(const Mat& f3_image,BlockInfo& block_info)
{
	return player_info_reader->getLookingAtBlock(f3_image,block_info);
}

bool UnrealCraftWinReader::getLookingAtBlockName(const Mat& f3_image, string& blockname)
{
	return player_info_reader->getLookingAtBlockName(f3_image,blockname);
}

bool UnrealCraftWinReader::getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos)
{
	return player_info_reader->getLookingAtBlockPos(f3_image,block_pos);
}

bool UnrealCraftWinReader::ifPosCanRead(const Mat& image)
{
	return player_info_reader->ifPosCanRead(image);
}

bool UnrealCraftWinReader::ifDirectionCanRead(const Mat& image)
{
	return player_info_reader->ifDirectionCanRead(image);
}

bool UnrealCraftWinReader::getPlayerPosition(const Mat& image,PlayerPos& player_pos)
{
	return player_info_reader->getPlayerPosition(image,player_pos);
}

bool UnrealCraftWinReader::getPlayerFacingDirection(const Mat& image, PlayerFacing& player_facing)
{
	return player_info_reader->getPlayerFacingDirection(image,player_facing);
}

void UnrealCraftWinReader::readContain(const Mat& mat, Contain& contain)
{
	contain_reader->readContain(mat, contain);
}
