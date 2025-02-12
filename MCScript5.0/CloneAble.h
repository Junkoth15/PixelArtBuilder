#pragma once
#include"NameSpace.h"
class CloneAble
{
public:
	virtual ~CloneAble() = default;
	virtual shared_ptr<CloneAble> clone() const = 0;
};

