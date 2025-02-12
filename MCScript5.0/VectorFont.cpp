#include "VectorFont.h"
using namespace std;

bool VectorFont::searchLetter(const Mat& mat, char& ch)const
{
	//cv::imshow("", mat);
	//cv::waitKey();

	for (int i = 0; i < font.size(); i++) {
		//获取字体图片
		const Letter& letter = font[i];
		const Mat& latter_img = letter.pic;
		/*cv::imshow("param", mat);
		cv::imshow("latter", latter_img);
		cv::waitKey();*/

		//cout << mat << endl;
		//cout << "----------------------" << endl;
		//cout << latter_img << endl;
		//system("pause");


		//若剩余图片尺寸不对，跳过此次识别
		if (mat.cols != latter_img.cols || mat.rows != latter_img.rows) {
			continue;
		}

		//标识是否识别成功的bool值
		bool identify_success = true;
		for (int dy = 0; dy < latter_img.rows; dy++) {
			for (int dx = 0; dx < latter_img.cols; dx++) {
				//比较像素
				if (mat.at<uchar>(dy, dx) != latter_img.at<uchar>(dy, dx)) {
					identify_success = false;
					break;
				}
			}
			if (!identify_success)	break;
		}
		//识别成功，返回结果
		if (identify_success) {
			ch = letter.ch;
			return true;
		}
	}
	//识别失败，返回0
	return false;
}

vector<int> VectorFont::getAllLetterWidth() const
{
	return all_letter_width;
}

int VectorFont::getLetterHeight() const
{
	return letter_height;
}