#ifndef INITIAL_SURFACE_DIALOG_H
#define INITIAL_SURFACE_DIALOG_H

#include <QtGui>
#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QAbstractButton>
#include<QtCore>


#include "DataStructures.h"

class InitialSurfaceDialog: public QDialog {
Q_OBJECT

public:
	InitialSurfaceDialog(QWidget *parent = 0);

	InitialSurfaceSettings ISS();
	void ISS(InitialSurfaceSettings settings);

private:
	QGroupBox *groupBox1;
	QRadioButton *radioButton1;
	QRadioButton *radioButton2;
	QRadioButton *radioButton3;
	QRadioButton *radioButton4;
	QRadioButton *radioButton5;

	QGroupBox *groupBox2;
	QCheckBox *checkBox1;
	QCheckBox *checkBox2;
	QLabel *label0;
	QSpinBox *spinBox0;
	QLabel *label1;
	QSpinBox *spinBox1;
	QLabel *label2;
	QSpinBox *spinBox2;
	QLabel *label3;
	QSpinBox *spinBox3;
	QLabel *label4;
	QSpinBox *spinBox4;
	QLabel *label5;
	QSpinBox *spinBox5;

	QPushButton *pushButton1;
	QPushButton *pushButton2;

	void createWidgets();
	void createLayout();
	void createConnections();

private slots:
	void enableWidgets();
};

#endif
