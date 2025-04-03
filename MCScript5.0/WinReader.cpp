//#include"WinReader.h"
//#include"UnrealCraftContainReader.h"
//#include"PlayerInfoReader120.h"
//
//WinReader::WinReader(
//	shared_ptr<ReadPlayerInfo> player_info_reader,
//	shared_ptr<ReadContain> contain_reader
//):
//	player_info_reader(player_info_reader),
//	contain_reader(contain_reader)
//{
//}
//
//shared_ptr<ReadPlayerInfo> WinReader::setPlayerInfoReader(shared_ptr<ReadPlayerInfo> reader)
//{
//	decltype(player_info_reader) ori = player_info_reader;
//	player_info_reader = reader;
//	return ori;
//}
//
//shared_ptr<ReadPlayerInfo> WinReader::getPlayerInfoReader()
//{
//	return player_info_reader;
//}
//
//shared_ptr<ReadContain> WinReader::setContainReader(shared_ptr<ReadContain> reader)
//{
//	auto ori = contain_reader;
//	contain_reader = reader;
//	return ori;
//}
//
//shared_ptr<ReadContain> WinReader::getContainReader()
//{
//	return contain_reader;
//}
//
//bool WinReader::isLookingAtBlock(const Mat& f3_image)
//{
//	return player_info_reader->isLookingAtBlock(f3_image);
//}
//
//bool WinReader::getLookingAtBlock(const Mat& f3_image,BlockInfo& block_info)
//{
//	return player_info_reader->getLookingAtBlock(f3_image,block_info);
//}
//
//bool WinReader::getLookingAtBlockName(const Mat& f3_image, string& blockname)
//{
//	return player_info_reader->getLookingAtBlockName(f3_image,blockname);
//}
//
//bool WinReader::getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos)
//{
//	return player_info_reader->getLookingAtBlockPos(f3_image,block_pos);
//}
//
//bool WinReader::ifPosCanRead(const Mat& image)
//{
//	return player_info_reader->ifPosCanRead(image);
//}
//
//bool WinReader::ifDirectionCanRead(const Mat& image)
//{
//	return player_info_reader->ifDirectionCanRead(image);
//}
//
//bool WinReader::getPlayerPosition(const Mat& image,PlayerPos& player_pos)
//{
//	return player_info_reader->getPlayerPosition(image,player_pos);
//}
//
//bool WinReader::getPlayerFacing(const Mat& image, PlayerFacing& player_facing)
//{
//	return player_info_reader->getPlayerFacing(image,player_facing);
//}
//
//void WinReader::readContain(const Mat& mat, Contain& contain)
//{
//	contain_reader->readContain(mat, contain);
//}
