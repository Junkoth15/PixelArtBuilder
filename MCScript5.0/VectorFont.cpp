#include "VectorFont.h"
using namespace std;

bool VectorFont::searchLetter(const Mat& mat, char& ch)const
{
	//cv::imshow("", mat);
	//cv::waitKey();

	for (int i = 0; i < font.size(); i++) {
		//��ȡ����ͼƬ
		const Letter& letter = font[i];
		const Mat& latter_img = letter.pic;
		/*cv::imshow("param", mat);
		cv::imshow("latter", latter_img);
		cv::waitKey();*/

		//cout << mat << endl;
		//cout << "----------------------" << endl;
		//cout << latter_img << endl;
		//system("pause");


		//��ʣ��ͼƬ�ߴ粻�ԣ������˴�ʶ��
		if (mat.cols != latter_img.cols || mat.rows != latter_img.rows) {
			continue;
		}

		//��ʶ�Ƿ�ʶ��ɹ���boolֵ
		bool identify_success = true;
		for (int dy = 0; dy < latter_img.rows; dy++) {
			for (int dx = 0; dx < latter_img.cols; dx++) {
				//�Ƚ�����
				if (mat.at<uchar>(dy, dx) != latter_img.at<uchar>(dy, dx)) {
					identify_success = false;
					break;
				}
			}
			if (!identify_success)	break;
		}
		//ʶ��ɹ������ؽ��
		if (identify_success) {
			ch = letter.ch;
			return true;
		}
	}
	//ʶ��ʧ�ܣ�����0
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