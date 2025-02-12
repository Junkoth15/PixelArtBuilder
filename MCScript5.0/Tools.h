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
	//������Ϸ����,x1y1x2y2Ϊ���δ�С��x3y3Ϊ����λ�ã������ڴ�СΪ0�����ͼ��Ϊnull��ע��ͬһ��image�����ܶ�ε��ô˺��������Ǹö�����ù�destory
	void getWindowPic(HWND window, CImage& image, int x1, int y1, int x2, int y2, int x3, int y3);
	//��ȡcimageͼ�����ص�rgbֵ
	Scalar getCImageRGB(const CImage& image, int x, int y);
	//��cimageת��Ϊmat
	Mat Cimage2Mat(const CImage& image);
	//Cimage�Ĳü�����������Ҫ�ֶ�����ͼƬ����
	void cutCimage(CImage& dst, const CImage& src, int width, int height, int x, int y);
	//��ȡ�ļ���������ͼƬ���ļ���
	vector<string> readAllPicNames(string folder_path);
	//����ͼƬ��ͨ������ȡͼƬĳ�������ɫ
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

