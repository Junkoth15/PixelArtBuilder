#pragma once
#include<opencv2/opencv.hpp>
#include<atlimage.h>
#include<math.h>
#include<sys/timeb.h>
#include"Logger.h"
#include"Shower.h"
#include"MapCounter.h"
#define PI acos(-1)
using std::string;

void usleep(int militime);
bool setClipbar(string str);
string CString2string(CString str);
CString string2CString(string str);
bool searchWindow(string sub_name, HWND& hwnd, string& name);
string POINTTostring(POINT p);

namespace imageHandle {
	using namespace cv;
	using namespace std;
	//保存游戏截屏,x1y1x2y2为矩形大小，x3y3为矩形位置，若窗口大小为0则可能图像为null，注意同一个image对象不能多次调用此函数，除非该对象调用过destory
	void getWindowPic(HWND window, CImage& image, int x1, int y1, int x2, int y2, int x3, int y3);
	//获取cimage图像像素的rgb值
	Scalar getCImageRGB(const CImage& image, int x, int y);
	//把cimage转换为mat
	Mat Cimage2Mat(const CImage& image);
	//Cimage的裁剪，调用者需要手动销毁图片对象
	void cutCimage(CImage& dst, const CImage& src, int width, int height, int x, int y);
	//读取文件夹里所有图片的文件名
	vector<string> readAllPicNames(string folder_path);
	//根据图片的通道数读取图片某个点的颜色
	Scalar getColor(const Mat& mat, int y, int x);
}
enum class TimeCounterMode {
	SECOND, MILISECOND
};
class TimeCounter {
	timeb begin_time;
	timeb end_time;
	TimeCounterMode mode;
public:
	TimeCounter(TimeCounterMode mode=TimeCounterMode::MILISECOND);
	void begin();
	void setMode(TimeCounterMode mode);
	int end();
};

class ThrowException
{
public:
	static void throwException(string func_name, string describe);
};


string boolTostr(bool b);

