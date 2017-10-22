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
	Vector3 getRotation();
	Vector3 getSpeed();
	
	//Mutator Functions
	void setMass(float);
	void setPosition(Vector3);
	void setRotation(Vector3);
	void setSpeed(Vector3);


private:
	float mass;
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Speed;
};

