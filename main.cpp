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

int main(){
	vector<Part> parts_vector;
	vector<thread> threads_vector;


	Part a(Vector3(10, 0, 500), 1);
	//a.addTimedForce(Vector3(1, 1, 40),2);
	
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
	int trigger_up = 0;

	unsigned int parts_nr = P.size();

	while (true) {
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before)/1000;
		time_before = time;

		std::cout << "T:" << time/1000 << " ";

		//forceend

		if (GetAsyncKeyState(VK_UP) & MSB && !trigger_up)
		{
			// then the specified key is "down"
			trigger_up = 1;
			P[0].addForce(Vector3(0, 0, 25));
		}
		else if(!(GetAsyncKeyState(VK_UP) & MSB) && trigger_up)
		{
			// the specified key is "up"
			trigger_up = 0;
			P[0].addForce(Vector3(0, 0, -25));
		}

		for (unsigned int i = 0; i < parts_nr ; i++) // -- updatare pozitie a fiecarui obiect
		{
			Vector3 newSpeed = P[i].getSpeed() + (P[i].getAcc() * deltaTime);
			Vector3 newPos = P[i].getPosition() + (P[i].getSpeed() * deltaTime);

			if (newPos.f.z > 0) {
				P[i].setSpeed(newSpeed);
				P[i].setPosition(newPos);
			}
			else {
				P[i].setSpeed(Vector3(newSpeed.f.x, newSpeed.f.y, 0));
				P[i].setPosition(Vector3(newPos.f.x, newPos.f.y, 0));
			}

			std::cout << setprecision(2) << fixed << i + 1 << ") Position:" << P[i].getPosition().toString() << "  Speed:" << P[i].getSpeed().toString() << "  Acceleration:" << P[i].getAcc().toString() << "     ";   //- afisare

			Sleep(50);

		}

		std::cout << "\r";
	}

}