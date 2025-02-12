#include "UnrealCraftShopBox.h"
using namespace std;
using namespace cv;

UnrealCraftShopBox::UnrealCraftShopBox():
	UnrealCraftBox(BoxType::BIG)
{
    box.resize(5);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 9; j++) {
            box[i - 1].push_back(Lattice(j, i));
        }
    }
}

int UnrealCraftShopBox::getMaxRow() const
{
    return 5;
}

vector<POINT> UnrealCraftShopBox::getAllLatticePOINT() const
{
    static vector<POINT> points = {};
    if (points.empty()) {
        for (int y = 1; y <= 5; y++) {
            for (int x = 1; x <= 9; x++) {
                POINT p;
                p.x = x;
                p.y = y;
                points.push_back(p);
            }
        }
    }
    return points;
}

shared_ptr<CloneAble> UnrealCraftShopBox::clone()const
{
    return make_shared<UnrealCraftShopBox>(*this);
}
