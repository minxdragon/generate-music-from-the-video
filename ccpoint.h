#pragma once
#include "includes.h"

class ccpoint
{
public:
	void CCpointHue(int Hue, int PreHue, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &CheckPointNumbers, int &ErrinFrame);
	void CCpointStatus(std::vector<unsigned char> status, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &ChangePointNumbers, int &ErrinFrame);
	ccpoint();
	~ccpoint();
};

