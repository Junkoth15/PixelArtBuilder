#include"NameSpace.h"
class ScanWindow
{
public:
	//获取窗口的图片
	virtual void getWindowPic(Mat& image) = 0;
	//获取窗口的指定区域的图片
	virtual void getWindowPic(Mat& image, int width, int height, int left_x, int top_y) = 0;
	//获取F3区域的图片
	virtual void getF3Pic(Mat& image) = 0;
};