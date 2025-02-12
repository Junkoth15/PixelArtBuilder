#include "Lattice.h"
using namespace cv;
using namespace std;
const MCItem Lattice::emptyItem = MCItem(Mat(), "����Ʒ", 1);
const MCItem Lattice::unknownItem = MCItem(Mat(), "δ֪��", 1);

Lattice::Lattice() :
	x(0), y(0),
	item_ptr(&emptyItem), num(0),status(LatticeStatus::Empty)
{
}
Lattice::Lattice(int x, int y) :
	x(x), y(y),
	item_ptr(&emptyItem), num(0), status(LatticeStatus::Empty)
{
}

bool Lattice::addItem(const MCItem& item, int num)
{
	//���ѵ��������ޣ��޷����
	if ((this->num + num) > (item.stacking_limit)) {
		return false;
	}
	//���������Ʒδ֪���޷����
	if (isUnknown()) {
		return false;
	}
	//����Ѿ�����Ʒ�Һʹ������Ʒ����ͬһ����Ʒ���޷����
	if ((!isEmpty()) && (!item_ptr->equal(item))) {
		return false;
	}

	//�����Ʒ
	if (isEmpty()) {
		item_ptr = &item;
		status = LatticeStatus::HasKnownItem;
	}
	this->num += num;
	return true;
}

bool Lattice::removeItem(int num)
{
	//ʣ����Ʒ�����Կ۳����Ƴ�ʧ��
	if (this->num < num) {
		return false;
	}
	else {
		this->num -= num;
		//�۳���Ʒ��Ϊ�գ���Ʒ���
		if (this->num == 0) {
			eraseItem();
		}
		return true;
	}
}

void Lattice::eraseItem()
{
	item_ptr = &emptyItem;
	num = 0;
	status = LatticeStatus::Empty;
}

void Lattice::setAsUnknown()
{
	item_ptr = &unknownItem;
	status = LatticeStatus::Unknown;
	num = 1;
}

bool Lattice::isUnknown() const
{
	return status==LatticeStatus::Unknown;
}

bool Lattice::isEmpty() const
{
	return status==LatticeStatus::Empty;
}

bool Lattice::isFull() const
{
	if (isEmpty()) {
		return false;
	}
	if (isUnknown()) {
		return true;
	}
	return num == item_ptr->stacking_limit;
}

bool Lattice::isHasKnownItem() const
{
	return status==LatticeStatus::HasKnownItem;
}

const MCItem& Lattice::getItem() const
{
	return *item_ptr;
}

int Lattice::getNum() const
{
	return num;
}

bool Lattice::judgeItemEqual(const MCItem& item) const
{
	if (!isHasKnownItem()) {
		return false;
	}
	return item_ptr->equal(item);
}

bool Lattice::judgeItemEqual(const Lattice& lattice) const
{
	//������Ϊ�ջ�δ֪�򲻽��бȽϣ�����false
	if (!isHasKnownItem() || !lattice.isHasKnownItem()) {
		return false;
	}
	return item_ptr->equal(*lattice.item_ptr);
}

string Lattice::getLatticeInfo() const
{
	string item_name;
	string item_num;
	item_name = item_ptr->name;
	if (item_name.length() < 6) {
		item_name.append(6 - item_name.length(), ' ');
	}
	item_num = to_string(num);
	if (item_num.length() < 2) {
		item_num.append(" ");
	}
	return item_name + " " + item_num;
}

void Lattice::exchangeItemWithLattice(Lattice& lattice)
{
	//exchangeLatticesItem(*this, lattice);

	const MCItem* item_ptr_tmp = item_ptr;
	int num_tmp = num;
	LatticeStatus status_tmp = status;

	item_ptr = lattice.item_ptr;
	num = lattice.num;
	status = lattice.status;

	lattice.item_ptr = item_ptr_tmp;
	lattice.num = num_tmp;
	lattice.status = status_tmp;
}

void exchangeLatticesItem(Lattice& first, Lattice& second)
{
	first.exchangeItemWithLattice(second);
}
