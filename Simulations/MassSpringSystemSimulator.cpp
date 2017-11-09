#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_iTestCase = 0;
}


const char * MassSpringSystemSimulator::getTestCasesStr() {
	return "MassSpringSystem";
}


void MassSpringSystemSimulator::initTestScene() {
	addMassPoint(Vec3(0.0, 0.0f, 0), Vec3(-1.0, 0.0f, 0), false);
	addMassPoint(Vec3(0.0, 1.0f, 0), Vec3(1.0, 0.0f, 0), false);
	addSpring(0, 1, 1);
}


void MassSpringSystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;

	m_fMass = 1;
	m_fStiffness = 0;
	m_fDamping = 0;
	m_iIntegrator = 0;
	m_fMassPointSize = 0.01f;

	m_masspointList = {};
	m_springList = {};

	initTestScene();
}


void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC) {

	typedef enum { SUMMER, FALL, WINTER, SPRING } Seasons;
	Seasons season = WINTER;
	TwType seasonType;

	seasonType = TwDefineEnum("SeasonType", NULL, 0);

	this->DUC = DUC;
	switch (1)
	{
	case 0:break;
	case 1: TwAddVarRW(DUC->g_pTweakBar, "Season", seasonType, &season, " enum='0 {Summer}, 1 {Fall}, 2 {Winter}, 3 {Spring}' "); break;
	default:break;
	}
}


void MassSpringSystemSimulator::notifyCaseChanged(int testCase) {
	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		cout << "Mass System!\n";
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}


void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed) {
	// Apply the mouse deltas to g_vfMovableObjectPos (move along cameras view plane)
	Point2D mouseDiff;
	mouseDiff.x = m_trackmouse.x - m_oldtrackmouse.x;
	mouseDiff.y = m_trackmouse.y - m_oldtrackmouse.y;
	if (mouseDiff.x != 0 || mouseDiff.y != 0)
	{
		Mat4 worldViewInv = Mat4(DUC->g_camera.GetWorldMatrix() * DUC->g_camera.GetViewMatrix());
		worldViewInv = worldViewInv.inverse();
		Vec3 inputView = Vec3((float)mouseDiff.x, (float)-mouseDiff.y, 0);
		Vec3 inputWorld = worldViewInv.transformVectorNormal(inputView);
		// find a proper scale!
		float inputScale = 0.001f;
		inputWorld = inputWorld * inputScale;
	}
	else {
	}
}


void MassSpringSystemSimulator::simulateTimestep(float timeStep) {
	// update current setup for each frame
	switch (m_iTestCase)
	{// handling different cases
	case 0:
		break;
	default:
		break;
	}
}


void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {
	switch (m_iTestCase)
	{
	case 0: 
		// Draw mass points
		for (int i = 0; i < m_masspointList.size(); i++) {
			DUC->drawSphere(m_masspointList[i].position, Vec3(m_fMassPointSize, m_fMassPointSize, m_fMassPointSize));
		}

		// Draw springs
		DUC->beginLine();
		for (int i = 0; i < m_springList.size(); i++) {
			DUC->drawLine(m_masspointList[m_springList.at(i).getPoint1()].position, Vec3(0, 1, 0), m_masspointList[m_springList.at(i).getPoint2()].position, Vec3(0, 1, 0));
		}
		DUC->endLine();
		break;
	}
}


void MassSpringSystemSimulator::onClick(int x, int y) {
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}


void MassSpringSystemSimulator::onMouse(int x, int y) {
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}


void MassSpringSystemSimulator::setMass(float mass) {
	m_fMass = mass;
}


void MassSpringSystemSimulator::setStiffness(float stiffness) {
	m_fStiffness = stiffness;
}


void MassSpringSystemSimulator::setDampingFactor(float damping) {
	m_fDamping = damping;
}


int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 velocity, bool isFixed) {
	m_masspointList.push_back(Masspoint(position, velocity, isFixed, Vec3(0, 0, 0), m_fMass, m_fDamping));
	return m_masspointList.size() - 1;
}


void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength) {
	m_springList.push_back(Spring(masspoint1, masspoint2, m_fStiffness, initialLength));
}


int MassSpringSystemSimulator::getNumberOfMassPoints() {
	return m_masspointList.size();
}


int MassSpringSystemSimulator::getNumberOfSprings() {
	return m_springList.size();
}


Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index) {
	return Vec3(0, 0, 0);
}


Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index) {
	return Vec3(0, 0, 0);
}


void MassSpringSystemSimulator::applyExternalForce(Vec3 force) {
}