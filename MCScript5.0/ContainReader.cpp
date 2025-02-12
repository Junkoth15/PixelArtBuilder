#include "ContainReader.h"
#include"Tools.h"
using namespace cv;

void ContainReader::readContain(const Mat& ori_img, Contain& contain)
{
	auto points = contain.getAllLatticePOINT();
	for (auto p : points) {
		readLattice(ori_img, p.x, p.y, contain);
	}
}

void ContainReader::readLattice(const Mat& ori_img, int x, int y, Contain& contain)
{
	Lattice& lattice = contain.getLattice(x, y);
	//������Ϊ�գ������ø���Ϊ��
	if (isLatticeEmpty(ori_img(contain.getLatticeRect(x,y)), contain.getLatticeBackgroundPic(x,y))) {
		lattice.eraseItem();
		return;
	}
	//cout << "WinReader::readLattice1" << endl;
	//��������Ʒδ֪������Ϊδ֪
	const MCItem& item = judgeLatticeItem(ori_img(contain.getLatticeItemRect(x,y)));
	if (item.equal(Lattice::unknownItem)) {
		lattice.setAsUnknown();
		return;
	}
	//cout << "WinReader::readLattice2" << endl;
	////��������Ʒ��֪�����������
	lattice.eraseItem();
	lattice.addItem(item, judgeLatticeItemNum(ori_img(contain.getLatticeTextRect(x,y)), contain.getLatticeTextColor(x,y)));
}