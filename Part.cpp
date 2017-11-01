#include "Part.h"
#include <time.h>
#include <Windows.h>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

Part::Part()
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	mass = 1;
	Acc = Vector3(0, 0, -9.81);
}

Part::Part(Vector3 pos, float given_mass)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	Acc = Vector3(0, 0, -9.81);
}

Part::Part(float given_mass)
{
	mass = given_mass;
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, -9.81);
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

/*void Part::ftimer(Vector3 force, float time , unsigned int index ,Part& part)
{
	std::cout << "sleeping\n\n";
	Sleep(1000 * time);
	std::cout << "done sleeping\n\n";
	part.addForce(Vector3(-force.f.x, -force.f.y, -force.f.z));
	//running_list[index].done = true;
	running_list[index].force = force.neg();
}


void Part::addTimedForce(Vector3 force, float time)
{
	addForce(force);

	running_list.push_back(fComponents(nullptr, false, force));
	thread *t1 = new thread(&Part::ftimer, this, force, time, running_list.size() - 1, std::ref(this));   //,running_list[running_list.size()-1].done
	running_list[running_list.size() - 1].th = t1;
	
}
*/
Part::~Part()
{
}
