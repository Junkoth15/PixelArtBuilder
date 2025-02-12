#pragma once
#include<Windows.h>
class WindowControl
{
public:
	//��ȡ���ھ��
	virtual HWND getWindow() = 0;
	//��ȡ����λ��
	virtual POINT getWindowPos() = 0;
	//��ȡ���ڿ��
	virtual void getWindowSize(int& width, int& height) = 0;
	//���Ĵ��ھ������ˢ�´���λ�úͿ��
	virtual void changeWinodw(HWND window) = 0;
	//ˢ�´���λ�úʹ�С
	virtual void refreshWindowPositionAndSize() = 0;
	//���ô���λ�ã���ˢ�´���λ�úʹ�С
	virtual void setWindowPos(int x, int y) = 0;
	//���ô��ڴ�С,��ˢ�´���λ�úʹ�С
	virtual void setWindowSize(int width, int height) = 0;
	//�ô��ڴ�Сģʽ���ô��ڴ�С����ˢ�´���λ�úʹ�С
	virtual void setWindowSize(int f_size_type) = 0;
};
