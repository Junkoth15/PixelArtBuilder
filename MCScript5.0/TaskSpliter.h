#pragma once
#include"SplitTask.h"
#include"ColorItemMat.h"
class TaskSpliter:public SplitTask
{
public:
	// ͨ�� SplitTask �̳У�row��0��ʼ
	int getNextEndRow(const ColorItemMat& mat, int begin_row, int max_row, 
		shared_ptr<const CanBuildMapPic> builder,map<string,int>& needed_item_map) override;
protected:
	//��һ�е���Ʒ��ӵ���Ʒͼ�У��д�0��ʼ
	void addRowToItemMap(const ColorItemMat& mat,int row, map<string, int>& item_map);
	//��һ�е���Ʒ����ɫ��Ʒͼ���Ƴ����д�0��ʼ
	void eraseRowFromItemMap(const ColorItemMat& mat,int row, map<string, int>& item_map);
	//���Խ���ɫ��Ʒͼ��ӵ�������
	bool testAddToPackage(shared_ptr<const CanBuildMapPic> builder,const map<string, int>& item_map);
	//����һ�ֲ��ϵ��������������������ʵ����
	int countActualNum(int ori_num);
	//����������ͼת��Ϊʵ������ͼ
	map<string, int> idealMapToActualMap(const map<string, int>& item_map);
};

