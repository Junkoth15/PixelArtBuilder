#pragma once
#include<Windows.h>
//����¼�
enum class MouseEvent {
	LeftDown, LeftUp, ClickLeft, RightDown, RightUp, ClickRight
};
class MouseControl
{
public:
	//������ƶ���ĳ�������л������������������
	virtual void moveMouseToPoint(int x, int y, bool absolute_coordinates = true) = 0;
	//�������ƶ�һ������
	virtual void moveMouse(int dx, int dy) = 0;
	//�̶�ʱ��ֱ���ƶ����
	virtual void moveMouseLinearly_inTime(float directionRad, int distance, int militime) = 0;
	//�̶��ٶ�ֱ���ƶ����
	virtual void moveMouseLinearly_inSpeed(float directionRad, int distance, float speed) = 0;
	//��ȡ������λ��
	virtual POINT getMousePosition() = 0;
	//��갴������
	virtual void mouseEvent(MouseEvent mouse_event) = 0;
};
