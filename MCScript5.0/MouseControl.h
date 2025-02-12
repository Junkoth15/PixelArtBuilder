#pragma once
#include<Windows.h>
//鼠标事件
enum class MouseEvent {
	LeftDown, LeftUp, ClickLeft, RightDown, RightUp, ClickRight
};
class MouseControl
{
public:
	//把鼠标移动到某处，可切换绝对坐标与相对坐标
	virtual void moveMouseToPoint(int x, int y, bool absolute_coordinates = true) = 0;
	//鼠标相对移动一定距离
	virtual void moveMouse(int dx, int dy) = 0;
	//固定时间直线移动鼠标
	virtual void moveMouseLinearly_inTime(float directionRad, int distance, int militime) = 0;
	//固定速度直线移动鼠标
	virtual void moveMouseLinearly_inSpeed(float directionRad, int distance, float speed) = 0;
	//获取鼠标绝对位置
	virtual POINT getMousePosition() = 0;
	//鼠标按键操作
	virtual void mouseEvent(MouseEvent mouse_event) = 0;
};
