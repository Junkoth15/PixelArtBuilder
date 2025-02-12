#include "StringReader.h"
using namespace std;
using namespace cv;

StringReader::StringReader(shared_ptr<const SearchLetter> letter_searcher):
	letter_searcher(letter_searcher)
{
}

string StringReader::readString(const Mat& img, Scalar font_color, bool from_left_top)const
{
	string result;
	//图片二值化处理
	Mat gray_img = BGR2GRAY(img, font_color);

	//cout << "StringReader::readString" << endl;
	//imshow("", gray_img);
	//waitKey();

	int x, y = 0;
	x = from_left_top ? 0 : gray_img.cols - 1;
	auto width_vec = letter_searcher->getAllLetterWidth();
	while (true)
	{
		char ch;
		bool success = false;
		for (auto width : width_vec) {
			Rect rect;
			//注意图片的空间是否还足够
			if (from_left_top) {
				if (gray_img.cols - x < width) continue;
				rect = Rect(x, y, width, gray_img.rows);
			}
			else {
				if (x + 1 < width) continue;
				rect = Rect(x - width + 1, y, width, gray_img.rows);
			}
			//if (rect.x < 0 || rect.x + rect.width >= gray_img.cols) {
			//	continue;
			//}
			if (letter_searcher->searchLetter(gray_img(rect), ch)) {
				//若识别成功，则x要增加或减少width
				success = true;
				x += from_left_top?width:-width;
				break;
			}
		}
		//字符识别失败，退出
		if (!success) {
			break;
		}
		//throw exception("WinReader::readLine:字符读取失败!");
		//连续两个空格，退出
		if (result.length() > 1 && result[result.length() - 1] == ' ' && result[result.length() - 2] == ' ')
			break;
		//否则字符读取成功，加入字符串
		result.push_back(ch);
	}

	//去除字符串末尾的空格
	if (result.length() > 0) {
		int count = 0;//记录字符串末尾空格数量
		for (int i = 0; i < result.length(); i++) {
			if (result[result.length() - 1 - count] == ' ')
				count++;
			else
				break;
		}
		//去除字符串末尾的空格
		result.resize(result.length() - count);
	}

	//若从右往左读，要翻转字符串
	if (!from_left_top) {
		reverse(result.begin(), result.end());
	}
	return result;
}

Mat StringReader::BGR2GRAY(const Mat& img, Scalar font_color)const
{
	Mat tmp_mat = img.clone();
	cvtColor(tmp_mat, tmp_mat, COLOR_BGR2GRAY);
	inRange(tmp_mat, font_color, font_color, tmp_mat);
	return tmp_mat;
}
