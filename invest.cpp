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
	QString indexQst = QString(QString::number(index));// 確認用

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
	QString indexQst = QString(QString::number(index));// 確認用

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
	VideoNameQString = QFileDialog::getOpenFileName(&widget, "media file", "", "*.mp4 *.mp3 *.avi");	// 読み込んだファイル名（Qstring)
	if (VideoNameQString != 0)
	{
		ui.LabelVideoName->setText(VideoNameQString);
		ui.ButtonMakeMidi->setEnabled(true);
	}
}

void invest::on_ButtonChoseSave_clicked()
{
	QVideoWidget widget;
	QString folder = QFileDialog::getExistingDirectory(this, "screenshot save　folder");
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

	// 途中の変更を受付ない
	ui.ButtonChoseVideo->setEnabled(false);		// ビデオ選択ボタンを停止
	ui.ButtonChoseSave->setEnabled(false);		// ビデオ選択ボタンを停止
	ui.ButtonMakeMidi->setEnabled(false);		// MIDI生成ボタンを停止
	ui.TextMidiName->setEnabled(false);			// MIDI名記入欄を停止
	ui.comboBox->setEnabled(false);				// 音の選択欄を停止
	ui.comboBoxSub->setEnabled(false);			// 音の選択欄を停止
	ui.ButtonCancel->show();						// キャンセルボタンを表示
	ui.LabelProcess->setText("making midi...");	// 今からつくります

	// 入力された名前を取得、拡張子を追加（名前がない場合はsample）
	QString FileNameQString;		// テキストエリアから取得した名前（QString)　未記入の場合は『sample』
	FileNameQString = ui.TextMidiName->toPlainText();				// 名前を取得
	if (FileNameQString.isEmpty()) FileNameQString = "sample";		// 名前に何も入ってない場合はsample
	std::string FileNameString = FileNameQString.toLocal8Bit();		// テキストエリアから取得した名前（string）			文字追加用に使用
	FileNameString += ".mid";										// 拡張子を追加
	std::wstring FileNameExWstring = std::wstring(FileNameString.begin(), FileNameString.end());	// テキストエリアから取得した名前.拡張子（wstring）	変換用に一時使用（string→wcharの経由）
	const wchar_t* FileNameExWchar = FileNameExWstring.c_str();			// テキストエリアから取得した名前.拡張子（wchar）	MIDIファイル保存時に使用

	// MIDI前設定
	const wchar_t *FileNameWchar = (wchar_t*)FileNameQString.utf16();		// テキストエリアから取得した名前（wchar）			MIDIトラック名に使用

	MIDIDataLib_SetDefaultCharCode(MIDIEVENT_JP);
	MIDIData* pMIDIData;
	MIDITrack* pMIDITrack;
	pMIDIData = MIDIData_Create(MIDIDATA_FORMAT1, 1, MIDIDATA_TPQNBASE, 120);// MIDIデータの生成(フォーマット1,トラック数1,TPQNベース,120)
	pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);				// 最初のトラックへのポインタを取得
	MIDITrack_InsertTrackName(pMIDITrack, 0, FileNameWchar);	// タイトル

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

	// 動画情報を取得
	CvCapture* CaptureCV = general.CvReadVideo(VideoNameQString);					// ファイルを読み込む
	const double FPS = cvGetCaptureProperty(CaptureCV, CV_CAP_PROP_FPS);			//FPS
	const double Frames = cvGetCaptureProperty(CaptureCV, CV_CAP_PROP_FRAME_COUNT);	//総フレーム数
	const double WholeTime = Frames / FPS;			// 動画全体の時間
	int sabinumbers = (WholeTime / 120) + 1;		// サビの数

	/**********************************************
	１週目
	***********************************************/
	cv::Mat NowImageCaptureMat, PreImageCaptureMat;			//[ IMAGE ] Now現在・Pre前のフレームの画像
	int SumRYGLBVBW[8] = {};								//[ COLOR ] 色相色番号結果
	int TopHSV[3] = {};										//[ COLOR ] HSV結果 Hは色番号
	int SumSat = 0, SumVal = 0;								//[ COLOR ] 合計　S彩度、V明度
	double PreHue = 0;										//[ COLOR ] 過去の色
	int errsum = 0, pointsum = 0;							//[ OptFL ] 移動距離、点の合計
	int ChangePoint[50] = {}, ChangePointErrsum[50] = {};	//[ CHANGE ] 変更点を保存
	int CheckChangePoint = 0, ChangePointNumbers = 0;		//[ CHANGE ] 変更点の順番と総数
	int ErrinFrame = 0;										//[ CHANGE ] 変更点から変更点までの移動距離

	PreImageCaptureMat = general.GetFramePict(1, CaptureCV);	//1枚目のフレームを設定

	for (int FrameNumber = 1 + FPS; FrameNumber <= Frames; FrameNumber += FPS){
		// 色
		NowImageCaptureMat = general.GetFramePict(FrameNumber, CaptureCV);	// 現在のフレームの画像を取得
		colors.FrequentColorInFrame(NowImageCaptureMat, TopHSV);			// H（最も多い色）とSV（平均）
		colors.CountNumber(TopHSV, SumRYGLBVBW);// [ COLOR ]1番多い色相を足す
		SumSat += TopHSV[1];					// [ COLOR ]彩度を足す
		SumVal += TopHSV[2];					// [ COLOR ]明度を足す
		double Hue = colors.CalcAverage(NowImageCaptureMat);			//[ COLOR ] 現在のフレームの平均値の画像

		// オプティカルフロー
		std::vector<cv::Point2f> points, newpoints;		// [ OptFL ] 特徴点、移動後の特徴点
		std::vector<float> errors;						// [ OptFL ] 特徴点の移動距離
		std::vector<unsigned char>  status = { 0 };		// [ OptFL ] 特徴点の探索成否
		optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);
		optflow.CalcErrsum(errors, errsum, pointsum);
		ErrinFrame += errsum;

		// 変化点探索
		ccpoint.CCpointHue(Hue, PreHue, ChangePoint, ChangePointErrsum, FrameNumber, CheckChangePoint, ChangePointNumbers, ErrinFrame);
		ccpoint.CCpointStatus(status, ChangePoint, ChangePointErrsum, FrameNumber, CheckChangePoint, ChangePointNumbers, ErrinFrame);

		// 後処理
		PreImageCaptureMat = NowImageCaptureMat.clone();
		PreHue = Hue;

		// 進み具合
		double Processing = ((FrameNumber - 1) / Frames) * 100;				// [ UI ] 現在の進み具合[処理用double]
		Processing /= 2;
		QString ProcessingQString = QString(QString::number(Processing));	// [ UI ] 現在の進み具合[Qstring]
		ui.LabelProcess->setText(ProcessingQString + "%");
		general.delay(10);
		if (canceled == true)
		{
			break;
		}
	}


	// 最後のフレームをチェンジポイントとして記録
	ChangePoint[CheckChangePoint] = Frames;	// [ CHANGE ]変化点を記録
	CheckChangePoint += 1;						// [ CHANGE ]変化点を次へ
	ChangePointNumbers += 1;					// [ CHANGE ]変化点の数

	// チェンジポイントがなかったら、最後のフレームを変化点とする
	if (ChangePointNumbers == 0)
	{
		ChangePointNumbers = 1;
		ChangePoint[1] = Frames;
	}

	int TopColors[3];									// [ COLOR ] 上位３色
	int ResultSumSat = SumSat / (Frames / FPS);			// [ COLOR ] 動画全体の彩度の平均
	int ResultSumVal = SumVal / (Frames / FPS);			// [ COLOR ] 動画全体の明度の平均
	colors.FrequentNumber(SumRYGLBVBW, TopColors);		// [ COLOR ] 動画全体で１番多かった色相

	// HSVを基に調を決定
	int MelodyNotes[29] = {}, AccompNotes[22] = {};				//[ Melody ] メロディの音
	notes.ChoseCode(TopColors, MelodyNotes, AccompNotes);		//[ COLOR ] 色・明度・彩度から調を決定

	// BPMを決定
	int ErrAve = general.CalcAverage(errsum, pointsum);			//[ OptFL ] 移動量の平均	
	const int BPM = notes.SetBPM(ErrAve);						// [ MUSIC ] BPMの決定
	MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / BPM);		// [ MUISC ] BPMの設定

	// 処理間隔を決定
	const double PlusFrame = notes.ClacPlusFrame(BPM, FPS);		// [ Process ]FPSの決定
	std::vector<int> ErrsumMaxFrame = optflow.CalcErrsumMaxFrames(ChangePointErrsum, sabinumbers);

	// メロディ・伴奏の音番号　あとで１から自動にしますが今は初期値１０です
	int MainMelodyNumber = 10, SubMelodyNumber = 10, AccompNumber = 10;	//[ Notes ]音番号
	int NoChange = 1, NoChange2 = 1;									//[ Notes ]同じ音が続く回数制御用
	int MelodyTime = 480, AccompTime = 480, DrumTime = 480, MelodyTime2 = 480;	//[ NoteTimes ] MIDIのノートが入る時間
	int MelodyDur = 0, MelodyDur2 = 0;		// [ NoteDur ] メロディの音の長さ
	bool HalfNote = false, HalfNoteSub = false;						// [ Notes ] 二分音符だったかどうか、YESなら１、NOなら０。
	int NotesInBar = 0;						// [ Notes ] 小節内の音符の数
	int fors = 0;							// [ Other ] forの回数

	int AngErRec[500] = {}, AveValueRec[500] = {};
	int symbalrecord[500] = {}, symbalframerecord[500] = {}, symbalswitchrecord[500] = {};
	int record = 0, bassreco = 0, symreco = 0;

	/**********************************************
	２週目
	***********************************************/
	double UsingFrame = 0 + PlusFrame;
	int PianoSwitch = 0, SaxSwitch = 0, BassSwitch = 0, DrumSwitch = 0, SwitchMusic = 0;
	int vels = 100, vels2 = 100;	// [ Velocity ]音量
	int countstatuspoint = 0, countsabi = 0;

	// 最初のフレームを設定
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

			// 現在のフレームの画像を取得、表示
			NowImageCaptureMat = general.GetFramePict(UsingFrameInFor2, CaptureCV);
			cv::Mat NowImageCaptureMatSwapped;
			cv::cvtColor(NowImageCaptureMat, NowImageCaptureMatSwapped, CV_RGB2BGR);
			QImage NowImageCaptureQImage = QImage(NowImageCaptureMatSwapped.data, NowImageCaptureMatSwapped.cols, NowImageCaptureMatSwapped.rows, QImage::Format_RGB888);
			ui.LabelImageLeft->resize(NowImageCaptureMat.cols, NowImageCaptureMat.rows);
			ui.LabelImageLeft->setPixmap(QPixmap::fromImage(NowImageCaptureQImage));

			// オプティカルフロー開始
			std::vector<cv::Point2f> points, newpoints;		// 特徴点、移動後の特徴点
			std::vector<float> errors;						// 特徴点の移動距離
			std::vector<unsigned char>  status = { 0 };
			optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);

			// 移動した特徴点を描画
			cv::Mat NowImageCaptureLinesMat = optflow.DrawLines(NowImageCaptureMat, errors, points, newpoints);

			// オプティカルフロー
			int LRUDN = 0, AngleError = 0, AveAngle = 0;	//[ OptFL ]  左右上下、最大方向の移動距離、平均角度
			optflow.LRUDCheck(errors, newpoints, points, AveAngle, LRUDN, AngleError);
			int ErrAve = optflow.CalcErrave(errors);		//[ OptFL ]移動距離の平均を計算

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
					if (fors > 0)	// 0回目は作業無し
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

				MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber], 50, 120);		//[ bass ] ベース
				if (AveValue < 60)
				{
					MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber + 2], 50, 120);	//[ bass ] ベース
				}

				if (AveValue < 20)
				{
					MIDITrack_InsertNote(bMIDITrack, AccompTime, 1, AccompNotes[AccompNumber + 4], 50, 120);	//[ bass ] ベース
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
					notes.InsertDrums(NotesInBar, DrumTime, cMIDITrack, SymColNum, SymValNum);//[ Drums ] メロディ
				}
			}
			else
			{
				if (fors % 4 == 3)
				{
					DrumTime += 480;
				}
			}

			// 進み具合を表示
			double Processing = ((UsingFrame - 1) / Frames) * 100;
			Processing /= 2;
			Processing += 50;
			QString ProcessingQString = QString(QString::number(Processing));
			ui.LabelProcess->setText(ProcessingQString + "%");

			// 処理完了の表示
			if ((UsingFrame - 1) >= (Frames - FPS))
			{
				ui.LabelProcess->setText("succeed!");
				ui.ButtonCancel->hide();		// キャンセルボタンを隠す
				break;
			}

			// 後処理
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

	// 処理用forココマデ
	// MIDI最後の処理
	MelodyTime += 200;	// 最後のノートの後に空き時間を少し追加
	MelodyTime2 += 200;	// 最後のノートの後に空き時間を少し追加
	AccompTime += 200;	// 最後のノートの後に空き時間を少し追加
	DrumTime += 200;	// 最後のノートの後に空き時間を少し追加
	MIDITrack_InsertEndofTrack(aMIDITrack, MelodyTime);	// エンドオブトラックイベントを挿入
	MIDITrack_InsertEndofTrack(dMIDITrack, MelodyTime2);	// エンドオブトラックイベントを挿入
	MIDITrack_InsertEndofTrack(bMIDITrack, AccompTime);	// エンドオブトラックイベントを挿入
	MIDITrack_InsertEndofTrack(cMIDITrack, DrumTime);	// エンドオブトラックイベントを挿入
	MIDIData_SaveAsSMF(pMIDIData, FileNameExWchar);// MIDIデータを保存 

	// 後始末
	MIDIData_Delete(pMIDIData);		// MIDIデータをメモリ上から削除
	pMIDIData = NULL;				// MIDIデータをメモリ上から削除
	cvReleaseCapture(&CaptureCV);	// 動画をメモリ上から削除

	ui.ButtonChoseVideo->setEnabled(true);		// ビデオ選択ボタンを戻す
	ui.ButtonMakeMidi->setEnabled(true);		// MIDI生成ボタンを戻す
	ui.TextMidiName->setEnabled(true);			// MIDI名記入欄を戻す

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