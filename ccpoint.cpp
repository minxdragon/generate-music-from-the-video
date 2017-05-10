#include "ccpoint.h"
#include "includes.h"

void ccpoint::CCpointHue(int Hue, int PreHue, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &ChangePointNumbers, int &ErrinFrame)
{
	double AbsDifHue = abs(Hue - PreHue);	// [ COLOR ] 色相の変更数
	if (AbsDifHue > 100)
	{
		ChangePoint[CheckChangePoint] = FrameNumber;	// [ CHANGE ]変化点を記録
		ChangePointErrsum[CheckChangePoint] = ErrinFrame;	// 移動距離合計を記録
		ErrinFrame = 0;		// 変化点に到達したので、移動距離合計をリセット
		CheckChangePoint += 1;						// [ CHANGE ]変化点を次へ
		ChangePointNumbers += 1;					// [ CHANGE ]変化点の数
	}
}


void ccpoint::CCpointStatus(std::vector<unsigned char> status, int *ChangePoint, int *ChangePointErrsum, const int FrameNumber, int &CheckChangePoint, int &ChangePointNumbers, int &ErrinFrame)
{
	// 変化点探索（ステータス）
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

			ChangePoint[CheckChangePoint] = FrameNumber;	// [ CHANGE ]変化点を記録
			ChangePointErrsum[CheckChangePoint] = ErrinFrame;	// 移動距離合計を記録
			ErrinFrame = 0;		// 変化点に到達したので、移動距離合計をリセット
			CheckChangePoint += 1;						// [ CHANGE ]変化点を次へ
			ChangePointNumbers += 1;					// [ CHANGE ]変化点の数
		}
	}
}

ccpoint::ccpoint()
{
}


ccpoint::~ccpoint()
{
}
