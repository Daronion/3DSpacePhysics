#include <iostream>
#include <iomanip>		// -- pt aproximarea zecimalelor
#include "structs.h"
#include "Part.h"
#include <time.h>		
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>


using namespace std;

void Update(vector<Part>&);  // - while infinit in care se updateaza pozitia obiectelor

int main() {
	vector<Part> parts_vector;
	vector<thread> threads_vector;


	Part a(Vector3(10, 0, 500), 10, 100);
	//a.addTimedForce(Vector3(1, 1, 40),2);
	//a.addForce(Vector3(0, 0, 9.81*a.getMass()));
	a.addAttachedForce(Vector3(0, 0, 24.5), Vector3(0, -10, 0));
	a.addAttachedForce(Vector3(0, 0, 24.5), Vector3(0, 10, 0));
	a.addAttachedForce(Vector3(0, 0, 24.5), Vector3(10, 0, 0));
	a.addAttachedForce(Vector3(0, 0, 24.5), Vector3(-10, 0, 0));



	parts_vector.push_back(a);

	Update(parts_vector);

	cin.get();

	return 0;
}

void Update(vector<Part>& P) {
	//clock_t time;
	//time = clock();
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
		deltaTime = (time - time_before) / 1000;
		time_before = time;

		//std::cout << "T:" << time/1000 << " ";     // Afisarea timpului

		//forceend

		if (GetAsyncKeyState(VK_UP) & MSB && !trigger_up)
		{
			// then the specified key is "down"
			trigger_up = true;
			P[0].addForce(Vector3(0, 0, 25));
			P[0].addTorque(Vector3(0, 0, 10));
		}
		else if (!(GetAsyncKeyState(VK_UP) & MSB) && trigger_up)
		{
			// the specified key is "up"
			trigger_up = false;
			P[0].addForce(Vector3(0, 0, -25));
			P[0].addTorque(Vector3(0, 0, -10));

		}

		if (GetAsyncKeyState(VK_DOWN) & MSB && !trigger_down)
		{
			// then the specified key is "down"
			trigger_down = true;
			P[0].addForce(Vector3(0, 0, -25));
			P[0].addTorque(Vector3(0, 0, -10));
		}
		else if (!(GetAsyncKeyState(VK_DOWN) & MSB) && trigger_down)
		{
			// the specified key is "up"
			trigger_down = false;
			P[0].addForce(Vector3(0, 0, 25));
			P[0].addTorque(Vector3(0, 0, 10));

		}

		for (unsigned int i = 0; i < parts_nr; i++) // -- updatare pozitie a fiecarui obiect
		{
			Vector3 newSpeed = P[i].getSpeed() + (P[i].getModifyingAcc() * deltaTime);
			Vector3 newPos = P[i].getPosition() + (P[i].getSpeed() * deltaTime);

			Vector3 newAngVel = P[i].getAngVel() + (P[i].getAngAcc() * deltaTime);
			Vector3 newRotation = P[i].getRotation() + (P[i].getAngVel() * deltaTime);
			P[i].setModifyingAcc(newRotation);

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

			std::cout << setprecision(2) << fixed << i + 1 << ") P:" << P[i].getPosition().toString() << " S:" << P[i].getSpeed().toString() << " A:" << P[i].getModifyingAcc().toString() << "     ";   //- afisare
			std::cout << setprecision(2) << fixed << i + 1 << ") R:" << P[i].getRotation().toString() << "  AV:" << P[i].getAngVel().toString() << " AA:" << P[i].getAngAcc().toString() << "     ";   //- afisare


			Sleep(50);

		}

		std::cout << "\r";
	}

}