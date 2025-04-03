#pragma once
#include"PlayerInfoReader120.h"
class UnrealCraftPlayerInfoReader:public PlayerInfoReader120
{
public:
	static Rect index_pool_rect;
	static Rect block_name_rect_up;
	static Rect block_pos_rect_up;
	static Rect block_name_rect_down;
	static Rect block_pos_rect_down;
public:
	UnrealCraftPlayerInfoReader();
protected:
	UpdatedStatus _offset_updated;
	int _offset;
protected:
	//�ж�block_info������ƫ����
	bool judgeOffset();
	//��ȡ��ȷ��block_name_rect
	Rect getBlockNameRect()override;
	//��ȡ��ȷ��block_pos_rect
	Rect getBlockPosRect()override;
	//�������
	virtual void clearData()override;
	//�Ƿ�ָ���˷��飬ָ�򲻴����ܹ�������
	bool isPointingToBlock()override;
};

