#include <iostream>
#include <iomanip>		// -- pt aproximarea zecimalelor
#include "structs.h"
#include "Part.h"
#include <math.h>
#include <time.h>		
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>
#include "Moteur.h"

#define g 9.81
#define pi 3.14159
using namespace std;

void Update(vector<Part>&,Moteur motors[]);  // - while infinit in care se updateaza pozitia obiectelor
void Hover(Part);
void Yaw(Part, float);
void AltUp(Part, float);

void Update_Attributes(Part *a, long double deltaTime)
{
	Vector3 newSpeed = a->getSpeed() + (a->getModifyingAcc() * deltaTime);
	Vector3 newPos = a->getPosition() + (a->getSpeed() * deltaTime);

	Vector3 newAngVel = a->getAngVel() + (a->getAngAcc() * deltaTime);
	Vector3 newRotation = a->getRotation() + (a->getAngVel() * deltaTime);
	newRotation -= 2 * pi;
	a->setRotation(newRotation);
	a->setModifyingAcc(newRotation);

	if (newPos.f.z >= 0) {
		a->setSpeed(newSpeed);
		a->setPosition(newPos);
	}
	else {
		a->setSpeed(Vector3(newSpeed.f.x, newSpeed.f.y, 0));
		a->setPosition(Vector3(newPos.f.x, newPos.f.y, 0));
	}

	a->setAngVel(newAngVel);
	a->setRotation(newRotation);
}

void Hover(Part *a, Moteur motors[])
{
	auto started = std::chrono::high_resolution_clock::now();
	long double angle_i, ang_delta;
	long double time_before = 0;
	long double deltaTime = 0;
	float mass = a->getMass();
	float zinit = a->getPosition().f.z;
	for (int i = 1; i <= 4; i++)
	{
		a->addAttachedForce(Vector3(0, 0, g*mass / 4 - motors[i].getForce().f.z), motors[i].getCoord());
		motors[i].setForce(Vector3(0, 0, g*mass / 4));
	}
	/*while (abs(a->getAngVel().f.y) > 0.0005 || abs(a->getSpeed().f.x>0.0005))
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;
		angle_i = a->getRotation().f.y;
		if (a->getSpeed().f.x > 0)
		{
			for (int i = 1; i <= 2; i++)
			{
				a->addAttachedForce(Vector3(0, 0, -pow(-1, i)*abs(a->getSpeed().f.x) / 10), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -pow(-1, i)*abs(a->getSpeed().f.x) / 10));
			}
		}
		else if (a->getSpeed().f.x < 0)
		{
			for (int i = 1; i <= 2; i++)
			{
				a->addAttachedForce(Vector3(0, 0, pow(-1, i)*abs(a->getSpeed().f.x) / 100), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, pow(-1, i)*abs(a->getSpeed().f.x) / 100));
			}
		}
		Update_Attributes(a, deltaTime);
		ang_delta = 0;
		if (abs(a->getPosition().f.z - zinit) > 0.05)
		{
			ang_delta = a->getRotation().f.y - angle_i;
			int sgn = 1;
			if (ang_delta>0) sgn = 1;
			else if (ang_delta<0) sgn = -1;
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, sgn* a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, sgn * a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z));
			}
		}
		
		std::cout << setprecision(2) << fixed << "PitchHover: " << a->getAngVel().toString() << a->getSpeed().toString() << " " << a->getPosition().toString();
		Sleep(50);
		std::cout << "\r";
	}*/

	while (abs(a->getAngVel().f.z) > 0.0005)
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;
		if (a->getAngVel().f.z > 0)
		{
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, -abs(i - 2.5) / (i - 2.5)*1*abs(a->getAngVel().f.z)), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -abs(i - 2.5) / (i - 2.5)*1*abs(a->getAngVel().f.z)));
			}
		}
		else if (a->getAngVel().f.z < 0)
		{
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, abs(i - 2.5) / (i - 2.5) * 1 * abs(a->getAngVel().f.z)), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, abs(i - 2.5) / (i - 2.5) * 1 * abs(a->getAngVel().f.z)));
			}
		}
		Update_Attributes(a, deltaTime);
		
		std::cout << setprecision(2) << fixed << "YawHover: " << a->getAngVel().toString() << a->getRotation().toString() << " " << a->getAngAcc().toString();
		Sleep(50);
		std::cout << "\r";
	}
	while (abs(a->getSpeed().f.z) > 0.0005)
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;
		if (a->getSpeed().f.z > 0)
		{
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, g*mass / 4 - motors[i].getForce().f.z - 10*a->getSpeed().f.z / 4), motors[i].getCoord());
				motors[i].setForce(Vector3(0, 0, g*mass / 4 - 10*a->getSpeed().f.z / 4));
			}
		}
		else if (a->getSpeed().f.z < 0)
		{
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, g*mass / 4 - motors[i].getForce().f.z - 10*a->getSpeed().f.z / 4), motors[i].getCoord());
				motors[i].setForce(Vector3(0, 0, g*mass / 4 - 10*a->getSpeed().f.z / 4));
			}
		}
		
		Update_Attributes(a, deltaTime);
		std::cout << setprecision(2) << fixed << "Hover: " << a->getSpeed().toString() << a->getPosition().toString() << " " << a->getModifyingAcc().toString();
		Sleep(50);
		std::cout << "\r";
	}
	for (int i = 1; i <= 4; i++)
	{
		a->addAttachedForce(Vector3(0, 0, g*mass / 4 - motors[i].getForce().f.z), motors[i].getCoord());
		motors[i].setForce(Vector3(0, 0, g*mass / 4));
	}
}

void Pitch(Part *a, float dist, Moteur motors[])
{
	auto started = std::chrono::high_resolution_clock::now();
	long double time_before = 0;
	long double deltaTime = 0;

	long double angle_i, ang_delta;
	long double eps = dist * cos(a->getRotation().f.z) - a->getPosition().f.x;  
	long double epsinit = abs(eps);
	float zinit = a->getPosition().f.z;
	/*long double c=round(epsinit);
	int gradeps = 0;
	
	while (c > 0)
	{
		c /= 10;
		gradeps++;
	}*/
		
	if (eps > 0)			//pentru a se duce in fata marim forta motorului 2 si o scadem pe cea a motorului 1
	{
		for (int i = 1; i <= 2; i++)
		{
			a->addAttachedForce(Vector3(0, 0, pow(-1,i)*abs(eps) / 60 / 4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, pow(-1,i)*abs(eps) / 60 / 4));
		}
	}
	else if (eps < 0)        //pentru a se duce in spate marim forta motorului 1 si o scadem pe cea a motorului 2
	{
		for (int i = 1; i <= 2; i++)
		{
			a->addAttachedForce(Vector3(0, 0, -pow(-1, i)*abs(eps) / 60 / 4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -pow(-1, i)*abs(eps) / 60 / 4));
		}
	}
	while (abs(eps) > 2.5 / 100 * epsinit)
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;
		angle_i = a->getRotation().f.y;
		
		while (abs(a->getRotation().f.y) > pi / 18 || a->getRotation().f.y < -abs(epsinit)/epsinit*pi/72)
		{
			auto done = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
			deltaTime = (time - time_before) / 1000;
			time_before = time;
			angle_i = a->getRotation().f.y;
			Update_Attributes(a, deltaTime);
			ang_delta = 0;
			/*if (abs(a->getPosition().f.z - zinit) > 0.05)
			{
				ang_delta = a->getRotation().f.y - angle_i;
				int sgn = 1;
				if (ang_delta>0) sgn = 1;
				else if (ang_delta<0) sgn = -1;
				for (int i = 1; i <= 4; i++)
				{
					a->addAttachedForce(Vector3(0, 0, sgn* a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z), motors[i].getCoord());
					motors[i].setForce(motors[i].getForce() + Vector3(0, 0, sgn * a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z));
				}
			}*/
			int sgn = abs(a->getRotation().f.y) / a->getRotation().f.y;
			for (int i = 1; i <= 2; i++)
			{
				a->addAttachedForce(Vector3(0, 0, -sgn*pow(-1, i)*pow(abs(a->getRotation().f.y)+1,2-2*sgn) /100 / 4), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -sgn*pow(-1, i)*pow(abs(a->getRotation().f.y)+1,2-2*sgn) /100 / 4));
			}
			std::cout << setprecision(2) << fixed << "Rot:" << a->getRotation().toString() << " " << "P:" << a->getAngVel().toString() << " " << eps << " " << ((motors[3].getForce() + motors[4].getForce() + motors[1].getForce() + motors[2].getForce())*cos(a->getRotation().f.y)).toString();
			Sleep(50);
			std::cout << "\r";
		}
		Update_Attributes(a, deltaTime);
		ang_delta = 0;
		/*if (abs(a->getPosition().f.z - zinit) > 0.05)
		{
			ang_delta = a->getRotation().f.y - angle_i;
			int sgn = 1;
			if (ang_delta>0) sgn = 1;
			else if (ang_delta<0) sgn = -1;
			for (int i = 1; i <= 4; i++)
			{
				a->addAttachedForce(Vector3(0, 0, sgn* a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z), motors[i].getCoord());
				motors[i].setForce(motors[i].getForce() + Vector3(0, 0, sgn * a->getMass()*g / cos(ang_delta) / 4 - motors[3].getForce().f.z));
			}
		}*/

		/*for (int i = 1; i <= 2; i++)
		{
			a->addAttachedForce(Vector3(0, 0, -abs(eps)/eps*pow(-1, i)*abs(a->getRotation().f.y) / 1000 / 4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -abs(eps)/eps*pow(-1, i)*abs(a->getRotation().f.y) / 1000 / 4));
		}*/
		

		eps = dist * cos(a->getRotation().f.z) - a->getPosition().f.x;
		std::cout << setprecision(2) << fixed << "Rot:" << a->getRotation().toString() << " " << "P:" << a->getPosition().toString() << " " << eps << " " << ((motors[3].getForce()+motors[4].getForce()+motors[1].getForce()+motors[2].getForce())*cos(a->getRotation().f.y)).toString();
		Sleep(50);
		std::cout << "\r";
	}
	Hover(a, motors);
}

void Yaw(Part *a, float rot ,Moteur motors[])
{
	auto started = std::chrono::high_resolution_clock::now();
	long double time_before = 0;
	long double deltaTime = 0;

	long double eps;
	eps = rot - a->getRotation().f.z;
	long double epsinit = abs(eps);
	if (eps < 0)		//pentru yaw cu botul spre stanga
	{
		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0, 0, -abs(i - 2.5) / (i - 2.5)*abs(eps)*2 / 4),motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -abs(i - 2.5) / (i - 2.5)*abs(eps)*2 / 4));
																		//abs(i-2.5)/(i-2.5) -> -1 pt i=1 si i=2
		}																// +1 pt i=3 si i=4 
																		//asta pentru a adauga cui trebuie
	}
	else if (eps > 0)    //pentru yaw cu botul spre dreapta
	{
		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0, 0, abs(i - 2.5) / (i - 2.5)*abs(eps)*2 / 4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, abs(i - 2.5) / (i - 2.5)*abs(eps)*2 / 4));
		}
	}
	while (abs(eps) > 1.6/100*epsinit)
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;

		Update_Attributes(a, deltaTime);

		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0, 0, -abs(eps)/eps*abs(i - 2.5) / (i - 2.5)*abs(a->getAngVel().f.z) /4.525 / 4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -abs(eps)/eps*abs(i - 2.5) / (i - 2.5)*abs(a->getAngVel().f.z) / 4.525 / 4));
		}
		eps = rot - a->getRotation().f.z;
		std::cout << setprecision(2) << fixed << "Rot:"<< a->getRotation().toString() << " " << "AA:"<<a->getAngAcc().toString() << " " << eps << " " << motors[2].getForce().toString();
		Sleep(50);
		std::cout << "\r";
	}
	Hover(a, motors);
}

void Drone_Start(Part *a,Moteur motors[],float s)
{
	auto started = std::chrono::high_resolution_clock::now();

	long double time_before = 0;
	long double deltaTime = 0;
	int i;
	Moteur x1(Vector3(10, 0, 0));
	i = (x1.getCoord()).f.x / 10 + (x1.getCoord()).f.y * 3 / 10;
	if (i < 0) i = 1 - i;
	motors[i] = x1;
	a->addAttachedForce(Vector3(0, 0, s), x1.getCoord());
	motors[i].setForce(Vector3(0, 0, s));
															//x1  si x2 counterclockwise motors(motors[1] si motors[2]
	Moteur x2(Vector3(-10, 0, 0));	
	i = (x2.getCoord()).f.x / 10 + (x2.getCoord()).f.y * 3 / 10;
	if (i < 0) i = 1 - i;
	motors[i] = x2;
	a->addAttachedForce(Vector3(0, 0, s), x2.getCoord());
	motors[i].setForce(Vector3(0, 0, s));
															//y1 si y2 clockwise motors(motors[3] si motors[4]
	Moteur y1(Vector3(0, 10, 0));
	i = (y1.getCoord()).f.x / 10 + (y1.getCoord()).f.y * 3 / 10;
	if (i < 0) i = 1 - i;
	motors[i] = y1;
	a->addAttachedForce(Vector3(0, 0, s), y1.getCoord());
	motors[i].setForce(Vector3(0, 0, s));

	Moteur y2(Vector3(0, -10, 0));
	i = (y2.getCoord()).f.x / 10 + (y2.getCoord()).f.y * 3 / 10;
	if (i < 0) i = 1 - i;
	motors[i] = y2;
	a->addAttachedForce(Vector3(0, 0, s), y2.getCoord());
	motors[i].setForce(Vector3(0, 0, s));
	
	auto done = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
	deltaTime = (time - time_before) / 1000;
	time_before = time;
	Update_Attributes(a, deltaTime);
	
}

void disp_Motors(Moteur motors[])
{
	for (int i = 1; i <= 4; i++)
	{
		std::cout << motors[i].getCoord().toString() << motors[i].getForce().toString() << endl;
	}
}

void Go_To_Height(Part *a, float height, Moteur motors[])//,long double deltaTime)
{
	auto started = std::chrono::high_resolution_clock::now();

	long double time_before = 0;
	long double deltaTime = 0;
	int count = 0;
	float eps= a->getPosition().f.z - height;
	float epsinit = abs(eps);
	float mass = a->getMass();
	if (eps > 0)       //daca e mai sus
	{
		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0, 0, -(eps/2)/4), motors[i].getCoord());
			motors[i].setForce(motors[i].getForce() + Vector3(0, 0, -(eps/2)/4));	
		}
	}
	else if (eps < 0)    //daca e mai jos	
	{
		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0,0,g*mass/4-motors[i].getForce().f.z-eps/2/4), motors[i].getCoord());
			motors[i].setForce(Vector3(0, 0, g*mass / 4) + Vector3(0, 0, -(eps / 2) / 4));
		}
	}
	while (abs(eps)>2.9/100*epsinit)
	{
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;

		Update_Attributes(a, deltaTime);

		for (int i = 1; i <= 4; i++)
		{
			a->addAttachedForce(Vector3(0, 0, (eps/abs(eps))*(abs(a->getSpeed().f.z)/18.1)/4), motors[i].getCoord());   //eps/abs(eps) ia semnul erorii
			motors[i].setForce(motors[i].getForce() + Vector3(0,0,(eps / abs(eps))*(abs(a->getSpeed().f.z) / 18.1) / 4));
		}
		std::cout << setprecision(2) << fixed << a->getPosition().toString() <<" "<< a->getModifyingAcc().toString() << " " << eps << " " << motors[2].getForce().toString();
		eps = a->getPosition().f.z - height;
		Sleep(50);
		std::cout << "\r";
	}
	Hover(a,motors);
}

int main() {
	vector<Part> parts_vector;
	vector<thread> threads_vector;

	Moteur motors[4];
	Part a(Vector3(10, 0, 10), 10, 100);
	/*Moteur x1(Vector3(10, 0, 0));
	Moteur x2(Vector3(-10, 0, 0));
	Moteur y1(Vector3(0, 10, 0));
	Moteur y2(Vector3(0, -10, 0));
	
	
	//a.addTimedForce(Vector3(1, 1, 40),2);
	//a.addForce(Vector3(0, 0, 9.81*a.getMass()));
	a.addAttachedForce(Vector3(0, 0, 23), y2.getCoord());
	a.addAttachedForce(Vector3(0, 0, 23), y1.getCoord());
	a.addAttachedForce(Vector3(0, 0, 23), x1.getCoord());
	a.addAttachedForce(Vector3(0, 0, 23), x2.getCoord());*/

	

	parts_vector.push_back(a);
	

	Update(parts_vector,motors);

	cin.get();

	return 0;
}

void Update(vector<Part>& P,Moteur motors[]) {
	//clock_t time;
	//time = clock();
	auto started = std::chrono::high_resolution_clock::now();

	long double time_before = 0;
	long double deltaTime = 0;

	//float g = 9.81;
	const unsigned short MSB = 0x8000;
	bool trigger_up = false;
	bool trigger_down = false;

	unsigned int parts_nr = P.size();
	Drone_Start(&P[0], motors, g*P[0].getMass()/4);

	Go_To_Height(&P[0], 10, motors);
	Pitch(&P[0], 20, motors);
	//Yaw(&P[0], pi/18,motors);
	//Hover(&P[0],motors);
	//disp_Motors(motors);
	//Go_To_Height(&P[0], 100, motors);// , deltaTime);
	
	while (true) {
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before) / 1000;
		time_before = time;

		//std::cout << "T:" << time/1000 << " ";     // Afisarea timpului

		//forceend

		if (GetAsyncKeyState(VK_UP) & MSB && !trigger_up)
		{
			// then the specified key is "down"
			trigger_up = true;
			Go_To_Height(&P[0], P[0].getPosition().f.z+10, motors);
		}
		else if (!(GetAsyncKeyState(VK_UP) & MSB) && trigger_up)
		{
			// the specified key is "up"
			trigger_up = false;
			//Go_To_Height(&P[0], P[0].getPosition().f.z-10, motors);
		}

		if (GetAsyncKeyState(VK_DOWN) & MSB && !trigger_down)
		{
			// then the specified key is "down"
			trigger_down = true;
			Go_To_Height(&P[0], P[0].getPosition().f.z-10, motors);
		}
		else if (!(GetAsyncKeyState(VK_DOWN) & MSB) && trigger_down)
		{
			// the specified key is "up"
			trigger_down = false;
			//Go_To_Height(&P[0], P[0].getPosition().f.z + 10, motors);
		}

		if (GetAsyncKeyState(VK_RIGHT) & MSB )
		{
			Yaw(&P[0], P[0].getRotation().f.z + pi/18, motors);
		}

		if (GetAsyncKeyState(VK_LEFT) & MSB )
		{
			Yaw(&P[0], P[0].getRotation().f.z - pi/18, motors);
		}
		
		for (unsigned int i = 0; i < parts_nr; i++) // -- updatare pozitie a fiecarui obiect
		{
			
			Update_Attributes(&P[0], deltaTime);

			std::cout << setprecision(2) << fixed << i + 1 << ") P:" << P[i].getPosition().toString() << " S:" << P[i].getSpeed().toString() << " A:" << P[i].getModifyingAcc().toString() << "     ";   //- afisare
			std::cout << setprecision(2) << fixed << i + 1 << ") R:" << P[i].getRotation().toString() << "  AV:" << P[i].getAngVel().toString();// << " AA:" << P[i].getAngAcc().toString() << "     ";   //- afisare


			Sleep(50);

		}

		std::cout << "\r";
	}

}