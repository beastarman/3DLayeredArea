#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP

#include <iostream>
#include <iomanip>

using namespace std;

class RGBColor
{
	public:
		short int blue;
		short int green;
		short int red;
	
	public:
		RGBColor();
		
		RGBColor(int k);
		
		RGBColor(short int r, short int g, short int b);
		
		RGBColor& operator =(const RGBColor& that);
		
		bool operator ==(const RGBColor& that);
		
		bool operator !=(const RGBColor& that);
};

std::ostream& operator<<(std::ostream& out, const RGBColor& color);

typedef union
{
	int cor;
	unsigned char separate[4];
}color;

#endif
