#pragma once
#include"BuildLine.h"
#include"CanBuildMapPic.h"
class LineBuilder:public BuildLine
{
protected:
	//�����ʼzλ��
	int ori_z;
	shared_ptr<CanBuildMapPic> builder;
	vector<ColorItem> line;
public:
	LineBuilder(shared_ptr<CanBuildMapPic> builder);
	virtual ~LineBuilder() = default;
	// ͨ�� BuildLine �̳У��ڽ���ǰӦ���ɿͻ�������׼����
	void buildLine(const vector<ColorItem>& line, int max_index) override;

protected:
	//��line�ĵ�item_num�������������ϣ���0��ʼ
	virtual void getMCItemToHand(int index);
	//�ƶ������ʵ�λ��
	virtual void move();
	//���ݿ��򷽿��λ�þ�����һ��Ҫ�����ĸ����飨��1��ʼ��
	virtual int decideNextBlockIndex();
	//��ʼ��
	virtual void init();
	//��ʼ��z��λ��
	virtual void init_ori_z();
	//��ʼ������
	virtual void init_package();
	//�ŷ���
	virtual void putBlock();



};

