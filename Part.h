#pragma once
#include "structs.h"
#include "Matrix.h"
#include <vector>
#include <utility>
#include <thread>

const double pi = 3.14;

class Part
{
public:

	Vector3 LastRotatedTorque2;
	Vector3 LastRotatedForce2;

	//Default Constructor
	Part();

	//Overload Constructors
	Part(Vector3 ,float );
	Part(Vector3, float, float);
	Part(float);

	//Default Destructor
	~Part();

	//Updates
	void rotationUpdater();

	//
	void addForce(Vector3);
	void addAttachedForce(Vector3);
	void addUnevenForce(Vector3, Vector3);
	void addUnevenAttachedForce(Vector3, Vector3);

	void addTorque(Vector3);
	
	//Accessor Functions
	float getMass();
	float getMoI();
	Vector3 getPosition();
	Vector3 getSpeed();
	Vector3 getAcc();
	Vector3 getRotation();
	Vector3 getAngVel(); // -- Angular Velocity & Acceleration
	Vector3 getAngAcc();



	//Mutator Functions
	void setMass(float);
	void setMoI(float);
	void setPosition(Vector3);
	void setSpeed(Vector3);
	void setAcc(Vector3);
	void setRotation(Vector3);
	void setAngVel(Vector3);
	void setAngAcc(Vector3);

	//Drone motors
	void Motor1(Vector3);
	void Motor2(Vector3);
	void Motor3(Vector3);
	void Motor4(Vector3);

	//Drone Movement Functions
	void Hover();
	void Pitch(bool front);
	void Roll(bool right);
	void Lift(bool up);

private:
	float mass;
	float momentOfInertia;
	Vector3 Position;
	Vector3 Speed;
	Vector3 Acc;
	Vector3 Rotation;
	Vector3 AngVel;
	Vector3 AngAcc;

	//Remember values
	Vector3 LastRotatedForce;

	//Remember values for the 
	//Last_Rotated_Forces
	Vector3 LRF1 = Vector3(0, 0, 0);
	Vector3 LRF2 = Vector3(0, 0, 0);
	Vector3 LRF3 = Vector3(0, 0, 0);
	Vector3 LRF4 = Vector3(0, 0, 0);

	//Last_Rotated_Torques
	Vector3 LRT1 = Vector3(0, 0, 0);
	Vector3 LRT2 = Vector3(0, 0, 0);
	Vector3 LRT3 = Vector3(0, 0, 0);
	Vector3 LRT4 = Vector3(0, 0, 0);

	//Hover helpers
	int bounce = 0;
	int l_bounce = 0;
	int count = 0;
	
	int moving = 0;
};



