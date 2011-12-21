#include "RGBColor.hpp"

RGBColor::RGBColor()
{
	blue=0;
	green=0;
	red=0;
}

RGBColor::RGBColor(int k)
{
	color a;
	
	a.cor=k;
	
	blue=a.separate[0];
	green=a.separate[1];
	red=a.separate[2];
}

RGBColor::RGBColor(short int r, short int g, short int b)
{
	blue=(b>255?255:b);
	green=(g>255?255:g);
	red=(r>255?255:r);
}

RGBColor& RGBColor::operator =(const RGBColor& that)
{
	blue=that.blue;
	green=that.green;
	red=that.red;
	
	return *this;
}

bool RGBColor::operator ==(const RGBColor& that)
{
	return blue==that.blue && green==that.green && red==that.red;
}

bool RGBColor::operator !=(const RGBColor& that)
{
	return !(blue==that.blue && green==that.green && red==that.red);
}

std::ostream& operator<<(std::ostream& out, const RGBColor& color)
{
	out << '#';
	
	out << uppercase << setfill('0') << setw(2) << color.red;
	out << uppercase << setfill('0') << setw(2) << color.green;
	return out << uppercase << setfill('0') << setw(2) << color.blue;
}
