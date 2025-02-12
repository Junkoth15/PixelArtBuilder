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
	//根据行物品列表和所需物品的index将物品拿到手上
	virtual	void getItemToHand(const vector<ColorItem>& line,int item_index)=0;
	virtual void putBlock()=0;
	virtual void move(MoveMode mode)=0;
	//获取执行函数的这一瞬间的玩家状态
	virtual PlayerStatus getPlayerStatus() = 0;
	virtual bool testAddItemToPackage(map<string,int> item_map) const = 0;
	//这里的列是从0开始
	virtual void goToLine(int line)=0;
	//传送到画板
	virtual void goToBoard() = 0;
	//打开背包
	virtual void openPackage() = 0;
	//刷新背包
	virtual void refreshPackage() = 0;
	//关闭背包
	virtual void closePackage() = 0;
	//回收物品
	virtual void recycleItem() = 0;
	//获取材料
	virtual void getItemMap(map<string, int> map)=0;
};

