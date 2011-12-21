#include "PlaneObject.hpp"

PlaneObject::PlaneObject()
{
	nodos=vector<Coordenate>();
}

PlaneObject::PlaneObject(unsigned int edges, double side)
{
	nodos=vector<Coordenate>();
	
	if(!edges) return;
	
	if(edges==1)
	{
		nodos.push_back(Coordenate());
		
		return;
	}
	
	double radius = side*sin((M_PI-(2*M_PI/edges))/2)/sin(2*M_PI/edges);
	
	unsigned int i=0;
	
	for (i=0; i<edges; i++)
	{
		nodos.push_back(Coordenate(sin((2*M_PI)*i/edges+(M_PI/edges)) * radius, cos((2*M_PI)*i/edges+(M_PI/edges)) * radius));
	}
}

bool PlaneObject::insert_nodo_before(unsigned int pos, const Coordenate& coord)
{
	if(pos>nodos.size()) return 0;
	
	if(pos==nodos.size()+1)
	{
		nodos.push_back(Coordenate(coord.x, coord.y));
		
		return 1;
	}
	
	nodos.insert(nodos.begin()+pos, Coordenate(coord.x, coord.y));
	
	return 1;
}

bool PlaneObject::insert_nodo_before(int pos, double x, double y)
{
	return insert_nodo_before(pos, Coordenate(x,y));
}

bool PlaneObject::insert_nodo_after(unsigned int pos, const Coordenate& coord)
{
	return insert_nodo_before(pos+1, coord);
}

bool PlaneObject::insert_nodo_after(int pos, double x, double y)
{
	return insert_nodo_before(pos+1, Coordenate(x,y));
}

bool PlaneObject::insert_nodo_nearest(Coordenate& coord)
{
	if(nodos.size()<2)
	{
		nodos.push_back(Coordenate(coord.x, coord.y));
		
		return 1;
	}
	
	double min = abs(coord.distance(nodos[0])) + abs(coord.distance(nodos[nodos.size()-1]));
	unsigned int near=0;
	unsigned int i=0;
	
	for (i=1; i<nodos.size(); i++)
	{
		if(min > abs(coord.distance(nodos[i-1])) + abs(coord.distance(nodos[i])))
		{
			min = abs(coord.distance(nodos[i-1])) + abs(coord.distance(nodos[i]));
			
			near=i;
		}
	}
	
	insert_nodo_before(near, coord);
	
	return 1;
}

bool PlaneObject::insert_nodo_nearest(double x, double y)
{
	Coordenate temp = Coordenate(x,y);
	
	return insert_nodo_nearest(temp);
}

bool PlaneObject::remove_nodo(unsigned int pos)
{
	
	if(pos>=nodos.size()) return 0;
	
	nodos.erase(nodos.begin()+pos);
	
	return 1;
}

Coordenate& PlaneObject::get_nodo(int pos)
{
	if(pos<0) pos+=nodos.size();
	
	return nodos[pos];
}

unsigned int PlaneObject::get_num_nodos()
{
	return nodos.size();
}
	
bool PlaneObject::move_nodo(unsigned int pos, double x, double y)
{
	if(pos>=nodos.size()) return 0;
	
	nodos[pos].x=x;
	nodos[pos].y=y;
	
	return 1;
}
	
bool PlaneObject::move_nodo(unsigned int pos, const Coordenate& coord)
{
	if(pos>=nodos.size()) return 0;
	
	nodos[pos].x=coord.x;
	nodos[pos].y=coord.y;
	
	return 1;
}

bool PlaneObject::move_object(double x, double y)
{
	if(!nodos.size()) return 0;
	
	unsigned int i=0;
	
	for(i=0; i<nodos.size(); i++)
	{
		nodos[i].x+=x;
		nodos[i].y+=y;
	}
	
	return 1;
}

bool PlaneObject::move_object(const Coordenate& coord)
{
	if(!nodos.size()) return 0;
	
	unsigned int i=0;
	
	for(i=0; i<nodos.size(); i++)
	{
		nodos[i].x+=coord.x;
		nodos[i].y+=coord.y;
	}
	
	return 1;
}

double PlaneObject::scale(double num)
{
	unsigned int i=0;
	
	for (i=0; i<nodos.size(); i++) nodos[i]*=num;
	
	return num;
}

bool PlaneObject::center()
{
	if(!nodos.size()) return 0;
	
	unsigned int i=0;
	double min_x=nodos[0].x;
	double min_y=nodos[0].y;
	double max_x=nodos[0].x;
	double max_y=nodos[0].y;
	
	for(i=1; i<nodos.size(); i++)
	{
		if(min_x>nodos[i].x) min_x=nodos[i].x;
		if(min_y>nodos[i].y) min_y=nodos[i].y;
		if(max_x<nodos[i].x) max_x=nodos[i].x;
		if(max_y<nodos[i].y) max_y=nodos[i].y;
	}
	
	move_object(-min_x, -min_y);
	
	max_x-=min_x;
	max_x/=2;
	
	max_y-=min_y;
	max_y/=2;
	
	move_object(-max_x, -max_y);
	
	return 1;
}

PlaneObject& PlaneObject::operator =(PlaneObject that)
{
	while (nodos.size()) nodos.pop_back();
	
	unsigned int i=0;
	
	for (i=0; i<that.get_num_nodos(); i++)
	{
		nodos.push_back(Coordenate(that.get_nodo(i).x, that.get_nodo(i).y));
	}
	
	line_color=that.line_color;
	fill_color=that.fill_color;
	
	return *this;
}

PlaneObject PlaneObject::operator *(const double& mul)
{
	PlaneObject temp=PlaneObject();
	
	temp.operator=(*this);
	
	temp.scale(mul);
	
	return temp;
}

PlaneObject PlaneObject::operator /(const double& div)
{
	PlaneObject temp=PlaneObject();
	
	temp.operator=(*this);
	
	temp.scale(1/div);
	
	return temp;
}

bool PlaneObject::operator ==(PlaneObject that)
{
	long int i=0;
	long int j=0;
	
	if(nodos.size() != that.get_num_nodos()) return 0;
	
	for (i=0; i<(long int)(nodos.size()); i++)
	{
		if(nodos[0] == that.get_nodo(i))
		{
			for(j=0; j<(long int)(nodos.size()); j++)
			{
				if(that.get_nodo((j+i>=(long int)(nodos.size())? j+i-nodos.size() : j+i))!=nodos[j])
				{
					break;
				}
			}
			
			if(j==(long int)(nodos.size())) return 1;
			
			for(j=0; j<(long int)(nodos.size()); j++)
			{
				if(that.get_nodo((i-j<0? i-j+nodos.size() : i-j))!=nodos[j])
				{
					break;
				}
			}
			
			if(j==(long int)(nodos.size())) return 1;
		}
	}
	
	return 0;
}

bool PlaneObject::operator !=(PlaneObject that)
{
	return !operator==(that);
}

PlaneObject& PlaneObject::operator *= (double mul)
{
	scale(mul);
	
	return *this;
}

PlaneObject& PlaneObject::operator /= (double div)
{
	scale(1/div);
	
	return *this;
}

Coordenate& PlaneObject::operator [](int pos)
{
	if(pos<0) pos+=nodos.size();
	
	return nodos[pos];
}

template <typename T>
T PlaneObject::abs(T num)
{
	return (num>0?num:-num);
}

std::ostream& operator<<(std::ostream& out, PlaneObject figure)
{
	out << '[';
	
	if(!figure.get_num_nodos()) return out << ']' << " (fill: " << figure.fill_color << ", line: " << figure.line_color << ")";
	
	unsigned int i = 0;
	
	for (i=0; i<figure.get_num_nodos()-1; i++) out << figure.get_nodo(i) << ", ";
	
	return out << figure.get_nodo(figure.get_num_nodos()-1) << ']' << " (fill: " << figure.fill_color << ", line: " << figure.line_color << ")";
}

PlaneObject operator *(const double& mul, PlaneObject obj)
{
	PlaneObject temp=PlaneObject();
	
	temp.operator=(obj);
	
	temp.scale(mul);
	
	return temp;
}
