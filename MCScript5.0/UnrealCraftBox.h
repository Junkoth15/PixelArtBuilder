#pragma once
#include"Box.h"
/// <summary>
/// Ĭ��Ϊ54��Ĵ�����
/// </summary>
class UnrealCraftBox :
	public Box//������
{
public:
	static string lattice_pic_path;
private:
	static Mat lattice_pic;	//���ӵı���
	static Rect text_rect;	//���ӵ���������
	static Rect item_rect;	//���ӵ���Ʒ����
	static Rect lattice_rect;//��������
	static Scalar text_color;//������ɫ
	static POINT big_box_pos;//������λ��
	static POINT small_box_pos;//С����λ��
	static bool data_loaded;	//�����Ƿ��Ѽ���
	static void load();	//��������
public:
	UnrealCraftBox(BoxType type);
	// ͨ�� Box �̳�
	virtual void setBoxType(BoxType type)override;
	POINT getLatticeRelativeMidPos(int x, int y) const override;
	POINT getLatticeRelativePos(int x, int y) const override;
	Mat getLatticeBackgroundPic(int x, int y) const override;
	Rect getLatticeItemRect(int x, int y) const override;
	Rect getLatticeTextRect(int x, int y) const override;
	Rect getLatticeRect(int x, int y) const override;
	Scalar getLatticeTextColor(int x, int y) const override;

	// ͨ�� CloneAble �̳�
	shared_ptr<CloneAble> clone()const override;
};

