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
		//每放置8个方块矫正下一个方块
		if (next_block_index % 8 == 7||next_block_index==0) {
			usleep(100);	//让方块完全更新其坐标再刷新
			next_block_index = decideNextBlockIndex();
		}
		else next_block_index++;
		//Logger::log("LineBuilder::buildLine", "next_block_index:" + std::to_string(next_block_index));

		if (next_block_index >max_index) {
			LogDebug("放置方块次数:" + std::to_string(count));
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
	//循环调整位置，直至位置正确
	float distance;
	while (true) {
		auto status = builder->getPlayerStatus();
		distance = status.block_info.block_pos.z- status.player_pos.z;
		if (status.is_looking_at_block) {
			//若看向方块，说明不需要向后和向右
			builder->move(MoveMode::BackEnd);
			//builder->move(MoveMode::RightEnd);
			//距离合适，结束
			if (distance > 1.5) {
				//结束位置调整
				builder->move(MoveMode::FrontEnd);
				return;
			}
			//距离太近，后退
			else builder->move(MoveMode::BackBegin);
		}
		else {
			//没看向方块，说明距离太远或者被怪物击退，向右并向前
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
