//#pragma once
//#include"Contain.h"
//#include"NameSpace.h"
//#include"PlayerInfo.h"
//#include<atlimage.h>
////已废弃
//class ReadAllInfoCImage
//{
//public:
//	virtual void analysisCImage(const CImage& img) = 0;
//public:
//	//根据窗口的图片检查玩家是否看着方块，不必担心花屏问题
//	virtual bool isLookingAtBlock() = 0;
//	//根据窗口的图片获取玩家所看方块信息，识别失败返回false
//	virtual bool getLookingAtBlock(BlockInfo& block_info) = 0;
//	//获取玩家所看方块名字，应保证可以读取，识别失败回false
//	virtual bool getLookingAtBlockName(string& blockname) = 0;
//	//获取玩家所看方块位置，应保证可以读取，识别失败返回false
//	virtual bool getLookingAtBlockPos(BlockPos& block_pos) = 0;
//public:
//	////判断位置是否处于可读状态
//	//virtual bool ifPosCanRead() = 0;
//	////判断方向是否处于可读状态
//	//virtual bool ifDirectionCanRead() = 0;
//	//判断F3是否开启
//	virtual bool ifF3CanRead() = 0;
//	//根据窗口的图片获取玩家的位置，有可能图片花屏，若花屏则返回false
//	virtual bool getPlayerPosition(PlayerPos& player_pos) = 0;
//	//根据窗口图片获取玩家的面朝方向，有可能花屏，若花屏返回false
//	virtual bool getPlayerFacing(PlayerFacing& player_facing) = 0;
//public:
//	virtual PlayerStatus getAllPlayerInfo() = 0;
//
//public:
//	virtual void readContain(const CImage& f3_img, Contain& contain) = 0;
//	virtual void readPackage(const CImage& img) = 0;
//};
//
