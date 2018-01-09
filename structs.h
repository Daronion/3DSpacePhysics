#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>

struct Vector3Fields
{
	float x, y, z;

	Vector3Fields(float xg=0, float yg=0, float zg=0) {
		x = xg;
		y = yg;
		z = zg;
	};
};

//#define VECTOR_FIELD_LEN (sizeof(struct Vector3Fields)/sizeof(float))

union Vector3 {
	Vector3Fields f; // f de la fields
	float raw[3];

	//Constructors
	Vector3() {
		f.x = 0;
		f.y = 0;
		f.z = 0;
	}
	Vector3(float x, float y, float z) {
		f.x = x;
		f.y = y;
		f.z = z;
	}
	//toString
	std::string toString()
	{
		std::ostringstream output;
		output << std::setprecision(2) << std::fixed << f.x << " " << f.y << " " << f.z << " ";
		return output.str();
	}
	
	//Operatori

	Vector3 operator+(const Vector3& other) {
		Vector3 result(0, 0, 0);          

		result.f.x = other.f.x + f.x;
		result.f.y = other.f.y + f.y;
		result.f.z = other.f.z + f.z;

		return result;
	}

	Vector3 operator-(const Vector3& other) {
		Vector3 result(0, 0, 0);

		result.f.x = other.f.x - f.x;
		result.f.y = other.f.y - f.y;
		result.f.z = other.f.z - f.z;

		return result;
	}

	Vector3 operator*(const Vector3& other) {
		Vector3 result(0, 0, 0);

		result.f.x = other.f.x * f.x;
		result.f.y = other.f.y * f.y;
		result.f.z = other.f.z * f.z;

		return result;
	}

	Vector3 operator/(const Vector3& other) {
		Vector3 result(0, 0, 0);

		result.f.x = f.x / other.f.x;
		result.f.y = f.y / other.f.y;
		result.f.z = f.z / other.f.z;

		return result;
	}

	Vector3 operator^(const Vector3& other) {   //Operatorul ^ va reprezenta inmultirea vectoriala
		Vector3 result(0, 0, 0);

		result.f.x = f.z*other.f.y - f.y*other.f.z;
		result.f.y = f.x*other.f.z - f.z*other.f.x;
		result.f.z = f.y*other.f.x - f.x*other.f.y;

		return result;
	}

	Vector3 operator*(const double& other) {
		Vector3 result(0, 0, 0);

		result.f.x = other * f.x;
		result.f.y = other * f.y;
		result.f.z = other * f.z;

		return result;
	}

	Vector3 operator/(const double& other) {
		Vector3 result(0, 0, 0);

		result.f.x = f.x / other;
		result.f.y = f.y / other;
		result.f.z = f.z / other;

		return result;
	}

	Vector3& operator=(const Vector3& other) {
		f.x = other.f.x;
		f.y = other.f.y;
		f.z = other.f.z;
		return *this;
	}

	int operator==(const Vector3 other) {
		if (f.x == other.f.x && f.y == other.f.y && f.z == other.f.z)
			return true;
		else
			return false;
	}

	Vector3 add(Vector3 other) {             //  -- adauga vectorului3 curent un alt vector, returneaza un vector3 nou.
		Vector3 result(0,0,0);                 //Ex: c = a.add(b)     , abc Vectori3 

		result.f.x = other.f.x + f.x;
		result.f.y = other.f.y + f.y;
		result.f.z = other.f.z + f.z;

		return result;
	}

	Vector3 subtract(Vector3 other){
		Vector3 result(0, 0, 0);

		result.f.x = other.f.x + f.x;
		result.f.y = other.f.y + f.y;
		result.f.z = other.f.z + f.z;

		return result;
	}

	Vector3 neg() {
		Vector3 result(-f.x, -f.y, -f.z);
		return result;
	}

};