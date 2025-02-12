#pragma once
#include"BuildLine.h"
#include"CanBuildMapPic.h"
class LineBuilder:public BuildLine
{
protected:
	//建造初始z位置
	int ori_z;
	shared_ptr<CanBuildMapPic> builder;
	vector<ColorItem> line;
public:
	LineBuilder(shared_ptr<CanBuildMapPic> builder);
	virtual ~LineBuilder() = default;
	// 通过 BuildLine 继承，在建造前应该由客户将背包准备好
	void buildLine(const vector<ColorItem>& line, int max_index) override;

protected:
	//将line的第item_num个方块拿在手上，从0开始
	virtual void getMCItemToHand(int index);
	//移动到合适的位置
	virtual void move();
	//根据看向方块的位置决定下一次要建造哪个方块（从1开始）
	virtual int decideNextBlockIndex();
	//初始化
	virtual void init();
	//初始化z轴位置
	virtual void init_ori_z();
	//初始化背包
	virtual void init_package();
	//放方块
	virtual void putBlock();



};

