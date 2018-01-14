#pragma once
#include "structs.h"

class Moteur
{
private:
	Vector3 localizare;
	Vector3 force;

public:
	Moteur();
	Moteur(Vector3);    //overload constructor

					   //setters
	void setForce(Vector3);
	void setCoord(Vector3);

	//getters
	Vector3 getCoord();
	Vector3 getForce();

	//operatori
	Moteur&  operator=(const Moteur&);

	//default destructor
	~Moteur();
};