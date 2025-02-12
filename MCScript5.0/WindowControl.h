#pragma once
#include<Windows.h>
class WindowControl
{
public:
	//获取窗口句柄
	virtual HWND getWindow() = 0;
	//获取窗口位置
	virtual POINT getWindowPos() = 0;
	//获取窗口宽高
	virtual void getWindowSize(int& width, int& height) = 0;
	//更改窗口句柄，并刷新窗口位置和宽高
	virtual void changeWinodw(HWND window) = 0;
	//刷新窗口位置和大小
	virtual void refreshWindowPositionAndSize() = 0;
	//设置窗口位置，并刷新窗口位置和大小
	virtual void setWindowPos(int x, int y) = 0;
	//设置窗口大小,并刷新窗口位置和大小
	virtual void setWindowSize(int width, int height) = 0;
	//用窗口大小模式设置窗口大小，并刷新窗口位置和大小
	virtual void setWindowSize(int f_size_type) = 0;
};
