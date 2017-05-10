#include "colors.h"
#include <iostream>
#include <algorithm>
#include <functional>

#define TO_STRING(VariableName) # VariableName

template
<
typename TYPE,
std::size_t SIZE
>

std::size_t array_length(const TYPE(&)[SIZE])
{
	return SIZE;
}

double colors::CalcMax(int *Numbers, int Members)
{

	int CalcedMax = Numbers[0];

	for (int i = 1; i < Members; ++i){
		if (CalcedMax < Numbers[i])
		{
			CalcedMax = Numbers[i];
		}
	}

	return CalcedMax;
}

int colors::CalcMaxforVector(std::vector<int> Numbers)
{
	int CalcedMax = Numbers[0];
	int MaxNumber=0;

	for (int i = 1; i < Numbers.size(); ++i){
		if (CalcedMax < Numbers[i])
		{
			CalcedMax = Numbers[i];
			MaxNumber = i;
		}
	}

	return MaxNumber;
}

double colors::CalcMin(int *Numbers, int Members) {

	int CalcedMin = Numbers[0];

	for (int i = 1; i < Members; ++i){
		if (CalcedMin > Numbers[i]){
			CalcedMin = Numbers[i];
		}
	}
	return CalcedMin;
}

cv::Mat colors::CalcAve(cv::Mat ImageCaptureMat)
{
	int SumBlue = 0, SumGreen = 0, SumRed = 0, SumPix = 0;
	const double ImageCols = ImageCaptureMat.cols, ImageRows = ImageCaptureMat.rows; // 画像のヨコ

	for (int x = 0; x < ImageRows; x++)
	{
		for (int y = 0; y < ImageCols; y++)
		{
			cv::Vec3b BGR = ImageCaptureMat.at<cv::Vec3b>(x, y);
			uchar Blue = BGR.val[0];
			uchar Green = BGR.val[1];
			uchar Red = BGR.val[2];

			SumBlue += Blue;
			SumGreen += Green;
			SumRed += Red;
			SumPix += 1;
		}
	}

	const int AverageBlue = SumBlue / SumPix;
	const int AverageGreen = SumGreen / SumPix;
	const int AverageRed = SumRed / SumPix;

	cv::Mat AverageImageMat(cv::Size(320, 240), CV_8UC3, cv::Scalar(AverageBlue, AverageGreen, AverageRed));	// RGB順番入れ替え前

	return AverageImageMat;
}

double colors::CalcAverage(cv::Mat ImageCaptureMat)
{
	int SumBlue = 0, SumGreen = 0, SumRed = 0, SumPix = 0;
	const double ImageCols = ImageCaptureMat.cols, ImageRows = ImageCaptureMat.rows;

	for (int x = 0; x < ImageRows; x++)
	{
		for (int y = 0; y < ImageCols; y++)
		{
			cv::Vec3b BGR = ImageCaptureMat.at<cv::Vec3b>(x, y);
			uchar Blue = BGR.val[0];
			uchar Green = BGR.val[1];
			uchar Red = BGR.val[2];

			SumBlue += Blue;
			SumGreen += Green;
			SumRed += Red;
			SumPix += 1;
		}
	}

	const int AverageBlue = SumBlue / SumPix;
	const int AverageGreen = SumGreen / SumPix;
	const int AverageRed = SumRed / SumPix;

	int ImageBGR[3];
	ImageBGR[0] = AverageBlue;
	ImageBGR[1] = AverageGreen;
	ImageBGR[2] = AverageRed;

	double Hue = ConvertRGBtoHue(ImageBGR);

	return Hue;

}

// RGBをHSVに変換する関数
double colors::ConvertRGBtoHue(int *ImageBGR)
{
	const double MaxRGB = CalcMax(ImageBGR, 3);
	const double MinRGB = CalcMin(ImageBGR, 3);
	const double Blue = ImageBGR[0];
	const double Green = ImageBGR[1];
	const double Red = ImageBGR[2];

	double Hue = 0;

	if (MaxRGB == MinRGB)
	{
		Hue = 0;
	}
	else if (MaxRGB == Blue){
		Hue = 60 * ((Red - Green) / (MaxRGB - MinRGB)) + 240;
	}
	else if (MaxRGB == Green){
		Hue = 60 * ((Blue - Red) / (MaxRGB - MinRGB)) + 120;
	}
	else if (MaxRGB == Red){
		Hue = 60 * ((Green - Blue) / (MaxRGB - MinRGB)) + 0;
	}

	if (Hue < 0)
	{
		Hue += 360;
	}

	return Hue;
}

// 画像内で頻出三色を探す関数
void colors::FrequentColorInFrame(cv::Mat ImageCaptureMat, int *TopHSV)
{
	const double ImageCols = ImageCaptureMat.cols, ImageRows = ImageCaptureMat.rows; // 画像のヨコ
	int HueRYGLBVBW[8] = { 0 };	// 0=Red, 1=Yellow, 2=Green, 3=LightBlue, 4=Blue, 5=Violet, 6=Black, 7=White
	int SatRYGLBVBW[8] = { 0 };	// 0=Red, 1=Yellow, 2=Green, 3=LightBlue, 4=Blue, 5=Violet, 6=Black, 7=White
	int ValRYGLBVBW[8] = { 0 };	// 0=Red, 1=Yellow, 2=Green, 3=LightBlue, 4=Blue, 5=Violet, 6=Black, 7=White
	int SumPix = 0;

	for (int x = 0; x < ImageRows; x++)
	{
		for (int y = 0; y < ImageCols; y++)
		{
			int ImageBGR[3];
			cv::Vec3b BGR = ImageCaptureMat.at<cv::Vec3b>(x, y);
			ImageBGR[0] = BGR.val[0];
			ImageBGR[1] = BGR.val[1];
			ImageBGR[2] = BGR.val[2];

			const double MaxRGB = CalcMax(ImageBGR, 3);
			const double MinRGB = CalcMin(ImageBGR, 3);
			const double Hue = ConvertRGBtoHue(ImageBGR);
			const double Sat = CalcSat(MaxRGB, MinRGB);
			const double Val = MaxRGB;

			if (Val < 30)	// Black
			{
				HueRYGLBVBW[7] += 1;
				SatRYGLBVBW[7] += Sat;
				ValRYGLBVBW[7] += Val;
			}
			else if (250 < Val && Sat < 30)		// White
			{
				HueRYGLBVBW[6] += 1;
				SatRYGLBVBW[6] += Sat;
				ValRYGLBVBW[6] += Val;
			}
			else if (Hue < 30 || 330 <= Hue)	// Red
			{
				HueRYGLBVBW[0] += 1;
				SatRYGLBVBW[0] += Sat;
				ValRYGLBVBW[0] += Val;
			}
			else if (30 <= Hue && Hue < 90)		// Yellow
			{
				HueRYGLBVBW[1] += 1;
				SatRYGLBVBW[1] += Sat;
				ValRYGLBVBW[1] += Val;
			}
			else if (90 <= Hue && Hue < 150)	// Green
			{
				HueRYGLBVBW[2] += 1;
				SatRYGLBVBW[2] += Sat;
				ValRYGLBVBW[2] += Val;
			}
			else if (150 <= Hue && Hue < 210)	// LightBlue
			{
				HueRYGLBVBW[3] += 1;
				SatRYGLBVBW[3] += Sat;
				ValRYGLBVBW[3] += Val;
			}
			else if (210 <= Hue && Hue < 270)	// Blue
			{
				HueRYGLBVBW[4] += 1;
				SatRYGLBVBW[4] += Sat;
				ValRYGLBVBW[4] += Val;
			}
			else if (270 <= Hue && Hue < 330)	// Violet
			{
				HueRYGLBVBW[5] += 1;
				SatRYGLBVBW[5] += Sat;
				ValRYGLBVBW[5] += Val;
			}
			SumPix += 1;
		}
	}

	// ソートする（元の変数は使用するので別の変数を作成してソート）
	int HueSorted[6] = { HueRYGLBVBW[0], HueRYGLBVBW[1], HueRYGLBVBW[2], HueRYGLBVBW[3], HueRYGLBVBW[4], HueRYGLBVBW[5] };
	std::sort(HueSorted, HueSorted + 6, std::greater<int>());

	// トップ３がRYGLBVのどれに当たるのか
	int Tops[3] = { 0, 0, 0 };
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (HueSorted[j] == HueRYGLBVBW[i])
			{
				Tops[j] = i;
			}
		}
	}

	for (int a = 0; a < 3; a++)
	{
		SatRYGLBVBW[Tops[a]] /= SumPix;
		ValRYGLBVBW[Tops[a]] /= SumPix;
	}

	TopHSV[0] = Tops[0];
	TopHSV[1] = SatRYGLBVBW[Tops[0]];
	TopHSV[2] = ValRYGLBVBW[Tops[0]];

	return;
}


void colors::FrequentColorforSymbal(cv::Mat ImageCaptureMat, std::vector <int> &SymbalsColor, std::vector<int> &SymbalsVal, int &SymbalPoints)
{
	const double ImageCols = ImageCaptureMat.cols, ImageRows = ImageCaptureMat.rows; // 画像のヨコ

	for (int x = 0; x < ImageRows; x++)
	{
		for (int y = 0; y < ImageCols; y++)
		{
			int ImageBGR[3];
			cv::Vec3b BGR = ImageCaptureMat.at<cv::Vec3b>(x, y);
			ImageBGR[0] = BGR.val[0];
			ImageBGR[1] = BGR.val[1];
			ImageBGR[2] = BGR.val[2];

			const double MaxRGB = CalcMax(ImageBGR, 3);
			const double MinRGB = CalcMin(ImageBGR, 3);
			const double Hue = ConvertRGBtoHue(ImageBGR);
			const double Sat = CalcSat(MaxRGB, MinRGB);
			const double Val = MaxRGB;

			if (Val < 30)	// Black
			{
				SymbalsColor[15] += 1;
			}
			else if (250 < Val && Sat < 30)		// White
			{
				SymbalsColor[8] += 1;
			}
			else if (Hue < 30 || 330 <= Hue)	// Red
			{
				SymbalsColor[13] += 1;
			}
			else if (30 <= Hue && Hue < 90)		// Yellow
			{
				SymbalsColor[12] += 1;
			}
			else if (90 <= Hue && Hue < 150)	// Green
			{
				SymbalsColor[0] += 1;
			}
			else if (150 <= Hue && Hue < 210)	// LightBlue
			{
				SymbalsColor[9] += 1;
			}
			else if (210 <= Hue && Hue < 270)	// Blue
			{
				SymbalsColor[11] += 1;
			}
			else if (270 <= Hue && Hue < 330)	// Violet
			{
				SymbalsColor[10] += 1;
			}

			if (120 < Hue && Hue < 300)	// cold
			{
				if (Val < 60)
				{
					SymbalsVal[5] += 1;
				}
				else
				{
					SymbalsVal[4] += 1;
				}
			}
			else //warm
			{
				if (Val < 60)
				{
					SymbalsVal[2] += 1;
				}
				else
				{
					SymbalsVal[7] += 1;
				}
			}
			SymbalPoints += 1;
		}
	}

	return;
}

void colors::FrequentNumber(const int *SumRYGLBVBW, int *TopColors)
{
	int HueSorted[6] = { SumRYGLBVBW[0], SumRYGLBVBW[1], SumRYGLBVBW[2], SumRYGLBVBW[3], SumRYGLBVBW[4], SumRYGLBVBW[5] };
	std::sort(HueSorted, HueSorted + 6, std::greater<int>());

	// トップ３がRYGLBVのどれに当たるのか
	for (int a = 0; a < 4; a++) TopColors[a] = 0;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (HueSorted[j] == SumRYGLBVBW[i])
			{
				TopColors[j] = i;
			}
		}
	}

	return;
}

void colors::CountNumber(const int *TopHSV, int *SumRYGLBVBW)
{

	if (TopHSV[0] == 7)				// Black
	{
		SumRYGLBVBW[7] += 1;
	}
	else if (TopHSV[0] == 6)		// White
	{
		SumRYGLBVBW[6] += 1;
	}
	else if (TopHSV[0] == 0)		// Red
	{
		SumRYGLBVBW[0] += 1;
	}
	else if (TopHSV[0] == 1)		// Yellow
	{
		SumRYGLBVBW[1] += 1;
	}
	else if (TopHSV[0] == 2)		// Green
	{
		SumRYGLBVBW[2] += 1;
	}
	else if (TopHSV[0] == 3)		// LightBlue
	{
		SumRYGLBVBW[3] += 1;
	}
	else if (TopHSV[0] == 4)		// Blue
	{
		SumRYGLBVBW[4] += 1;
	}
	else if (TopHSV[0] == 5)		// Violet
	{
		SumRYGLBVBW[5] += 1;
	}

	return;
}

int colors::CalcSat(const int MaxRGB, const int MinRGB){

	int Sat;

	if (MaxRGB == 0)
	{
		Sat = 0;
	}
	else
	{
		Sat = ((MaxRGB - MinRGB) / MaxRGB) * 255;
	}

	return Sat;
}

double colors::AveValinImage(const cv::Mat NowImageCaptureMat)
{

	int SumBlue = 0, SumGreen = 0, SumRed = 0, SumPix = 0;
	const double ImageCols = NowImageCaptureMat.cols, ImageRows = NowImageCaptureMat.rows; // 画像のヨコ
	int ImageBGR[3] = {};

	for (int x = 0; x < ImageRows; x++)
	{
		for (int y = 0; y < ImageCols; y++)
		{
			cv::Vec3b BGR = NowImageCaptureMat.at<cv::Vec3b>(x, y);

			SumBlue += BGR.val[0];
			SumGreen += BGR.val[1];
			SumRed += BGR.val[2];

			SumPix += 1;
		}
	}

	ImageBGR[0] = SumBlue / SumPix;
	ImageBGR[1] = SumGreen / SumPix;
	ImageBGR[2] = SumRed / SumPix;

	const double MaxRGB = CalcMax(ImageBGR, 3);
	const double Val = (MaxRGB / 255) * 100;

	return Val;

}
colors::colors()
{
}


colors::~colors()
{
}
