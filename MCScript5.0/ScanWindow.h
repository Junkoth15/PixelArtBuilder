#include<atlimage.h>
class ScanWindow
{
public:
	typedef CImage WindowCImage;
public:
	//��ȡ���ڵ�ͼƬ
	virtual void getWindowPic(WindowCImage& image) = 0;
	//��ȡ���ڵ�ָ�������ͼƬ
	virtual void getWindowPic(WindowCImage& image, int width, int height, int left_x, int top_y) = 0;
	//��ȡF3�����ͼƬ
	virtual void getF3Pic(WindowCImage& image) = 0;
};