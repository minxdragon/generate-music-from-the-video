#pragma once
#include "includes.h"

class colors
{
public:
	double CalcMax(int *Numbers, int Members);
	int CalcMaxforVector(std::vector<int> Numbers);
	double CalcMin(int *Numbers, int Members);
	cv::Mat CalcAve(cv::Mat ImageCaptureMat);
	double CalcAverage(cv::Mat ImageCaptureMat);
	double ConvertRGBtoHue(int *ImageBGR);
	int int_cmp(const int *a, const int *b);
	void FrequentColorInFrame(cv::Mat ImageCaptureMat, int *TopHSV);
	void FrequentColorforSymbal(cv::Mat ImageCaptureMat, std::vector <int> &SymbalsColor,std::vector<int> &SymbalsVal,int &SymbalPoints);
	void FrequentNumber(const int *TopHSV, int *TopColors);
	void CountNumber(const int *TopHSV, int *SumRYGLBVBW);
	int CalcSat(const int MaxRGB,const int MinRGB);
	double AveValinImage(const cv::Mat NowImageCaptureMat);
	colors();
	~colors();
};

