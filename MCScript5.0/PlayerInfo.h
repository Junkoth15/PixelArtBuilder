#pragma once
#include"NameSpace.h"
struct PlayerPos
{
	float x = 0;
	float y = 0;
	float z = 0;
	string to_string() const;
};

struct BlockPos
{
	int x = 0;
	int y = 0;
	int z = 0;
	string to_string() const;
};

struct PlayerFacing
{
	float x = 0;
	float y = 0;
	string to_string() const;
};

struct BlockInfo {
	BlockPos block_pos;
	string block_name;
	string to_string() const;
};
//Íæ¼Ò×´Ì¬
struct PlayerStatus {
	bool is_F3_can_read = false;
	bool is_looking_at_block = false;
	PlayerPos player_pos;
	PlayerFacing facing_direction;
	BlockInfo block_info;
	string to_string() const;
};

