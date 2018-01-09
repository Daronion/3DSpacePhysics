#include <iostream>
#include <iomanip>		// -- pt aproximarea zecimalelor
#include "structs.h"
#include "Part.h"
#include "Matrix.h"
#include <time.h>		
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>

#define PI 3.14159265

using namespace std;

void Update(vector<Part>&);  // - while infinit in care se updateaza pozitia obiectelor

int main(){
	vector<Part> parts_vector;
	vector<thread> threads_vector;


	Part a(Vector3(10, 0, 500), 10 , 100);
	a.setRotation(Vector3(0, 0, 0));
	//a.setRotation(Vector3(PI/6, 0, 0));



	parts_vector.push_back(a);

	Update(parts_vector);

	cin.get();

	return 0;
}

void Update(vector<Part>& P) {
	auto started = std::chrono::high_resolution_clock::now();

	long double time_before = 0;
	long double deltaTime = 0;

	float g = 9.81;
	const unsigned short MSB = 0x8000;
	bool trigger_up = false;
	bool trigger_down = false;

	unsigned int parts_nr = P.size();

	while (true) {
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before)/1000;
		time_before = time;

		//std::cout << "T:" << time/1000 << " ";     // Afisarea timpului

		//forceend

		if (GetAsyncKeyState(VK_UP) & MSB)
		{
			// then the specified key is "down"
			cout << "PF-";
			P[0].Pitch(true);
		}
		else if (GetAsyncKeyState(VK_DOWN) & MSB)
		{
			// then the specified key is "down"
			P[0].Pitch(false);
			cout << "PB-";
		}
		else if (GetAsyncKeyState(VK_RIGHT) & MSB)
		{
			P[0].Roll(true);
			cout << "RR-";
		}
		else if (GetAsyncKeyState(VK_LEFT) & MSB)
		{
			P[0].Roll(false);
			cout << "RL-";
		}
		else if (GetAsyncKeyState('A') & MSB)
		{
			P[0].Lift(true);
			cout << "LU-";
		}
		else if (GetAsyncKeyState('D') & MSB)
		{
			P[0].Lift(false);
			cout << "LD-";
		}
		else {
			cout << "H-";
			P[0].Hover();
		}
		for (unsigned int i = 0; i < parts_nr ; i++) // -- updatare pozitie a fiecarui obiect
		{
			P[0].rotationUpdater();

			Vector3 newSpeed = P[i].getSpeed() + (P[i].getAcc() * deltaTime);
			Vector3 newPos = P[i].getPosition() + (P[i].getSpeed() * deltaTime);

			Vector3 newAngVel = P[i].getAngVel() + (P[i].getAngAcc() * deltaTime);
			Vector3 newRotation = P[i].getRotation() + (P[i].getAngVel() * deltaTime);

			if (newPos.f.z > 0) {
				P[i].setSpeed(newSpeed);
				P[i].setPosition(newPos);
			}
			else {
				P[i].setSpeed(Vector3(newSpeed.f.x, newSpeed.f.y, 0));
				P[i].setPosition(Vector3(newPos.f.x, newPos.f.y, 0));
			}

			P[i].setAngVel(newAngVel);
			P[i].setRotation(newRotation);

			std::cout << setprecision(2) << fixed << i + 1 << ") P:" << P[i].getPosition().toString() << " S:" << P[i].getSpeed().toString() << " A:" << P[i].getAcc().toString() << "     ";   //- afisare
			std::cout << setprecision(2) << fixed << i + 1 << ") R:" << P[i].getRotation().toString()/* << "  AV:" << P[i].getAngVel().toString() << " AA:" << P[i].getAngAcc().toString()*/ << "     ";   //- afisare

			Sleep(50);

		}

		std::cout << "\r";
	}

}