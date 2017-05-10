#include "optflow.h"
#include "includes.h"
#include "colors.h"
#include <iostream>
#include <algorithm>
#include <functional>

optflow::optflow()
{
}


optflow::~optflow()
{
}

void optflow::OptFlow(cv::Mat PreImageCaptureMat, cv::Mat NowImageCaptureMat, std::vector<cv::Point2f> &points, std::vector<cv::Point2f> &newpoints, std::vector<float> &errors, std::vector<unsigned char> &status)
{
	// �����p�Ɍ��݂ƑO�̉摜�̃O���[�摜��p��
	cv::Mat PreImageCaptureMatGray;											// �O�t���[���̃O���[�摜�i�I�v�e�B�J���t���[�p�j
	cvtColor(PreImageCaptureMat, PreImageCaptureMatGray, CV_RGB2GRAY);
	cv::Mat NowImageCaptureMatGray;											// ���݃t���[���̃O���[�摜�i�I�v�e�B�J���t���[�p�j
	cvtColor(NowImageCaptureMat, NowImageCaptureMatGray, CV_RGB2GRAY);

	// �����_��T��
	std::vector<cv::KeyPoint> keypoints;		// �����_
	cv::GoodFeaturesToTrackDetector detector(100, 0.05, 3);	// �����_�̒T����������
	detector.detect(PreImageCaptureMatGray, keypoints);		// �����_��T��

	// �T���������_�̌`���̕ύX
	for (std::vector<cv::KeyPoint>::iterator itk = keypoints.begin(); itk != keypoints.end(); ++itk)
	{
		points.push_back(itk->pt);
	}

	// �I�v�e�B�J���t���[���v�Z
	if (points.size() > 0)
	{
		cv::calcOpticalFlowPyrLK(PreImageCaptureMatGray, NowImageCaptureMatGray, points, newpoints, status, errors, cv::Size(21, 21), 3, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.05), 0);
	}
	return;

}

void optflow::LRUDCheck(const std::vector<float> errors, const std::vector<cv::Point2f> newpoints, const std::vector<cv::Point2f> points, int &AveAngle, int& LRUDN, int &AngleError)
{
	colors colors;
	int SumAngle = 0, UsePoints = 0;
	int SumLRUDN[5] = {}, SumErrorsLRUDN[5] = {};

	if (errors.size() > 0)
	{
		for (int a = 0; a < points.size(); a++)
		{
			if (errors[a]>10) {	// �P�O�ȏ�ړ����Ă���ꍇ�݂̂��v�Z
				double rad = atan2(points[a].y - newpoints[a].y, points[a].x - newpoints[a].x);	// ���W�A�����擾
				int RadAngle = rad * 180 / 3.14;		// �x���ɂȂ����i�����킩��₷������j
				if (RadAngle < 0)						// �O�ȉ��Ȃ�΂R�U�O�ɑ����Ē���
				{
					RadAngle = 360 + RadAngle;
				}

				if (RadAngle < 30 || RadAngle > 330)
				{
					if (newpoints[a].x > points[a].x)
					{
						SumLRUDN[1] += 1;
						SumErrorsLRUDN[1] += errors[a];
					}
					else
					{
						SumLRUDN[0] += 1;
						SumErrorsLRUDN[0] += errors[a];
					}
				}
				else if (RadAngle > 150 && RadAngle < 210)
				{
					if (newpoints[a].x > points[a].x)		// ���̒n�_���V�����n�_���E�Ȃ�
					{
						SumLRUDN[1] += 1;	// �E
						SumErrorsLRUDN[1] += errors[a];
					}
					else
					{
						SumLRUDN[0] += 1;	// ��
						SumErrorsLRUDN[0] += errors[a];
					}
				}
				else if (RadAngle >= 30 && RadAngle <= 150)
				{
					if (newpoints[a].y < points[a].y)		// ���̒n�_���V�����n�_����Ȃ�
					{
						SumLRUDN[2] += 1;
						SumErrorsLRUDN[2] += errors[a];
					}
					else
					{
						SumLRUDN[3] += 1;
						SumErrorsLRUDN[3] += errors[a];
					}
				}
				else if (RadAngle >= 210 && RadAngle <= 330)
				{
					if (newpoints[a].y < points[a].y)
					{
						SumLRUDN[2] += 1;
						SumErrorsLRUDN[2] += errors[a];
					}
					else
					{
						SumLRUDN[3] += 1;
						SumErrorsLRUDN[3] += errors[a];
					}
				}
				SumAngle += RadAngle;
				UsePoints++;
			}
		}
	}

	// �㉺���E�𔻒�
	double CalcedLRUDN;
	CalcedLRUDN = colors.CalcMax(SumLRUDN, 4);
	if (SumLRUDN[0] == 0 && SumLRUDN[1] == 0 && SumLRUDN[2] == 0 && SumLRUDN[3] == 0)
	{
		LRUDN = 4;
	}
	else
	{
		for (int a = 0; a < 4; a++)
		{
			if (static_cast<int>(CalcedLRUDN) == SumLRUDN[a])
			{
				LRUDN = a;
			}
		}
	}
	if (UsePoints > 0)
	{
		AveAngle = SumAngle / UsePoints;
		AngleError = (SumErrorsLRUDN[LRUDN]) / SumLRUDN[LRUDN];
	}
	return;
}

int optflow::CalcErrave(const std::vector<float> errors)
{
	int errsum = 0;
	int errave = 0;
	int errcount = 0;

	for (int a = 0; a < errors.size(); a++)
	{
		if (errors[a] > 10)
		{
			errsum += errors[a];
			errcount += 1;
		}
	}

	if (errsum > 0)
	{
		errave = errsum / errcount;
	}
	else
	{
		errave = 0;
	}

	return errave;
}


void optflow::CalcErrsum(const std::vector<float> errors, int &errsum, int &pointsum)
{
	if (errors.size() > 0)
	{
		for (int a = 0; a < errors.size(); a++)
		{
			if (errors[a]>10)		// �y�����ړ��������͂������߁A�ړ��������P�O�ȏ�̂��̂������v�Z����
			{
				errsum += errors[a];									// �����_�̍��v�ړ�����
				pointsum += 1;											// �v�Z�Ɏg�p���������_�̐�
			}
		}
	}
}


std::vector<int>  optflow::CalcErrsumMaxFrames(const int *ChangePointErrsum, const int sabinumbers)
{
	std::vector<int> ErrsumMaxFrame;
	int SortedChangePointErrsum[50] = {};
	for (int i = 0; i < sizeof(SortedChangePointErrsum) / sizeof(SortedChangePointErrsum[0]); i++) {
		SortedChangePointErrsum[i] = ChangePointErrsum[i];
	}

	std::sort(SortedChangePointErrsum, SortedChangePointErrsum + 50, std::greater<int>());
	for (int i = 0; i < sabinumbers; i++)
	{
		for (int j = 0; j < sizeof(SortedChangePointErrsum) / sizeof(SortedChangePointErrsum[0]); j++)
		{
			if (SortedChangePointErrsum[i] == ChangePointErrsum[j])
			{
				ErrsumMaxFrame.push_back(j);
			}
		}
	}

	std::sort(ErrsumMaxFrame.begin(), ErrsumMaxFrame.end());

	return ErrsumMaxFrame;
}

cv::Mat optflow::DrawLines(cv::Mat NowImageCaptureMat, std::vector<float> errors, std::vector<cv::Point2f> points, std::vector<cv::Point2f> newpoints)
{
	cv::Mat NowImageCaptureLinesMat;
	NowImageCaptureMat.copyTo(NowImageCaptureLinesMat);
	if (errors.size() > 0)
	{
		for (int a = 0; a < points.size(); a++)
		{
			if (errors[a]>10) cv::line(NowImageCaptureLinesMat, points[a], newpoints[a], cv::Scalar(0, 0, 200), 3, 4);
		}
	}

	return NowImageCaptureLinesMat;
}