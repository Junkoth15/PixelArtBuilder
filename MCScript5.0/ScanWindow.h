#include"NameSpace.h"
class ScanWindow
{
public:
	//��ȡ���ڵ�ͼƬ
	virtual void getWindowPic(Mat& image) = 0;
	//��ȡ���ڵ�ָ�������ͼƬ
	virtual void getWindowPic(Mat& image, int width, int height, int left_x, int top_y) = 0;
	//��ȡF3�����ͼƬ
	virtual void getF3Pic(Mat& image) = 0;
};