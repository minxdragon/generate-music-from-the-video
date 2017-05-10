#pragma once
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <windows.h>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

//CV
#include <opencv2/opencv.hpp>
#include <opencv2/superres/optical_flow.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


//MIDI
#include <MIDIData.h>

//Qt
#include <QUrl>
#include <QtGui/QIcon>
#include <QRgb>
#include <QImage>
#include <QColor>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QTime>

struct MusicComp
{
	int MelNumber;
	int DurNote;
};