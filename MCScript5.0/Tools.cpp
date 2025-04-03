#include<Windows.h>
#include<fstream>
#include "Tools.h"
#include<filesystem>
using namespace cv;
using namespace std;

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
static void HighPrecisionSleep(int milliseconds) {
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);  // 设置为硬件支持的最小周期

	Sleep(milliseconds);

	timeEndPeriod(tc.wPeriodMin);
}

void usleep(int militime)
{
	HighPrecisionSleep(militime);

	//static TimeCounter tc;
	//static int threshold_num=30;//阈值
	//if (militime <= 0) return;
	//if (militime <= threshold_num) {
	//	tc.begin();
	//	while (tc.end() < militime);
	//}
	////若休眠超过阈值，则优先使用大休眠，一般误差不会超过阈值
	//if (militime > threshold_num) {
	//	tc.begin();
	//	Sleep(militime - threshold_num);
	//	militime -= tc.end();
	//	usleep(militime);
	//}


	//if (militime <= 0) return;
	//LARGE_INTEGER tick;
	//LARGE_INTEGER begintime, endtime;
	//QueryPerformanceFrequency(&tick);
	//QueryPerformanceCounter(&begintime);
	//while (true)
	//{
	//	QueryPerformanceCounter(&endtime);
	//	if ((double)(endtime.QuadPart - begintime.QuadPart) / tick.QuadPart * 1000 > militime)
	//	{
	//		return;
	//	}
	//}
}

bool setClipbar(string str)
{
	//const char* data = str.c_str();
	//int contentSize = strlen(data) + 1;
	//HGLOBAL hMemory; LPTSTR lpMemory;
	//if (!OpenClipboard(NULL)) return false;/* 打开剪切板 */
	//if (!EmptyClipboard()) return false; /* 清空剪切板 */
	//if (!(hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize))) return false;/* 对剪切板分配内存 */
	//if (!(lpMemory = (LPTSTR)GlobalLock(hMemory))) return false;/* 锁定内存区域 */
	//memcpy_s(lpMemory, contentSize, data, contentSize);    /* 复制数据到内存区域 */
	//GlobalUnlock(hMemory);                                 /* 解除内存锁定 */
	//if (!SetClipboardData(CF_TEXT, hMemory)) return false;      /* 设置剪切板数据 */
	//CloseClipboard();/* 关闭剪切板 */
	//return true;


	CString strSource = string2CString(str);
	if (::OpenClipboard(NULL))
	{
		int buff_size = strSource.GetLength();
		CStringW strWide = CStringW(strSource);
		int nLen = strWide.GetLength();
		HANDLE clipbuffer;
		char* buffer;
		::EmptyClipboard();
		clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, (nLen + 1) * 2);
		buffer = (char*)::GlobalLock(clipbuffer);
		memset(buffer, 0, (nLen + 1) * 2);
		memcpy_s(buffer, nLen * 2, strWide.GetBuffer(0), nLen * 2);
		strWide.ReleaseBuffer();
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_UNICODETEXT, clipbuffer);
		::CloseClipboard();
	}
	return FALSE;


}

string CString2string(CString str)
{
	/*USES_CONVERSION;
	return W2A(str);*/
	return string(CT2A(str.GetString()));
}

CString string2CString(string str)
{
	return CString(str.c_str());
}

bool searchWindow(string sub_name, HWND& hwnd, string& name)
{
	CString w_sub_name = string2CString(sub_name);
	HWND hd = GetDesktopWindow();        //得到桌面窗口
	hd = GetWindow(hd, GW_CHILD);        //得到屏幕上第一个子窗口
	wchar_t s[200] = {};
	while (hd != NULL)                    //循环得到所有的子窗口
	{
		memset(s, 0, 200);
		GetWindowTextW(hd, s, 200);
		CString str(s);
		if (str.Find(w_sub_name) != -1) {
			hwnd = hd;
			name = CString2string(str);
			return true;
		}
		hd = GetNextWindow(hd, GW_HWNDNEXT);
	}
	return false;
}

string POINTTostring(POINT p)
{
	return "X:"+to_string(p.x)+" "+"Y:"+to_string(p.y);
}

string boolTostr(bool b)
{
	return b?"true":"false";
}

void imageHandle::getWindowPic(HWND window, CImage& image, int x1, int y1, int x2, int y2, int x3, int y3)
{
	HDC hDc = NULL;
	HWND hWnd = window;
	hWnd = (hWnd == NULL) ? GetDesktopWindow() : hWnd; //判断窗口句柄是否为NULL,如果为NULL则默认获取桌面DC
	hDc = GetDC(hWnd); //获取DC

	if (hDc == NULL) return;
	int bitOfPix = GetDeviceCaps(hDc, BITSPIXEL); //获取DC像素的大小

	//cout << "getWindowPic-1\n";
	image.Create(x2 - x1, y2 - y1, bitOfPix); //为图像类创建与窗口DC相同大小的DC

	//cout << "getWindowPic0\n";
	if (!image.IsNull()) {

		//cout << "getWindowPic1\n";
		BitBlt(image.GetDC(), x1, y1, x2, y2, hDc, x3, y3, SRCCOPY); //将窗口DC图像复制到image
		//cout << "getWindowPic2\n";

		image.ReleaseDC(); //释放DC
		ReleaseDC(hWnd, hDc); //释放DC资源
	}
	return;
}

Scalar imageHandle::getCImageRGB(const CImage& image, int x, int y)
{
	if (image.IsNull())
	{
		return {};
	}
	Scalar color;

	uchar* pRealData = (uchar*)image.GetBits();
	int _nPit = image.GetPitch();
	int bitCount = image.GetBPP() / 8;

	color[0] = *(pRealData + _nPit * y + x * bitCount);
	color[1] = *(pRealData + _nPit * y + x * bitCount + 1);
	color[2] = *(pRealData + _nPit * y + x * bitCount + 2);
	return color;
}

Mat imageHandle::Cimage2Mat(const CImage& image)
{
	if (image.IsNull()) {
		return {};
	}

	int width = image.GetWidth();
	int height = image.GetHeight();
	int pitch = image.GetPitch();
	int channels = image.GetBPP() / 8;

	Mat mat(height, width, CV_8UC(channels));
	uchar* imgData = (uchar*)(image.GetBits());

	for (int y = 0; y < height; ++y) {
		uchar* row = mat.ptr<uchar>(y);
		memcpy(row, imgData + y * pitch, width * channels);
	}

	return mat;
}

void imageHandle::cutCimage(CImage& dst, const CImage& src, int width, int height, int x, int y)
{
	dst.Create(width, height, src.GetBPP());
	src.BitBlt(dst.GetDC(), 0, 0, width, height, x, y, SRCCOPY);
	dst.ReleaseDC();
}

vector<string> imageHandle::readAllPicNames(string folder_path)
{
	if (!filesystem::exists(folder_path)) {
		throw exception(string("readAllPicNames:不存在该路径" + folder_path).c_str());
	}

	String pattern = folder_path + "/*.png";	//文件名模板
	vector<string> img_path;//找到的图片路径string格式
	vector<cv::String> fn;//找到的图片路径String格式
	glob(pattern, fn, false);
	size_t count = fn.size(); //number of png files in images folder
	for (size_t i = 0; i < count; i++)
	{
		img_path.push_back(fn[i]);
	}
	return img_path;
}

Scalar imageHandle::getColor(const Mat& mat, int y, int x)
{
	Scalar color;
	switch (mat.channels())
	{
	case 1:color = mat.at<uchar>(y, x); break;
	case 3:color = mat.at<Vec3b>(y, x); break;
	case 4:color = mat.at<Vec4b>(y, x); color[3] = 0; break;
	default:break;
	}
	return color;
}

void imageHandle::saveMat(string path,const Mat& mat)
{
	Mat image=mat.clone();
	if (mat.channels() == 4) {
		cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
	}
	cv::imwrite(path, image);
}

void ThrowException::throwException(string func_name, string describe)
{
	string result = func_name +':'+ describe + '\n';
	throw exception(result.c_str());
}