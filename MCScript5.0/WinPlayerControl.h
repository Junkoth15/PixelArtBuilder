#pragma once
class WinPlayerControl
{
public:
	//x方向按一定角度转头，并选择向右还是向左，选择转头速度(度/s)，rad必须为正数，两种模式下精度为(int)(rad_speed/50/0.1028)*0.1028
	virtual void winTurnHead_x(float rad, float rad_speed, bool right, bool virtualAction = false) = 0;
	//y方向按一定角度转头，并选择向上还是向下，选择转头速度(度/s)，rad必须为正数，两种模式下精度为(int)(rad_speed/50/0.1028)*0.1028
	virtual void winTurnHead_y(float rad, float rad_speed, bool up, bool virtualAction = false) = 0;
	//水平转向,可选择是否进行虚拟操作，默认为实质性操作
	virtual void winChangeFace_x(float rad_begin, float rad_target, float rad_speed, bool virtualAction = false) = 0;
	//垂直转向,可选择是否进行虚拟操作，默认为实质性操作，输入应该在[-90,90]范围内
	virtual void winChangeFace_y(float rad_begin, float rad_target, float rad_speed, bool virtualAction = false) = 0;
	//固定距离移动，依赖于F3开启，方向为0~7，若精确移动需要指定窗口大小，不会改变窗口大小
	virtual void winMovePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift = false, bool virtualAction = false) = 0;
};

