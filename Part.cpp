#include "Part.h"

Part::Part()
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);
	mass = 1;
}

Part::Part(Vector3 pos, float given_mass)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);
	Acc = Vector3(0, 0, 0);

	mass = given_mass;
}

Part::Part(float given_mass)
{
	mass = given_mass;
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

void Part::setSpeed(Vector3 g_speed)
{
	Speed = g_speed;
}

void Part::setAcc(Vector3 g_acc)
{
	Acc = g_acc;
}

Part::~Part()
{
}
