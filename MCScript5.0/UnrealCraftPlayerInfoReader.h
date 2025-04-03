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
	//判断block_info的向下偏移量
	bool judgeOffset();
	//获取正确的block_name_rect
	Rect getBlockNameRect()override;
	//获取正确的block_pos_rect
	Rect getBlockPosRect()override;
	//清空数据
	virtual void clearData()override;
	//是否指向了方块，指向不代表能够到方块
	bool isPointingToBlock()override;
};

