#pragma once
#include"NameSpace.h"
#include"PlayerInfo.h"
class ReadPlayerInfo
{
public:
	//根据窗口的图片检查玩家是否看着方块，不必担心花屏问题
	virtual bool isLookingAtBlock(const Mat& f3_image) = 0;
	//根据窗口的图片获取玩家所看方块信息，识别失败返回false
	virtual bool getLookingAtBlock(const Mat& f3_image,BlockInfo& block_info) = 0;
	//获取玩家所看方块名字，应保证可以读取，识别失败回false
	virtual bool getLookingAtBlockName(const Mat& f3_image,string& name) = 0;
	//获取玩家所看方块位置，应保证可以读取，识别失败返回false
	virtual bool getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos) = 0;
public:
	//判断位置是否处于可读状态
	virtual bool ifPosCanRead(const Mat& image) = 0;
	//判断方向是否处于可读状态
	virtual bool ifDirectionCanRead(const Mat& image) = 0;
	//根据窗口的图片获取玩家的位置，有可能图片花屏，若花屏则返回false
	virtual bool getPlayerPosition(const Mat& image,PlayerPos& player_pos) = 0;
	//根据窗口图片获取玩家的面朝方向，有可能花屏，若花屏返回false
	virtual bool getPlayerFacingDirection(const Mat& image, PlayerFacing& player_facing) = 0;
};

