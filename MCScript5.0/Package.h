#pragma once
#include"Contain.h"
/// <summary>
/// 抽象类
/// 角色背包类的抽象类，我们认为背包的基本结构是稳定的（四行九列的背包结构）
/// 认为背包的位置和背景图片是易变的
/// </summary>
enum class PackageStatus
{
	COMMON, USE_BIG_BOX, USE_SMALL_BOX
};
class Package :public Contain
{
protected:
	//普通背包
	vector<vector<Lattice>> package;
	//背包左上角的位置
	POINT packagePos;
	PackageStatus status;
public:
	Package();
	virtual ~Package() = default;

	//交换两格物品
	virtual void exchangeItems(int first_x, int first_y, int second_x, int second_y);
	//设置背包打开方式
	virtual void setPackageStatus(PackageStatus open_type);
	//获取背包的打开方式
	virtual PackageStatus getPackageStatus()const;
	//寻找第一个物品，优先从第四行开始找，未找到返回(0,0)
	virtual POINT findFirsItemFirstFromRow4(const MCItem& item)const;
	virtual void setContainRelativePosition(int x, int y) override;
	virtual POINT getContainRelativePos() const override;
	virtual vector<POINT> findItem(const MCItem& item)const override;
	virtual POINT findFirstItem(const MCItem& item) const override;
	virtual Lattice& getLattice(int x, int y)override;
	const Lattice& getLattice(int x, int y) const override;
	virtual vector<POINT> getAllLatticePOINT()const override;
	virtual void changePosByWindowSizeType(int size_type) override;
	virtual void clear() override;
	virtual string getAllLatticeInfo()const override;
	virtual bool addItemByShift(const MCItem& item, int num) override;
	virtual bool testAddItemByShift(const MCItem& item, int num)const override;
};

