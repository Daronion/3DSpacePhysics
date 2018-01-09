#include "Part.h"
#include "Matrix.h"
#include <time.h>
#include <Windows.h>
#include <thread>
#include <utility>
#include <vector>
#include <math.h>

#define PI 3.14159265

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
	LastRotatedForce = Vector3(0, 0, 0);
}
//different Constructors
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
	LastRotatedForce = Vector3(0, 0, 0);
	LastRotatedForce2 = Vector3(0, 0, 0);
	LastRotatedTorque2 = Vector3(0, 0, 0);
}
Part::Part(Vector3 pos, float given_mass,float given_moi)
{
	Position = pos;
	Rotation = Vector3(0, 0, 0);
	AngAcc = Vector3(0, 0, 0);
	AngVel = Vector3(0, 0, 0);
	Speed = Vector3(0, 0, 0);

	mass = given_mass;
	momentOfInertia = given_moi;

	Acc = Vector3(0, 0, -9.81);
	LastRotatedForce = Vector3(0, 0, 0);
	LastRotatedForce2 = Vector3(0, 0, 0);
	LastRotatedTorque2 = Vector3(0, 0, 0);

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
	Acc = Vector3(0, 0, -9.81);
	LastRotatedForce = Vector3(0, 0, 0);
	LastRotatedForce2 = Vector3(0, 0, 0);
	LastRotatedTorque2 = Vector3(0, 0, 0);
}

void Part::rotationUpdater()
{
	Rotation.f.x = fmod(Rotation.f.x, 2 * PI);
	Rotation.f.y = fmod(Rotation.f.y, 2 * PI);
	Rotation.f.z = fmod(Rotation.f.z, 2 * PI);
	if (Rotation.f.x < 0)
		Rotation.f.x += 2 * PI;
	if (Rotation.f.y < 0)
		Rotation.f.y += 2 * PI;
	if (Rotation.f.z < 0)
		Rotation.f.z += 2 * PI;
}


void Part::addForce(Vector3 force)
{
	setAcc(getAcc() + force / mass);
}

void Part::addAttachedForce(Vector3 force)
{
	addForce(LastRotatedForce.neg());

	Vector3 RotatedForce;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
					   force.f.y * cosB * cosC +
					   force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
					   force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
					   force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
					   force.f.y * (cosA*sinB*sinC + sinA*cosC) +
					   force.f.z * cosA*cosB;

	//std::cout<<"** ROTF: "<<RotatedForce.toString();

	addForce(RotatedForce);
	LastRotatedForce = RotatedForce;
}
// serveste doar ca un blueprint pt Motoare
void Part::addUnevenAttachedForce(Vector3 force, Vector3 distance)
{
	//std::cout << "\r";
	addForce(LastRotatedForce2.neg());
	addTorque(LastRotatedTorque2.neg());

	Vector3 RotatedForce;
	Vector3 RotatedDistance;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
					   force.f.y * cosB * sinC +
					   force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
					   force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
					   force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
					   force.f.y * (cosA*sinB*sinC + sinA*cosC) +
					   force.f.z * cosA*cosB;

	RotatedDistance.f.x = distance.f.x * cosB * cosC -
						  distance.f.y * cosB * sinC +
						  distance.f.z * sinB;
	RotatedDistance.f.y = distance.f.x * (sinA*sinB*cosC + cosA*sinC) +
						  distance.f.y * (-sinA*sinB*sinC + cosA*cosC) -
						  distance.f.z * sinA*cosB;
	RotatedDistance.f.z = distance.f.x * (-cosA*sinB*cosC + sinA*sinC) +
						  distance.f.y * (cosA*sinB*sinC + sinA*cosC) +
						  distance.f.z * cosA*cosB;

	Vector3 RotatedTorque = (RotatedForce^RotatedDistance);

	addForce(RotatedForce);
	addTorque(RotatedTorque);

	LastRotatedForce2 = RotatedForce;
	LastRotatedTorque2 = RotatedTorque;
}  

void Part::addUnevenForce(Vector3 force, Vector3 distance) // distance - dintre originea fortei si centrul obiectului
{
	addForce(force);
	//setAcc(getAcc() + force / mass);
	addTorque(force ^ distance);
}

void Part::addTorque(Vector3 torque)
{
	setAngAcc(getAngAcc() + torque / momentOfInertia);
}

//Drone Motors

void Part::Motor1(Vector3 force)
{
	Vector3 distance = Vector3(0,1,0);

	addForce(LRF1.neg());
	addTorque(LRT1.neg());

	Vector3 RotatedForce;
	Vector3 RotatedDistance;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
		force.f.y * cosB * sinC +
		force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
		force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		force.f.y * (cosA*sinB*sinC + sinA*cosC) +
		force.f.z * cosA*cosB;

	RotatedDistance.f.x = distance.f.x * cosB * cosC -
		distance.f.y * cosB * sinC +
		distance.f.z * sinB;
	RotatedDistance.f.y = distance.f.x * (sinA*sinB*cosC + cosA*sinC) +
		distance.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		distance.f.z * sinA*cosB;
	RotatedDistance.f.z = distance.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		distance.f.y * (cosA*sinB*sinC + sinA*cosC) +
		distance.f.z * cosA*cosB;

	Vector3 RotatedTorque = (RotatedForce^RotatedDistance);

	addForce(RotatedForce);
	addTorque(RotatedTorque);

	LRF1 = RotatedForce;
	LRT1 = RotatedTorque;
}

void Part::Motor2(Vector3 force)
{
	Vector3 distance = Vector3(0, -1, 0);

	addForce(LRF2.neg());
	addTorque(LRT2.neg());

	Vector3 RotatedForce;
	Vector3 RotatedDistance;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
		force.f.y * cosB * sinC +
		force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
		force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		force.f.y * (cosA*sinB*sinC + sinA*cosC) +
		force.f.z * cosA*cosB;

	RotatedDistance.f.x = distance.f.x * cosB * cosC -
		distance.f.y * cosB * sinC +
		distance.f.z * sinB;
	RotatedDistance.f.y = distance.f.x * (sinA*sinB*cosC + cosA*sinC) +
		distance.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		distance.f.z * sinA*cosB;
	RotatedDistance.f.z = distance.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		distance.f.y * (cosA*sinB*sinC + sinA*cosC) +
		distance.f.z * cosA*cosB;

	Vector3 RotatedTorque = (RotatedForce^RotatedDistance);

	addForce(RotatedForce);
	addTorque(RotatedTorque);

	LRF2 = RotatedForce;
	LRT2 = RotatedTorque;
}

void Part::Motor3(Vector3 force)
{
	Vector3 distance = Vector3(1, 0, 0);

	addForce(LRF3.neg());
	addTorque(LRT3.neg());

	Vector3 RotatedForce;
	Vector3 RotatedDistance;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
		force.f.y * cosB * sinC +
		force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
		force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		force.f.y * (cosA*sinB*sinC + sinA*cosC) +
		force.f.z * cosA*cosB;

	RotatedDistance.f.x = distance.f.x * cosB * cosC -
		distance.f.y * cosB * sinC +
		distance.f.z * sinB;
	RotatedDistance.f.y = distance.f.x * (sinA*sinB*cosC + cosA*sinC) +
		distance.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		distance.f.z * sinA*cosB;
	RotatedDistance.f.z = distance.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		distance.f.y * (cosA*sinB*sinC + sinA*cosC) +
		distance.f.z * cosA*cosB;

	Vector3 RotatedTorque = (RotatedForce^RotatedDistance);

	addForce(RotatedForce);
	addTorque(RotatedTorque);

	LRF3 = RotatedForce;
	LRT3 = RotatedTorque;
}

void Part::Motor4(Vector3 force)
{
	Vector3 distance = Vector3(-1, 0, 0);

	addForce(LRF4.neg());
	addTorque(LRT4.neg());

	Vector3 RotatedForce;
	Vector3 RotatedDistance;
	double A = getRotation().f.x;
	double B = getRotation().f.y;
	double C = getRotation().f.z;
	double cosA = cos(A);
	double sinA = sin(A);
	double cosB = cos(B);
	double sinB = sin(B);
	double cosC = cos(C);
	double sinC = sin(C);

	RotatedForce.f.x = force.f.x * cosB * cosC -
		force.f.y * cosB * sinC +
		force.f.z * sinB;
	RotatedForce.f.y = force.f.x * (sinA*sinB*cosC + cosA*sinC) +
		force.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		force.f.z * sinA*cosB;
	RotatedForce.f.z = force.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		force.f.y * (cosA*sinB*sinC + sinA*cosC) +
		force.f.z * cosA*cosB;

	RotatedDistance.f.x = distance.f.x * cosB * cosC -
		distance.f.y * cosB * sinC +
		distance.f.z * sinB;
	RotatedDistance.f.y = distance.f.x * (sinA*sinB*cosC + cosA*sinC) +
		distance.f.y * (-sinA*sinB*sinC + cosA*cosC) -
		distance.f.z * sinA*cosB;
	RotatedDistance.f.z = distance.f.x * (-cosA*sinB*cosC + sinA*sinC) +
		distance.f.y * (cosA*sinB*sinC + sinA*cosC) +
		distance.f.z * cosA*cosB;

	Vector3 RotatedTorque = (RotatedForce^RotatedDistance);

	addForce(RotatedForce);
	addTorque(RotatedTorque);

	LRF4 = RotatedForce;
	LRT4 = RotatedTorque;
}


//Drone Movement Functions

void Part::Hover()
{

	if (getRotation() == Vector3(0, 0, 0)) {
		if (getSpeed().f.z < 1 && getSpeed().f.z > -1) {
			Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
					Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
			Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
		}
		else if (getSpeed().f.z > 1) {
			Motor1(Vector3(0, 0, getMass()*(double)9.81 / 5));
			Motor2(Vector3(0, 0, getMass()*(double)9.81 / 5));
			Motor3(Vector3(0, 0, getMass()*(double)9.81 / 5));
			Motor4(Vector3(0, 0, getMass()*(double)9.81 / 5));
		}
		else if (getSpeed().f.z < -1) {
			Motor1(Vector3(0, 0, getMass()*(double)9.81 / 3));
			Motor2(Vector3(0, 0, getMass()*(double)9.81 / 3));
			Motor3(Vector3(0, 0, getMass()*(double)9.81 / 3));
			Motor4(Vector3(0, 0, getMass()*(double)9.81 / 3));
		}
		bounce = 0;
			Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
count = 0;
		l_bounce = 0;
		moving = 0;
		return;
	}
	else if (getRotation().f.x >  3 * PI / 2 && ( abs(getSpeed().f.y)>abs(getSpeed().f.x) ) ) {
		cout << "1))3pi2";
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 2 * (2 * PI - getRotation().f.x)*(count + 1)));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4 * (2 * PI - getRotation().f.x)));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
		bounce = 1;
		moving = 1;

	}
	else if (getRotation().f.x <  PI / 2 && getRotation().f.x != 0 && (abs(getSpeed().f.y)>abs(getSpeed().f.x)))
	{
		cout << "1))pi2";
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4 * (getRotation().f.x)));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 2 * (getRotation().f.x)*(count + 1)));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
		bounce = 2;
		moving = 1;

	}
	else if (getRotation().f.y >  3 * PI / 2 && (abs(getSpeed().f.x)>abs(getSpeed().f.y))) {
		cout << "2))3pi2";
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4 * (2 * PI - getRotation().f.y)));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 2 * (2 * PI - getRotation().f.y)*(count+1)));
		bounce = 3;
		moving = 1;

	}
	else if (getRotation().f.y <  PI / 2 && (abs(getSpeed().f.x)>abs(getSpeed().f.y)))
	{
		cout << "2))pi2";
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 2 * (getRotation().f.y)*(count + 1)));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4 * (getRotation().f.y)));
		bounce = 4;
		moving = 1;
	}

	if ((getRotation().f.x < PI / 48 || getRotation().f.x > 95 * PI / 48)
		&& (getRotation().f.y < PI / 48 || getRotation().f.y > 95 * PI / 48) && count > 2)
	{
		setAngAcc(Vector3(0, 0, 0));
		setAngVel(Vector3(0, 0, 0));
		setRotation(Vector3(0, 0, 0));
		setSpeed(Vector3(0, 0, 0));
		setAcc(Vector3(0, 0, -9.81));
	
		LRF1 = Vector3(0, 0, 0);
		LRF2 = Vector3(0, 0, 0);
		LRF3 = Vector3(0, 0, 0);
		LRF4 = Vector3(0, 0, 0);

		LRT1 = Vector3(0, 0, 0);
		LRT2 = Vector3(0, 0, 0);
		LRT3 = Vector3(0, 0, 0);
		LRT4 = Vector3(0, 0, 0);

		moving = 0;
	}

	//if (getSpeed().f.z < 1  && getSpeed().f.z > -1 && moving == 0) {
	//	
	//	setAcc(Vector3(0, 0, -9.81));
	//	setSpeed(Vector3(getSpeed().f.x, getSpeed().f.y, 0));
	//	cout << "***";

	//}

	if (l_bounce != bounce)
		count++;
	l_bounce = bounce;

}

void Part::Pitch(bool front)
{
	if (front) {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
	}
	else {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 3));
	}
}

void Part::Roll(bool right)
{
	if (right) {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
	}
	else {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 4));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 4));
	}
}

void Part::Lift(bool up)
{
	if (up) {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 3));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 3));
	}
	else {
		Motor1(Vector3(0, 0, getMass()*(double)9.81 / 5));
		Motor2(Vector3(0, 0, getMass()*(double)9.81 / 5));
		Motor3(Vector3(0, 0, getMass()*(double)9.81 / 5));
		Motor4(Vector3(0, 0, getMass()*(double)9.81 / 5));
	}
}

Part::~Part()
{
}

//Accessors

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
