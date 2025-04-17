#include "TaskSpliter.h"

int TaskSpliter::getNextEndRow(const ColorItemMat& mat, int begin_row, int max_row,
	shared_ptr<const CanBuildMapPic> builder, map<string, int>& needed_item_map)
{
	map<string, int> item_map;
	int now_row = begin_row;
	int result = begin_row;
	while (now_row <= max_row) {
		addRowToItemMap(mat,now_row, item_map);
		auto actual_map = idealMapToActualMap(item_map);
		//����������
		if (testAddToPackage(builder,actual_map)) {
			now_row++;
		}
		//���������£��򳷻أ�Ȼ��ֻ�ܽ�����һ�е���һ��
		else {
			eraseRowFromItemMap(mat,now_row, item_map);
			result = now_row - 1;
			needed_item_map = idealMapToActualMap(item_map);
			return result;  
		}
	}
	//begin_line����max_line�������£�˵������һֱ���쵽ĩβ
	result = max_row;
	needed_item_map = idealMapToActualMap(item_map);
	return result;
}

void TaskSpliter::addRowToItemMap(const ColorItemMat& mat, int row, map<string, int>& item_map)
{
	for (auto item : mat.mat[row]) {
		string item_name = item.name;
		if (item_map.count(item_name)) {
			item_map[item_name]++;
		}
		else {
			item_map[item_name] = 1;
		}
	}
}

void TaskSpliter::eraseRowFromItemMap(const ColorItemMat& mat, int row, map<string, int>& item_map)
{
	for (auto& item : mat.mat[row]) {
		string item_name = item.name;
		item_map[item_name]--;
		if (item_map[item_name] == 0) {
			item_map.erase(item_name);
		}
	}
}

bool TaskSpliter::testAddToPackage(shared_ptr<const CanBuildMapPic> builder, const map<string, int>& item_map)
{
	return builder->testAddItemToPackage(item_map);
}

int TaskSpliter::countActualNum(int ori_num)
{
	//����������
	static auto group_counter = [](int num) {
		return ((num - 1) / 64 + 1);
	};

	//��Ʒ�ж�����
	//����ʣ��3*(n+1)����Ʒ��nΪ��Ʒԭ����
	ori_num += (group_counter(ori_num)+1)* 3;
	ori_num = 64 * group_counter(ori_num);
	return ori_num;
}

map<string, int> TaskSpliter::idealMapToActualMap(const map<string, int>& item_map)
{
	map<string, int> result = item_map;
	for (auto& pair : result) {
		pair.second = countActualNum(pair.second);
	}
	return result;
}
