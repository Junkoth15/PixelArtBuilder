#pragma once
#include"Contain.h"
#include"NameSpace.h"
#include"PlayerInfo.h"
#include<atlimage.h>
class ReadAllInfoCImage
{
public:
	//���ݴ��ڵ�ͼƬ�������Ƿ��ŷ��飬���ص��Ļ�������
	virtual bool isLookingAtBlock(const CImage& f3_image) = 0;
	//���ݴ��ڵ�ͼƬ��ȡ�������������Ϣ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlock(const CImage& f3_image,BlockInfo& block_info) = 0;
	//��ȡ��������������֣�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܻ�false
	virtual bool getLookingAtBlockName(const CImage& f3_image, string& blockname) = 0;
	//��ȡ�����������λ�ã�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlockPos(const CImage& f3_image,BlockPos& block_pos) = 0;
public:
	//�ж�λ���Ƿ��ڿɶ�״̬
	virtual bool ifPosCanRead(const CImage& f3_image) = 0;
	//�жϷ����Ƿ��ڿɶ�״̬
	virtual bool ifDirectionCanRead(const CImage& f3_image) = 0;
	//���ݴ��ڵ�ͼƬ��ȡ��ҵ�λ�ã��п���ͼƬ�������������򷵻�false
	virtual bool getPlayerPosition(const CImage& f3_image,PlayerPos& player_pos) = 0;
	//���ݴ���ͼƬ��ȡ��ҵ��泯�����п��ܻ���������������false
	virtual bool getPlayerFacingDirection(const CImage& f3_image,PlayerFacing& player_facing) = 0;
public:
	virtual PlayerStatus getAllPlayerInfo(CImage img) = 0;

public:
	virtual void readContain(const CImage& f3_img, Contain& contain) = 0;
	virtual void readPackage(const CImage& img) = 0;
};

