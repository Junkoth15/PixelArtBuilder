#pragma once
#include"ImagePerformer.h"
class MCScript
{
private:
	enum class MoveMode
	{
		LeftDown,LeftUp,RightDown,RightUp,FrontDown,FrontUp,BackDown,BackUp,ShiftDown,ShiftUp,
		SpaceDown,SpaceUp,
		ClickSpace
	};
	enum class SMouseEvent
	{
		LeftDown,LeftUp,RightDown,RightUp,ClickLeft,ClickRight
	};
	enum class MoveDirection
	{
		Left,Right,Front,Back,Jump
	};

private:
	NoImagePerformer* m_noImagePerformer;
	ImagePerformer* m_imagePerformer;

public:
	MCScript(NoImagePerformer* noImagePerformer);
	MCScript(ImagePerformer* imagePerformer);

	void shouCai();// ’≤À

private:
	void move(MoveMode move_mode);
	void moveForTime(MoveDirection dir,int interval_time,int delay_time);
	void mouseEvent(SMouseEvent mouse_event);
	void sleep(int militime);
	void openBox();
	void closeBoxOrPackage();
	void mouseEventForTime(SMouseEvent mouse_event, int militime, int interval_time);
};

