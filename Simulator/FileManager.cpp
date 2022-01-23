#include "FileManager.h"

FileManager::FileManager() {
	dataStream.setDevice(&file);
	folder = QString("");
}

void FileManager::setFolder(const QString &f) {
	folder = f;
}

QString FileManager::getCurrentFileName() {
	return file.fileName().left(file.fileName().size() - 4);
}

bool FileManager::openFile(const SimulationSettings &settings) {
	QString fileName;

	while (true) //try to open the file till it succeeds
	{
		//QDate date = QDate::currentDate();
		QTime time = QTime::currentTime();
		QString currentTime = QString("%1%2%3%4").arg(time.hour(), 2, 10, QChar('0')).arg(
						time.minute(), 2, 10, QChar('0')).arg(time.second(), 2,
						10, QChar('0')).arg(time.msec(), 2, 10, QChar('0'));

		int surfVal = settings.initialSurfaceSettings.type;
		QString surface = "noSurface";

		if (surfVal==INIT_FLAT){
			surface = "flat";
		}else if (surfVal==INIT_SPIKE){
			surface = "spike-" + QString::number(settings.initialSurfaceSettings.spikeFactor);
			if (settings.initialSurfaceSettings.spikeField==true){
				surface += "_field-" + QString::number(settings.initialSurfaceSettings.spikeSpacing);
			}
		}else if(surfVal == INIT_SINUSOIDAL){
			surface = "sin";
		}else if(surfVal == INIT_RANDOM){
			surface = "random";
		}else if(surfVal == INIT_DISKS){
			surface = "disk";
		}

		VariableValue sedVal = settings.sedimentation;
		QString sed;
		if (sedVal.isConstant){
			sed = "sed-"+ QString::number(sedVal.constantValue);
		}else if(!sedVal.isConstant){
			sed = "sed-variable";
		}

		VariableValue aRVal = settings.attractionDistance;
				QString aR;
				if (aRVal.isConstant){
					aR = "aR-"+ QString::number(aRVal.constantValue);
				}else if(!aRVal.isConstant){
					aR = "aR-variable";
				}

		VariableValue sRVal = settings.stabilityDistance;
						QString sR;
						if (sRVal.isConstant){
							sR = "sR-"+ QString::number(sRVal.constantValue);
						}else if(!sRVal.isConstant){
							sR = "sR-variable";
						}

		fileName = surface + "_" + sed + "_" + aR + "_" + sR + "_" + currentTime;

		if (folder.isEmpty())
			fileName += ".d3e";
		else
			fileName = folder + "/" + fileName + ".d3e";

		if (file.exists(fileName)) //if file already exists, wait a second and try again
				{
			clock_t endWait = clock() + CLOCKS_PER_SEC;
			while (clock() < endWait) {
			}
		} else
			break;
	}

	file.setFileName(fileName);

	if (!file.open(QIODevice::WriteOnly)) //try to open file
		return false;

	dataStream << QString("DLA 3D EXT 1.2");
	writeVariableValue(settings.attractionDistance);
	writeVariableValue(settings.stabilityDistance);
	writeVariableValue(settings.verticalMovementIndex);
	writeVariableValue(settings.sedimentation);
	dataStream << settings.sizeBase << settings.sizeHeight
			<< settings.sedimentationDistance;

	return true;
}

void FileManager::closeFile() {
	file.close();
}

void FileManager::writeParticle(quint16 x, quint16 y, quint16 z) {
	dataStream << x << y << z;
}

void FileManager::writeVariableValue(const VariableValue &value) {
	dataStream << value.isConstant;

	if (value.isConstant)
		dataStream << value.constantValue;
	else
		dataStream << QVector<unsigned int>::fromStdVector(value.values);
}
