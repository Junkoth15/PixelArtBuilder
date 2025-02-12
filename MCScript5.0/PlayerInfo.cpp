#include "PlayerInfo.h"
using namespace std;
string PlayerPos::to_string() const
{
	string result = "";
	result += "PlayerPos:";
	result += "x:"+std::to_string(x) + " ";
	result += "y:"+ std::to_string(y) + " ";
	result += "z:"+ std::to_string(z);
	return result;
}

string BlockPos::to_string() const
{
	string result;
	result += 
		"BlockPos:x:"+ std::to_string(x)
		+ " y:" + std::to_string(y)
		+ " z:" + std::to_string(z);
	return result;
}

string PlayerFacing::to_string()const
{
	string result = "";
	result += "PlayerFacing:";
	result += "x:" + std::to_string(x) + " ";
	result += "y:" + std::to_string(y);
	return result;
}

string BlockInfo::to_string()const
{
	string result = "";
	result += "BlockName:" + block_name+ "\n";
	result += block_pos.to_string();
	return result;
}

string PlayerStatus::to_string() const
{
	string result = "";
	result += "is_F3_can_read:";
	if (is_F3_can_read)	result += "true";
	else result += "false";
	result += "\n";

	result += "is_looking_at_block:";
	if (is_looking_at_block)	result += "true";
	else result += "false";
	
	if (is_F3_can_read) {
		result += "\n";
		result += player_pos.to_string() + '\n';
		result += facing_direction.to_string();
	}
	if (is_looking_at_block) {
		result += "\n";
		result += block_info.to_string();
	}
	return result;
}
