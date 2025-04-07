#include "LineBuilder.h"
#include"Tools.h"

void LineBuilder::buildLine(const vector<ColorItem>& line, int max_index)
{
	this->line = line;
	init();
	int next_block_index = 0;

	int count = 0;
	while (true)
	{
		//ÿ����8�����������һ������
		if (next_block_index % 8 == 7||next_block_index==0) {
			usleep(100);	//�÷�����ȫ������������ˢ��
			next_block_index = decideNextBlockIndex();
		}
		else next_block_index++;
		//Logger::log("LineBuilder::buildLine", "next_block_index:" + std::to_string(next_block_index));

		if (next_block_index >max_index) {
			LogDebug("���÷������:" + std::to_string(count));
			return;
		}
		getMCItemToHand(next_block_index);
		move();
		putBlock();
		count++;
	}

}

void LineBuilder::getMCItemToHand(int item_index)
{
	builder->getItemToHand(line,item_index);
}

void LineBuilder::move()
{
	//ѭ������λ�ã�ֱ��λ����ȷ
	float distance;
	while (true) {
		auto status = builder->getPlayerStatus();
		distance = status.block_info.block_pos.z- status.player_pos.z;
		if (status.is_looking_at_block) {
			//�����򷽿飬˵������Ҫ��������
			builder->move(MoveMode::BackEnd);
			//builder->move(MoveMode::RightEnd);
			//������ʣ�����
			if (distance > 1.5) {
				//����λ�õ���
				builder->move(MoveMode::FrontEnd);
				return;
			}
			//����̫��������
			else builder->move(MoveMode::BackBegin);
		}
		else {
			//û���򷽿飬˵������̫Զ���߱�������ˣ����Ҳ���ǰ
			//builder->move(MoveMode::RightBegin);
			builder->move(MoveMode::FrontBegin);
		}
		usleep(50);
	}
}

int LineBuilder::decideNextBlockIndex()
{
	auto status = builder->getPlayerStatus();
	return ori_z - status.block_info.block_pos.z;
}

void LineBuilder::init()
{
	init_ori_z();
	//init_package();
}

void LineBuilder::init_ori_z()
{
	auto status = builder->getPlayerStatus();
	ori_z = status.block_info.block_pos.z;
	//Logger::log("LineBuilder::init_ori_z", "z:" + std::to_string(ori_z));
}

void LineBuilder::init_package()
{
	builder->openPackage();
	builder->refreshPackage();
	builder->closePackage();
}

void LineBuilder::putBlock()
{
	builder->putBlock();
}

LineBuilder::LineBuilder(shared_ptr<CanBuildMapPic> builder):
	ori_z(0),builder(builder)
{
	
}
