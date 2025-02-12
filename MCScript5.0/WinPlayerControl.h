#pragma once
class WinPlayerControl
{
public:
	//x����һ���Ƕ�תͷ����ѡ�����һ�������ѡ��תͷ�ٶ�(��/s)��rad����Ϊ����������ģʽ�¾���Ϊ(int)(rad_speed/50/0.1028)*0.1028
	virtual void winTurnHead_x(float rad, float rad_speed, bool right, bool virtualAction = false) = 0;
	//y����һ���Ƕ�תͷ����ѡ�����ϻ������£�ѡ��תͷ�ٶ�(��/s)��rad����Ϊ����������ģʽ�¾���Ϊ(int)(rad_speed/50/0.1028)*0.1028
	virtual void winTurnHead_y(float rad, float rad_speed, bool up, bool virtualAction = false) = 0;
	//ˮƽת��,��ѡ���Ƿ�������������Ĭ��Ϊʵ���Բ���
	virtual void winChangeFace_x(float rad_begin, float rad_target, float rad_speed, bool virtualAction = false) = 0;
	//��ֱת��,��ѡ���Ƿ�������������Ĭ��Ϊʵ���Բ���������Ӧ����[-90,90]��Χ��
	virtual void winChangeFace_y(float rad_begin, float rad_target, float rad_speed, bool virtualAction = false) = 0;
	//�̶������ƶ���������F3����������Ϊ0~7������ȷ�ƶ���Ҫָ�����ڴ�С������ı䴰�ڴ�С
	virtual void winMovePlayerPosition_inDistance(int direction, float distance, float move_speed, bool shift = false, bool virtualAction = false) = 0;
};

