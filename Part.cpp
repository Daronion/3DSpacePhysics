#include "Part.h"
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <thread>
#include <utility>
#include <vector>
#include "structs.h"

using namespace std;

Part::Part()
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	mass = 1;
	momentOfInertia = 1;
	Acc = Vector3(0, 0, -9.81);
	ModifyingAcc = Vector3(0, 0, -9.81);
}

Part::Part(Vector3 pos, float given_mass)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	momentOfInertia = 1;

	Acc = Vector3(0, 0, -9.81);
	ModifyingAcc = Vector3(0, 0, -9.81);
}

Part::Part(Vector3 pos, float given_mass, float given_moi)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	momentOfInertia = given_moi;

	Acc = Vector3(0, 0, 0);
	ModifyingAcc = Vector3(0, 0, -9.81);
}
Part::Part(float given_mass)
{
	mass = given_mass;
	momentOfInertia = 1;

	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);
	ModifyingAcc = Vector3(0, 0, -9.81);
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

Vector3 Part::getModifyingAcc()
{
	return ModifyingAcc;
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

float Part::module(Vector3 vec)
{
	return cbrt(pow(vec.f.x,3) + pow(vec.f.y,3) + pow(vec.f.z,3));        //calculeaza modulul unui vector de 3
}

void Part::setModifyingAcc(Vector3 rotation)
{
	rotation = getRotation();
	float modul = module(getAcc());
	float a = modul*(sin(Rotation.f.y)*sin(Rotation.f.x) + cos(Rotation.f.x)*sin(Rotation.f.y));
	float b = modul*sin(Rotation.f.x)*cos(Rotation.f.y);				//acceleratia care se modifica pe axe
	float c = modul*cos(Rotation.f.y)*cos(Rotation.f.x) - 9.81;
	Vector3 newAcc(a, b, c);
	ModifyingAcc = newAcc;
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

void Part::addTorqueZ(Vector3 force, Vector3 distance)
{
	int k;
	if (distance.f.x != 0) k = 1;
	else if (distance.f.y != 0) k = 2;
	Vector3 torque(0, 0, pow((-1),k) * module(force));           //**module(force)** trebuie modificat in functie
	setAngAcc(getAngAcc() + torque / momentOfInertia);			//de o formula pt calcularea mom de rotatie
}


void Part::addAttachedForce(Vector3 force,Vector3 distance)
{
	addTorque(force ^ distance);
	addTorqueZ(force,distance);
	setAcc(getAcc() + force / mass);							  //am adaugat moment in jurul axei Oz;
	ModifyingAcc = getModifyingAcc() + getAcc();
}

Vector3 Part::rotmatrixprod(Vector3 angvel, Vector3 rot)
{
	Vector3 l1(cos(rot.f.y), 0, -cos(rot.f.x)*sin(rot.f.y));    //am construit matricea de rotatie in functie de unghiurile
	Vector3 l2(0, 1, sin(rot.f.x));                         //de rotatie
	Vector3 l3(sin(rot.f.y), 0, cos(rot.f.x)*cos(rot.f.y));
	Vector3 prod(l1 | angvel, l2 | angvel, l3 | angvel);		  //operatorul ** definit in structs.h sper ca bine
	return prod;											//vectorul rezultat contine vitezele unghiulare 
														  //relative la sist de referinta
}													  

Part::~Part()
{
}
