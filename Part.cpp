#include "Part.h"
#include <time.h>
#include <Windows.h>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

Part::Part()								// constructor nul
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	mass = 1;
	momentOfInertia = 1;
	Acc = Vector3(0, 0, -9.81);	//acceleratie gravitationala
}

Part::Part(Vector3 pos, float given_mass)	// constructor pentru pozitie si masa date
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	momentOfInertia = 1;

	Acc = Vector3(0, 0, -9.81);
}

Part::Part(Vector3 pos, float given_mass,float given_moi)	// constructor pentru pozitie, masa si "moment of inertia" date
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	momentOfInertia = given_moi;

	Acc = Vector3(0, 0, -9.81);
}
Part::Part(float given_mass)		// constructor doar pt masa data
{
	mass = given_mass;
	momentOfInertia = 1;

	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, -9.81);
}

//Accessors - numele destul de sugestiv

float Part::getMass()
{
	return mass;
}

float Part::getMoI()
{
	return momentOfInertia;
}
Vector3 Part::getPosition()
{
	return Position;
}

Vector3 Part::getRotation()
{
	return Rotation;
}

Vector3 Part::getAngVel()  // "viteza unghiulara"
{
	return AngVel;
}

Vector3 Part::getAngAcc() // "acceleratie unghiulara"
{
	return AngAcc;
}

Vector3 Part::getSpeed()
{
	return Speed;
}

Vector3 Part::getAcc()
{
	return Acc;
}

//Mutators

void Part::setMass(float g_mass)
{
	mass = g_mass;
}

void Part::setMoI(float g_MoI)
{
	momentOfInertia = g_MoI;
}
void Part::setPosition(Vector3 g_pos)
{
	Position = g_pos;
}

void Part::setRotation(Vector3 g_rot)
{
	Rotation = g_rot;
}

void Part::setAngVel(Vector3 g_angvel)
{
	AngVel = g_angvel;
}

void Part::setAngAcc(Vector3 g_angacc)
{
	AngAcc = g_angacc;
}

void Part::setSpeed(Vector3 g_speed)
{
	Speed = g_speed;
}

void Part::setAcc(Vector3 g_acc)
{
	Acc = g_acc;
}

void Part::addForce(Vector3 force)
{
	setAcc(getAcc() + force / mass);
}

void Part::addUnevenForce(Vector3 force, Vector3 distance) // distance - dintre originea fortei si centrul obiectului
{
	setAcc(getAcc() + force / mass);
	addTorque(force ^ distance);
}

void Part::addTorque(Vector3 torque)
{
	setAngAcc(getAngAcc() + torque / momentOfInertia);
}

Part::~Part() 
{
}
