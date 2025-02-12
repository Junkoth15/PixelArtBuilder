#pragma once
#include<Windows.h>
#include<vector>
#include<string>
#include<opencv2/opencv.hpp>
#include"Lattice.h"
#include"MCItem.h"
#include"CloneAble.h"
/// <summary>
/// ������
/// �ṩ������������UI��Ϣ
/// �������ӡ�������λ����Ϣ��ͼ����Ϣ
/// </summary>
class Contain:
	public CloneAble
{
public:
	template<typename T>
	using vector = std::vector<T>;
	using string = std::string;
	using Mat = cv::Mat;
	using Rect = cv::Rect;
	using Scalar = cv::Scalar;

public:
	virtual ~Contain() = default;
	//�������������Ͻ�����ڴ��ڵ�λ��
	virtual void setContainRelativePosition(int x, int y) = 0;
	//���ݴ��ڴ�С����������λ��
	virtual void changePosByWindowSizeType(int size_type) = 0;
	//��shift�ķ�ʽ����Ʒ��������
	virtual bool addItemByShift(const MCItem& item, int num) = 0;
	//�������
	virtual void clear() = 0;
	//ͨ����Ż�ȡ����
	virtual Lattice& getLattice(int x, int y) = 0;
	//��ȡ���������λ��
	virtual POINT getContainRelativePos()const = 0;
	//��ȡ�������ĵĵ����λ��(����ڴ��ڵ�����)
	virtual POINT getLatticeRelativeMidPos(int x, int y)const = 0;
	//�õ��������Ͻ���Դ���λ��
	virtual POINT getLatticeRelativePos(int x, int y)const = 0;
	//������Ѱ����Ʒ�����ظ��ӵı������
	virtual vector<POINT> findItem(const MCItem& item)const = 0;
	//������Ѱ���ҵ��ĵ�һ����Ʒ
	virtual POINT findFirstItem(const MCItem& item)const = 0;
	//ͨ����Ż�ȡ����
	virtual const Lattice& getLattice(int x, int y)const = 0;
	//��ȡ�������и��ӵı��
	virtual vector<POINT> getAllLatticePOINT()const = 0;
	//��ȡ���ӵı���ͼƬ
	virtual Mat getLatticeBackgroundPic(int x, int y)const = 0;
	//��ȡĳ���ӵĸ������򣬰���λ�����С��Ϣ
	virtual Rect getLatticeRect(int x, int y)const = 0;
	//��ȡĳ���ӵ���Ʒ���򣬰���λ�����С��Ϣ
	virtual Rect getLatticeItemRect(int x, int y)const = 0;
	//��ȡĳ���ӵ���������λ�ã�����λ�����С��Ϣ
	virtual Rect getLatticeTextRect(int x, int y)const = 0;
	//��ȡ���и��ӵ���Ϣ
	virtual string getAllLatticeInfo()const = 0;
	//��ȡ�������ֵ���ɫ
	virtual Scalar getLatticeTextColor(int x, int y)const = 0;
	//������shift�ķ�ʽ����Ʒ����������������ķ���
	virtual bool testAddItemByShift(const MCItem& item, int num)const = 0;
};

