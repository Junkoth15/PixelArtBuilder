#include "MCItem.h"

bool operator==(const MCItem& item_1, const MCItem& item_2)
{
    return item_1.equal(item_2);
}

MCItem::MCItem(const Mat& image, string name, int stacking_limit) :
    image(image.clone()),
    name(name),
    stacking_limit(stacking_limit)
{
}

MCItem::MCItem(const MCItem& item) :
    image(item.image.clone()),
    name(item.name),
    stacking_limit(item.stacking_limit)
{
}

MCItem::MCItem() :
    image(Mat()),
    name(""),
    stacking_limit(0)
{
}

MCItem& MCItem::operator=(const MCItem& item)
{
    image = item.image.clone();
    name = item.name;
    stacking_limit = item.stacking_limit;
    return *this;
}

bool MCItem::equal(const MCItem& item) const
{
    return name == item.name;
}