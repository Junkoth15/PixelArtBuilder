#pragma once
#include"ReadPlayerInfo.h"
#include"ReadString.h"
class UnrealCraftPlayerInfoReader:
	public ReadPlayerInfo
{
public:
	static Scalar f3_font_color;
	static Rect player_pos_rect;
	static Rect player_facing_rect;
	static Rect looking_at_block_name_rect;
	static Rect looking_at_block_pos_rect;

protected:
	shared_ptr<const ReadString> str_reader;
public:
	UnrealCraftPlayerInfoReader();
	// 通过 ReadPlayerInfo 继承
	bool isLookingAtBlock(const Mat& f3_image) override;
	bool getLookingAtBlock(const Mat& f3_image, BlockInfo& block_info) override;
	bool getLookingAtBlockName(const Mat& f3_image,string& name) override;
	bool getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos) override;
	bool ifPosCanRead(const Mat& image) override;
	bool ifDirectionCanRead(const Mat& image) override;
	bool getPlayerPosition(const Mat& image, PlayerPos& player_pos) override;
	bool getPlayerFacingDirection(const Mat& image, PlayerFacing& player_facing) override;

private:
	//是否指向了方块，指向不代表能够到方块
	bool isPointingToBlock(const Mat& image);
	//若from_left_top为false，则rect的x和y指的是区域右上角坐标
	string readF3Line(const Mat& img, Rect rect, bool from_left_top = true);

};

