#pragma once
class PlayerControl
{
public:
	//x����һ���Ƕ�תͷ,rad����Ϊ����
	virtual void turnHead_x(float rad, float rad_speed, bool right) = 0;
	//y����һ���Ƕ�תͷ��rad����Ϊ����
	virtual void turnHead_y(float rad, float rad_speed, bool up) = 0;
	//�������ǶȺ��յ�Ƕ�ˮƽת��
	virtual void changeFace_x(float rad_begin, float rad_target, float rad_speed) = 0;
	//��ֱת��,����Ӧ����[-90,90]��Χ��
	virtual void changeFace_y(float rad_begin, float rad_target, float rad_speed) = 0;
	//�̶������ƶ�������Ϊ0~7
	virtual void movePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift = false) = 0;
	//�̶�ʱ���ƶ�,����Ϊ0~7
	virtual void movePlayerPosition_inTime(int direction, int militime, bool shift = false) = 0;
};

