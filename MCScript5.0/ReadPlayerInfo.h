#pragma once
#include"NameSpace.h"
#include"PlayerInfo.h"
//ֻ��ȡ�����Ϣ�����������Ϣ�Ϳ��򷽿���Ϣ
class ReadPlayerInfo
{
public:		//ͼƬ���ýӿ�
	//���ô�������ͼƬ
	virtual void analysisPic(const Mat& img)=0;
public:		//�����ȡ�ӿ�
	//���ݴ��ڵ�ͼƬ�������Ƿ��ŷ��飬���ص��Ļ�������
	virtual bool isLookingAtBlock() = 0;
	//���ݴ��ڵ�ͼƬ��ȡ�������������Ϣ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlock(BlockInfo& block_info) = 0;
	//��ȡ��������������֣�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܻ�false
	virtual bool getLookingAtBlockName(string& name) = 0;
	//��ȡ�����������λ�ã�Ӧ��֤���Զ�ȡ��ʶ��ʧ�ܷ���false
	virtual bool getLookingAtBlockPos(BlockPos& block_pos) = 0;
	//��ȡ���������Ϣ
	virtual PlayerStatus getAllPlayerInfo() = 0;
public:		//λ�ö�ȡ�ӿ�
	////�ж�λ���Ƿ��ڿɶ�״̬
	//virtual bool ifPosCanRead() = 0;
	////�жϷ����Ƿ��ڿɶ�״̬
	//virtual bool ifDirectionCanRead() = 0;
	virtual bool ifF3CanRead() = 0;
	//���ݴ��ڵ�ͼƬ��ȡ��ҵ�λ�ã��п���ͼƬ�������������򷵻�false
	virtual bool getPlayerPosition(PlayerPos& player_pos) = 0;
	//���ݴ���ͼƬ��ȡ��ҵ��泯�����п��ܻ���������������false
	virtual bool getPlayerFacing(PlayerFacing& player_facing) = 0;
};

