#pragma once
#include <string>
#include "structs.h"

using namespace std;

class Matrix
{
public:
	int rows, columns;
	float **f;
	//Overload Constructor
	Matrix(int r, int c);

	//Operatori
	Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	Matrix operator*(float);		//Inmultirea unei matrice cu un scalar, in ordinea aceasta;
	Vector3 operator*(Vector3);		//Inmultiea unei matrice 3x3 cu un Vector3, cu rezultatul tot un Vector3;
	Matrix operator^(unsigned int);
	Matrix& operator=(const Matrix);

	//Pt Initializare
	Matrix& operator*=(float[]);

	//toString
	std::string toString();

	~Matrix();
};

