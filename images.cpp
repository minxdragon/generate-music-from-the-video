#include "images.h"
#include "general.h"

cv::Mat images::ResizeImage(cv::Mat ImageCaptureMat)
{

	double ImageRatio;				// �摜�̏k���䗦
	double ImageCols, ImageRows;	// �摜�̃^�e���R

	ImageCols = ImageCaptureMat.cols;
	ImageRows = ImageCaptureMat.rows;

	if (ImageCols >= ImageRows)			// �^�e�̕����傫���Ƃ�
	{
		ImageRatio = 400 / ImageCols;
	}
	else								// ���R�̕����傫���Ƃ�
	{
		ImageRatio = 400 / ImageRows;
	}

	//cv::Mat ImageCaptureResizedMat(ImageRows*ImageRatio, ImageCols*ImageRatio, ImageCpatureMat.type());		// ���T�C�Y��̉摜���������
	cv::Mat ImageCaptureResizedMat;
	cv::resize(ImageCaptureMat, ImageCaptureResizedMat, cv::Size(), ImageRatio, ImageRatio);	// ���T�C�Y


	return ImageCaptureResizedMat;
}

void images::UpdateImage(cv::Mat &NowImageCaptureMat, cv::Mat &PreImageCaptureMat, double &UsingFrame, const double PlusFrame, CvCapture* CaptureCV, int divide)
{
	general general;
	PreImageCaptureMat = NowImageCaptureMat.clone();	// ���݃t���[�����ߋ��t���[���ɂ���
	UsingFrame = UsingFrame + (PlusFrame / divide);
	NowImageCaptureMat = general.GetFramePict(UsingFrame, CaptureCV);

	return;
}


images::images()
{
}


images::~images()
{
}
