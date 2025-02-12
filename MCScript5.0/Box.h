#pragma once
#include"Contain.h"
enum class BoxType
{
	BIG, SMALL
};
class Box :
	public Contain//�ӿ�
{
protected:
	vector<vector<Lattice>> box;
	BoxType box_type;
	//�������Ͻ�λ��
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
	//���������˳���Ǵ��ϵ��£�������
	virtual vector<POINT> getAllLatticePOINT()const override;
	virtual void clear()override;
	//��ȡ���и��ӵ���Ϣ
	virtual string getAllLatticeInfo()const override;
	virtual void changePosByWindowSizeType(int size_type) override;
	//��shift�ķ�ʽ����Ʒ��������
	virtual bool addItemByShift(const MCItem& item, int num) override;
	virtual bool testAddItemByShift(const MCItem& item, int num) const override;
};

