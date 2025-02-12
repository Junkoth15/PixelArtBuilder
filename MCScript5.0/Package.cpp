#include "Package.h"
using namespace cv;
using namespace std;

Package::Package()
{
    package.resize(4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            package[i].push_back(Lattice(j + 1, i + 1));
        }
    }
}

POINT Package::findFirsItemFirstFromRow4(const MCItem& item)const
{
    POINT point;
    point.x = 0;
    point.y = 0;
    //先在第四行找
    for (int j = 1; j <= 9; j++) {
        const Lattice& tmp_lattice = getLattice(j, 4);
        if (tmp_lattice.getItem().equal(item)) {
            point.x = j;
            point.y = 4;
            return point;
        }
    }

    //再在普通背包1~3行里找
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            const Lattice& tmp_lattice = getLattice(j, i);
            if (tmp_lattice.getItem().equal(item)) {
                point.x = j;
                point.y = i;
                return point;
            }
        }
    }
    return point;
}

void Package::exchangeItems(int first_x, int first_y, int second_x, int second_y)
{
    exchangeLatticesItem(getLattice(first_x, first_y), getLattice(second_x, second_y));
}


vector<POINT> Package::findItem(const MCItem& item) const
{
    vector<POINT> point_vector;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 9; j++) {
            const Lattice& tmp_lattice = getLattice(j, i);
            if (tmp_lattice.judgeItemEqual(item)) {
                POINT point;
                point.x = j;
                point.y = i;
                point_vector.push_back(point);
            }
        }
    }
    return point_vector;
}

POINT Package::findFirstItem(const MCItem& item) const
{
    POINT result_point;
    result_point.x = 0;
    result_point.y = 0;
    //先在普通背包里找
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 9; j++) {
            const Lattice& tmp_lattice = getLattice(j, i);
            if (tmp_lattice.judgeItemEqual(item)) {
                result_point.x = j;
                result_point.y = i;
                break;
            }
        }
    }
    return result_point;
}

Lattice& Package::getLattice(int x, int y)
{
    return package[y - 1][x - 1];
}

const Lattice& Package::getLattice(int x, int y) const
{
    return package[y - 1][x - 1];
}


vector<POINT> Package::getAllLatticePOINT() const
{
    static vector<POINT> result;
    static bool inited = false;
    if (!inited) {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 9; j++) {
                POINT tmp_point;
                tmp_point.x = j;
                tmp_point.y = i;
                result.push_back(tmp_point);
            }
        }
        inited = true;
    }

    return result;
}


void Package::changePosByWindowSizeType(int size_type)
{
  /*  switch (size_type)
    {
    case SIZE_1740_945:setContainRelativePosition(694, 306); break;
    default:
        break;
    }*/
}

void Package::clear()
{
    vector<POINT> package_points = getAllLatticePOINT();
    for (POINT point : package_points) {
        getLattice(point.x, point.y).eraseItem();
    }
}

string Package::getAllLatticeInfo() const
{
    string message;
    for (int i = 1; i <= 4; i++) {
        message += "|";
        for (int j = 1; j <= 9; j++) {
            message += getLattice(j, i).getLatticeInfo();
            message += "|";
        }
        message += '\n';
    }
    return message;
}

bool Package::addItemByShift(const MCItem& item, int num)
{
    vector<POINT> same_item_points;
    vector<POINT> empty_points;
    int stacking_limit = item.stacking_limit;
    int useable_capacity = 0;
    //背包是从下到上，从右到左的分配规则
    for (int i = 4; i >= 1; i--) {
        for (int j = 9; j >= 1; j--) {
            //若可用空间已经够了就不用加了
            //遍历背包，把有空位的相同物品和空位置记录下来
            Lattice& tmp = getLattice(j, i);
            if (tmp.judgeItemEqual(item) && !tmp.isFull() && useable_capacity < num) {
                POINT tmp_point;
                tmp_point.x = j;
                tmp_point.y = i;
                same_item_points.emplace_back(tmp_point);
                useable_capacity += stacking_limit - tmp.getNum();
            }

            if (tmp.isEmpty() && useable_capacity < num) {
                POINT tmp_point;
                tmp_point.x = j;
                tmp_point.y = i;
                empty_points.emplace_back(tmp_point);
                useable_capacity += stacking_limit;
            }
        }
    }

    //空间不足，无法分配
    if (useable_capacity < num) {
        return false;
    }

    //先分配相同物品的空间
    for (POINT point : same_item_points) {
        Lattice& tmp_lattice = getLattice(point.x, point.y);
        int reduce_num = min(num, stacking_limit - tmp_lattice.getNum());
        tmp_lattice.addItem(item, reduce_num);
        num -= reduce_num;

        if (num == 0) {
            break;
        }
    }

    //再分配空格子的空间
    if (num != 0) {
        for (POINT point : empty_points) {
            Lattice& tmp_lattice = getLattice(point.x, point.y);
            int reduce_num = min(num, stacking_limit - tmp_lattice.getNum());
            tmp_lattice.addItem(item, reduce_num);
            num -= reduce_num;
            if (num == 0) {
                break;
            }
        }
    }
    return true;
}

bool Package::testAddItemByShift(const MCItem& item, int num) const
{
    int stacking_limit = item.stacking_limit;
    int useable_capacity = 0;
    //背包是从下到上，从右到左的分配规则
    for (int y = 4; y >= 1; y--) {
        for (int x = 9; x >= 1; x--) {
            //若可用空间已经够了就不用加了
            auto& tmp = getLattice(x, y);
            if (tmp.judgeItemEqual(item) && !tmp.isFull()) {
                useable_capacity += stacking_limit - tmp.getNum();
            }

            if (tmp.isEmpty()) {
                useable_capacity += stacking_limit;
            }
            if (useable_capacity >= num) break;
        }
        if (useable_capacity >= num) break;
    }

    //空间充足
    if (useable_capacity >= num) {
        return true;
    }
    return false;
}

POINT Package::getContainRelativePos() const
{
    return packagePos;
}

void Package::setPackageStatus(PackageStatus open_type)
{
    status = open_type;
}

PackageStatus Package::getPackageStatus()const
{
    return status;
}

void Package::setContainRelativePosition(int x, int y)
{
    packagePos.x = x;
    packagePos.y = y;
}