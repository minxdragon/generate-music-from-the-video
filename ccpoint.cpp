#include "ccpoint.h"
#include "includes.h"

void ccpoint::CCpointHue(int Hue, int PreHue, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &ChangePointNumbers, int &ErrinFrame)
{
	double AbsDifHue = abs(Hue - PreHue);	// [ COLOR ] �F���̕ύX��
	if (AbsDifHue > 100)
	{
		ChangePoint[CheckChangePoint] = FrameNumber;	// [ CHANGE ]�ω��_���L�^
		ChangePointErrsum[CheckChangePoint] = ErrinFrame;	// �ړ��������v���L�^
		ErrinFrame = 0;		// �ω��_�ɓ��B�����̂ŁA�ړ��������v�����Z�b�g
		CheckChangePoint += 1;						// [ CHANGE ]�ω��_������
		ChangePointNumbers += 1;					// [ CHANGE ]�ω��_�̐�
	}
}


void ccpoint::CCpointStatus(std::vector<unsigned char> status, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &ChangePointNumbers, int &ErrinFrame)
{
	// �ω��_�T���i�X�e�[�^�X�j
	int statusyes = 0;
	int statusno = 0;
	int statussize = status.size();

	for (int i = 0; i < statussize; i++)
	{
		if (status[i] == 1)
		{
			statusyes++;
		}
		else if (status[i] == 0)
		{
			statusno++;
		}
	}

	if (statusno > 60)
	{
		if (ChangePoint[(CheckChangePoint - 1)] != FrameNumber )
		{	

			ChangePoint[CheckChangePoint] = FrameNumber;	// [ CHANGE ]�ω��_���L�^
			ChangePointErrsum[CheckChangePoint] = ErrinFrame;	// �ړ��������v���L�^
			ErrinFrame = 0;		// �ω��_�ɓ��B�����̂ŁA�ړ��������v�����Z�b�g
			CheckChangePoint += 1;						// [ CHANGE ]�ω��_������
			ChangePointNumbers += 1;					// [ CHANGE ]�ω��_�̐�
		}
	}
}

ccpoint::ccpoint()
{
}


ccpoint::~ccpoint()
{
}
