#include "RGBAColor.hpp"

RGBAColor::RGBAColor() : RGBColor()
{
	alpha=255;
}

RGBAColor::RGBAColor(int k) : RGBColor(k)
{
	alpha=255;
}

RGBAColor::RGBAColor(int k, short int a) : RGBColor(k)
{
	alpha=(a>255?255:a);
}

RGBAColor::RGBAColor(short int r, short int g, short int b) : RGBColor(r,g,b)
{
	alpha=255;
}

RGBAColor::RGBAColor(short int r, short int g, short int b, short int a) : RGBColor(r,g,b)
{
	alpha=(a>255?255:a);
}

RGBAColor& RGBAColor::operator = (const RGBAColor& that)
{
	blue=that.blue;
	green=that.green;
	red=that.red;
	alpha=that.alpha;
	
	return *this;
}

bool RGBAColor::operator == (const RGBAColor& that)
{
	return blue==that.blue && green==that.green && red==that.red && alpha==that.alpha;
}

bool RGBAColor::operator != (const RGBAColor& that)
{
	return !(blue==that.blue && green==that.green && red==that.red && alpha==that.alpha);
}

std::ostream& operator<<(std::ostream& out, const RGBAColor& color)
{
	out << '#';
	
	out << uppercase << setfill('0') << setw(2) << hex << color.red;
	out << uppercase << setfill('0') << setw(2) << hex << color.green;
	out << uppercase << setfill('0') << setw(2) << hex << color.blue;
	return out << uppercase << '(' << setfill('0') << setw(2) << hex << color.alpha << ')';
}
