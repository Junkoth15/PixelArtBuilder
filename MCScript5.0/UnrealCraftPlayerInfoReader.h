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
	// ͨ�� ReadPlayerInfo �̳�
	bool isLookingAtBlock(const Mat& f3_image) override;
	bool getLookingAtBlock(const Mat& f3_image, BlockInfo& block_info) override;
	bool getLookingAtBlockName(const Mat& f3_image,string& name) override;
	bool getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos) override;
	bool ifPosCanRead(const Mat& image) override;
	bool ifDirectionCanRead(const Mat& image) override;
	bool getPlayerPosition(const Mat& image, PlayerPos& player_pos) override;
	bool getPlayerFacingDirection(const Mat& image, PlayerFacing& player_facing) override;

private:
	//�Ƿ�ָ���˷��飬ָ�򲻴����ܹ�������
	bool isPointingToBlock(const Mat& image);
	//��from_left_topΪfalse����rect��x��yָ�����������Ͻ�����
	string readF3Line(const Mat& img, Rect rect, bool from_left_top = true);

};

