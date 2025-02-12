#pragma once
class HandControl
{
public:
	virtual ~HandControl() = default;
	virtual int getHand() = 0;
	virtual void setHand(int hand) = 0;
	virtual void changeHand(int hand) = 0;
};

