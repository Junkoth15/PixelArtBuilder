#pragma once
#include"NameSpace.h"
class BuildMapPic
{
public:
	virtual ~BuildMapPic() = default;
	//��ͼ������
	virtual void buildMapPic(Mat mat, int begin_line, int end_line) = 0;
};

