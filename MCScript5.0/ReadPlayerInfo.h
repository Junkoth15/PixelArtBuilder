#pragma once
#include"NameSpace.h"
#include"PlayerInfo.h"
class ReadPlayerInfo
{
public:
	//���ݴ��ڵ�ͼƬ�������Ƿ��ŷ��飬���ص��Ļ�������
	virtual bool isLookingAtBlock(const Mat& f3_image) = 0;
	//���ݴ��ڵ�ͼƬ��ȡ�������������Ϣ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlock(const Mat& f3_image,BlockInfo& block_info) = 0;
	//��ȡ��������������֣�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܻ�false
	virtual bool getLookingAtBlockName(const Mat& f3_image,string& name) = 0;
	//��ȡ�����������λ�ã�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlockPos(const Mat& f3_image,BlockPos& block_pos) = 0;
public:
	//�ж�λ���Ƿ��ڿɶ�״̬
	virtual bool ifPosCanRead(const Mat& image) = 0;
	//�жϷ����Ƿ��ڿɶ�״̬
	virtual bool ifDirectionCanRead(const Mat& image) = 0;
	//���ݴ��ڵ�ͼƬ��ȡ��ҵ�λ�ã��п���ͼƬ�������������򷵻�false
	virtual bool getPlayerPosition(const Mat& image,PlayerPos& player_pos) = 0;
	//���ݴ���ͼƬ��ȡ��ҵ��泯�����п��ܻ���������������false
	virtual bool getPlayerFacingDirection(const Mat& image, PlayerFacing& player_facing) = 0;
};

