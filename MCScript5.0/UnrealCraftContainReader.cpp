#include "UnrealCraftContainReader.h"
#include"StringReader.h"
#include"MCItemMapFactory.h"
#include"VectorFontFactory.h"
#include"UnrealCraftPerformerFile.h"
#include"Tools.h"
using namespace cv;

UnrealCraftContainReader::UnrealCraftContainReader():
	_str_reader(make_shared<StringReader>(VectorFontFactory::getFont(UnrealCraftPerformerFile::getFontPath()))),
	item_map(&MCItemMapFactory::getMCItemMap(UnrealCraftPerformerFile::getMCItemSetPath()))
{
}

bool UnrealCraftContainReader::isLatticeEmpty(const Mat& lattice_img, const Mat& lattice_background_pic)
{
	//�ȼ������Ƿ�����Ʒ
	//��־�Ƿ�Ϊ��
	bool isEmpty = true;
	//��־�Ѽ��������Ƿ�ȫ��
	bool match_success = true;

	//��ͼƬ������֮һ����ʼƥ�䣬��ֹ�·��ĸ���
	for (int dy = lattice_background_pic.rows / 3; dy < lattice_background_pic.rows; dy++) {
		for (int dx = 0; dx < lattice_background_pic.cols; dx++) {
			//���ӱ�������ɫ
			Scalar lattice_color = imageHandle::getColor(lattice_background_pic, dy, dx);
			//�����ͼƬ����ɫ
			Scalar image_color = imageHandle::getColor(lattice_img, dy, dx);
			//����������ɫ�������ɫ��һ����˵���ǿգ�����ѭ��
			/*if (!(lattice_color[0] == image_color[0]
				&& lattice_color[1] == image_color[1]
				&& lattice_color[2] == image_color[2])) {
				isEmpty = false;
				match_success = false;
				break;
			}*/
			if (!isSameColor(lattice_color,image_color)) {
				isEmpty = false;
				match_success = false;
				break;
			}
		}
		//��һ�����ز�һ���Ͳ��ñȽ���
		if (!match_success) {
			break;
		}
	}
	return isEmpty;
}

const MCItem& UnrealCraftContainReader::judgeLatticeItem(const Mat& item_img)
{
	const auto& map = item_map->item_map;
	//���ͼƬ
	string name;
	bool match_success;
	for (auto iter : map) {
		const Mat& item_pic = iter.second.image;
		//��־�Ƿ�ƥ��ɹ�
		match_success = true;
		//ֻ���һ���ͼƬ���ɣ���ƥ�䲻�ɹ���match_successֵΪfalse
		for (int dy = 0; dy < item_pic.rows / 2; dy++) {
			for (int dx = 0; dx < item_pic.cols; dx++) {
				//��Ʒ��ͼƬ����ɫ�������������ͨ��
				Scalar item_color = item_pic.at<Vec4b>(dy, dx);
				//ֻ�ȽϷ�͸������
				if (item_color[3] != 0) {
					//�����ͼƬ����ɫ
					Scalar image_color = imageHandle::getColor(item_img, dy, dx);
					/*if (!(item_color[0] == image_color[0]
						&& item_color[1] == image_color[1]
						&& item_color[2] == image_color[2])) {
						match_success = false;
						break;
					}*/
					if (!isSameColor(image_color,item_color)) {
						match_success = false;
						break;
					}
				}
			}
			if (!match_success) {
				break;
			}
		}
		//���ƥ��ɹ�����¼������
		if (match_success) {
			name = iter.first;
			break;
		}
	}

	//���ɹ�ƥ�䣬�򷵻ض�Ӧ��Ʒ��ƥ��ʧ���򷵻�δ֪��Ʒ
	if (match_success) {
		return item_map->item_map.at(name);
	}
	else {
		return Lattice::unknownItem;
	}
}

int UnrealCraftContainReader::judgeLatticeItemNum(const Mat& text_img, Scalar font_color)
{
	//����ƷͼƬƥ��ɹ�����ȡ����
	//�ü����ֵ������ͼƬ
	//��ȡ����ʱ�����ӵı߿������ֵ���ɫ��ͬ����������������Ҫ���⴦��

	////����ͼƬ���Ұױߺ͵װױ�
	text_img.col(text_img.cols - 1).setTo(Scalar(0, 0, 0));
	text_img.row(text_img.rows - 2).setTo(Scalar(0, 0, 0));
	text_img.row(text_img.rows - 1).setTo(Scalar(0, 0, 0));

	//��ʼ��ȡ
	string str=_str_reader->readString(text_img, font_color, false);
	int item_num = 0;
	//���ַ���Ϊ�գ�����Ʒ����Ϊ1
	if (str.empty()) {
		item_num = 1;
	}
	//������ַ���ת��Ϊ����
	else {
		item_num = stoi(str);
	}
	return item_num;
}

bool UnrealCraftContainReader::isSameColor(Scalar a, Scalar b)
{
	static double max_error = 3;
	double error = fabs(a[0] - b[0]) + fabs(a[1] - b[1]) + fabs(a[2] - b[2]);
	return error<=max_error;
}
