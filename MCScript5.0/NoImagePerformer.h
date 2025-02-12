#pragma once
#include"KeyBoardControl.h"
#include"MouseControl.h"
#include"PlayerControl.h"
#include"WindowControl.h"
#include"NoImageBasicFunction.h"
#include"PackageControl.h"
#include"HandControl.h"
class NoImagePerformer:
	public KeyBoardControl,
	public MouseControl,
	public PlayerControl,
	public WindowControl,
	public NoImageBasicFunction,
	public PackageControl,
	public HandControl
{
};

