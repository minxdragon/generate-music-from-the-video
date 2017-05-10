#include "images.h"
#include "general.h"

cv::Mat images::ResizeImage(cv::Mat ImageCaptureMat)
{

	double ImageRatio;				// 画像の縮小比率
	double ImageCols, ImageRows;	// 画像のタテヨコ

	ImageCols = ImageCaptureMat.cols;
	ImageRows = ImageCaptureMat.rows;

	if (ImageCols >= ImageRows)			// タテの方が大きいとき
	{
		ImageRatio = 400 / ImageCols;
	}
	else								// ヨコの方が大きいとき
	{
		ImageRatio = 400 / ImageRows;
	}

	//cv::Mat ImageCaptureResizedMat(ImageRows*ImageRatio, ImageCols*ImageRatio, ImageCpatureMat.type());		// リサイズ後の画像をいれるやつ
	cv::Mat ImageCaptureResizedMat;
	cv::resize(ImageCaptureMat, ImageCaptureResizedMat, cv::Size(), ImageRatio, ImageRatio);	// リサイズ


	return ImageCaptureResizedMat;
}

void images::UpdateImage(cv::Mat &NowImageCaptureMat, cv::Mat &PreImageCaptureMat, double &UsingFrame, const double PlusFrame, CvCapture* CaptureCV, int divide)
{
	general general;
	PreImageCaptureMat = NowImageCaptureMat.clone();	// 現在フレームを過去フレームにする
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
