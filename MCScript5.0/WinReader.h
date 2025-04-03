//#pragma once
//#include"ReadAllInfo.h"
//class WinReader:
//	public ReadAllInfo
//{
//protected:
//	shared_ptr<ReadPlayerInfo> player_info_reader;
//	shared_ptr<ReadContain> contain_reader;
//
//public:
//	WinReader(
//		shared_ptr<ReadPlayerInfo> player_info_reader,
//		shared_ptr<ReadContain> contain_reader
//		);
//	shared_ptr<ReadPlayerInfo> setPlayerInfoReader(shared_ptr<ReadPlayerInfo> reader);
//	shared_ptr<ReadPlayerInfo> getPlayerInfoReader();
//	shared_ptr<ReadContain> setContainReader(shared_ptr<ReadContain> reader);
//	shared_ptr<ReadContain> getContainReader();
//
//	bool isLookingAtBlock(const Mat& f3_image) override;
//	bool getLookingAtBlock(const Mat& f3_image,BlockInfo& block_info) override;
//	bool getLookingAtBlockName(const Mat& f3_image, string& blockname) override;
//	bool getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos) override;
//	bool ifPosCanRead(const Mat& image) override;
//	bool ifDirectionCanRead(const Mat& image) override;
//	bool getPlayerPosition(const Mat& image, PlayerPos& player_pos) override;
//	bool getPlayerFacing(const Mat& image,PlayerFacing& player_facing) override;
//	void readContain(const Mat& mat, Contain& contain) override;
//};

