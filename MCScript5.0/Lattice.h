#pragma once
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
#include"MCItem.h"
/// <summary>
/// 经过研究决定，本项目不考虑内存管理问题
/// </summary>
class Lattice
{
public:
	template<typename Content>
	using vector = std::vector<Content>;
	using string = std::string;
	using Mat = cv::Mat;
	using Rect = cv::Rect;
	template<typename Type>
	using shared_ptr = std::shared_ptr<Type>;
private:
	enum class LatticeStatus {
		HasKnownItem, Empty, Unknown
	};

public:
	static const MCItem emptyItem;
	static const MCItem unknownItem;
public:
	//格子的x编号
	int x;
	//格子的y编号
	int y;
private:
	//格子存储的物品
	const MCItem* item_ptr;
	//已存储的物品数量
	int num;
	//格子的存储状态
	LatticeStatus status;

public:
	Lattice();
	//创建对象，输入格子的坐标
	Lattice(int x, int y);
	//为格子添加物品，并返回是否可以添加
	bool addItem(const MCItem& item, int num);
	//减少格子内物品，并返回操作是否合理
	bool removeItem(int num);
	//移除格子内物品
	void eraseItem();
	//格子设为物品未知
	void setAsUnknown();
	//与另一个格子交换物品，函数的特点是不会导致格子的坐标等信息也交换了
	void exchangeItemWithLattice(Lattice& lattice);

	//判断格子是否未知
	bool isUnknown()const;
	//判断格子是否为空
	bool isEmpty()const;
	//判断格子是否已满
	bool isFull()const;
	//判断格子是否有已知的东西
	bool isHasKnownItem()const;
	//获取物品信息
	const MCItem& getItem()const;
	//获取已存储的物品数量
	int getNum()const;
	//判断某物品与格子内的物品是否相同
	bool judgeItemEqual(const MCItem& item)const;
	//判断某两格子内的物品是否相同
	bool judgeItemEqual(const Lattice& lattice)const;
	//获取格子信息
	string getLatticeInfo()const;
};

//交换两格子的物品，函数的特点是不会导致格子的坐标等信息也交换了
void exchangeLatticesItem(Lattice& first, Lattice& second);
