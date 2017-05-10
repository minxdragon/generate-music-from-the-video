#pragma once
#include "includes.h"

class general
{
public:
	void delay(int time);
	CvCapture* CvReadVideo(QString VideoNameQString);
	cv::Mat GetFramePict(int FrameNumber, CvCapture* CaptureCV);
	int CalcAverage(const int Sums, const int Points);
	void MakeTemp(const int MainMelodyNumber, const int NoteType, std::vector<MusicComp> &Meltemp);

	general();
	~general();
};

