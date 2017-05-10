#include "includes.h"
#include "invest.h"
#include "general.h"
#include "colors.h"
#include "images.h"
#include "notes.h"
#include "optflow.h"
#include "ccpoint.h"
#include "csv_read.h"

bool canceled = false;
QString VideoNameQString;
int Melodies = 0,MelodiesSub = 0;


invest::invest(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChanged(int)));
	connect(ui.comboBoxSub, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChangedSub(int)));
	ui.ButtonCancel->hide();
	ui.ButtonMakeMidi->setEnabled(false);
}

invest::~invest()
{
}

void invest::handleSelectionChanged(int index)
{
	QString indexQst = QString(QString::number(index));// �m�F�p

	if (index == 0)
	{
		Melodies = 0;
	}
	else if (index == 1)
	{
		Melodies = 20;
	}
	else if (index == 2)
	{
		Melodies = 22;
	}
	else if (index == 3)
	{
		Melodies = 27;
	}
}

void invest::handleSelectionChangedSub(int index)
{
	QString indexQst = QString(QString::number(index));// �m�F�p

	if (index == 0)
	{
		MelodiesSub = 56;
	}
	else if (index == 1)
	{
		MelodiesSub = 65;
	}
	else if (index == 2)
	{
		MelodiesSub = 73;
	}
	else if (index == 3)
	{
		MelodiesSub = 74;
	}
}

void invest::on_ButtonChoseVideo_clicked()
{
	QVideoWidget widget;
	VideoNameQString = QFileDialog::getOpenFileName(&widget, "media file", "", "*.mp4 *.mp3 *.avi");	// �ǂݍ��񂾃t�@�C�����iQstring)
	if (VideoNameQString != 0)
	{
		ui.LabelVideoName->setText(VideoNameQString);
		ui.ButtonMakeMidi->setEnabled(true);
	}
}

void invest::on_ButtonChoseSave_clicked()
{
	QVideoWidget widget;
	QString folder = QFileDialog::getExistingDirectory(this, "screenshot save�@folder");
	qDebug() << folder;
	if (folder != 0)
	{
		ui.LabelSaveName->setText(folder);
	}
}

void invest::on_ButtonMakeMidi_clicked()
{
	general general;
	colors colors;
	images images;
	notes notes;
	optflow optflow;
	csv_read csvr;
	ccpoint ccpoint;

	// �r���̕ύX����t�Ȃ�
	ui.ButtonChoseVideo->setEnabled(false);		// �r�f�I�I���{�^�����~
	ui.ButtonChoseSave->setEnabled(false);		// �r�f�I�I���{�^�����~
	ui.ButtonMakeMidi->setEnabled(false);		// MIDI�����{�^�����~
	ui.TextMidiName->setEnabled(false);			// MIDI���L�������~
	ui.comboBox->setEnabled(false);				// ���̑I�𗓂��~
	ui.comboBoxSub->setEnabled(false);			// ���̑I�𗓂��~
	ui.ButtonCancel->show();						// �L�����Z���{�^����\��
	ui.LabelProcess->setText("making midi...");	// ���������܂�

	// ���͂��ꂽ���O���擾�A�g���q��ǉ��i���O���Ȃ��ꍇ��sample�j
	QString FileNameQString;		// �e�L�X�g�G���A����擾�������O�iQString)�@���L���̏ꍇ�́wsample�x
	FileNameQString = ui.TextMidiName->toPlainText();				// ���O���擾
	if (FileNameQString.isEmpty()) FileNameQString = "sample";		// ���O�ɉ��������ĂȂ��ꍇ��sample
	std::string FileNameString = FileNameQString.toLocal8Bit();		// �e�L�X�g�G���A����擾�������O�istring�j			�����ǉ��p�Ɏg�p
	FileNameString += ".mid";										// �g���q��ǉ�
	std::wstring FileNameExWstring = std::wstring(FileNameString.begin(), FileNameString.end());	// �e�L�X�g�G���A����擾�������O.�g���q�iwstring�j	�ϊ��p�Ɉꎞ�g�p�istring��wchar�̌o�R�j
	const wchar_t* FileNameExWchar = FileNameExWstring.c_str();			// �e�L�X�g�G���A����擾�������O.�g���q�iwchar�j	MIDI�t�@�C���ۑ����Ɏg�p

	// MIDI�O�ݒ�
	const wchar_t *FileNameWchar = (wchar_t*)FileNameQString.utf16();		// �e�L�X�g�G���A����擾�������O�iwchar�j			MIDI�g���b�N���Ɏg�p

	MIDIDataLib_SetDefaultCharCode(MIDIEVENT_JP);
	MIDIData* pMIDIData;
	MIDITrack* pMIDITrack;
	pMIDIData = MIDIData_Create(MIDIDATA_FORMAT1, 1, MIDIDATA_TPQNBASE, 120);// MIDI�f�[�^�̐���(�t�H�[�}�b�g1,�g���b�N��1,TPQN�x�[�X,120)
	pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);				// �ŏ��̃g���b�N�ւ̃|�C���^���擾
	MIDITrack_InsertTrackName(pMIDITrack, 0, FileNameWchar);	// �^�C�g��

	MIDITrack* dMIDITrack;//[ 2_Sax ]
	dMIDITrack = MIDITrack_Create();
	MIDIData_InsertTrackAfter(pMIDIData, dMIDITrack, pMIDIData->m_pLastTrack);
	MIDITrack_InsertTrackName(dMIDITrack, 0, L"sax");
	MIDITrack_InsertProgramChange(dMIDITrack, 0, 2, MelodiesSub);	// sax

	MIDITrack* aMIDITrack;//[ 0_Piano ]
	aMIDITrack = MIDITrack_Create();
	MIDIData_InsertTrackAfter(pMIDIData, aMIDITrack, pMIDIData->m_pLastTrack);
	MIDITrack_InsertTrackName(aMIDITrack, 0, L"Piano");
	MIDITrack_InsertProgramChange(aMIDITrack, 0, 0, Melodies);		// Piano

	MIDITrack* bMIDITrack;//[ 1_Bass ]
	bMIDITrack = MIDITrack_Create();
	MIDIData_InsertTrackAfter(pMIDIData, bMIDITrack, pMIDIData->m_pLastTrack);
	MIDITrack_InsertTrackName(bMIDITrack, 0, L"bass");
	MIDITrack_InsertProgramChange(bMIDITrack, 0, 1, 36);	// bass

	MIDITrack* cMIDITrack;//[ 9_Drums ]
	cMIDITrack = MIDITrack_Create();
	MIDIData_InsertTrackAfter(pMIDIData, cMIDITrack, pMIDIData->m_pLastTrack);
	MIDITrack_InsertTrackName(cMIDITrack, 0, L"drums");
	MIDITrack_InsertProgramChange(cMIDITrack, 0, 9, 0);		// drums

	// ��������擾
	CvCapture* CaptureCV = general.CvReadVideo(VideoNameQString);					// �t�@�C����ǂݍ���
	const double FPS = cvGetCaptureProperty(CaptureCV, CV_CAP_PROP_FPS);			//FPS
	const double Frames = cvGetCaptureProperty(CaptureCV, CV_CAP_PROP_FRAME_COUNT);	//���t���[����
	const double WholeTime = Frames / FPS;			// ����S�̂̎���
	int sabinumbers = (WholeTime / 120) + 1;		// �T�r�̐�

	/**********************************************
	�P�T��
	***********************************************/
	cv::Mat NowImageCaptureMat, PreImageCaptureMat;			//[ IMAGE ] Now���݁EPre�O�̃t���[���̉摜
	int SumRYGLBVBW[8] = {};								//[ COLOR ] �F���F�ԍ�����
	int TopHSV[3] = {};										//[ COLOR ] HSV���� H�͐F�ԍ�
	int SumSat = 0, SumVal = 0;								//[ COLOR ] ���v�@S�ʓx�AV���x
	double PreHue = 0;										//[ COLOR ] �ߋ��̐F
	int errsum = 0, pointsum = 0;							//[ OptFL ] �ړ������A�_�̍��v
	int ChangePoint[50] = {}, ChangePointErrsum[50] = {};	//[ CHANGE ] �ύX�_��ۑ�
	int CheckChangePoint = 0, ChangePointNumbers = 0;		//[ CHANGE ] �ύX�_�̏��ԂƑ���
	int ErrinFrame = 0;										//[ CHANGE ] �ύX�_����ύX�_�܂ł̈ړ�����

	PreImageCaptureMat = general.GetFramePict(1, CaptureCV);	//1���ڂ̃t���[����ݒ�

	for (int FrameNumber = 1 + FPS; FrameNumber <= Frames; FrameNumber += FPS){
		// �F
		NowImageCaptureMat = general.GetFramePict(FrameNumber, CaptureCV);	// ���݂̃t���[���̉摜���擾
		colors.FrequentColorInFrame(NowImageCaptureMat, TopHSV);			// H�i�ł������F�j��SV�i���ρj
		colors.CountNumber(TopHSV, SumRYGLBVBW);// [ COLOR ]1�ԑ����F���𑫂�
		SumSat += TopHSV[1];					// [ COLOR ]�ʓx�𑫂�
		SumVal += TopHSV[2];					// [ COLOR ]���x�𑫂�
		double Hue = colors.CalcAverage(NowImageCaptureMat);			//[ COLOR ] ���݂̃t���[���̕��ϒl�̉摜

		// �I�v�e�B�J���t���[
		std::vector<cv::Point2f> points, newpoints;		// [ OptFL ] �����_�A�ړ���̓����_
		std::vector<float> errors;						// [ OptFL ] �����_�̈ړ�����
		std::vector<unsigned char>  status = { 0 };		// [ OptFL ] �����_�̒T������
		optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);
		optflow.CalcErrsum(errors, errsum, pointsum);
		ErrinFrame += errsum;

		// �ω��_�T��
		ccpoint.CCpointHue(Hue, PreHue, ChangePoint, ChangePointErrsum, FrameNumber, CheckChangePoint, ChangePointNumbers, ErrinFrame);
		ccpoint.CCpointStatus(status, ChangePoint, ChangePointErrsum, FrameNumber, CheckChangePoint, ChangePointNumbers, ErrinFrame);

		// �㏈��
		PreImageCaptureMat = NowImageCaptureMat.clone();
		PreHue = Hue;

		// �i�݋
		double Processing = ((FrameNumber - 1) / Frames) * 100;				// [ UI ] ���݂̐i�݋[�����pdouble]
		Processing /= 2;
		QString ProcessingQString = QString(QString::number(Processing));	// [ UI ] ���݂̐i�݋[Qstring]
		ui.LabelProcess->setText(ProcessingQString + "%");
		general.delay(10);
		if (canceled == true)
		{
			break;
		}
	}


	// �Ō�̃t���[�����`�F���W�|�C���g�Ƃ��ċL�^
	ChangePoint[CheckChangePoint] = Frames;	// [ CHANGE ]�ω��_���L�^
	CheckChangePoint += 1;						// [ CHANGE ]�ω��_������
	ChangePointNumbers += 1;					// [ CHANGE ]�ω��_�̐�

	// �`�F���W�|�C���g���Ȃ�������A�Ō�̃t���[����ω��_�Ƃ���
	if (ChangePointNumbers == 0)
	{
		ChangePointNumbers = 1;
		ChangePoint[1] = Frames;
	}

	int TopColors[3];									// [ COLOR ] ��ʂR�F
	int ResultSumSat = SumSat / (Frames / FPS);			// [ COLOR ] ����S�̂̍ʓx�̕���
	int ResultSumVal = SumVal / (Frames / FPS);			// [ COLOR ] ����S�̖̂��x�̕���
	colors.FrequentNumber(SumRYGLBVBW, TopColors);		// [ COLOR ] ����S�̂łP�ԑ��������F��

	// HSV����ɒ�������
	int MelodyNotes[29] = {}, AccompNotes[22] = {};				//[ Melody ] �����f�B�̉�
	notes.ChoseCode(TopColors, MelodyNotes, AccompNotes);		//[ COLOR ] �F�E���x�E�ʓx���璲������

	// BPM������
	int ErrAve = general.CalcAverage(errsum, pointsum);			//[ OptFL ] �ړ��ʂ̕���	
	const int BPM = notes.SetBPM(ErrAve);						// [ MUSIC ] BPM�̌���
	MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / BPM);		// [ MUISC ] BPM�̐ݒ�

	// �����Ԋu������
	const double PlusFrame = notes.ClacPlusFrame(BPM, FPS);		// [ Process ]FPS�̌���
	std::vector<int> ErrsumMaxFrame = optflow.CalcErrsumMaxFrames(ChangePointErrsum, sabinumbers);

	// �����f�B�E���t�̉��ԍ��@���ƂłP���玩���ɂ��܂������͏����l�P�O�ł�
	int MainMelodyNumber = 10, SubMelodyNumber = 10, AccompNumber = 10;	//[ Notes ]���ԍ�
	int NoChange = 1, NoChange2 = 1;									//[ Notes ]�������������񐔐���p
	int MelodyTime = 480, AccompTime = 480, DrumTime = 480, MelodyTime2 = 480;	//[ NoteTimes ] MIDI�̃m�[�g�����鎞��
	int MelodyDur = 0, MelodyDur2 = 0;		// [ NoteDur ] �����f�B�̉��̒���
	bool HalfNote = false, HalfNoteSub = false;						// [ Notes ] �񕪉������������ǂ����AYES�Ȃ�P�ANO�Ȃ�O�B
	int NotesInBar = 0;						// [ Notes ] ���ߓ��̉����̐�
	int fors = 0;							// [ Other ] for�̉�

	int AngErRec[500] = {}, AveValueRec[500] = {};
	int symbalrecord[500] = {}, symbalframerecord[500] = {}, symbalswitchrecord[500] = {};
	int record = 0, bassreco = 0, symreco = 0;

	/**********************************************
	�Q�T��
	***********************************************/
	double UsingFrame = 0 + PlusFrame;
	int PianoSwitch = 0, SaxSwitch = 0, BassSwitch = 0, DrumSwitch = 0, SwitchMusic = 0;
	int vels = 100, vels2 = 100;	// [ Velocity ]����
	int countstatuspoint = 0, countsabi = 0;

	// �ŏ��̃t���[����ݒ�
	cv::Mat PreImgCapMat, NowImgCapMat;
	PreImageCaptureMat = general.GetFramePict(1, CaptureCV);
	PreImgCapMat = general.GetFramePict(1, CaptureCV);
	double SumHue;


	for (int CountChangePoint = 0; CountChangePoint <= ChangePointNumbers; CountChangePoint++)
	{
		std::vector<int> SymbalsColors(16, 0);
		std::vector<int> SymbalsVal(16, 0);
		int SymbalPoints;
		for (double UsingFrameInFor = UsingFrame; UsingFrameInFor <= ChangePoint[CountChangePoint]; UsingFrameInFor += PlusFrame)
		{
			NowImgCapMat = general.GetFramePict(UsingFrameInFor, CaptureCV);

			double Hue = colors.CalcAverage(NowImgCapMat);
			colors.FrequentColorforSymbal(NowImageCaptureMat, SymbalsColors, SymbalsVal, SymbalPoints);
			PreImgCapMat = NowImageCaptureMat.clone();
		}

		const int SymColNum = colors.CalcMaxforVector(SymbalsColors);
		const int SymValNum = colors.CalcMaxforVector(SymbalsVal);

		symbalrecord[symreco] = (DrumTime - 960);
		symbalframerecord[symreco] = (UsingFrame - PlusFrame);
		symbalswitchrecord[symreco] = SwitchMusic;
		symreco++;

		if (CountChangePoint > 0) notes.SwitchingMusic(SwitchMusic, DrumTime, cMIDITrack, ChangePointNumbers, CountChangePoint, ErrsumMaxFrame, sabinumbers, countsabi);

		std::vector<MusicComp> MelTemp;
		bool OneFlag = false;
		int MelodyNumberRythem = 0;
		int PianoRepeat = 0;
		int PreAveVal = 0;

		for (double UsingFrameInFor2 = UsingFrame; UsingFrameInFor2 <= ChangePoint[CountChangePoint]; UsingFrameInFor2 += PlusFrame)
		{
			if (CountChangePoint > 0)	notes.InstOnOff(SwitchMusic, PianoSwitch, SaxSwitch, BassSwitch, DrumSwitch);
			if (canceled == true)		break;

			// ���݂̃t���[���̉摜���擾�A�\��
			NowImageCaptureMat = general.GetFramePict(UsingFrameInFor2, CaptureCV);
			cv::Mat NowImageCaptureMatSwapped;
			cv::cvtColor(NowImageCaptureMat, NowImageCaptureMatSwapped, CV_RGB2BGR);
			QImage NowImageCaptureQImage = QImage(NowImageCaptureMatSwapped.data, NowImageCaptureMatSwapped.cols, NowImageCaptureMatSwapped.rows, QImage::Format_RGB888);
			ui.LabelImageLeft->resize(NowImageCaptureMat.cols, NowImageCaptureMat.rows);
			ui.LabelImageLeft->setPixmap(QPixmap::fromImage(NowImageCaptureQImage));

			// �I�v�e�B�J���t���[�J�n
			std::vector<cv::Point2f> points, newpoints;		// �����_�A�ړ���̓����_
			std::vector<float> errors;						// �����_�̈ړ�����
			std::vector<unsigned char>  status = { 0 };
			optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);

			// �ړ����������_��`��
			cv::Mat NowImageCaptureLinesMat = optflow.DrawLines(NowImageCaptureMat, errors, points, newpoints);

			// �I�v�e�B�J���t���[
			int LRUDN = 0, AngleError = 0, AveAngle = 0;	//[ OptFL ]  ���E�㉺�A�ő�����̈ړ������A���ϊp�x
			optflow.LRUDCheck(errors, newpoints, points, AveAngle, LRUDN, AngleError);
			int ErrAve = optflow.CalcErrave(errors);		//[ OptFL ]�ړ������̕��ς��v�Z

			AngErRec[record] = AngleError;
			record++;

			bool Symbal6 = false;
			int AveValue = colors.AveValinImage(NowImageCaptureMat);
			if (PreAveVal < 60)
			{
				if (AveValue >= 60)
				{
					MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 46, 100, 120);
				}
			}

			// Sax
			if (SaxSwitch == 1)
			{
				if (HalfNoteSub == false)
				{
					if (fors > 0)	// 0��ڂ͍�Ɩ���
					{
						int NoteType;
						MelodyDur2 = notes.CalcMelodyDur(ErrAve, HalfNoteSub, NoteType);
						if ((UsingFrameInFor2 + PlusFrame > ChangePoint[CountChangePoint]) && HalfNoteSub == true)
						{
							HalfNoteSub = false;
							MelodyDur2 = 120;
						}

						int PlusMelody = MelodyDur2;
						if (fors % 8 == 0)
						{
							MelodyDur2 += -20;
						}
						notes.ChoseMainMelodyNumber(SubMelodyNumber, LRUDN, NoChange, vels2);
						MIDITrack_InsertNote(dMIDITrack, MelodyTime2, 2, MelodyNotes[SubMelodyNumber], vels2, MelodyDur2);	// [ SAX ]
						MelodyTime2 += PlusMelody;
						NotesInBar += 1;

						if (NoteType == 8)
						{
							double UsingFramefor8 = UsingFrame;
							images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor8, PlusFrame, CaptureCV, 2);
							notes.InsertSubMelody(NowImageCaptureMat, PreImageCaptureMat, NotesInBar, SubMelodyNumber, NoChange, vels2, MelodyTime2, MelodyNotes, MelodyDur2, dMIDITrack, PlusMelody);
						}
						else if (NoteType == 16)
						{
							for (int i = 1; i <= 3; i++)
							{
								double UsingFramefor16 = UsingFrame;
								images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor16, PlusFrame, CaptureCV, 4);
								notes.InsertSubMelody(NowImageCaptureMat, PreImageCaptureMat, NotesInBar, SubMelodyNumber, NoChange, vels2, MelodyTime2, MelodyNotes, MelodyDur2, dMIDITrack, PlusMelody);
							}
						}
					}
				}
				else
				{
					HalfNoteSub = false;
				}
			}
			else
			{
				MelodyTime2 += 120;
			}

			// Piano
			if (PianoSwitch == 1 && fors > 0)
			{
				if (SwitchMusic == 1 || SwitchMusic == 2 || SwitchMusic == 4)
				{
					if (OneFlag == false)
					{
						for (int i = 0; i < 4; i++)
						{
							notes.ChoseMainMelodyNumber(MainMelodyNumber, LRUDN, NoChange, vels);
							int NoteType = 4;
							MelodyDur = notes.CalcMelodyDurforRythem(ErrAve, NoteType);
							notes.CheckSameMelNum(MelTemp, MainMelodyNumber, AveAngle);
							general.MakeTemp(MainMelodyNumber, NoteType, MelTemp);

							if (NoteType == 8)
							{
								double UsingFramefor8 = UsingFrame;
								images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor8, PlusFrame, CaptureCV, 2);
								notes.InsertMelodyforRythem(NowImageCaptureMat, PreImageCaptureMat, MainMelodyNumber, NoChange, vels);
								general.MakeTemp(MainMelodyNumber, NoteType, MelTemp);
							}
							else if (NoteType == 16)
							{
								for (int i = 1; i <= 3; i++)
								{
									double UsingFramefor16 = UsingFrame;
									images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor16, PlusFrame, CaptureCV, 4);
									notes.InsertMelodyforRythem(NowImageCaptureMat, PreImageCaptureMat, MainMelodyNumber, NoChange, vels);
									general.MakeTemp(MainMelodyNumber, NoteType, MelTemp);
								}
							}
						}
						OneFlag = true;
					}

					notes.RepeatRythem(MelodyNumberRythem, MelTemp, MainMelodyNumber, aMIDITrack, MelodyTime, vels, MelodyNotes);

				}
				else if (SwitchMusic == 3)
				{
					if (HalfNote == false)
					{
						notes.ChoseMainMelodyNumber(MainMelodyNumber, LRUDN, NoChange, vels);
						int NoteType = 4;
						MelodyDur = notes.CalcMelodyDur(ErrAve, HalfNote, NoteType);
						if (UsingFrameInFor2 + PlusFrame <= ChangePoint[CountChangePoint] && HalfNoteSub == true)
						{
							HalfNote = false;
							MelodyDur = 120;
						}

						MIDITrack_InsertNote(aMIDITrack, MelodyTime, 0, MelodyNotes[MainMelodyNumber], vels, MelodyDur);	//[ 0_Piano ]
						MelodyTime += MelodyDur;

						if (NoteType == 8)
						{
							double UsingFramefor8 = UsingFrame;
							images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor8, PlusFrame, CaptureCV, 2);
							notes.InsertMelody(NowImageCaptureMat, PreImageCaptureMat, NotesInBar, MainMelodyNumber, NoChange, vels, MelodyTime, MelodyNotes, MelodyDur, aMIDITrack);
						}
						else if (NoteType == 16)
						{
							for (int i = 1; i <= 3; i++)
							{
								double UsingFramefor16 = UsingFrame;
								images.UpdateImage(NowImageCaptureMat, PreImageCaptureMat, UsingFramefor16, PlusFrame, CaptureCV, 4);
								notes.InsertMelody(NowImageCaptureMat, PreImageCaptureMat, NotesInBar, MainMelodyNumber, NoChange, vels, MelodyTime, MelodyNotes, MelodyDur, aMIDITrack);
							}
						}
					}
					else
					{
						HalfNote = false;
					}
				}
			}
			else
			{
				MelodyTime += 120;
			}

			if (BassSwitch == 1)
			{
				AccompNumber = SubMelodyNumber;
				AveValueRec[bassreco] = AveValue;
				bassreco++;

				if (AccompNumber > 21)
				{
					AccompNumber += -7;
				}

				MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber], 50, 120);		//[ bass ] �x�[�X
				if (AveValue < 60)
				{
					MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber + 2], 50, 120);	//[ bass ] �x�[�X
				}

				if (AveValue < 20)
				{
					MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber + 4], 50, 120);	//[ bass ] �x�[�X
				}
				AccompTime += 120;
			}
			else
			{
				AccompTime += 120;
			}

			if (DrumSwitch == 1)
			{
				if (fors % 4 == 3)
				{
					notes.InsertDrums(NotesInBar, DrumTime, cMIDITrack, SymColNum, SymValNum);//[ Drums ] �����f�B
				}
			}
			else
			{
				if (fors % 4 == 3)
				{
					DrumTime += 480;
				}
			}

			// �i�݋��\��
			double Processing = ((UsingFrame - 1) / Frames) * 100;
			Processing /= 2;
			Processing += 50;
			QString ProcessingQString = QString(QString::number(Processing));
			ui.LabelProcess->setText(ProcessingQString + "%");

			// ���������̕\��
			if ((UsingFrame - 1) >= (Frames - FPS))
			{
				ui.LabelProcess->setText("succeed!");
				ui.ButtonCancel->hide();		// �L�����Z���{�^�����B��
				break;
			}

			// �㏈��
			UsingFrame += PlusFrame;
			PreImageCaptureMat = NowImageCaptureMat.clone();
			PreAveVal = AveValue;
			fors += 1;
			general.delay(1);

			if (canceled == true) break;
		}
		general.delay(1);

		if (canceled == true)
		{
			canceled = false;
			break;
		}
	}

	// �����pfor�R�R�}�f
	// MIDI�Ō�̏���
	MelodyTime += 200;	// �Ō�̃m�[�g�̌�ɋ󂫎��Ԃ������ǉ�
	MelodyTime2 += 200;	// �Ō�̃m�[�g�̌�ɋ󂫎��Ԃ������ǉ�
	AccompTime += 200;	// �Ō�̃m�[�g�̌�ɋ󂫎��Ԃ������ǉ�
	DrumTime += 200;	// �Ō�̃m�[�g�̌�ɋ󂫎��Ԃ������ǉ�
	MIDITrack_InsertEndofTrack(aMIDITrack, MelodyTime);	// �G���h�I�u�g���b�N�C�x���g��}��
	MIDITrack_InsertEndofTrack(dMIDITrack, MelodyTime2);	// �G���h�I�u�g���b�N�C�x���g��}��
	MIDITrack_InsertEndofTrack(bMIDITrack, AccompTime);	// �G���h�I�u�g���b�N�C�x���g��}��
	MIDITrack_InsertEndofTrack(cMIDITrack, DrumTime);	// �G���h�I�u�g���b�N�C�x���g��}��
	MIDIData_SaveAsSMF(pMIDIData, FileNameExWchar);// MIDI�f�[�^��ۑ� 

	// ��n��
	MIDIData_Delete(pMIDIData);		// MIDI�f�[�^���������ォ��폜
	pMIDIData = NULL;				// MIDI�f�[�^���������ォ��폜
	cvReleaseCapture(&CaptureCV);	// ������������ォ��폜

	ui.ButtonChoseVideo->setEnabled(true);		// �r�f�I�I���{�^����߂�
	ui.ButtonMakeMidi->setEnabled(true);		// MIDI�����{�^����߂�
	ui.TextMidiName->setEnabled(true);			// MIDI���L������߂�

	std::vector <int> for_vector_push;
	for (int i = 0; i < 50; i++)
	{
		for_vector_push.push_back(ChangePoint[i]);
	}
	csvr.writeOnly1vector("changepoint.csv", for_vector_push);

	std::vector <int> for_vector_push2;
	for (int i = 0; i < 500; i++)
	{
		for_vector_push2.push_back(AngErRec[i]);
	}
	csvr.writeOnly1vector("AngErr.csv", for_vector_push2);


	std::vector <int> for_vector_push3;
	for (int i = 0; i < 500; i++)
	{
		for_vector_push3.push_back(AveValueRec[i]);
	}
	csvr.writeOnly1vector("AveValue.csv", for_vector_push3);


	std::vector <int> for_vector_push6;
	for (int i = 0; i < 500; i++)
	{
		for_vector_push6.push_back(symbalrecord[i]);
	}
	csvr.writeOnly1vector("symbalrecord.csv", for_vector_push6);

	std::vector <int> for_vector_push7;
	for (int i = 0; i < 500; i++)
	{
		for_vector_push7.push_back(symbalframerecord[i]);
	}
	csvr.writeOnly1vector("symbalframerecord.csv", for_vector_push7);


	std::vector <int> for_vector_push8;
	for (int i = 0; i < 500; i++)
	{
		for_vector_push8.push_back(symbalswitchrecord[i]);
	}
	csvr.writeOnly1vector("symbalswitchrecord.csv", for_vector_push8);

}

void invest::on_ButtonCancel_clicked()
{
	canceled = true;
	ui.ButtonCancel->hide();
	ui.LabelProcess->setText("canceled!");	
}

void invest::on_ButtonEnd_clicked()
{

		qApp->quit();

}

void invest::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		qApp->quit();
	}
}