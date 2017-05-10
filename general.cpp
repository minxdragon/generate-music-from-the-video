#include "general.h"
#include "includes.h"
#include "images.h"

void general::delay(int time)
{
	QTime dieTime = QTime::currentTime().addMSecs(time);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

CvCapture* general::CvReadVideo(QString VideoNameQString)
{
	std::string VideoNameString = VideoNameQString.toLocal8Bit();	// 作業するビデオのファイルパス(string)　変換用
	int len = VideoNameString.length();								// VideoStringの長さ（変換用）
	char *VideoNameChar = new char[len + 1];						// 作業するビデオのファイルパス（char）　CvCaptureに読み込ませる用
	memcpy(VideoNameChar, VideoNameString.c_str(), len + 1);		// char←string		作業するビデオのファイルパス
	CvCapture* CaptureCV = cvCaptureFromFile(VideoNameChar);		// 読み込んだファイル（CvCapture)

	delete[] VideoNameChar;			// newを使用したcharをメモリ上から削除

	return CaptureCV;
}

cv::Mat general::GetFramePict(int FrameNumber, CvCapture* CaptureCV)
{
	images images;
	IplImage *ImageCaptureIpl;	// 現在フレームの画像（IplImage）	初期
	cv::Mat ImageCaptureMat;		// 前のフレームの画像（Mat)			処理用

	cvSetCaptureProperty(CaptureCV, CV_CAP_PROP_POS_FRAMES, (double)FrameNumber);		// １フレーム目を設定
	ImageCaptureIpl = cvQueryFrame(CaptureCV);							// 前のフレーム数の画像（IplImage）
	ImageCaptureMat = cv::cvarrToMat(ImageCaptureIpl);				// 前のフレーム数の画像（Mat）

	if (ImageCaptureMat.cols > 400 || ImageCaptureMat.rows > 400) ImageCaptureMat = images.ResizeImage(ImageCaptureMat);

	return ImageCaptureMat;
}

int general::CalcAverage(const int Sums,const int Points) 
{
	int Averages = 0;

	if (Sums == 0)
	{
		Averages = 0;
	}
	else
	{
		Averages = Sums / Points;
	}

	return Averages;
}

void general::MakeTemp(const int MainMelodyNumber,const int NoteType,std::vector<MusicComp> &MelTemp)
{
	MusicComp MelTempTemp;
	MelTempTemp.MelNumber = MainMelodyNumber;
	MelTempTemp.DurNote = NoteType;
	MelTemp.push_back(MelTempTemp);
}


general::general()
{
}


general::~general()
{
}
