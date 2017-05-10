#pragma once
#include "includes.h"

class notes
{
public:
	void MajorCode(int Tonic, int *Scale, int Oktave);
	void MinorCode(int Tonic, int *Scale, int Oktave);
	void ChoseCode(const int *hsv, int *MelodyCodes, int *AccompCodes);
	void NoteHue(double hue, MIDITrack* aMIDITrack, int DurNote);
	int SetBPM(const int ErrAve);
	double ClacPlusFrame(const int BPM, const double FPS);
	void ChoseMainMelodyNumber(int &MelodyNumber, const int LRUDN, int NoChange, int &vels);
	void ChoseSubMelodyNumber(int &MelodyNumber, const int LRUDN, int NoChange, int &vels, int AngleError);
	int CalcMelodyDur(const int ErrAve, bool &HalfNote, int &NoteType);
	int CalcMelodyDurforRythem(const int ErrAve, int &NoteType);
	int CalcMelodyDurforSax(const int ErrAve, bool &HalfNote, int &NoteType);
	void InsertDrums(int &NotesInBar, int &DrumTime, MIDITrack* cMIDITrack,int SymbalsColNum,int SymbalsValNum);
	void InsertPiano(int &NotesInBar, int &PianoTime, MIDITrack* aMIDITrack);
	void InsertMelody(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &NotesInBar, int &MainMelodyNumber, int &NoChange, int &vels, int &MelodyTime, int *MelodyNotes, int &MelodyDur, MIDITrack* aMIDITrack);
	void InsertMelodyforRythem(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &MainMelodyNumber, int &NoChange, int &vels);
	void InsertSubMelody(cv::Mat NowImageCaptureMat, cv::Mat PreImageCaptureMat, int &NotesInBar, int &MainMelodyNumber, int &NoChange, int &vels, int &MelodyTime, int *MelodyNotes, int &MelodyDur, MIDITrack* aMIDITrack, int PlusMelody);
	void SwitchingMusic(int &SwitchMusic, int &DrumTime, MIDITrack* cMIDITrack, const int ChangePointNumbers, const int CountChangePoint, std::vector<int> ErrsumMaxFrame, int sabinumbers, int &countsabi);
	void InstOnOff(int &SwitchMusic, int &PianoSwitch, int &SaxSwitch, int &BassSwitch, int &DrumSwitch);
	void CheckSameMelNum(std::vector<MusicComp> MelTemp, int &MainMelodyNumber, const int AveAngle);
	void RepeatRythem(int &MelodyNumberRythem, const std::vector<MusicComp> MelTemp, int &MainMelodyNumber, MIDITrack* aMIDITrack, int &MelodyTime, int &vels, int *MelodyNotes);

	notes();
	~notes();
};

