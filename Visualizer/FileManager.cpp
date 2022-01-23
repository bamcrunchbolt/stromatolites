#include "FileManager.h"
#include <iostream>

FileManager::FileManager()
{
	dataStream.setDevice(&file);
}

int FileManager::openFile(QString fileName, SimulationProperties& properties, std::vector<int>& particles)
{
	file.setFileName(fileName);

	/* Try to open file */
	if(!file.open(QIODevice::ReadOnly))
	{
		file.close();

		return 0;
	}

	QString header;
	dataStream >> header;

	/* Check file version */
	if(header.compare("DLA 3D EXT 1.2") != 0)
	{
		file.close();
		std::cout<<"Header does not say DLA 3D EXT 1.2\n";

		return 0;
	}

	/* Read variable values */
	bool b;
	unsigned int value;
	QVector<unsigned int> values;

	/* Read attraction */
	dataStream >> b;
	if(b)
		dataStream >> value;
	else
		dataStream >> values;

	if(!readVariableValue(properties.attractionDistance, b, value, values, 0, 40))
	{
		file.close();
		std::cout<<"Attraction distance out of range.\n";

		
		return 0;
	}

	/* Read stability */
	dataStream >> b;
	if(b)
		dataStream >> value;
	else
		dataStream >> values;

	if(!readVariableValue(properties.stabilityDistance, b, value, values, 1, 20))
	{
		file.close();
		std::cout<<"Stability distance out of range.\n";

		return 0;
	}

	/* Read vertical movement index */
	dataStream >> b;
	if(b)
		dataStream >> value;
	else
		dataStream >> values;

	if(!readVariableValue(properties.verticalMovementIndex, b, value, values, 0, 10))
	{
		file.close();
		std::cout<<"Vertical movement out of range.\n";

		return 0;
	}

	/* Read sedimentation */
	dataStream >> b;
	if(b)
		dataStream >> value;
	else
		dataStream >> values;

	if(!readVariableValue(properties.sedimentation, b, value, values, 0, 100))
	{
		file.close();
		std::cout<<"Sedimentation frequency out of range.\n";

		return 0;
	}

	/* Read sizes and sedimentation distance */
	int sizeBase, sizeHeight, sedimentationDistance;

	dataStream >> sizeBase >> sizeHeight >> sedimentationDistance;
	
	properties.sizeBase = sizeBase;
	if(properties.sizeBase < 50 || properties.sizeBase > 200)
	{
		file.close();
		std::cout<<"sizeBase out of range\n";

		return 0;
	}

	properties.sizeHeight = sizeHeight;
	if(properties.sizeHeight < 50 || properties.sizeHeight > 200)
	{
		file.close();
		std::cout<<"sizeHeight out of range.\n";

		return 0;
	}

	properties.sedimentationDistance = sedimentationDistance;
	if(properties.sedimentationDistance < 1 || properties.sedimentationDistance > 5)
	{
		file.close();
		std::cout<<"Sedimentation distance out of range.\n";

		return 0;
	}

	/* Read particles */
	std::fill(particles.begin(), particles.end(), 0);
	int particleCount = 0;

	quint16 x, y, z;

	while(!dataStream.atEnd())
	{
		dataStream >> x >> z >> y;
//		std::cout<<"Particle count = " << particleCount << "\n";

		if(y < 512){
			particles[x + y * properties.sizeBase + z * properties.sizeBase * properties.sizeBase] = ++particleCount;
//			std::cout<<"y = " << y << "\ny < 512.\n";
		}
		else if(y < 1024)
		{
			particleCount++;
			particles[x + (y - 512) * properties.sizeBase + z * properties.sizeBase * properties.sizeBase] = -particleCount;
//			std::cout<<"y = " << y << "\ny < 1024.\n";
		}
		else{
	//		std::cout<<"y = " << y << "\n";
			particles[x + (y - 1024) * properties.sizeBase + z * properties.sizeBase * properties.sizeBase] = INT_MAX;
	//		std::cout<<"Particle = " << INT_MAX << ".\n";
		}
	}
//	std::cout<<"Particle count = " << particleCount << "\n";
	//std::cout<<"Closing file \n";
	file.close();	
	return particleCount;
}

bool FileManager::readVariableValue(VariableValue& variableValue, bool isConstant, unsigned int value, const QVector<unsigned int>& values, unsigned int min, unsigned int max)
{
	variableValue.isConstant = isConstant;

	if(isConstant)
	{
		if(value < min || value > max)
			return false;

		variableValue.constantValue = value;
	}
	else
	{
		for(int i = 0; i < 10; i++)
			if(values[i] < min || values[i] > max)
				return false;

		variableValue.values = values.toStdVector();
	}

	return true;
}
