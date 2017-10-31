#pragma once
#include "structs.h"
#include "fComponents.h"
#include <vector>
#include <utility>
#include <thread>



class Part
{
public:

	//std::vector< std::pair<std::thread *, bool> >running_list;
	std::vector< fComponents >running_list;

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
	void addForce(Vector3);
	//void addTimedForce(Vector3, float);
	//void ftimer(Vector3 , float, unsigned int,Part&);
	

private:
	float mass;
	Vector3 Position;
	Vector3 Speed;
	Vector3 Acc;
	Vector3 Rotation;
	Vector3 AngVel;
	Vector3 AngAcc;

};

