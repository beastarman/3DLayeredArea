#ifndef COORDENATE_HPP
#define COORDENATE_HPP

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Coordenate
{
	public:
		double x;
		double y;
		double z;
		
	public:
		Coordenate();
		
		Coordenate(double newX);
		
		Coordenate(double newX, double newY);
		
		Coordenate(double newX, double newY, double newZ);
		
		virtual ~Coordenate();
		
		Coordenate& operator =(const Coordenate& that);
		
		Coordenate operator +(const Coordenate& that);
		
		Coordenate operator -(const Coordenate& that);
		
		Coordenate operator +();
		
		Coordenate operator -();
		
		Coordenate operator *(const double& mul);
		
		Coordenate operator /(const double& div);
		
		Coordenate& operator ++();
		
		Coordenate operator ++(int);
		
		Coordenate& operator --();
		
		Coordenate operator --(int);
		
		bool operator ==(const Coordenate& that);
		
		bool operator !=(const Coordenate& that);
		
		bool operator !();
		
		bool operator &&(const Coordenate& that);
		
		bool operator ||(const Coordenate& that);
		
		Coordenate& operator +=(const Coordenate& that);
		
		Coordenate& operator -=(const Coordenate& that);
		
		Coordenate& operator *=(const double& mul);
		
		Coordenate& operator /=(const double& div);
		
		operator bool();
		
		double distance(const Coordenate& that);
};

std::ostream& operator<<(std::ostream& out, const Coordenate& coord);

Coordenate operator *(const int& num, const Coordenate& coord);

#endif
