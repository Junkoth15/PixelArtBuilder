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
	void startFromFile();
private:
	void start(Mat mat,int begin_line,int end_line);
};

