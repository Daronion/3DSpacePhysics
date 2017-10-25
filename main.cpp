#include <iostream>
#include <iomanip>		// -- pt aproximarea zecimalelor
#include "structs.h"
#include "Part.h"
#include <time.h>		
#include <Windows.h>
#include <vector>


using namespace std;

void Update(vector<Part>&);  // - while infinit in care se updateaza pozitia obiectelor

int main(){
	vector<Part> parts_vector;

	Part a(Vector3(10, 0, 5000), 10);
	//a.addTimedForce(Vector3(1, 1, 40),10);
	//a.addForce(Vector3(1, 1, 40));
	
	parts_vector.push_back(a);

	Update(parts_vector);

	cin.get();

	return 0;
}

void Update(vector<Part>& P) {
	clock_t time;
	time = clock();
	float g = 9.81;

	unsigned int parts_nr = P.size();

	while (true) {
		time = ((float)(clock() - time)) / CLOCKS_PER_SEC;   // -- aproximatie sa dea in secunde, nu stiu cat de buna e

		cout << "Time: " << time << "  ";

		for (unsigned int i = 0; i < parts_nr ; i++) // -- updatare pozitie a fiecarui obiect
		{
			if (P[i].getPosition().f.z > 0) {						// -- verifica daca obiectul se afla deasupra pamantului
				P[i].setSpeed(Vector3(
				P[i].getSpeed().f.x + P[i].getAcc().f.x,
				P[i].getSpeed().f.y + P[i].getAcc().f.y, 
				P[i].getSpeed().f.z - g + P[i].getAcc().f.z));       // creste/scade viteza pe baza acceleratiei

				P[i].setPosition(P[i].getPosition().add(P[i].getSpeed()));		// update coord
			}
			else {
				P[i].setSpeed(Vector3(
				P[i].getSpeed().f.x + P[i].getAcc().f.x,
				P[i].getSpeed().f.y + P[i].getAcc().f.y,
				P[i].getSpeed().f.z + P[i].getAcc().f.z));             // creste/scade viteza pe baza acceleratiei dar nu se mai ia in calcul G-ul	
																			  // -- opreste obiectul din cadere
				if (P[i].getSpeed().f.z < 0) {
					P[i].setSpeed(Vector3(P[i].getSpeed().f.x, P[i].getSpeed().f.y, 0));
				}

				P[i].setPosition(Vector3(
				P[i].getPosition().f.x + P[i].getSpeed().f.x ,
				P[i].getPosition().f.y + P[i].getSpeed().f.y,
					0)); // update coord
			}

			cout << setprecision(2) << fixed << i + 1 << ") Position:" << P[i].getPosition().toString() << "  Speed:" << P[i].getSpeed().toString() << "  Acceleration:" << P[i].getAcc().toString() << "     ";   //- afisare
			Sleep(500);

		}

		cout << "\r";

	}

}