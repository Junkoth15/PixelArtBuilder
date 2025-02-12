#include "ColorItem.h"

ColorItem::ColorItem(int ID, string name, Scalar color) :
	ID(ID), name(name), color(color)
{
}

ColorItem::ColorItem() :
	ID(0), name(""), color(Scalar())
{
}
