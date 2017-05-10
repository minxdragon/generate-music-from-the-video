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
	std::string VideoNameString = VideoNameQString.toLocal8Bit();	// ��Ƃ���r�f�I�̃t�@�C���p�X(string)�@�ϊ��p
	int len = VideoNameString.length();								// VideoString�̒����i�ϊ��p�j
	char *VideoNameChar = new char[len + 1];						// ��Ƃ���r�f�I�̃t�@�C���p�X�ichar�j�@CvCapture�ɓǂݍ��܂���p
	memcpy(VideoNameChar, VideoNameString.c_str(), len + 1);		// char��string		��Ƃ���r�f�I�̃t�@�C���p�X
	CvCapture* CaptureCV = cvCaptureFromFile(VideoNameChar);		// �ǂݍ��񂾃t�@�C���iCvCapture)

	delete[] VideoNameChar;			// new���g�p����char���������ォ��폜

	return CaptureCV;
}

cv::Mat general::GetFramePict(int FrameNumber, CvCapture* CaptureCV)
{
	images images;
	IplImage *ImageCaptureIpl;	// ���݃t���[���̉摜�iIplImage�j	����
	cv::Mat ImageCaptureMat;		// �O�̃t���[���̉摜�iMat)			�����p

	cvSetCaptureProperty(CaptureCV, CV_CAP_PROP_POS_FRAMES, (double)FrameNumber);		// �P�t���[���ڂ�ݒ�
	ImageCaptureIpl = cvQueryFrame(CaptureCV);							// �O�̃t���[�����̉摜�iIplImage�j
	ImageCaptureMat = cv::cvarrToMat(ImageCaptureIpl);				// �O�̃t���[�����̉摜�iMat�j

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
