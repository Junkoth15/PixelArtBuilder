#pragma once
#include"Package.h"
/// <summary>
/// ��������ı���ʵ����
/// </summary>
class UnrealCraftPackage :
	public Package//������
{
public:
	static string common_lattice_pic_path;
	static string other_lattice_pic_path;
private:
	static Mat package_lattice_pic;	//���ӵı���
	static Mat others_lattice_pic;	//���������ı���
	static POINT commonRowPos[4];	//��ͨ����ÿ������ڱ�����λ��
	static Rect text_rect;	//���ӵ���������
	static Rect item_rect;	//���ӵ���Ʒ����
	static Rect lattice_rect;//��������
	static Scalar text_color;//������ɫ
	static bool data_loaded;//�����Ƿ��Ѽ���
	static void load();
private:
	//������״̬
	PackageStatus status;
public:
	/// <summary>
	/// �������米�����캯��
	/// </summary>
	/// <param name="lattice_pic">�������ӵı�����������Ʒ����߿�</param>
	UnrealCraftPackage();
	// ͨ�� Package �̳�
	//���ñ����򿪷�ʽ
	virtual void setPackageStatus(PackageStatus open_type) override;
	Mat getLatticeBackgroundPic(int x, int y) const override;
	virtual POINT getLatticeRelativeMidPos(int x, int y) const override;
	virtual POINT getLatticeRelativePos(int x, int y) const override;
	virtual Rect getLatticeTextRect(int x, int y)const override;
	virtual Rect getLatticeItemRect(int x, int y)const override;
	virtual Rect getLatticeRect(int x, int y) const override;
	Scalar getLatticeTextColor(int x, int y) const override;

	// ͨ�� CloneAble �̳�
	shared_ptr<CloneAble> clone()const override;
};

