#pragma once
#include "Sphere.h"

class SphereSystem
{
public:
	SphereSystem();
	~SphereSystem();

	void addSphere(float radius, float mass, Vec3 position);
	void updateStep(float elapsedTime, float damping, int accelerator);
	void checkBox();
	void naiveCollision();
	void uniformGridCollision();
	void checkCells(Sphere **cell1, Sphere **cell2);
	void resolveCollision(Sphere &a, Sphere &b);
	void checkForCollision(Sphere &a, Sphere &b);

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::vector<Sphere> spheres;
	float boxSize;

	static const int numCells = 2;
	static const int maxSpheres = 10;
};

