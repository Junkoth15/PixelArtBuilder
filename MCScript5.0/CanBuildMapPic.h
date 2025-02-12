#pragma once
#include<Windows.h>
#include"PlayerInfo.h"
#include"ColorItem.h"
#include"NameSpace.h"

enum class MoveMode{
	FrontBegin,FrontEnd,BackBegin,BackEnd,LeftBegin,LeftEnd,RightBegin,RightEnd
};

class CanBuildMapPic
{
public:
	//��������Ʒ�б��������Ʒ��index����Ʒ�õ�����
	virtual	void getItemToHand(const vector<ColorItem>& line,int item_index)=0;
	virtual void putBlock()=0;
	virtual void move(MoveMode mode)=0;
	//��ȡִ�к�������һ˲������״̬
	virtual PlayerStatus getPlayerStatus() = 0;
	virtual bool testAddItemToPackage(map<string,int> item_map) const = 0;
	//��������Ǵ�0��ʼ
	virtual void goToLine(int line)=0;
	//���͵�����
	virtual void goToBoard() = 0;
	//�򿪱���
	virtual void openPackage() = 0;
	//ˢ�±���
	virtual void refreshPackage() = 0;
	//�رձ���
	virtual void closePackage() = 0;
	//������Ʒ
	virtual void recycleItem() = 0;
	//��ȡ����
	virtual void getItemMap(map<string, int> map)=0;
};

