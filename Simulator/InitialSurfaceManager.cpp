#include "InitialSurfaceManager.h"

InitialSurfaceManager::InitialSurfaceManager() {
}

int InitialSurfaceManager::makeInitialSurface(std::vector<char> &particlesField,
		InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
		int sizeBaseSquare) {
	particlesField.resize(sizeBaseSquare * (sizeHeight + 40)); //add 40, this is the maximum attractionDistance
	std::fill(particlesField.begin(), particlesField.end(),
			static_cast<char>(NONE));

	switch (settings.type) {
	case INIT_FLAT:
		return makeFlat(particlesField, sizeBaseSquare);
	case INIT_SINUSOIDAL:
		return makeSinusoidal(particlesField, settings, sizeBase, sizeHeight,
				sizeBaseSquare);
	case INIT_RANDOM:
		return makeRandom(particlesField, settings, sizeBase, sizeHeight,
				sizeBaseSquare);
	case INIT_SPIKE:
			return makeSpike(particlesField, settings, sizeBase, sizeHeight, sizeBaseSquare);
	case INIT_DISKS:
		return makeCircles(particlesField, settings, sizeBase);
	}

	return 0;
}

int InitialSurfaceManager::makeFlat(std::vector<char> &particlesField,
		int sizeBaseSquare) {
	for (int i = 0; i < sizeBaseSquare; i++)
		particlesField[i] = NORMAL;

	return 0;
}

int InitialSurfaceManager::makeSinusoidal(std::vector<char> &particlesField,
		InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
		int sizeBaseSquare) {
	int currentHeight = 0;
	int maxHeight, k;
	float w, d, h;

	for (int i = 0; i < sizeBase; i++) {
		for (int j = 0; j < sizeBase; j++) {
			w = sin(settings.widthFrequency * i * 3.141592654f / sizeBase);
			d = sin(settings.depthFrequency * j * 3.141592654f / sizeBase);
			h = settings.amplitude * sizeHeight * 0.01f;

			if (w < 0.0f)
				w = -w;
			if (d < 0.0f)
				d = -d;

			maxHeight = static_cast<int>(w * d * h) + 1;
			if (maxHeight > static_cast<int>(h))
				maxHeight = static_cast<int>(h);

			for (k = 0; k < maxHeight; k++)
				particlesField[i + j * sizeBase + k * sizeBaseSquare] = NORMAL;

			if (k > currentHeight)
				currentHeight = k;
		}
	}

	return currentHeight;
}

int InitialSurfaceManager::makeRandom(std::vector<char> &particlesField,
		InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
		int sizeBaseSquare) {
	int currentHeight = 0;
	int count = sizeBaseSquare / 250;
	int maxHeight = settings.amplitude * sizeHeight / 100 - 1;
	int x, y, z;
	int a, b, c, maxC;

	for (int index = 0; index < sizeBaseSquare; index++)
		particlesField[index] = NORMAL;

	for (int n = 0; n < count; n++) {
		x = static_cast<int>(random.next() * sizeBase);
		y = static_cast<int>(random.next() * sizeBase);
		z = static_cast<int>(random.next() * maxHeight) + 1;

		for (int i = x - z; i <= x + z; i++) {
			for (int j = y - z; j <= y + z; j++) {
				maxC = z- static_cast<int>(Vector3i(x - i, 0, y - j).magnitude());

				for (c = 0; c <= maxC; c++) {
					a = i;
					if (a < 0)
						a += sizeBase;
					else if (a >= sizeBase)
						a -= sizeBase;

					b = j;
					if (b < 0)
						b += sizeBase;
					else if (b >= sizeBase)
						b -= sizeBase;

					particlesField[a + b * sizeBase + c * sizeBaseSquare] =
							NORMAL;

					if (c > currentHeight)
						currentHeight = c;
				}
			}
		}
	}

	return currentHeight;
}

int InitialSurfaceManager::makeSpike(std::vector<char> &particlesField,
		InitialSurfaceSettings settings, int sizeBase, int sizeHeight, int sizeBaseSquare) {
	// start with random surface
	if (settings.spikeBottom==true){
		makeRandom(particlesField, settings, sizeBase, sizeHeight, sizeBaseSquare);
	}else{
		makeFlat(particlesField, sizeBaseSquare);
	}

	int x, y;
	int spikeHeight = settings.spikeFactor*sizeHeight*0.01f;
	if (settings.spikeField==true){
		for (int i=0; i<sizeBase; i++){
			if (i%settings.spikeSpacing==0){
				x = i;
			}
			for (int j=0; j<sizeBase; j++){
				if (j%settings.spikeSpacing==0){
					y=j;
				}
				for (int k=0; k<=spikeHeight; k++){
					particlesField[x + y*sizeBase + k*sizeBaseSquare] = NORMAL;
				}
			}
		}

	}else{
		x = sizeBase/2;
		for (int k=0; k<=spikeHeight; k++){
			particlesField[x + x*sizeBase + k*sizeBaseSquare] = NORMAL;
			}
	}


	return 0;
}

int InitialSurfaceManager::makeCircles(std::vector<char> &particlesField,
		InitialSurfaceSettings settings, int sizeBase) {
	int center = sizeBase / 2;
	int radius = settings.radius * sizeBase / 100 + 1;
	double radiusD = static_cast<double>(radius);
	std::vector<int> coord;

	coord.push_back(sizeBase / 4);
	coord.push_back(3 * sizeBase / 4);

	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			if (Vector3i(i, 0, j).magnitude() < radiusD) {
				particlesField[center + i + (center + j) * sizeBase] = NORMAL;
			}
		}
	}

	return 0;
}
