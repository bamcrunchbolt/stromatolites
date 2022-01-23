/* Manage DLA 3D EXT files */
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <ctime>

#include <QDataStream>
#include <QDateTime>
#include <QFile>
#include <QVector>

#include "DataStructures.h"

/* A class to save DLA 3D EXT files */
class FileManager {
public:
	FileManager();

	void setFolder(const QString &f); //folder to save files
	QString getCurrentFileName(); //current file name without the extension

	bool openFile(const SimulationSettings &settings); //generate a file with data and time of creation in its name, and write header
	void closeFile();

	void writeParticle(quint16 x, quint16 y, quint16 z);
	void writeVariableValue(const VariableValue &value);

private:
	QFile file;
	QDataStream dataStream;
	QString folder;
};

#endif
