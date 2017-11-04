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

void Update(vector<Part>&, Part a);  // - while infinit in care se updateaza pozitia obiectelor

int main(){
	vector<Part> parts_vector;
	vector<thread> threads_vector;
	


	Part a(Vector3(10, 0, 500), 10 , 100); // metri, kg, ???
	//a.addTimedForce(Vector3(1, 1, 40),2);
	//a.addForce(Vector3(0, 0, 9.81*a.getMass())); // N
	//a.addUnevenForce(Vector3(0, 0, 10), Vector3(0, -10, 0));
	//a.addUnevenForce(Vector3(0, 0, 10), Vector3(0, 10, 0));
	//a.addUnevenForce(Vector3(0, 0, 10), Vector3(10, 0, 0));




	parts_vector.push_back(a);

	Update(parts_vector, a);

	cin.get();

	return 0;
}

void Update(vector<Part>& P, Part a) {
	//clock_t time;
	//time = clock();
	auto started = std::chrono::high_resolution_clock::now();

	long double time_before = 0;
	long double deltaTime = 0;

	float g = 9.81; // m/s^2
	const unsigned short MSB = 0x8000;
	bool trigger_altdup = false;
	bool trigger_altddown = false;
	bool trigger_up = false;
	bool trigger_down = false;
	bool trigger_left = false;
	bool trigger_right = false;

	unsigned int parts_nr = P.size();

	while (true) {
		auto done = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
		deltaTime = (time - time_before)/1000;
		time_before = time;

		std::cout << "T:" << time/1000 << "s ";     // Afisarea timpului

		//forceend

		// altitudine; folosim tastele de la numpad + si - ca sa marim, crestem altitudinea

		if (GetAsyncKeyState(VK_ADD) & MSB && !trigger_altdup) 
		{
			// then the specified key is "down"
			trigger_altdup = true;
			P[0].addForce(Vector3(0, 0, a.getMass()*1.5*9.81));     // masa * 9.81 doar ca sa invinga forta gravitationala. recomand un x1.5-x2
			P[0].addTorque(Vector3(0, 0, 10));  // posibil sa nu depinda de nimic? cam dubios
		}
		else if(!(GetAsyncKeyState(VK_ADD) & MSB) && trigger_altdup)
		{
			// the specified key is "up"
			trigger_altdup = false;
			P[0].addForce(Vector3(0, 0, -1*a.getMass()*1.5*9.81));
			P[0].addTorque(Vector3(0, 0, -10));   

		}

		if (GetAsyncKeyState(VK_SUBTRACT) & MSB && !trigger_altddown)
		{
			trigger_altddown = true;
			P[0].addForce(Vector3(0, 0, -1*a.getMass()*1.5*9.81));
			P[0].addTorque(Vector3(0, 0, -10));
		}
		else if (!(GetAsyncKeyState(VK_SUBTRACT) & MSB) && trigger_altddown)
		{
			trigger_altddown = false;
			P[0].addForce(Vector3(0, 0, a.getMass()*1.5*9.81));
			P[0].addTorque(Vector3(0, 0, 10));

		}
		 // end of altitudine
		 // nord si sud 
		if (GetAsyncKeyState(VK_UP) & MSB && !trigger_up)
		{
			trigger_up = true;
			P[0].addForce(Vector3(0, 2, 0));      // aleg 2 pentru ca nu opune rezistenta nimenea
			P[0].addTorque(Vector3(0, -10, 0));  //inca nu inteleg cum functioneaza torque (sau ce e) asa ca iau ca dimos
		}
		else if (!(GetAsyncKeyState(VK_UP) & MSB) && trigger_up)
		{
			trigger_up = false;
			P[0].addForce(Vector3(0, -2, 0));
			P[0].addTorque(Vector3(0, -10, 0));

		}

		if (GetAsyncKeyState(VK_DOWN) & MSB && !trigger_down)
		{
			trigger_down = true;
			P[0].addForce(Vector3(0, -2, 0));
			P[0].addTorque(Vector3(0, -10, 0));
		}
		else if (!(GetAsyncKeyState(VK_DOWN) & MSB) && trigger_down)
		{
			trigger_down = false;
			P[0].addForce(Vector3(0, 2, 0));
			P[0].addTorque(Vector3(0, 10, 0));

		}
		//end of nord si sud

		//vest est
		if (GetAsyncKeyState(VK_RIGHT) & MSB && !trigger_right)
		{
			trigger_right = true;
			P[0].addForce(Vector3(2, 0, 0));     
			P[0].addTorque(Vector3(10, 0, 0));  
		}
		else if (!(GetAsyncKeyState(VK_RIGHT) & MSB) && trigger_right)
		{
			trigger_right = false;
			P[0].addForce(Vector3(-2, 0, 0));
			P[0].addTorque(Vector3(-10, 0, 0));

		}

		if (GetAsyncKeyState(VK_LEFT) & MSB && !trigger_left)
		{
			trigger_left = true;
			P[0].addForce(Vector3(-2, 0, 0));
			P[0].addTorque(Vector3(-10, 0, 0));
		}
		else if (!(GetAsyncKeyState(VK_LEFT) & MSB) && trigger_left)
		{
			trigger_left = false;
			P[0].addForce(Vector3(2, 0, 0));
			P[0].addTorque(Vector3(10, 0, 0));

		}
		// end of vest est

		for (unsigned int i = 0; i < parts_nr ; i++) // -- updatare pozitie a fiecarui obiect
		{
			Vector3 newSpeed = P[i].getSpeed() + (P[i].getAcc() * deltaTime);
			Vector3 newPos = P[i].getPosition() + (P[i].getSpeed() * deltaTime);

			Vector3 newAngVel = P[i].getAngVel() + (P[i].getAngAcc() * deltaTime);
			Vector3 newRotation = P[i].getRotation() + (P[i].getAngVel() * deltaTime);

			if (newPos.f.z >= 0) {
				P[i].setSpeed(newSpeed);
				P[i].setPosition(newPos);
			}
			else {
				P[i].setSpeed(Vector3(newSpeed.f.x, newSpeed.f.y, 0));
				P[i].setPosition(Vector3(newPos.f.x, newPos.f.y, 0));
			}

			P[i].setAngVel(newAngVel);
			P[i].setRotation(newRotation);

			std::cout << setprecision(2) << fixed << i + 1 << ") Poz:" << P[i].getPosition().toString() << " S:" << P[i].getSpeed().toString() << " A:" << P[i].getAcc().toString() << "     ";   //- afisare
		//	std::cout << setprecision(2) << fixed << " R:" << P[i].getRotation().toString() << "  AV:" << P[i].getAngVel().toString() << " AA:" << P[i].getAngAcc().toString() << "     ";   //- afisare


			Sleep(50);

		}

		std::cout << "\r";
	}

}