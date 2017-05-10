#include "notes.h"
#include "images.h"
#include "optflow.h"
#include "includes.h"

void notes::MajorCode(int Tonic, int *Scale, int Oktave)
{
	for (int a = 0; a <= Oktave; a++)
	{
		Scale[0 + a * 7] = Tonic + 0 + 12 * a;		//c
		Scale[1 + a * 7] = Tonic + 2 + 12 * a;		//d
		Scale[2 + a * 7] = Tonic + 4 + 12 * a;		//e
		Scale[3 + a * 7] = Tonic + 5 + 12 * a;		//f
		Scale[4 + a * 7] = Tonic + 7 + 12 * a;		//g
		Scale[5 + a * 7] = Tonic + 9 + 12 * a;		//a
		Scale[6 + a * 7] = Tonic + 11 + 12 * a;		//b
	}
	return;
}

void notes::MinorCode(int Tonic, int *Scale, int Oktave)
{
	for (int a = 0; a <= Oktave; a++)
	{
		Scale[0 + a * 7] = Tonic + 0 + 12 * a;		//c
		Scale[1 + a * 7] = Tonic + 2 + 12 * a;		//d
		Scale[2 + a * 7] = Tonic + 3 + 12 * a;		//e
		Scale[3 + a * 7] = Tonic + 5 + 12 * a;		//f
		Scale[4 + a * 7] = Tonic + 7 + 12 * a;		//g
		Scale[5 + a * 7] = Tonic + 8 + 12 * a;		//a
		Scale[6 + a * 7] = Tonic + 10 + 12 * a;		//b
	}
	return;
}

void notes::ChoseCode(const int *hsv, int *MelodyCodes, int *AccompCodes)
{
	if (hsv[0] == 7)// black
	{
		// B Flat Major
		int tonicnote = 22;
		MajorCode(tonicnote + 36, MelodyCodes, 4);
		MajorCode(tonicnote, AccompCodes, 3);
		return;

	}
	else if (hsv[0] == 6)// White
	{
		// C Major

		int tonicnote = 12;
		MajorCode(tonicnote + 36, MelodyCodes, 4);
		MajorCode(tonicnote, AccompCodes, 3);
		return;
	}
	else if (hsv[0] == 0)// Red
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// F Minor
				int tonicnote = 17;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// D Major
				int tonicnote = 14;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// E Minor
				int tonicnote = 16;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// G Flat Major
				int tonicnote = 18;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
	else if (hsv[0] == 1)// Yellow
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// C Minor
				int tonicnote = 12;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// A major
				int tonicnote = 21;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// E Flat Major
				int tonicnote = 15;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// B Major
				int tonicnote = 23;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
	else if (hsv[0] == 2)// Green
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// C Minor
				int tonicnote = 12;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// B Flat Major
				int tonicnote = 22;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// G Major
				int tonicnote = 19;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// E Major
				int tonicnote = 16;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
	else if (hsv[0] == 3)// LightBlue
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// G Minor
				int tonicnote = 19;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// A Minor
				int tonicnote = 21;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// D Minor
				int tonicnote = 14;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// F Major
				int tonicnote = 17;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
	else if (hsv[0] == 4)// Blue
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// E Flat Minor
				int tonicnote = 15;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// B Minor
				int tonicnote = 23;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// A Flat Minor
				int tonicnote = 20;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// A Flat Major
				int tonicnote = 20;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
	else if (hsv[0] == 5)// Violet
	{
		if (hsv[1] < 175)
		{
			if (hsv[2] < 175)
			{
				// Low Low
				// C Sharp Minor
				int tonicnote = 13;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// Low High
				// G Sharp Major
				int tonicnote = 20;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
		else
		{
			if (hsv[2] < 175)
			{
				// High Low
				// F Sharp Minor
				int tonicnote = 18;
				MinorCode(tonicnote + 36, MelodyCodes, 4);
				MinorCode(tonicnote, AccompCodes, 3);
				return;
			}
			else
			{
				// High High
				// D Flat Major
				int tonicnote = 13;
				MajorCode(tonicnote + 36, MelodyCodes, 4);
				MajorCode(tonicnote, AccompCodes, 3);
				return;
			}
		}
	}
}

void notes::NoteHue(double hue, MIDITrack* aMIDITrack, int DurNote)
{
	// ノートイベントを挿入         Time  ch  key  vel  dur
	if (0 <= hue && hue <= 45)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 60, 100, 120); // ど（C5)
	}
	else if (45 < hue && hue <= 90)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 62, 100, 120); // れ（D5）
	}
	else if (90 < hue && hue <= 135)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 64, 100, 120); // み（E5）
	}
	else if (135 < hue && hue <= 180)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 65, 100, 120); // ふぁ（F5）
	}
	else if (180 < hue && hue <= 225)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 67, 100, 120); // そ（G5)
	}
	else if (225 < hue && hue <= 270)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 69, 100, 120); // ら（A5)
	}
	else if (270 < hue && hue <= 315)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 71, 100, 120); // し（B5）
	}
	else if (315 < hue && hue <= 360)
	{
		MIDITrack_InsertNote(aMIDITrack, DurNote, 0, 72, 100, 120); // ど（C6）
	}
}

int notes::SetBPM(const int ErrAve)
{
	int BPM;
	if (ErrAve < 20)
	{
		BPM = 100;
	}
	else if (ErrAve < 40)
	{
		BPM = 120;
	}
	else if (ErrAve < 60)
	{
		BPM = 150;
	}
	else
	{
		BPM = 200;
	}

	return BPM;
}

double notes::ClacPlusFrame(const int BPM, const double FPS)
{
	double BPS, SingleBeat;
	double PlusFrame;
	BPS = (double)BPM / 60;
	SingleBeat = 1 / BPS;
	PlusFrame = SingleBeat*FPS;

	return PlusFrame;

}

void notes::ChoseMainMelodyNumber(int &MelodyNumber, const int LRUDN, int NoChange, int &vels)
{
	if (LRUDN == 2)	// 上ならば１上げる
	{
		if (MelodyNumber > 27)
		{
			MelodyNumber += -2;
		}
		MelodyNumber += 1;
	}
	else if (LRUDN == 3)	// 下ならば１下げる
	{
		MelodyNumber += -1;

		if (MelodyNumber < 0)
		{
			MelodyNumber += 2;
		}
	}
	else	// 左右ならば下げずにそのまま
	{
		MelodyNumber += 0;
		NoChange += 1;	// 変更のなかった回数を計算
		if (NoChange >= 2)	// 2回以上変更がなかったならば
		{
			if (MelodyNumber > 10)
			{
				MelodyNumber += -1;
			}
			else
			{
				MelodyNumber += 1;
			}
			NoChange = 1;	// 変更無し回数の値を基に戻す
		}
	}

	if (LRUDN == 2)
	{
		if (vels < 127)
		{
			vels += 2;
		}
	}
	else if (LRUDN == 3)
	{
		if (vels > 60)
		{
			vels += -2;
		}
	}

}

void notes::ChoseSubMelodyNumber(int &MelodyNumber, const int LRUDN, int NoChange, int &vels, int AngleError)
{
	int PlusNumber;
	if (AngleError < 15)
	{
		PlusNumber = 1;
	}
	else if (AngleError < 30)
	{
		PlusNumber = 2;
	}
	else if (AngleError < 50)
	{
		PlusNumber = 3;
	}
	else
	{
		PlusNumber = 4;
	}

	if (LRUDN == 2)	// 上ならば１上げる
	{
		if (MelodyNumber > 27)
		{
			MelodyNumber += -5;
		}
		MelodyNumber += PlusNumber;
	}
	else if (LRUDN == 3)	// 下ならば１下げる
	{
		MelodyNumber += -PlusNumber;

		if (MelodyNumber < 0)
		{
			MelodyNumber += 5;
		}
	}
	else	// 左右ならば下げずにそのまま
	{
		MelodyNumber += 0;
		NoChange++;	// 変更のなかった回数を計算
		if (NoChange > 1)	// 2回以上変更がなかったならば
		{
			if (MelodyNumber > 10)
			{
				MelodyNumber += -PlusNumber;
			}
			else
			{
				MelodyNumber += PlusNumber;
			}
			NoChange = 0;	// 変更無し回数の値を基に戻す
		}
	}

	if (LRUDN == 2)
	{
		if (vels < 127)
		{
			vels += 2;
		}
	}
	else if (LRUDN == 3)
	{
		if (vels > 60)
		{
			vels += -2;
		}
	}

}

int notes::CalcMelodyDur(const int ErrAve, bool &HalfNote, int &NoteType)
{
	int MelodyDur;

	if (ErrAve < 10)
	{
		MelodyDur = 240;
		NoteType = 2;
		HalfNote = true;
	}
	else if (ErrAve < 15)
	{
		MelodyDur = 120;
		NoteType = 4;

	}
	else if (ErrAve < 20)
	{
		MelodyDur = 60;
		NoteType = 8;
	}
	else
	{
		MelodyDur = 30;
		NoteType = 16;
	}

	return MelodyDur;
}

int notes::CalcMelodyDurforRythem(const int ErrAve, int &NoteType)
{
	int MelodyDur;

	if (ErrAve < 25)
	{
		MelodyDur = 120;

	}
	else if (ErrAve < 35)
	{
		MelodyDur = 60;
		NoteType = 8;
	}
	else
	{
		MelodyDur = 30;
		NoteType = 16;
	}

	return MelodyDur;
}

int notes::CalcMelodyDurforSax(const int ErrAve, bool &HalfNote, int &NoteType)
{
	int MelodyDur;

	if (ErrAve < 15)
	{
		MelodyDur = 240;
		HalfNote = true;
	}
	else if (ErrAve < 30)
	{
		MelodyDur = 120;
		NoteType = 4;

	}
	else if (ErrAve < 60)
	{
		MelodyDur = 60;
		NoteType = 8;
	}
	else
	{
		MelodyDur = 30;
		NoteType = 16;
	}

	return MelodyDur;
}

void notes::InsertDrums(int &NotesInBar, int &DrumTime, MIDITrack* cMIDITrack, int SymbalsColNum, int SymbalsValNum)
{

	if (NotesInBar <= 2)
	{
		for (int AccompLoop = 0; AccompLoop < 2; AccompLoop++)
		{
			MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 36, 100, 120);
			DrumTime += 240;
		}
	}
	else if (NotesInBar >2 && NotesInBar <= 4)
	{
		for (int AccompLoop = 0; AccompLoop < 2; AccompLoop++)
		{
			MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 36, 100, 120);
			if (AccompLoop % 2 == 0)
			{
				MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, SymbalsValNum, 100, 120);
			}
			DrumTime += 240;
		}
	}
	else if (NotesInBar >4 && NotesInBar <= 8)
	{
		for (int AccompLoop = 0; AccompLoop < 4; AccompLoop++)
		{
			MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 36, 100, 120);
			DrumTime += 120;
			if (AccompLoop % 2 == 0)
			{
				MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, SymbalsValNum, 100, 120);
			}
		}
	}
	else if (NotesInBar >8 && NotesInBar <= 16)
	{
		for (int AccompLoop = 0; AccompLoop < 4; AccompLoop++)
		{
			MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 36, 100, 120);
			if (AccompLoop % 2 == 0)
			{
				MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, SymbalsValNum, 100, 120);
			}
			if (AccompLoop % 2 == 1)
			{
				MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, SymbalsColNum, 100, 120);
			}
			DrumTime += 120;
		}
	}
	NotesInBar = 0;

}

void notes::InsertPiano(int &NotesInBar, int &PianoTime, MIDITrack* aMIDITrack)
{

	if (NotesInBar <= 2)
	{
		for (int AccompLoop = 0; AccompLoop < 2; AccompLoop++)
		{
			MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 54, 100, 120);
			PianoTime += 240;
		}
	}
	else if (NotesInBar >2 && NotesInBar <= 4)
	{
		for (int AccompLoop = 0; AccompLoop < 2; AccompLoop++)
		{
			MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 54, 100, 120);
			if (AccompLoop % 2 == 0)
			{
				MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 37, 100, 120);
			}
			PianoTime += 240;
		}
	}
	else if (NotesInBar >4 && NotesInBar <= 8)
	{
		for (int AccompLoop = 0; AccompLoop < 4; AccompLoop++)
		{
			MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 54, 100, 120);
			PianoTime += 120;
		}
	}
	else if (NotesInBar >8 && NotesInBar <= 16)
	{
		for (int AccompLoop = 0; AccompLoop < 4; AccompLoop++)
		{
			MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 54, 100, 120);
			if (AccompLoop % 2 == 0)
			{
				MIDITrack_InsertNote(aMIDITrack, PianoTime, 9, 37, 100, 120);
			}
			PianoTime += 120;
		}
	}
	NotesInBar = 0;

}

void notes::InsertMelody(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &NotesInBar, int &MainMelodyNumber, int &NoChange, int &vels, int &MelodyTime, int *MelodyNotes, int &MelodyDur, MIDITrack* aMIDITrack)
{
	optflow optflow;
	notes notes;

	std::vector<cv::Point2f> points, newpoints;	
	std::vector<float> errors;
	std::vector<unsigned char>  status = { 0 };
	optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);
	int LRUDN = 0, AngleError = 0, AveAngle = 0;
	optflow.LRUDCheck(errors, newpoints, points, AveAngle, LRUDN, AngleError);
	notes.ChoseMainMelodyNumber(MainMelodyNumber, LRUDN, NoChange, vels);

	MIDITrack_InsertNote(aMIDITrack, MelodyTime, 0, MelodyNotes[MainMelodyNumber], vels, MelodyDur);

	MelodyTime += MelodyDur;
}

void notes::InsertMelodyforRythem(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &MainMelodyNumber, int &NoChange, int &vels)
{
	optflow optflow;
	notes notes;

	std::vector<cv::Point2f> points, newpoints;
	std::vector<float> errors;
	std::vector<unsigned char>  status = { 0 };
	optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);
	int LRUDN = 0, AngleError = 0, AveAngle = 0;
	optflow.LRUDCheck(errors, newpoints, points, AveAngle, LRUDN, AngleError);
	notes.ChoseMainMelodyNumber(MainMelodyNumber, LRUDN, NoChange, vels);
}

void notes::InsertSubMelody(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &NotesInBar, int &MainMelodyNumber, int &NoChange, int &vels, int &MelodyTime, int *MelodyNotes, int &MelodyDur, MIDITrack* aMIDITrack, int PlusMelody)
{
	optflow optflow;
	notes notes;

	std::vector<cv::Point2f> points, newpoints;	
	std::vector<float> errors;
	std::vector<unsigned char>  status = { 0 };
	optflow.OptFlow(PreImageCaptureMat, NowImageCaptureMat, points, newpoints, errors, status);
	int LRUDN = 0, AngleError = 0, AveAngle = 0;
	optflow.LRUDCheck(errors, newpoints, points, AveAngle, LRUDN, AngleError);
	notes.ChoseSubMelodyNumber(MainMelodyNumber, LRUDN, NoChange, vels, AngleError);

	MIDITrack_InsertNote(aMIDITrack, MelodyTime, 2, MelodyNotes[MainMelodyNumber], vels, MelodyDur);

	MelodyTime += PlusMelody;
	NotesInBar += 1;

}

void notes::SwitchingMusic(int &SwitchMusic, int &DrumTime, MIDITrack* cMIDITrack, const int ChangePointNumbers, const int CountChangePoint, std::vector<int> ErrsumMaxFrame, int sabinumbers, int &countsabi)
{

	int sabicheck = 0;
	if (countsabi < sabinumbers)
	{
		if (ErrsumMaxFrame[countsabi] == CountChangePoint)
		{
			countsabi++;
			SwitchMusic = 3;
		}
		else
		{
			sabicheck = 1;
		}
	}
	else
	{
		sabicheck = 1;
	}

	if (sabicheck == 0)
	{

	}
	else if (SwitchMusic == 0)		// first
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 1;		// mel1
	}
	else  if (CountChangePoint == (ChangePointNumbers - 1))//last
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 5;		// sabi
	}
	else if (SwitchMusic == 1)	// mel1
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 2;		// mel2
	}
	else if (SwitchMusic == 2)	//mel2
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 1;		// mel1
	}
	else if (SwitchMusic == 3)	// sabi
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 4;		//interval
	}
	else if (SwitchMusic == 4)	//interval
	{
		MIDITrack_InsertNote(cMIDITrack, DrumTime, 9, 49, 100, 120);
		SwitchMusic = 1;		//mel1
	}

	return;
}

void notes::InstOnOff(int &SwitchMusic, int &PianoSwitch, int &SaxSwitch, int &BassSwitch, int &DrumSwitch)
{
	if (SwitchMusic == 0)//first
	{
		PianoSwitch = 0;
		SaxSwitch = 0;
		BassSwitch = 0;
		DrumSwitch = 1;
	}
	else if (SwitchMusic == 1)//mel1
	{
		PianoSwitch = 1;
		SaxSwitch = 1;
		BassSwitch = 1;
		DrumSwitch = 1;
	}
	else if (SwitchMusic == 2)//mel2
	{
		PianoSwitch = 1;
		SaxSwitch = 1;
		BassSwitch = 1;
		DrumSwitch = 1;
	}
	else if (SwitchMusic == 3)//sabi
	{
		PianoSwitch = 1;
		SaxSwitch = 1;
		BassSwitch = 1;
		DrumSwitch = 1;
	}
	else if (SwitchMusic == 4)//interval
	{
		PianoSwitch = 1;
		SaxSwitch = 0;
		BassSwitch = 1;
		DrumSwitch = 1;
	}
	else if (SwitchMusic == 5)//end
	{
		PianoSwitch = 1;
		SaxSwitch = 0;
		BassSwitch = 1;
		DrumSwitch = 1;
	}

	return;
}

void notes::CheckSameMelNum(std::vector<MusicComp> MelTemp, int &MainMelodyNumber, const int AveAngle)
{
	if (MelTemp.size() > 0)
	{
		int NoSame = 0;
		while (NoSame != 1)
		{
			for (int a = 0; a < MelTemp.size(); a++)
			{
				if (MainMelodyNumber == MelTemp[a].MelNumber)
				{
					if (AveAngle < 180)
					{
						MainMelodyNumber++;
					}
					else
					{
						MainMelodyNumber--;
					}
					break;
				}
				NoSame = 1;
			}
		}
	}
}

void notes::RepeatRythem(int &MelodyNumberRythem, const std::vector<MusicComp> MelTemp, int &MainMelodyNumber, MIDITrack* aMIDITrack, int &MelodyTime, int &vels, int *MelodyNotes)
{
	int MelodyDurSum = 0;
	int MelodyDur = 0;
	if (MelodyNumberRythem == MelTemp.size())
	{
		MelodyNumberRythem = 0;
	}

	while (MelodyDurSum < 4)
	{
		MainMelodyNumber = MelTemp[MelodyNumberRythem].MelNumber;
		int NoteTypeRythem = MelTemp[MelodyNumberRythem].DurNote;

		if (NoteTypeRythem == 16)
		{
			MelodyDur = 30;
			MelodyDurSum += 1;
		}
		else if (NoteTypeRythem == 8)
		{
			MelodyDur = 60;
			MelodyDurSum += 2;
		}
		else if (NoteTypeRythem == 4)
		{
			MelodyDur = 120;
			MelodyDurSum += 4;
		}

		MIDITrack_InsertNote(aMIDITrack, MelodyTime, 0, MelodyNotes[MainMelodyNumber], vels, MelodyDur);
		MelodyTime += MelodyDur;
		MelodyNumberRythem++;
	}
}

notes::notes()
{
}


notes::~notes()
{
}
