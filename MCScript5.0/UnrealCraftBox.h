#pragma once
#include"Box.h"
/// <summary>
/// 默认为54格的大箱子
/// </summary>
class UnrealCraftBox :
	public Box//抽象类
{
public:
	static string lattice_pic_path;
private:
	static Mat lattice_pic;	//格子的背景
	static Rect text_rect;	//格子的文字区域
	static Rect item_rect;	//格子的物品区域
	static Rect lattice_rect;//格子区域
	static Scalar text_color;//文字颜色
	static POINT big_box_pos;//大箱子位置
	static POINT small_box_pos;//小箱子位置
	static bool data_loaded;	//数据是否已加载
	static void load();	//加载数据
public:
	UnrealCraftBox(BoxType type);
	// 通过 Box 继承
	virtual void setBoxType(BoxType type)override;
	POINT getLatticeRelativeMidPos(int x, int y) const override;
	POINT getLatticeRelativePos(int x, int y) const override;
	Mat getLatticeBackgroundPic(int x, int y) const override;
	Rect getLatticeItemRect(int x, int y) const override;
	Rect getLatticeTextRect(int x, int y) const override;
	Rect getLatticeRect(int x, int y) const override;
	Scalar getLatticeTextColor(int x, int y) const override;

	// 通过 CloneAble 继承
	shared_ptr<CloneAble> clone()const override;
};

