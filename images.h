#pragma once
#include "includes.h"

class images
{
public:
	cv::Mat ResizeImage(cv::Mat ImageCaptureMat);
	void UpdateImage(cv::Mat &NowImageCaptureMat, cv::Mat &PreImageCaptureMat, double &UsingFrame, const double PlusFrame, CvCapture* CaptureCV, int divide);
	void AveValinImage(const cv::Mat NowImageCaptureMat);
	images();
	~images();
};

