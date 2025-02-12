#pragma once
class PlayerControl
{
public:
	//x方向按一定角度转头,rad必须为正数
	virtual void turnHead_x(float rad, float rad_speed, bool right) = 0;
	//y方向按一定角度转头，rad必须为正数
	virtual void turnHead_y(float rad, float rad_speed, bool up) = 0;
	//根据起点角度和终点角度水平转向
	virtual void changeFace_x(float rad_begin, float rad_target, float rad_speed) = 0;
	//垂直转向,输入应该在[-90,90]范围内
	virtual void changeFace_y(float rad_begin, float rad_target, float rad_speed) = 0;
	//固定距离移动，方向为0~7
	virtual void movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift = false) = 0;
	//固定时间移动,方向为0~7
	virtual void movePlayerPosition_inTime(int direction, int militime, bool shift = false) = 0;
};

