#pragma once
#include"BuildMapPic.h"
#include"NoImagePerformer.h"
#include"NameSpace.h"
class MPBQuickStarter
{
public:
	static string config_path;
private:
	BuildMapPic* builder;
	NoImagePerformer* performer;
public:
	MPBQuickStarter(BuildMapPic* builder, NoImagePerformer* performer);
	void start();
};

