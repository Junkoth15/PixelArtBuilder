#pragma once
#include"ContainReader.h"
class UnrealCraftContainReader:public ContainReader
{
protected:
	shared_ptr<ReadString> _str_reader;
	const MCItemMap* item_map;
public:
	UnrealCraftContainReader();

	//判断格子是否为空，lattice_rect是相对于图片的绝对坐标
	virtual bool isLatticeEmpty(const Mat& lattice_img, const Mat& lattice_background_pic)override;
	//在格子不空的情况下，判断格子包含什么物品，item_rect是相对于图片的绝对坐标
	virtual const MCItem& judgeLatticeItem(const Mat& item_img)override;
	//在格子不空的情况下，判断格子内物品的数量，text_rect是相对于图片的绝对坐标
	virtual int judgeLatticeItemNum(const Mat& text_img, Scalar font_color)override;
	//判断颜色是否相同，由于未知原因，物品图片和实际图片总会有几个像素的差距
	virtual bool isSameColor(Scalar a, Scalar b);
};

