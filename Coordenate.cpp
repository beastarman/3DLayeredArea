#include "Coordenate.hpp"

Coordenate::Coordenate()
{
	x=0;
	y=0;
	z=0;
}

Coordenate::Coordenate(double newX)
{
	x=newX;
	y=0;
	z=0;
}

Coordenate::Coordenate(double newX, double newY)
{
	x=newX;
	y=newY;
	z=0;
}

Coordenate::Coordenate(double newX, double newY, double newZ)
{
	x=newX;
	y=newY;
	z=newZ;
}

Coordenate::~Coordenate()
{
}

Coordenate& Coordenate::operator =(const Coordenate& that)
{
	x=that.x;
	y=that.y;
	z=that.z;
	
	return *this;
}

Coordenate Coordenate::operator +(const Coordenate& that)
{
	return Coordenate(x+that.x, y+that.y, z+that.z);
}

Coordenate Coordenate::operator -(const Coordenate& that)
{
	return Coordenate(x-that.x, y-that.y, z-that.z);
}

Coordenate Coordenate::operator +()
{
	return Coordenate(x,y,z);
}

Coordenate Coordenate::operator -()
{
	return Coordenate(-x,-y,-z);
}

Coordenate Coordenate::operator *(const double& mul)
{
	return Coordenate(x*mul, y*mul, z*mul);
}

Coordenate Coordenate::operator /(const double& div)
{
	return Coordenate(x/div, y/div, z/div);
}

Coordenate& Coordenate::operator ++()
{
	x++;
	y++;
	z++;
	
	return *this;
}

Coordenate Coordenate::operator ++(int)
{
	Coordenate temp = Coordenate(x,y,z);
	
	x++;
	y++;
	z++;
	
	return temp;
}

Coordenate& Coordenate::operator --()
{
	x--;
	y--;
	z--;
	
	return *this;
}

Coordenate Coordenate::operator --(int)
{
	Coordenate temp = Coordenate(x,y,z);
	
	x--;
	y--;
	z--;
	
	return temp;
}

bool Coordenate::operator ==(const Coordenate& that)
{
	return x==that.x && y==that.y && z==that.z;
}

bool Coordenate::operator !=(const Coordenate& that)
{
	return x!=that.x || y!=that.y || z!=that.z;
}

bool Coordenate::operator !()
{
	return !(x || y || z);
}

bool Coordenate::operator &&(const Coordenate& that)
{
	return (x || y || z) && (that.x || that.y || that.z);
}

bool Coordenate::operator ||(const Coordenate& that)
{
	return (x || y || z) || (that.x || that.y || that.z);
}

Coordenate& Coordenate::operator +=(const Coordenate& that)
{
	x+=that.x;
	y+=that.y;
	z+=that.z;
	
	return *this;
}

Coordenate& Coordenate::operator -=(const Coordenate& that)
{
	x-=that.x;
	y-=that.y;
	z-=that.z;
	
	return *this;
}

Coordenate& Coordenate::operator *=(const double& mul)
{
	x*=mul;
	y*=mul;
	z*=mul;
	
	return *this;
}

Coordenate& Coordenate::operator /=(const double& div)
{
	x/=div;
	y/=div;
	z/=div;
	
	return *this;
}

Coordenate::operator bool()
{
	return x || y || z;
}

double Coordenate::distance(const Coordenate& that)
{
	return sqrt((z-that.z)*(z-that.z) + (x-that.x)*(x-that.x) + (y-that.y)*(y-that.y));
}

std::ostream& operator<<(std::ostream& out, const Coordenate& coord)
{
	return out<< '[' << setprecision(4) << coord.x << ", " << coord.y << ", " << coord.z << "]";
}

Coordenate operator *(const int& num, const Coordenate& coord)
{
	return Coordenate(coord.x*num, coord.y*num, coord.z*num);
}
