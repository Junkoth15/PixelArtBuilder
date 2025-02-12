#pragma once
#include"Contain.h"
enum class BoxType
{
	BIG, SMALL
};
class Box :
	public Contain//接口
{
protected:
	vector<vector<Lattice>> box;
	BoxType box_type;
	//箱子左上角位置
	POINT boxPos;
public:
	Box(BoxType box_type);
	virtual ~Box() = default;

	virtual void setBoxType(BoxType type);
	virtual int getMaxRow()const;

	void setContainRelativePosition(int x, int y) override;
	POINT getContainRelativePos() const override;

	virtual vector<POINT> findItem(const MCItem& item)const override;
	virtual POINT findFirstItem(const MCItem& item)const override;
	virtual Lattice& getLattice(int x, int y) override;
	virtual const Lattice& getLattice(int x, int y) const override;
	//格子坐标的顺序是从上到下，从左到右
	virtual vector<POINT> getAllLatticePOINT()const override;
	virtual void clear()override;
	//获取所有格子的信息
	virtual string getAllLatticeInfo()const override;
	virtual void changePosByWindowSizeType(int size_type) override;
	//以shift的方式将物品放入容器
	virtual bool addItemByShift(const MCItem& item, int num) override;
	virtual bool testAddItemByShift(const MCItem& item, int num) const override;
};

