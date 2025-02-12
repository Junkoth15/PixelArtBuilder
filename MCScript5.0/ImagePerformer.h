#pragma once
#include"NoImagePerformer.h"
#include"ReadAllInfoCImage.h"
#include"WinPlayerControl.h"
#include"ScanWindow.h"
class ImagePerformer:
	public NoImagePerformer,//接口
	public ReadAllInfoCImage,//接口
	public WinPlayerControl,//接口
	public ScanWindow//接口
{
};

