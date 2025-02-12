#include "UnrealCraftBox.h"
#include"FileLoader.h"
using namespace cv;
using namespace std;
string UnrealCraftBox::lattice_pic_path = "./src/LatticeBackgroundPic/虚幻世界格子背景/box/box.png";
Mat UnrealCraftBox::lattice_pic;//格子的背景
Rect UnrealCraftBox::text_rect = Rect(11, 18, 24, 18);	//格子的文字区域
Rect UnrealCraftBox::item_rect = Rect(2, 2, 32, 32);	//物品区域
Rect UnrealCraftBox::lattice_rect = Rect(0, 0, 36, 36);//格子区域
Scalar UnrealCraftBox::text_color = Scalar(252, 252, 252);//文字颜色
POINT UnrealCraftBox::big_box_pos = {708,284};//大箱子位置
POINT UnrealCraftBox::small_box_pos = {708,338};//小箱子位置
bool UnrealCraftBox::data_loaded = false;	//数据是否已加载
void UnrealCraftBox::load()
{
	if (!data_loaded) {
		lattice_pic = FileLoader::loadMat(lattice_pic_path, ImreadModes::IMREAD_UNCHANGED);
		data_loaded = true;
	}
}
//格子的物品区域
UnrealCraftBox::UnrealCraftBox(BoxType box_type) :
	Box(box_type)
{
	load();
	setBoxType(box_type);
}

void UnrealCraftBox::setBoxType(BoxType type)
{
	switch (type)
	{
	case BoxType::BIG:setContainRelativePosition(big_box_pos.x, big_box_pos.y);
		break;
	case BoxType::SMALL:setContainRelativePosition(small_box_pos.x, small_box_pos.y);
		break;
	}
	Box::setBoxType(type);
}

POINT UnrealCraftBox::getLatticeRelativeMidPos(int x, int y) const
{
	POINT point;
	point.x = boxPos.x + (x - 1) * lattice_rect.width + lattice_rect.width / 2;
	point.y = boxPos.y + (y - 1) * lattice_rect.height + lattice_rect.height / 2;
	return point;
}

POINT UnrealCraftBox::getLatticeRelativePos(int x, int y) const
{
	POINT point;
	point.x = boxPos.x + (x - 1) * lattice_rect.width;
	point.y = boxPos.y + (y - 1) * lattice_rect.height;
	return point;
}

Mat UnrealCraftBox::getLatticeBackgroundPic(int x, int y) const
{
	return lattice_pic;
}

Rect UnrealCraftBox::getLatticeItemRect(int x, int y) const
{
	Rect result = item_rect;
	POINT p = getLatticeRelativePos(x, y);
	result.x += p.x;
	result.y += p.y;
	return result;
}

Rect UnrealCraftBox::getLatticeTextRect(int x, int y) const
{
	Rect result = text_rect;
	POINT p = getLatticeRelativePos(x, y);
	result.x += p.x;
	result.y += p.y;
	return result;
}

Rect UnrealCraftBox::getLatticeRect(int x, int y) const
{
	Rect result = lattice_rect;
	POINT p = getLatticeRelativePos(x, y);
	result.x += p.x;
	result.y += p.y;
	return result;
}

Scalar UnrealCraftBox::getLatticeTextColor(int x, int y) const
{
	return text_color;
}

shared_ptr<CloneAble> UnrealCraftBox::clone()const
{
	return make_shared<UnrealCraftBox>(*this);
}


