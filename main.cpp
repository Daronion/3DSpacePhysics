#include <iostream>
#include <iomanip>
#include "structs.h"
#include "Part.h"
#include <time.h>
#include <Windows.h>
#include <vector>


using namespace std;

void Update(vector<Part>&);  // - while infinit in care se updateaza pozitia obiectelor

int main(){
	vector<Part> parts_vector;

	Part a(Vector3(10,0,500),10);
	Part b(Vector3(0,10,5000),5);
	
	parts_vector.push_back(a);
	parts_vector.push_back(b);

	Update(parts_vector);

	cout << a.getPosition().add(b.getPosition()).toString();
	cin.get();

	return 0;
}

void Update(vector<Part>& P) {
	clock_t time;
	time = clock();
	double g = 9.81;

	unsigned int parts_nr = P.size();

	while (true) {
		time = (clock() - time) / 850;   // -- aproximatie sa dea in secunde, nu stiu cat de buna e

		for (unsigned int i = 0; i < parts_nr ; i++) // -- updatare pozitie a fiecarui obiect
		{
			if (P[i].getPosition().f.z > 0) {						// -- verifica daca obiectul se afla deasupra pamantului
				P[i].setSpeed(Vector3(0, 0, -(float)g*time));             // creste/scade viteza pe baza acceleratiei
			}
			else {
				P[i].setSpeed(Vector3(0,0,0));						// -- opreste obiectul
				P[i].setPosition(Vector3(P[i].getPosition().f.x, P[i].getPosition().f.y, 0)); // corecteaza erori
			}

			P[i].setPosition(P[i].getPosition().add(P[i].getSpeed()));	// -- updateaza coordonatele obiectului pe baza vitezei in secunda respectiva

			cout << setprecision(2) << fixed << "         " << "Time:" << time << " " << P[i].getPosition().toString() << "            ";
			Sleep(100);

		}

		cout << "\r";

	}

}