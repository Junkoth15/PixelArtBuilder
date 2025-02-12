#pragma once
#include<Windows.h>
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
#include"Lattice.h"
#include"MCItem.h"
#include"CloneAble.h"
/// <summary>
/// 容器类
/// 提供容器的数据与UI信息
/// 包括格子、容器的位置信息和图像信息
/// </summary>
class Contain:
	public CloneAble
{
public:
	template<typename T>
	using vector = std::vector<T>;
	using string = std::string;
	using Mat = cv::Mat;
	using Rect = cv::Rect;
	using Scalar = cv::Scalar;

public:
	virtual ~Contain() = default;
	//设置容器的左上角相对于窗口的位置
	virtual void setContainRelativePosition(int x, int y) = 0;
	//根据窗口大小调整容器的位置
	virtual void changePosByWindowSizeType(int size_type) = 0;
	//以shift的方式将物品放入容器
	virtual bool addItemByShift(const MCItem& item, int num) = 0;
	//清空容器
	virtual void clear() = 0;
	//通过编号获取格子
	virtual Lattice& getLattice(int x, int y) = 0;
	//获取容器的相对位置
	virtual POINT getContainRelativePos()const = 0;
	//获取格子中心的的相对位置(相对于窗口的坐标)
	virtual POINT getLatticeRelativeMidPos(int x, int y)const = 0;
	//得到格子左上角相对窗口位置
	virtual POINT getLatticeRelativePos(int x, int y)const = 0;
	//容器内寻找物品并返回格子的编号数组
	virtual vector<POINT> findItem(const MCItem& item)const = 0;
	//容器内寻找找到的第一个物品
	virtual POINT findFirstItem(const MCItem& item)const = 0;
	//通过编号获取格子
	virtual const Lattice& getLattice(int x, int y)const = 0;
	//获取容器所有格子的编号
	virtual vector<POINT> getAllLatticePOINT()const = 0;
	//获取格子的背景图片
	virtual Mat getLatticeBackgroundPic(int x, int y)const = 0;
	//获取某格子的格子区域，包括位置与大小信息
	virtual Rect getLatticeRect(int x, int y)const = 0;
	//获取某格子的物品区域，包括位置与大小信息
	virtual Rect getLatticeItemRect(int x, int y)const = 0;
	//获取某格子的文字区域位置，包括位置与大小信息
	virtual Rect getLatticeTextRect(int x, int y)const = 0;
	//获取所有格子的信息
	virtual string getAllLatticeInfo()const = 0;
	//获取格子文字的颜色
	virtual Scalar getLatticeTextColor(int x, int y)const = 0;
	//尝试以shift的方式将物品放入容器，不会真的放入
	virtual bool testAddItemByShift(const MCItem& item, int num)const = 0;
};

