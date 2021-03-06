#pragma once
#include "structs.h"
#include "Moteur.h"
#include <vector>
#include <utility>
#include <thread>

const double pi = 3.14;

class Part
{
public:

	//Default Constructor
	Part();

	//Overload Constructors
	Part(Vector3, float);
	Part(Vector3, float, float);
	Part(float);

	//Default Destructor
	~Part();

	//Accessor Functions
	float getMass();
	Vector3 getPosition();
	Vector3 getSpeed();
	Vector3 getAcc();
	Vector3 getRotation();
	Vector3 getAngVel(); // -- Angular Velocity & Acceleration
	Vector3 getAngAcc();
	Vector3 getModifyingAcc();


	//Mutator Functions
	void setMass(float);
	void setPosition(Vector3);
	void setSpeed(Vector3);
	void setAcc(Vector3);
	void setRotation(Vector3);
	void setAngVel(Vector3);
	void setAngAcc(Vector3);
	void setModifyingAcc(Vector3);

	//
	void addForce(Vector3);
	void addAttachedForce(Vector3, Vector3);
	void addUnevenForce(Vector3, Vector3);
	void addTorque(Vector3);
	void addTorqueZ(Vector3,Vector3);
	Vector3 rotmatrixprod(Vector3, Vector3);
	float module(Vector3);

private:
	Moteur motors[4];
	float mass;
	float momentOfInertia;
	Vector3 Position;
	Vector3 Speed;
	Vector3 ModifyingAcc;
	Vector3 Acc;
	Vector3 Rotation;
	Vector3 AngVel;
	Vector3 AngAcc;

};

