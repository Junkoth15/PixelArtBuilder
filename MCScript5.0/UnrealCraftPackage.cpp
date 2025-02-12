#include "UnrealCraftPackage.h"
#include<exception>
#include"FileLoader.h"
using namespace cv;
using namespace std;
string UnrealCraftPackage::common_lattice_pic_path = "./src/LatticeBackgroundPic/���������ӱ���/package/package.png";
string UnrealCraftPackage::other_lattice_pic_path = "./src/LatticeBackgroundPic/���������ӱ���/package/others.png";
POINT UnrealCraftPackage::commonRowPos[4] = { {0,0},{0,36},{0,72},{0,116} };
Mat UnrealCraftPackage::package_lattice_pic;	//���ӵı���
Mat UnrealCraftPackage::others_lattice_pic;	//���������ı���
Rect UnrealCraftPackage::text_rect = Rect(11, 18, 24, 18);	//���ӵ���������
Rect UnrealCraftPackage::item_rect = Rect(2, 2, 32, 32);	//���ӵ���Ʒ����
Rect UnrealCraftPackage::lattice_rect = Rect(0, 0, 36, 36);//��������
Scalar UnrealCraftPackage::text_color=Scalar(252,252,252);//������ɫ
bool UnrealCraftPackage::data_loaded = false;//�����Ƿ��Ѽ���

void UnrealCraftPackage::load()
{
    if (!data_loaded) {
        package_lattice_pic = FileLoader::loadMat(common_lattice_pic_path, ImreadModes::IMREAD_UNCHANGED);
        others_lattice_pic = FileLoader::loadMat(other_lattice_pic_path, ImreadModes::IMREAD_UNCHANGED);
        data_loaded = true;
    }
}

UnrealCraftPackage::UnrealCraftPackage()
{
    load();
    setPackageStatus(PackageStatus::COMMON);
}

void UnrealCraftPackage::setPackageStatus(PackageStatus open_type)
{
    status = open_type;
    switch (open_type)
    {
    case PackageStatus::COMMON:    //���ñ������λ��
        setContainRelativePosition(708, 472);
        break;
    case PackageStatus::USE_BIG_BOX:
        setContainRelativePosition(708, 526);
        break;
    case PackageStatus::USE_SMALL_BOX:
        setContainRelativePosition(708, 472);
        break;
    default:
        break;
    }
}


Mat UnrealCraftPackage::getLatticeBackgroundPic(int x, int y) const
{
    switch (status)
    {
    case PackageStatus::COMMON:return package_lattice_pic;
        break;
    case PackageStatus::USE_BIG_BOX:return others_lattice_pic;
        break;
    case PackageStatus::USE_SMALL_BOX:return others_lattice_pic;
        break;
    default:
        break;
    }
    return package_lattice_pic;
}

Rect UnrealCraftPackage::getLatticeTextRect(int x, int y) const
{
    Rect result = text_rect;
    POINT p = getLatticeRelativePos(x, y);
    result.x += p.x;
    result.y += p.y;
    return result;
}

Rect UnrealCraftPackage::getLatticeItemRect(int x, int y) const
{
    Rect result = item_rect;
    POINT p = getLatticeRelativePos(x, y);
    result.x += p.x;
    result.y += p.y;
    return result;
}

Rect UnrealCraftPackage::getLatticeRect(int x, int y) const
{
    Rect result = lattice_rect;
    POINT p = getLatticeRelativePos(x, y);
    result.x += p.x;
    result.y += p.y;
    return result;
}

Scalar UnrealCraftPackage::getLatticeTextColor(int x, int y) const
{
    return text_color;
}

shared_ptr<CloneAble> UnrealCraftPackage::clone()const
{
    return make_shared<UnrealCraftPackage>(*this);
}

POINT UnrealCraftPackage::getLatticeRelativeMidPos(int x, int y) const
{
    POINT point = getLatticeRelativePos(x, y);
    point.x += lattice_rect.width / 2;
    point.y += lattice_rect.height / 2;

    return point;
}

POINT UnrealCraftPackage::getLatticeRelativePos(int x, int y) const
{

    POINT point;
    point.x = 0;
    point.y = 0;

    POINT package_pos = getContainRelativePos();

    if (1 <= y && y <= 4) {
        point.x = package_pos.x + commonRowPos[y - 1].x + (x - 1) * lattice_rect.width;
        point.y = package_pos.y + commonRowPos[y - 1].y;
    }
    else {
        throw std::exception("����yֵ����!");
    }
    return point;
}