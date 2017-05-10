#ifndef INVEST_H
#define INVEST_H

#include <QtWidgets/QMainWindow>
#include "ui_invest.h"

class invest : public QMainWindow
{
	Q_OBJECT

public:
	invest(QWidget *parent = 0);
	~invest();

public slots:
	void on_ButtonMakeMidi_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonChoseVideo_clicked();
	void on_ButtonEnd_clicked();
	void on_ButtonChoseSave_clicked();
	void keyPressEvent(QKeyEvent *event);
	void handleSelectionChanged(int index);
	void handleSelectionChangedSub(int index);

private:
	Ui::investClass ui;

};

#endif // INVEST_H
