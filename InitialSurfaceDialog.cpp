#include "InitialSurfaceDialog.h"
#include "InitialSurfaceDialog.moc"


InitialSurfaceDialog::InitialSurfaceDialog(QWidget *parent) :
		QDialog(parent) {
	createWidgets();
	createLayout();
	createConnections();

	setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint);
	setWindowTitle("Pick initial surface");
	adjustSize();
	setMinimumSize(size());
	setMaximumSize(size());
	move(parentWidget()->parentWidget()->rect().center() - rect().center());
}

InitialSurfaceSettings InitialSurfaceDialog::ISS() {
	InitialSurfaceSettings result;

	if (radioButton1->isChecked())
		result.type = INIT_FLAT;
	else if (radioButton2->isChecked())
		result.type = INIT_SINUSOIDAL;
	else if (radioButton3->isChecked())
		result.type = INIT_RANDOM;
	else if (radioButton4->isChecked())
		result.type = INIT_DISKS;
	else if (radioButton5->isChecked())
		result.type = INIT_SPIKE;
	if (checkBox1->isChecked())
		result.spikeBottom = true;
	else
		result.spikeBottom = false;
	if (checkBox2->isChecked())
			result.spikeField = true;
		else
			result.spikeField = false;

	result.spikeSpacing = spinBox0->value();
	result.amplitude = spinBox1->value();
	result.widthFrequency = spinBox2->value();
	result.depthFrequency = spinBox3->value();
	result.radius = spinBox4->value();
	result.spikeFactor = spinBox5->value();

	return result;
}

void InitialSurfaceDialog::ISS(InitialSurfaceSettings settings) {
	switch (settings.type) {
	case INIT_FLAT:
		radioButton1->setChecked(true);
		break;
	case INIT_SINUSOIDAL:
		radioButton2->setChecked(true);
		break;
	case INIT_RANDOM:
		radioButton3->setChecked(true);
		break;
	case INIT_DISKS:
		radioButton4->setChecked(true);
		break;
	case INIT_SPIKE:
		radioButton5->setChecked(true);
		break;
	}

	spinBox0->setValue(settings.spikeSpacing);
	spinBox1->setValue(settings.amplitude);
	spinBox2->setValue(settings.widthFrequency);
	spinBox3->setValue(settings.depthFrequency);
	spinBox4->setValue(settings.radius);
	spinBox5->setValue(settings.spikeFactor);
}

void InitialSurfaceDialog::createWidgets() {
	groupBox1 = new QGroupBox("Type", this);
	radioButton1 = new QRadioButton("Flat", this);
	radioButton1->setChecked(true);
	radioButton2 = new QRadioButton("Sinusoidal", this);
	radioButton3 = new QRadioButton("Random", this);
	radioButton4 = new QRadioButton("Disk", this);
	radioButton5 = new QRadioButton("Spike", this);

	groupBox2 = new QGroupBox("Settings", this);
	checkBox1 = new QCheckBox("Spike on random (bumpy) surface?", this);
	checkBox1->setDisabled(true);
	checkBox2 = new QCheckBox("Spike field?", this);
	checkBox2->setDisabled(true);
	label0 = new QLabel("Spike spacing", this);
	label0->setDisabled(true);
	spinBox0 = new QSpinBox(this);
	spinBox0->setRange(2, 40);
	spinBox0->setValue(2);
	spinBox0->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox0->setDisabled(true);
	label1 = new QLabel("Amplitude", this);
	label1->setDisabled(true);
	spinBox1 = new QSpinBox(this);
	spinBox1->setRange(5, 50);
	spinBox1->setValue(20);
	spinBox1->setSuffix("%");
	spinBox1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox1->setDisabled(true);
	label2 = new QLabel("Width frequency", this);
	label2->setDisabled(true);
	spinBox2 = new QSpinBox(this);
	spinBox2->setRange(1, 40);
	spinBox2->setValue(1);
	spinBox2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox2->setDisabled(true);
	label3 = new QLabel("Depth frequency", this);
	label3->setDisabled(true);
	spinBox3 = new QSpinBox(this);
	spinBox3->setRange(1, 40);
	spinBox3->setValue(1);
	spinBox3->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox3->setDisabled(true);
	label4 = new QLabel("Radius", this);
	label4->setDisabled(true);
	spinBox4 = new QSpinBox(this);
	spinBox4->setRange(1, 45);
	spinBox4->setValue(10);
	spinBox4->setSuffix("%");
	spinBox4->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox4->setDisabled(true);
	label5 = new QLabel("Spike height (% of max height)", this);
	label5->setDisabled(true);
	spinBox5 = new QSpinBox(this);
	spinBox5->setRange(1, 100);
	spinBox5->setValue(50);
	spinBox5->setSuffix("%");
	spinBox5->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	spinBox5->setDisabled(true);

	pushButton1 = new QPushButton("Accept", this);
	pushButton2 = new QPushButton("Cancel", this);
}

void InitialSurfaceDialog::createLayout() {
	QHBoxLayout *layout1 = new QHBoxLayout(groupBox1);
	layout1->addWidget(radioButton1);
	layout1->addWidget(radioButton2);
	layout1->addWidget(radioButton3);
	layout1->addWidget(radioButton4);
	layout1->addWidget(radioButton5);

	groupBox1->setLayout(layout1);

	QGridLayout *layout2 = new QGridLayout(groupBox2);
	layout2->addWidget(checkBox1, 0, 0);
	layout2->addWidget(checkBox2, 0, 1);
	layout2->addWidget(label0, 0, 2);
	layout2->addWidget(spinBox0, 0, 3);
	layout2->addWidget(label1, 1, 0);
	layout2->addWidget(spinBox1, 1, 1);
	layout2->addWidget(label2, 1, 2);
	layout2->addWidget(spinBox2, 1, 3);
	layout2->addWidget(label3, 2, 0);
	layout2->addWidget(spinBox3, 2, 1);
	layout2->addWidget(label4, 3, 0);
	layout2->addWidget(spinBox4, 3, 1);
	layout2->addWidget(label5, 4, 0);
	layout2->addWidget(spinBox5, 4, 1);
	groupBox2->setLayout(layout2);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(groupBox1, 0, 0, 1, 4);
	layout->addWidget(groupBox2, 1, 0, 1, 4);
	layout->addWidget(pushButton1, 2, 2);
	layout->addWidget(pushButton2, 2, 3);
	setLayout(layout);
}

void InitialSurfaceDialog::createConnections() {
	connect(radioButton1, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));
	connect(radioButton2, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));
	connect(radioButton3, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));
	connect(radioButton4, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));
	connect(radioButton5, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));
	connect(checkBox1, SIGNAL(toggled(bool)), this, SLOT(enableWidgets()));

	connect(pushButton1, SIGNAL(pressed()), this, SLOT(accept()));
	connect(pushButton2, SIGNAL(pressed()), this, SLOT(reject()));
}

void InitialSurfaceDialog::enableWidgets() {
	int n = 0;

	if (radioButton1->isChecked())
		n = 1;
	else if (radioButton2->isChecked())
		n = 2;
	else if (radioButton3->isChecked())
		n = 3;
	else if (radioButton4->isChecked())
		n = 4;
	else if (radioButton5->isChecked())
		n = 5;
	if (checkBox1->isChecked())
		n = 6;
	if (checkBox2->isChecked())
			n = 7;

	checkBox1->setEnabled(n==5 || n==6);
	checkBox2->setEnabled(n==5 || n==6);
	label1->setEnabled(n == 2 || n == 3 || n==6);
	spinBox1->setEnabled(n == 2 || n == 3 || n==6);
	label2->setEnabled(n == 2);
	spinBox2->setEnabled(n == 2);
	label3->setEnabled(n == 2);
	spinBox3->setEnabled(n == 2);
	label4->setEnabled(n == 4);
	spinBox4->setEnabled(n == 4);
	label5->setEnabled(n == 5 || n == 6);
	spinBox5->setEnabled(n == 5 || n == 6);
	label0->setEnabled(n == 5 || n == 6 || n==7);
	spinBox0->setEnabled(n == 5 || n == 6 || n==7);


}
