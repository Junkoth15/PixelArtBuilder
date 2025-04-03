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
	//先检测格子是否有物品
	//标志是否为空
	bool isEmpty = true;
	//标志已检测的像素是否全对
	bool match_success = true;

	//从图片的三分之一处开始匹配，防止衣服的干扰
	for (int dy = lattice_background_pic.rows / 3; dy < lattice_background_pic.rows; dy++) {
		for (int dx = 0; dx < lattice_background_pic.cols; dx++) {
			//格子背景的颜色
			Scalar lattice_color = imageHandle::getColor(lattice_background_pic, dy, dx);
			//待检测图片的颜色
			Scalar image_color = imageHandle::getColor(lattice_img, dy, dx);
			//若有像素颜色与格子颜色不一样，说明非空，跳出循环
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
		//有一个像素不一样就不用比较了
		if (!match_success) {
			break;
		}
	}
	return isEmpty;
}

const MCItem& UnrealCraftContainReader::judgeLatticeItem(const Mat& item_img)
{
	const auto& map = item_map->item_map;
	//检测图片
	string name;
	bool match_success;
	for (auto iter : map) {
		const Mat& item_pic = iter.second.image;
		//标志是否匹配成功
		match_success = true;
		//只辨别一半的图片即可，若匹配不成功则match_success值为false
		for (int dy = 0; dy < item_pic.rows / 2; dy++) {
			for (int dx = 0; dx < item_pic.cols; dx++) {
				//物品集图片的颜色，这里必须用四通道
				Scalar item_color = item_pic.at<Vec4b>(dy, dx);
				//只比较非透明部分
				if (item_color[3] != 0) {
					//待检测图片的颜色
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
		//如果匹配成功，记录，跳出
		if (match_success) {
			name = iter.first;
			break;
		}
	}

	//若成功匹配，则返回对应物品，匹配失败则返回未知物品
	if (match_success) {
		return item_map->item_map.at(name);
	}
	else {
		return Lattice::unknownItem;
	}
}

int UnrealCraftContainReader::judgeLatticeItemNum(const Mat& text_img, Scalar font_color)
{
	//若物品图片匹配成功，读取数量
	//裁剪数字的区域的图片
	//读取格子时，箱子的边框与数字的颜色相同会产生混淆，因此需要特殊处理

	////消除图片的右白边和底白边
	text_img.col(text_img.cols - 1).setTo(Scalar(0, 0, 0));
	text_img.row(text_img.rows - 2).setTo(Scalar(0, 0, 0));
	text_img.row(text_img.rows - 1).setTo(Scalar(0, 0, 0));

	//开始读取
	string str=_str_reader->readString(text_img, font_color, false);
	int item_num = 0;
	//若字符串为空，则物品数量为1
	if (str.empty()) {
		item_num = 1;
	}
	//否则把字符串转换为数字
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
