#pragma once
#include"ReadContain.h"
#include"ReadString.h"
#include"NameSpace.h"
#include"MCItemMap.h"
class ContainReader:public ReadContain
{
public:
	// ͨ�� ReadContain �̳�
	void readContain(const Mat& ori_img, Contain& contain) override;
private:
	//��ȡ����
	virtual void readLattice(const Mat& image, int x,int y,Contain& contain);
	//�жϸ����Ƿ�Ϊ�գ�lattice_rect�������ͼƬ�ľ�������
	virtual bool isLatticeEmpty(const Mat& lattice_img,const Mat& lattice_background_pic)=0;
	//�ڸ��Ӳ��յ�����£��жϸ��Ӱ���ʲô��Ʒ��item_rect�������ͼƬ�ľ�������
	virtual const MCItem& judgeLatticeItem(const Mat& item_img)=0;
	//�ڸ��Ӳ��յ�����£��жϸ�������Ʒ��������text_rect�������ͼƬ�ľ�������
	virtual int judgeLatticeItemNum(const Mat& text_img, Scalar font_color)=0;
};

