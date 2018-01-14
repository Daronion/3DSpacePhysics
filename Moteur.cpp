#include "Moteur.h"
#include "structs.h"


Moteur::Moteur(Vector3 a)
{
	localizare = a;
}

Moteur::Moteur()
{
	localizare = Vector3(0, 0, 0);
	force = Vector3(0, 0, 0);
}

void Moteur::setForce(Vector3 f)
{
	force = f;
}

void Moteur::setCoord(Vector3 c)
{
	localizare = c;
}

Vector3 Moteur::getCoord()
{
	return localizare;
}

Vector3 Moteur::getForce()
{
	return force;
}

Moteur& Moteur::operator=(const Moteur& a)
{
	this->localizare = a.localizare;
	this->force = a.force;
	return *this;
}

Moteur::~Moteur()
{
	
}