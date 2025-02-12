#pragma once
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
#include"MCItem.h"
/// <summary>
/// �����о�����������Ŀ�������ڴ��������
/// </summary>
class Lattice
{
public:
	template<typename Content>
	using vector = std::vector<Content>;
	using string = std::string;
	using Mat = cv::Mat;
	using Rect = cv::Rect;
	template<typename Type>
	using shared_ptr = std::shared_ptr<Type>;
private:
	enum class LatticeStatus {
		HasKnownItem, Empty, Unknown
	};

public:
	static const MCItem emptyItem;
	static const MCItem unknownItem;
public:
	//���ӵ�x���
	int x;
	//���ӵ�y���
	int y;
private:
	//���Ӵ洢����Ʒ
	const MCItem* item_ptr;
	//�Ѵ洢����Ʒ����
	int num;
	//���ӵĴ洢״̬
	LatticeStatus status;

public:
	Lattice();
	//��������������ӵ�����
	Lattice(int x, int y);
	//Ϊ���������Ʒ���������Ƿ�������
	bool addItem(const MCItem& item, int num);
	//���ٸ�������Ʒ�������ز����Ƿ����
	bool removeItem(int num);
	//�Ƴ���������Ʒ
	void eraseItem();
	//������Ϊ��Ʒδ֪
	void setAsUnknown();
	//����һ�����ӽ�����Ʒ���������ص��ǲ��ᵼ�¸��ӵ��������ϢҲ������
	void exchangeItemWithLattice(Lattice& lattice);

	//�жϸ����Ƿ�δ֪
	bool isUnknown()const;
	//�жϸ����Ƿ�Ϊ��
	bool isEmpty()const;
	//�жϸ����Ƿ�����
	bool isFull()const;
	//�жϸ����Ƿ�����֪�Ķ���
	bool isHasKnownItem()const;
	//��ȡ��Ʒ��Ϣ
	const MCItem& getItem()const;
	//��ȡ�Ѵ洢����Ʒ����
	int getNum()const;
	//�ж�ĳ��Ʒ������ڵ���Ʒ�Ƿ���ͬ
	bool judgeItemEqual(const MCItem& item)const;
	//�ж�ĳ�������ڵ���Ʒ�Ƿ���ͬ
	bool judgeItemEqual(const Lattice& lattice)const;
	//��ȡ������Ϣ
	string getLatticeInfo()const;
};

//���������ӵ���Ʒ���������ص��ǲ��ᵼ�¸��ӵ��������ϢҲ������
void exchangeLatticesItem(Lattice& first, Lattice& second);
