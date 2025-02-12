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
	//若格子为空，则设置格子为空
	if (isLatticeEmpty(ori_img(contain.getLatticeRect(x,y)), contain.getLatticeBackgroundPic(x,y))) {
		lattice.eraseItem();
		return;
	}
	//cout << "WinReader::readLattice1" << endl;
	//若格子物品未知，则设为未知
	const MCItem& item = judgeLatticeItem(ori_img(contain.getLatticeItemRect(x,y)));
	if (item.equal(Lattice::unknownItem)) {
		lattice.setAsUnknown();
		return;
	}
	//cout << "WinReader::readLattice2" << endl;
	////若格子物品已知，则计算数量
	lattice.eraseItem();
	lattice.addItem(item, judgeLatticeItemNum(ori_img(contain.getLatticeTextRect(x,y)), contain.getLatticeTextColor(x,y)));
}