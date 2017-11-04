#include "Matrix.h"
#include "structs.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Matrix::Matrix(int r, int c)
{
	rows = r;
	columns = c;
	f = new float*[rows];
	for (int i = 0; i < rows; i++)
		f[i] = new float[columns];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			f[i][j] = 0;
		}
	}
}

Matrix Matrix::operator+(Matrix other) {
	if (!(this->rows == other.rows && this->columns == other.columns))
	{
		std::cout << ("ERROR: The matrices you are trying to add have different sizes");
		terminate();
	}
	Matrix aux(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			aux.f[i][j] = f[i][j] + other.f[i][j];
		}
	}
	return aux;
}

Matrix Matrix::operator-(Matrix other) {
	if (!(this->rows == other.rows && this->columns == other.columns))
	{
		std::cout << ("ERROR: The matrices you are trying to add  have different sizes");
		terminate();
	}
	Matrix aux(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			aux.f[i][j] = f[i][j] - other.f[i][j];
		}
	}
	return aux;
}

Matrix Matrix::operator*(Matrix b) {
	int i, j, k;
	float sum;
	if (this->columns != b.rows)
	{
		std::cout << ("ERROR: The number columns of this  != number of rows in Matrix2!");
		terminate();
	}
	Matrix result(this->rows, b.columns);
	for (i = 0; i < this->rows; i += 1)
	{
		for (k = 0; k < b.columns; k += 1)
		{
			sum = 0;

			for (j = 0; j < this->columns; j += 1)
			{
				sum += this->f[i][j] * b.f[j][k];
			}

			result.f[i][k] = sum;
		}
	}
	return result;
}

Matrix Matrix::operator^(unsigned int putere){

	Matrix out(this->rows, this->columns);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->columns; ++j)
			out.f[i][j] = (i == j);

	Matrix temp(this->rows, this->columns);

	for (int i = 0; i < putere; i++)
	{
		for (int i = 0; i<this->rows; i++)
		{
			for (int j = 0; j<this->rows; j++)
			{
				temp.f[i][j] = 0;
				for (int k = 0; k<this->rows; k++)
				{
					temp.f[i][j] += out.f[i][k] * this->f[k][j];
				}
			}
		}

		for (int i = 0; i<this->rows; i++)
		{
			for (int j = 0; j<this->rows; j++)
			{
				out.f[i][j] = temp.f[i][j];
			}
		}
	}
	return out;
}

Matrix& Matrix::operator=(const Matrix other) {
	if (!(this->rows == other.rows && this->columns == other.columns))
	{
		std::cout << ("ERROR: The matrices you are trying to add  have different sizes");
		terminate();
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			f[i][j] = other.f[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(float arr[]) {
	int k = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			f[i][j] = arr[k];
			k++;
		}
	}

	return *this;
}

std::string Matrix::toString()
{
	std::ostringstream str;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			str << f[i][j] << " ";
		}
		str <<	"\n";
	}
	str << "\n";
	return str.str();
}

Matrix::~Matrix()
{
}
