#pragma once
#include"NameSpace.h"
/// <summary>
/// 非图像依赖性的一些基础功能接口
/// </summary>
class NoImageBasicFunction
{
public:
	virtual void guaji(int seconds) = 0;
	virtual void backGame() = 0;
	virtual void speak(string str) = 0;
	virtual void randomSpeak(string str) = 0;
	virtual void resTp(string destination) = 0;
	virtual void useInstruction(string instruction) = 0;
	virtual void putBlock(bool change_package) = 0;
	virtual void moveMouseAndClickLeft(int x, int y, bool absolute = true, int move_delay = 200, int click_delay = 200)=0;
};