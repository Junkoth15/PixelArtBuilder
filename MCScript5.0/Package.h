#pragma once
#include"Contain.h"
/// <summary>
/// ������
/// ��ɫ������ĳ����࣬������Ϊ�����Ļ����ṹ���ȶ��ģ����о��еı����ṹ��
/// ��Ϊ������λ�úͱ���ͼƬ���ױ��
/// </summary>
enum class PackageStatus
{
	COMMON, USE_BIG_BOX, USE_SMALL_BOX
};
class Package :public Contain
{
protected:
	//��ͨ����
	vector<vector<Lattice>> package;
	//�������Ͻǵ�λ��
	POINT packagePos;
	PackageStatus status;
public:
	Package();
	virtual ~Package() = default;

	//����������Ʒ
	virtual void exchangeItems(int first_x, int first_y, int second_x, int second_y);
	//���ñ����򿪷�ʽ
	virtual void setPackageStatus(PackageStatus open_type);
	//��ȡ�����Ĵ򿪷�ʽ
	virtual PackageStatus getPackageStatus()const;
	//Ѱ�ҵ�һ����Ʒ�����ȴӵ����п�ʼ�ң�δ�ҵ�����(0,0)
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

