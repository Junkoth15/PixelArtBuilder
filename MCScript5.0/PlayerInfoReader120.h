#pragma once
#include"ReadPlayerInfo.h"
#include"ReadString.h"
class PlayerInfoReader120:
	public ReadPlayerInfo
{
public:
	static Scalar f3_font_color;
	static Rect player_pos_rect;
	static Rect player_facing_rect;
	static Rect block_name_rect;
	static Rect block_pos_rect;
protected:
	enum class UpdatedStatus
	{
		NO,YES,ERR
	};

protected:
	shared_ptr<const ReadString> _str_reader;
	const Mat* _img;
	PlayerStatus _player_status;
	UpdatedStatus _player_pos_updated;
	UpdatedStatus _player_facing_updated;
	UpdatedStatus _block_pos_updated;
	UpdatedStatus _block_name_updated;
	UpdatedStatus _F3_can_read_updated;
	UpdatedStatus _is_looking_at_block_updated;
	UpdatedStatus _is_pointing_to_block_updated;
	bool _is_pointing_to_block;
public:
	PlayerInfoReader120(shared_ptr<const ReadString> str_reader);
	// 通过 ReadPlayerInfo 继承
	void analysisPic(const Mat& img) override;
	bool isLookingAtBlock() override;
	bool getLookingAtBlock(BlockInfo& block_info) override;
	bool getLookingAtBlockName(string& name) override;
	bool getLookingAtBlockPos(BlockPos& block_pos) override;
	//bool ifPosCanRead() override;
	//bool ifDirectionCanRead() override;
	bool ifF3CanRead() override;
	bool getPlayerPosition(PlayerPos& player_pos) override;
	bool getPlayerFacing(PlayerFacing& player_facing) override;
	PlayerStatus getAllPlayerInfo() override;
protected:
	//清空数据
	virtual void clearData();
	//是否指向了方块，指向不代表能够到方块
	virtual bool isPointingToBlock();
	//若from_left_top为false，则rect的x和y指的是区域右上角坐标
	virtual string readF3Line(const Mat& img, Rect rect, bool from_left_top = true);
	virtual Rect getPlayerPosRect();
	virtual Rect getPlayerFacingRect();
	virtual Rect getBlockNameRect();
	virtual Rect getBlockPosRect();
};

