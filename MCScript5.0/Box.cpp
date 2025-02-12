#include "Box.h"
using namespace std;
using namespace cv;
Box::Box(BoxType box_type) :
    box_type(box_type)
{
    box.resize(6);
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 9; j++) {
            box[i - 1].push_back(Lattice(j, i));
        }
    }
}

void Box::setBoxType(BoxType type)
{
    box_type = type;
}

int Box::getMaxRow() const
{
    switch (box_type)
    {
    case BoxType::BIG:return 6;
        break;
    case BoxType::SMALL:return 3;
        break;
    default:return 3;
        break;
    }
}


vector<POINT> Box::findItem(const MCItem& item) const
{
    vector<POINT> result;
    auto all_lattice_point = getAllLatticePOINT();

    for (auto point : all_lattice_point) {
        const Lattice& tmp_lattice = getLattice(point.x, point.y);
        if (tmp_lattice.judgeItemEqual(item)) {
            result.push_back(point);
        }
    }
    return result;
}

POINT Box::findFirstItem(const MCItem& item) const
{
    auto all_lattice_point = getAllLatticePOINT();
    for (auto point : all_lattice_point) {
        const Lattice& tmp_lattice = getLattice(point.x, point.y);
        if (tmp_lattice.judgeItemEqual(item)) {
            return point;
        }
    }
    return { 0,0 };
    //return result;
    //POINT result;
    //result.x = 0;
    //result.y = 0;
    //for (int i = 1; i <= 6; i++) {
    //    for (int j = 1; j <= 9; j++) {
    //        const Lattice& tmp_lattice = getLattice(j, i);
    //        if (tmp_lattice.judgeItemEqual(item)) {

    //            result.x = j;
    //            result.y = i;
    //            return result;
    //        }
    //    }
    //}
    //return result;
}

Lattice& Box::getLattice(int x, int y)
{
    if (1 <= x && x <= 9 && 1 <= y && y <= getMaxRow())
        return box[y - 1][x - 1];
    else
        throw exception("Box::getLattice:格子坐标错误!\n");
}

const Lattice& Box::getLattice(int x, int y) const
{
    if (1 <= x && x <= 9 && 1 <= y && y <= getMaxRow())
        return box[y - 1][x - 1];
    else
        throw exception("Box::getLattice:格子坐标错误!\n");
}


vector<POINT> Box::getAllLatticePOINT() const
{
    static vector<POINT> small;
    static vector<POINT> big;
    static bool init_finished = false;

    if (!init_finished) {
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 9; j++) {
                POINT tmp_point;
                tmp_point.x = j;
                tmp_point.y = i;
                small.push_back(tmp_point);
            }
        }
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= 9; j++) {
                POINT tmp_point;
                tmp_point.x = j;
                tmp_point.y = i;
                big.push_back(tmp_point);
            }
        }
        init_finished = true;
    }
    switch (box_type)
    {
    case BoxType::BIG:return big;
        break;
    case BoxType::SMALL:return small;
        break;
    }
}

void Box::clear()
{
    auto points = getAllLatticePOINT();
    for (auto point : points) {
        getLattice(point.x, point.y).eraseItem();
    }

    //for (int i = 1; i <= 6; i++) {
    //    for (int j = 1; j <= 9; j++) {
    //        box[i][j].eraseItem();
    //    }
    //}
}

string Box::getAllLatticeInfo()const
{
    string result;
    auto points = getAllLatticePOINT();
    for (int i = 0; i < points.size(); i++) {
        result += "|" + getLattice(points[i].x, points[i].y).getLatticeInfo();
        if (i % 9 == 8)
            result += "|\n";
    }
    return result;


    //string message;
    //for (int i = 1; i <= 6; i++) {
    //    message += "|";
    //    for (int j = 1; j <= 9; j++) {
    //        message += getLattice(j, i).getLatticeInfo();
    //        message += "|";
    //    }
    //    message += '\n';
    //}
    //return message;
}

void Box::changePosByWindowSizeType(int size_type)
{
    //switch (size_type)
    //{
    //case SIZE_1740_945:setContainRelativePosition(694, 280); break;
    //default:
    //    break;
    //}
}

bool Box::addItemByShift(const MCItem& item, int num)
{
    vector<POINT> same_item_points;
    vector<POINT> empty_points;
    auto all_points = getAllLatticePOINT();
    int useable_capacity = 0;
    for (auto p : all_points) {
        //遍历背包，把有空位的相同物品和空位置记录下来,若可用空间已经够了就不用加了
            //相同物品
        Lattice& lattice = getLattice(p.x, p.y);
        if (lattice.judgeItemEqual(item) && !lattice.isFull() && useable_capacity < num) {
            same_item_points.push_back(p);
            useable_capacity += item.stacking_limit - lattice.getNum();
        }
        //空位置
        if (lattice.isEmpty() && useable_capacity < num) {
            empty_points.push_back(p);
            useable_capacity += item.stacking_limit;
        }
    }

    //空间不足，无法分配
    if (useable_capacity < num) {
        return false;
    }

    //先分配相同物品的空间
    for (POINT point : same_item_points) {
        Lattice& tmp_lattice = getLattice(point.x, point.y);
        int reduce_num = min(num, item.stacking_limit - tmp_lattice.getNum());
        tmp_lattice.addItem(item, reduce_num);
        num -= reduce_num;
        if (num == 0) {
            break;
        }
    }

    //再分配空物品的空间
    if (num != 0) {
        for (POINT point : empty_points) {
            Lattice& tmp_lattice = getLattice(point.x, point.y);
            int reduce_num = min(num, item.stacking_limit - tmp_lattice.getNum());
            tmp_lattice.addItem(item, reduce_num);
            num -= reduce_num;
            if (num == 0) {
                break;
            }
        }
    }
    return true;

    //for (int i = 1; i <= 6; i++) {
    //    for (int j = 1; j <= 9; j++) {
    //        //遍历背包，把有空位的相同物品和空位置记录下来,若可用空间已经够了就不用加了
    //        //相同物品
    //        Lattice& lattice = getLattice(j, i);
    //        if (lattice.judgeItemEqual(item) && !lattice.isFull() && useable_capacity < num) {
    //            POINT tmp_point;
    //            tmp_point.x = j;
    //            tmp_point.y = i;
    //            same_item_points.emplace_back(tmp_point);
    //            useable_capacity += item.stacking_limit - lattice.getNum();
    //        }
    //        //空位置
    //        if (lattice.isEmpty() && useable_capacity < num) {
    //            POINT tmp_point;
    //            tmp_point.x = j;
    //            tmp_point.y = i;
    //            empty_points.emplace_back(tmp_point);
    //            useable_capacity += item.stacking_limit;
    //        }
    //    }
    //}

    ////空间不足，无法分配
    //if (useable_capacity < num) {
    //    return false;
    //}

    ////先分配相同物品的空间
    //for (POINT point : same_item_points) {
    //    Lattice& tmp_lattice = getLattice(point.x, point.y);
    //    int reduce_num = min(num, item.stacking_limit - tmp_lattice.getNum());
    //    tmp_lattice.addItem(&item, reduce_num);
    //    num -= reduce_num;

    //    if (num == 0) {
    //        break;
    //    }
    //}

    ////再分配空物品的空间
    //if (num != 0) {
    //    for (POINT point : empty_points) {
    //        Lattice& tmp_lattice = getLattice(point.x, point.y);
    //        int reduce_num = min(num, item.stacking_limit - tmp_lattice.getNum());
    //        tmp_lattice.addItem(&item, reduce_num);
    //        num -= reduce_num;

    //        if (num == 0) {
    //            break;
    //        }
    //    }
    //}
    //return true;
}

bool Box::testAddItemByShift(const MCItem& item, int num) const
{
    auto all_points = getAllLatticePOINT();
    int useable_capacity = 0;
    for (auto p : all_points) {
        //遍历背包，把有空位的相同物品和空位置记录下来,若可用空间已经够了就不用加了
            //相同物品
        auto& lattice = getLattice(p.x, p.y);
        if (lattice.judgeItemEqual(item) && !lattice.isFull()) {
            useable_capacity += item.stacking_limit - lattice.getNum();
        }
        //空位置
        if (lattice.isEmpty()) {
            useable_capacity += item.stacking_limit;
        }
        if (useable_capacity >= num) break;
    }

    //空间不足，无法分配
    if (useable_capacity >= num) {
        return true;
    }
    return false;
}

void Box::setContainRelativePosition(int x, int y)
{
    boxPos.x = x;
    boxPos.y = y;
}

POINT Box::getContainRelativePos() const
{
    return boxPos;
}

