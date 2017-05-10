#pragma once
#include "includes.h"

class optflow

{
public:
	void OptFlow(cv::Mat PreImageCaptureMat, cv::Mat NowImageCaptureMat, std::vector<cv::Point2f> &points, std::vector<cv::Point2f> &newpoints, std::vector<float> &errors, std::vector<unsigned char> &status);
	void LRUDCheck(const std::vector<float> errors, const std::vector<cv::Point2f> newpoints,const std::vector<cv::Point2f> points, int &AveAngle, int& LRUDN, int &AngleError);
	int CalcErrave(const std::vector<float> errors);
	void CalcErrsum(const std::vector<float> errors,int &errsum,int &pointsum);
	std::vector<int> CalcErrsumMaxFrames(const int *ChangePointErrsum, const int sabinumbers);
	cv::Mat DrawLines(cv::Mat NowImageCaptureMat, std::vector<float> errors, std::vector<cv::Point2f> points, std::vector<cv::Point2f> newpoints);

	
	optflow();
	~optflow();
};

