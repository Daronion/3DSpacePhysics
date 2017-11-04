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
	Matrix operator^(unsigned int);
	Matrix& operator=(const Matrix);

	//Pt Initializare
	Matrix& operator*=(float[]);

	//toString
	std::string toString();

	~Matrix();
};

