#include "SimulationSettingsDialog.h"
#include "SimulationSettingsDialog.moc"


SimulationSettingsDialog::SimulationSettingsDialog(QWidget *parent) :
		QDialog(parent) {
	createWidgets();
	createLayout();
	createConnections();

	setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint);
	adjustSize();
	setMinimumSize(size());
	setMaximumSize(size());
	move(parentWidget()->rect().center() - rect().center());

	initialSurfaceDialog = new InitialSurfaceDialog(this);
}

void SimulationSettingsDialog::mode(QString mode) {
	setWindowTitle(mode + " simulation");
	pushButton1->setText(mode);
}

SimulationSettings SimulationSettingsDialog::SS() {
	SimulationSettings result;

	result.attractionDistance = groupBox1->VV();
	result.stabilityDistance = groupBox2->VV();
	result.verticalMovementIndex = groupBox3->VV();
	result.sedimentation = groupBox4->VV();
	result.sedimentationDistance = spinBox2->value();
	result.sizeBase = sizeGroupBox->sizeBase();
	result.sizeHeight = sizeGroupBox->sizeHeight();
	result.initialSurfaceSettings = initialSurfaceDialog->ISS();

	return result;
}

void SimulationSettingsDialog::SS(SimulationSettings settings) {
	groupBox1->VV(settings.attractionDistance);
	groupBox2->VV(settings.stabilityDistance);
	groupBox3->VV(settings.verticalMovementIndex);
	groupBox4->VV(settings.sedimentation);
	spinBox2->setValue(settings.sedimentationDistance);
	sizeGroupBox->sizeBase(settings.sizeBase);
	sizeGroupBox->sizeHeight(settings.sizeHeight);
	initialSurfaceDialog->ISS(settings.initialSurfaceSettings);

	switch (settings.initialSurfaceSettings.type) {
	case INIT_FLAT:
		pushButton3->setText("Flat");
		break;
	case INIT_SINUSOIDAL:
		pushButton3->setText("Sinusoidal");
		break;
	case INIT_RANDOM:
		pushButton3->setText("Random");
		break;
	case INIT_DISKS:
		pushButton3->setText("Disk");
		break;
	case INIT_SPIKE:
		pushButton3->setText("Spike");
		break;
	}
}

int SimulationSettingsDialog::repetitions() {
	return spinBox1->value();
}

void SimulationSettingsDialog::repetitions(int n) {
	spinBox1->setValue(n);
}

void SimulationSettingsDialog::createWidgets() {
	groupBox1 = new VariableValueGroupBox("Attraction radius", 0, 40, 1, "",
			this);
	groupBox2 = new VariableValueGroupBox("Stability radius", 1, 20, 1, "",
			this);
	groupBox3 = new VariableValueGroupBox("Vertical movement index", 0, 10, 5,
			"", this);
	groupBox4 = new VariableValueGroupBox("Sedimentation", 0, 100, 0, "%",
			this);

	sizeGroupBox = new SizeGroupBox(this);

	label2 = new QLabel("Initial surface", this);
	pushButton3 = new QPushButton("Flat", this);

	label3 = new QLabel("Sedimentation radius", this);
	spinBox2 = new QSpinBox(this);
	spinBox2->setRange(1, 5);
	spinBox2->setValue(1);
	spinBox2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	label1 = new QLabel("Repeat", this);
	spinBox1 = new QSpinBox(this);
	spinBox1->setRange(1, 999);
	spinBox1->setValue(1);
	spinBox1->setSuffix(" time ");
	spinBox1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	pushButton1 = new QPushButton("Add", this);
	pushButton2 = new QPushButton("Cancel", this);
}

void SimulationSettingsDialog::createLayout() {
	QGridLayout *layout = new QGridLayout();
	layout->addWidget(groupBox1, 0, 0, 1, 2);
	layout->addWidget(groupBox2, 0, 2, 1, 2);
	layout->addWidget(groupBox3, 1, 0, 1, 2);
	layout->addWidget(groupBox4, 1, 2, 1, 2);
	layout->addWidget(sizeGroupBox, 2, 0, 5, 2);
	layout->addWidget(label3, 2, 2);
	layout->addWidget(spinBox2, 2, 3);
	layout->addWidget(label2, 3, 2);
	layout->addWidget(pushButton3, 3, 3);
	layout->addWidget(label1, 4, 2);
	layout->addWidget(spinBox1, 4, 3);
	layout->addWidget(pushButton1, 6, 2);
	layout->addWidget(pushButton2, 6, 3);
	setLayout(layout);
}

void SimulationSettingsDialog::createConnections() {
	connect(pushButton3, SIGNAL(pressed()), this, SLOT(pickInitialSurface()));
	connect(spinBox1, SIGNAL(valueChanged(int)), this,
			SLOT(repetitionsChanged()));
	connect(pushButton1, SIGNAL(pressed()), this, SLOT(accept()));
	connect(pushButton2, SIGNAL(pressed()), this, SLOT(reject()));
}

void SimulationSettingsDialog::repetitionsChanged() {
	if (spinBox1->value() == 1)
		spinBox1->setSuffix(" time ");
	else
		spinBox1->setSuffix(" times");
}

void SimulationSettingsDialog::pickInitialSurface() {
	InitialSurfaceSettings iss = initialSurfaceDialog->ISS();

	if (initialSurfaceDialog->exec() == QDialog::Accepted) {
		switch (initialSurfaceDialog->ISS().type) {
		case INIT_FLAT:
			pushButton3->setText("Flat");
			break;
		case INIT_SINUSOIDAL:
			pushButton3->setText("Sinusoidal");
			break;
		case INIT_RANDOM:
			pushButton3->setText("Random");
			break;
		case INIT_DISKS:
			pushButton3->setText("Disk");
			break;
		case INIT_SPIKE:
			pushButton3->setText("Spike");
			break;
		}
	} else
		initialSurfaceDialog->ISS(iss);
}
