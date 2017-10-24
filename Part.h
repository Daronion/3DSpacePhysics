#pragma once
#include "structs.h"



class Part
{
public:

	//Default Constructor
	Part();

	//Overload Constructors
	Part(Vector3 ,float );
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
	
	//Mutator Functions
	void setMass(float);
	void setPosition(Vector3);
	void setSpeed(Vector3);
	void setAcc(Vector3);
	void setRotation(Vector3);
	void setAngVel(Vector3);
	void setAngAcc(Vector3);

	//

	void addForce(Vector3, int);

private:
	float mass;
	Vector3 Position;
	Vector3 Speed;
	Vector3 Acc;
	Vector3 Rotation;
	Vector3 AngVel;
	Vector3 AngAcc;
};

