#ifndef SIMULATION_SETTINGS_DIALOG
#define SIMULATION_SETTINGS_DIALOG

#include <QtGui>
#include<QtCore>
#include<QString>
#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>



#include "VariableValueGroupBox.h"
#include "SizeGroupBox.h"
#include "InitialSurfaceDialog.h"

class SimulationSettingsDialog: public QDialog {
Q_OBJECT

public:
	SimulationSettingsDialog(QWidget *parent = 0);

	void mode(QString mode);

	SimulationSettings SS();
	void SS(SimulationSettings settings);

	int repetitions();
	void repetitions(int n);

private:
	VariableValueGroupBox *groupBox1;
	VariableValueGroupBox *groupBox2;
	VariableValueGroupBox *groupBox3;
	VariableValueGroupBox *groupBox4;

	QLabel *label2;
	QPushButton *pushButton3;
	InitialSurfaceDialog *initialSurfaceDialog;

	QLabel *label3;
	QSpinBox *spinBox2;

	SizeGroupBox *sizeGroupBox;

	QLabel *label1;
	QSpinBox *spinBox1;

	QPushButton *pushButton1;
	QPushButton *pushButton2;

	void createWidgets();
	void createLayout();
	void createConnections();

private slots:
	void repetitionsChanged();
	void pickInitialSurface();
};

#endif
