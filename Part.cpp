#include "Part.h"
#include <time.h>
#include <Windows.h>
#include <thread>

using namespace std;

Part::Part()
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);
	mass = 1;
}

Part::Part(Vector3 pos, float given_mass)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);

	mass = given_mass;
}

Part::Part(float given_mass)
{
	mass = given_mass;
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);
}

//Accessors

float Part::getMass()
{
	return mass;
}

Vector3 Part::getPosition()
{
	return Position;
}

Vector3 Part::getRotation()
{
	return Rotation;
}

Vector3 Part::getAngVel()
{
	return AngVel;
}

Vector3 Part::getAngAcc()
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

void Part::addForce(Vector3 dir)
{
	setAcc(Vector3(getAcc().f.x + dir.f.x/mass, getAcc().f.y + dir.f.y/mass, getAcc().f.z + dir.f.z/mass));
	
}
/*
void Part::addTimedForce(Vector3 force, float time)
{
	addForce(force);
	
	thread t1(ftimer(force,time));
	t1.join;

}

void Part::ftimer(Vector3 force,float time)
{
	Sleep(1000 * time);
	addForce(Vector3(-force.f.x, -force.f.y, -force.f.z));
}
 */
Part::~Part()
{
}
