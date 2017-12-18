﻿#include "SphereSystemSimulator.h"

std::function<float(float)> SphereSystemSimulator::m_Kernels[5] = {
	[](float x) {return 1.0f; },              // Constant, m_iKernel = 0
	[](float x) {return 1.0f - x; },          // Linear, m_iKernel = 1, as given in the exercise Sheet, x = d/2r
	[](float x) {return (1.0f - x)*(1.0f - x); }, // Quadratic, m_iKernel = 2
	[](float x) {return 1.0f / (x)-1.0f; },     // Weak Electric Charge, m_iKernel = 3
	[](float x) {return 1.0f / (x*x) - 1.0f; },   // Electric Charge, m_iKernel = 4
};

// SphereSystemSimulator member functions

SphereSystemSimulator::SphereSystemSimulator() {
	m_pSphereSystem = new SphereSystem();
	m_pSphereSystem->addSphere(0.08, 1, Vec3(0, 0, 0));
}

const char * SphereSystemSimulator::getTestCasesStr() {
	return "Spheres";
}

void SphereSystemSimulator::initUI(DrawingUtilitiesClass * DUC) {
	this->DUC = DUC;
	//TwAddVarRW(DUC->g_pTweakBar, "test", TW_TYPE_FLOAT, &m_test, "step=0.1 min=0.0");
}

void SphereSystemSimulator::initTestScene()
{
	switch (m_iTestCase)
	{
	case 0:
		break;
	}
}

void SphereSystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;

	initTestScene();
}

void SphereSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {
	// Draw spheres
	for (auto& sphere : m_pSphereSystem->spheres) {
		DUC->setUpLighting(Vec3(sphere.red, sphere.green, sphere.blue), 0.4*Vec3(1, 1, 1), 2000.0, Vec3(sphere.red, sphere.green, sphere.blue));
		DUC->drawSphere(sphere.pos, Vec3(sphere.r, sphere.r, sphere.r));
	}
}

void SphereSystemSimulator::notifyCaseChanged(int testCase) {
	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	default:
		reset();
		break;
	}
}

void SphereSystemSimulator::externalForcesCalculations(float timeElapsed) {
}

void SphereSystemSimulator::simulateTimestep(float timeStep) {
	switch (m_iTestCase)
	{
	default:
		break;
	}
}

void SphereSystemSimulator::onClick(int x, int y) {
}

void SphereSystemSimulator::onMouse(int x, int y) {
}