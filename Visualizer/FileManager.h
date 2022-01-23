/* Manage DLA 3D EXT files */
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <climits>

#include <QFile>
#include <QVector>

#include "DataStructures.h"

/* A class to load DLA 3D EXT files */
class FileManager
{
public:
	FileManager();

	int openFile(QString fileName, SimulationProperties& properties, std::vector<int>& particles); //return particle count or 0 if failure

private:
	QFile file;
	QDataStream dataStream;

	bool readVariableValue(VariableValue& variableValue, bool isConstant, unsigned int value, const QVector<unsigned int>& values, unsigned int min, unsigned int max);
};

#endif