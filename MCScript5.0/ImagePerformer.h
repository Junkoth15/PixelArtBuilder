#pragma once
#include"NoImagePerformer.h"
#include"ReadAllInfoCImage.h"
#include"WinPlayerControl.h"
#include"ScanWindow.h"
#include"ReadPlayerInfo.h"
#include"ReadContain.h"
class ImagePerformer:
	public NoImagePerformer,//�ӿ�
	//public ReadAllInfoCImage,//�ӿ�
	public WinPlayerControl,//�ӿ�
	public ScanWindow,//�ӿ�
	public ReadPlayerInfo,//�ӿ�
	public ReadContain
{
public:
	virtual void readPackage(const Mat& mat)=0;
};

