#ifndef RGBACOLOR_HPP
#define RGBACOLOR_HPP

#include "RGBColor.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

class RGBAColor : public RGBColor
{
	public:
		short int alpha;
	
	public:
		RGBAColor();
		
		RGBAColor(int k);
		
		RGBAColor(int k, short int a);
		
		RGBAColor(short int r, short int g, short int b);
		
		RGBAColor(short int r, short int g, short int b, short int a);
		
		RGBAColor& operator = (const RGBAColor& that);
		
		bool operator == (const RGBAColor& that);
		
		bool operator != (const RGBAColor& that);
};

std::ostream& operator<<(std::ostream& out, const RGBAColor& color);

#endif
