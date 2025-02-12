#pragma once
#include"ReadContain.h"
#include"ReadString.h"
#include"NameSpace.h"
#include"MCItemMap.h"
class ContainReader:public ReadContain
{
public:
	// 通过 ReadContain 继承
	void readContain(const Mat& ori_img, Contain& contain) override;
private:
	//读取格子
	virtual void readLattice(const Mat& image, int x,int y,Contain& contain);
	//判断格子是否为空，lattice_rect是相对于图片的绝对坐标
	virtual bool isLatticeEmpty(const Mat& lattice_img,const Mat& lattice_background_pic)=0;
	//在格子不空的情况下，判断格子包含什么物品，item_rect是相对于图片的绝对坐标
	virtual const MCItem& judgeLatticeItem(const Mat& item_img)=0;
	//在格子不空的情况下，判断格子内物品的数量，text_rect是相对于图片的绝对坐标
	virtual int judgeLatticeItemNum(const Mat& text_img, Scalar font_color)=0;
};

