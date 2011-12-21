#ifndef PLANEOBJECT_HPP
#define PLANEOBJECT_HPP

#include "Coordenate.hpp"
#include "RGBAColor.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class PlaneObject
{
	private:
		vector<Coordenate> nodos;
	
	public:
		RGBAColor line_color;
		RGBAColor fill_color;
	
	public:
		PlaneObject();
		
		PlaneObject(unsigned int edges, double radius);
		
		bool insert_nodo_before(unsigned int pos, const Coordenate& coord);
		
		bool insert_nodo_before(int pos, double x, double y);
		
		bool insert_nodo_after(unsigned int pos, const Coordenate& coord);
		
		bool insert_nodo_after(int pos, double x, double y);
		
		bool insert_nodo_nearest(Coordenate& coord);
		
		bool insert_nodo_nearest(double x, double y);
		
		bool remove_nodo(unsigned int pos);
		
		Coordenate& get_nodo(int pos);
		
		unsigned int get_num_nodos();
	
		bool move_nodo(unsigned int pos, double x, double y);
	
		bool move_nodo(unsigned int pos, const Coordenate& coord);
		
		bool move_object(double x, double y);
		
		bool move_object(const Coordenate& coord);
		
		double scale(double num);
		
		bool center();
		
		PlaneObject& operator =(PlaneObject that);
		
		PlaneObject operator *(const double& mul);
		
		PlaneObject operator /(const double& div);
		
		bool operator ==(PlaneObject that);
		
		bool operator !=(PlaneObject that);
		
		PlaneObject& operator *= (double mul);
		
		PlaneObject& operator /= (double div);
		
		Coordenate& operator [](int pos);
	
	private:
		template <typename T>
		T abs(T num);
};

std::ostream& operator<<(std::ostream& out, PlaneObject figure);

PlaneObject operator *(const double& mul, PlaneObject obj);

#endif
