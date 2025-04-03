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
	// ͨ�� ReadPlayerInfo �̳�
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
	//�������
	virtual void clearData();
	//�Ƿ�ָ���˷��飬ָ�򲻴����ܹ�������
	virtual bool isPointingToBlock();
	//��from_left_topΪfalse����rect��x��yָ�����������Ͻ�����
	virtual string readF3Line(const Mat& img, Rect rect, bool from_left_top = true);
	virtual Rect getPlayerPosRect();
	virtual Rect getPlayerFacingRect();
	virtual Rect getBlockNameRect();
	virtual Rect getBlockPosRect();
};

