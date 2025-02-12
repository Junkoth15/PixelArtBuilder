#pragma once
#include"Package.h"
/// <summary>
/// 虚无世界的背包实现类
/// </summary>
class UnrealCraftPackage :
	public Package//抽象类
{
public:
	static string common_lattice_pic_path;
	static string other_lattice_pic_path;
private:
	static Mat package_lattice_pic;	//格子的背景
	static Mat others_lattice_pic;	//其他容器的背景
	static POINT commonRowPos[4];	//普通背包每行相对于背包的位置
	static Rect text_rect;	//格子的文字区域
	static Rect item_rect;	//格子的物品区域
	static Rect lattice_rect;//格子区域
	static Scalar text_color;//文字颜色
	static bool data_loaded;//数据是否已加载
	static void load();
private:
	//背包的状态
	PackageStatus status;
public:
	/// <summary>
	/// 虚无世界背包构造函数
	/// </summary>
	/// <param name="lattice_pic">背包格子的背景，包括物品区与边框</param>
	UnrealCraftPackage();
	// 通过 Package 继承
	//设置背包打开方式
	virtual void setPackageStatus(PackageStatus open_type) override;
	Mat getLatticeBackgroundPic(int x, int y) const override;
	virtual POINT getLatticeRelativeMidPos(int x, int y) const override;
	virtual POINT getLatticeRelativePos(int x, int y) const override;
	virtual Rect getLatticeTextRect(int x, int y)const override;
	virtual Rect getLatticeItemRect(int x, int y)const override;
	virtual Rect getLatticeRect(int x, int y) const override;
	Scalar getLatticeTextColor(int x, int y) const override;

	// 通过 CloneAble 继承
	shared_ptr<CloneAble> clone()const override;
};

