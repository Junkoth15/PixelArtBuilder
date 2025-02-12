#pragma once
#include"ReadPlayerInfo.h"
#include"ReadContain.h"
/// <summary>
/// 输入的都是原图
/// </summary>
class ReadAllInfo:
	public ReadPlayerInfo,
	public ReadContain
{
};