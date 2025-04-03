#pragma once
#include"ContainReader.h"
class UnrealCraftContainReader:public ContainReader
{
protected:
	shared_ptr<ReadString> _str_reader;
	const MCItemMap* item_map;
public:
	UnrealCraftContainReader();

	//�жϸ����Ƿ�Ϊ�գ�lattice_rect�������ͼƬ�ľ�������
	virtual bool isLatticeEmpty(const Mat& lattice_img, const Mat& lattice_background_pic)override;
	//�ڸ��Ӳ��յ�����£��жϸ��Ӱ���ʲô��Ʒ��item_rect�������ͼƬ�ľ�������
	virtual const MCItem& judgeLatticeItem(const Mat& item_img)override;
	//�ڸ��Ӳ��յ�����£��жϸ�������Ʒ��������text_rect�������ͼƬ�ľ�������
	virtual int judgeLatticeItemNum(const Mat& text_img, Scalar font_color)override;
	//�ж���ɫ�Ƿ���ͬ������δ֪ԭ����ƷͼƬ��ʵ��ͼƬ�ܻ��м������صĲ��
	virtual bool isSameColor(Scalar a, Scalar b);
};

