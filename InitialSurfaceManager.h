/* Manage initial surfaces */
#ifndef INITIAL_SURFACE_MANAGER_H
#define INITIAL_SURFACE_MANAGER_H

#include <vector>
#include<math.h>

#include "DataStructures.h"
#include "Random.h"
#include "Vector3i.h"

enum {
	NONE, NORMAL, SEDIMENT
};

/* A class to generate initial surfaces */
class InitialSurfaceManager {
public:
	InitialSurfaceManager();

	int makeInitialSurface(std::vector<char> &particlesField,
			InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
			int sizeBaseSquare); //function returning the maximum height of the initial surface

private:
	Random random;

	int makeFlat(std::vector<char> &particlesField, int sizeBaseSquare);
	int makeSpike(std::vector<char> &particlesField,
			InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
			int sizeBaseSquare);
	int makeSinusoidal(std::vector<char> &particlesField,
			InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
			int sizeBaseSquare);
	int makeRandom(std::vector<char> &particlesField,
			InitialSurfaceSettings settings, int sizeBase, int sizeHeight,
			int sizeBaseSquare);
	int makeCircles(std::vector<char> &particlesField,
			InitialSurfaceSettings settings, int sizeBase);
};

#endif
