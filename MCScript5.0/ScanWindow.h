#include<atlimage.h>
class ScanWindow
{
public:
	typedef CImage WindowCImage;
public:
	//获取窗口的图片
	virtual void getWindowPic(WindowCImage& image) = 0;
	//获取窗口的指定区域的图片
	virtual void getWindowPic(WindowCImage& image, int width, int height, int left_x, int top_y) = 0;
	//获取F3区域的图片
	virtual void getF3Pic(WindowCImage& image) = 0;
};