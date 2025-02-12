#include "ColorItemSet.h"

ColorItem ColorItemSet::getColorMCItem(Scalar color) const
{
	for (auto& item : item_set) {
		if (item.color == color) {
			return item;
		}
	}
	std::ostringstream oss;
	oss << color;
	throw exception(string("ColorItemSet::getColorMCItem:δ�ҵ���ɫ:"+oss.str()+'\n').c_str());
}
