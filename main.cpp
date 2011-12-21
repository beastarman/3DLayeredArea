#include "PlaneObject.hpp"
#include "RGBAColor.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <gtkmm.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

class PlaneObjectInSpace : public PlaneObject, public Coordenate
{
	public:
		PlaneObjectInSpace() : PlaneObject(), Coordenate()
		{
		}
		
		PlaneObjectInSpace(const PlaneObject& obj, const Coordenate& coord) : PlaneObject(obj), Coordenate(coord)
		{
		}
		
		PlaneObjectInSpace(const PlaneObject& obj) : PlaneObject(obj), Coordenate()
		{
		}
		
		virtual ~PlaneObjectInSpace()
		{
		}
		
		bool operator > (const PlaneObjectInSpace& that)
		{
			return z>that.z;
		}
		
		bool operator < (const PlaneObjectInSpace& that)
		{
			return z<that.z;
		}
		
		bool operator >= (const PlaneObjectInSpace& that)
		{
			return z>=that.z;
		}
		
		bool operator <= (const PlaneObjectInSpace& that)
		{
			return z<=that.z;
		}
		
		Coordenate get_nodo_position(int id)
		{
			return get_nodo(id)+Coordenate(x,-y,z);
		}
};

class PlaneObjectColection : public Gtk::DrawingArea
{
	private:
		vector<PlaneObjectInSpace> objects;
		bool drawing;
	
	public:
		Coordenate camera;
	
	public:
		PlaneObjectColection()
		{
			objects=vector<PlaneObjectInSpace>();
			camera=Coordenate();
			drawing=0;
		}
		
		virtual ~PlaneObjectColection()
		{
		}
		
		unsigned int push_object(const PlaneObject& obj)
		{
			objects.push_back(PlaneObjectInSpace(obj));
			return objects.size()-1;
		}
		
		unsigned int push_object(const PlaneObject& obj, double x)
		{
			objects.push_back(PlaneObjectInSpace(obj, Coordenate(x)));
			return objects.size()-1;
		}
		
		unsigned int push_object(const PlaneObject& obj, double x, double y)
		{
			objects.push_back(PlaneObjectInSpace(obj, Coordenate(x,y)));
			return objects.size()-1;
		}
		
		unsigned int push_object(const PlaneObject& obj, double x, double y, double z)
		{
			objects.push_back(PlaneObjectInSpace(obj, Coordenate(x,y,z)));
			return objects.size()-1;
		}
		
		unsigned int push_object(const PlaneObject& obj, const Coordenate& pos)
		{
			objects.push_back(PlaneObjectInSpace(obj, pos));
			return objects.size()-1;
		}
		
		bool move_camera (const Coordenate& coord)
		{
			camera+=coord;
			
			return 1;
		}
	
	private:
		int fit_scale(double value, double cur_min, double cur_max, double new_min, double new_max)
		{
			cur_max-=cur_min;
			new_max-=new_min;
			
			value-=cur_min;
			
			value*=(double(new_max)/double(cur_max));
			
			value+=new_min;
			
			return value;
		}
		
		Coordenate get_draw_location(Coordenate real_position, int width, int height, double abertura)
		{
			double size = 2*sin(abertura/2)*(camera.z-real_position.z)/sin(M_PI/2 - abertura/2);
			
			real_position-=Coordenate(camera.x, -camera.y, camera.z);
			
			Coordenate final_position;
			
			final_position.x = fit_scale(real_position.x, 0, size, 0, width)+width/2;
			final_position.y = fit_scale(real_position.y, 0, size, 0, height)+height/2;
			
			return final_position;
			
			return real_position-Coordenate(camera.x,-camera.y,camera.z)+Coordenate(width/2, height/2);
		}
		
		bool static compare(const PlaneObjectInSpace& a, const PlaneObjectInSpace& b)
		{
			return a.z<b.z;
		}
	
	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
		{
			Gtk::Allocation allocation = get_allocation();
			const int width = allocation.get_width();
			const int height = allocation.get_height();
			
			if(!drawing)
			{
				sort(objects.begin(), objects.end(), PlaneObjectColection::compare);
			}
			
			drawing=1;
			
			unsigned int i;
			unsigned int j;
			
			cr->set_line_width(2);
			
			Coordenate temp;
			
			for(i=0; i<objects.size(); i++)
			{
				if(objects[i].get_num_nodos()<2 || objects[i].z>=camera.z) continue;
				
				cr->save();
				
				temp=get_draw_location(objects[i].get_nodo_position(0), width, height, 26.5/M_PI);
					
				cr->line_to(temp.x, temp.y);
				
				cr->move_to(temp.x, temp.y);
				
				for(j=1; j<objects[i].get_num_nodos(); j++)
				{
					temp=get_draw_location(objects[i].get_nodo_position(j), width, height, 26.5/M_PI);
					
					cr->line_to(temp.x, temp.y);
				}
				
				temp=get_draw_location(objects[i].get_nodo_position(0), width, height, 26.5/M_PI);
				cr->line_to(temp.x, temp.y);
				
				temp=get_draw_location(objects[i].get_nodo_position(1), width, height, 26.5/M_PI);
				cr->line_to(temp.x, temp.y);
				
				cr->set_source_rgba(double(objects[i].fill_color.red)/255, double(objects[i].fill_color.green)/255, double(objects[i].fill_color.blue)/255, double(objects[i].fill_color.alpha)/255);
				cr->fill_preserve();
				cr->set_source_rgba(double(objects[i].line_color.red)/255, double(objects[i].line_color.green)/255, double(objects[i].line_color.blue)/255, double(objects[i].line_color.alpha)/255);
				cr->stroke();
				cr->restore();
			}
			
			return 1;
		}
};

class AreaWindow : public Gtk::Window
{
	private:
		PlaneObjectColection* objects;
		
	public:
		AreaWindow()
		{
			set_title("3D Area");
			set_default_size(500, 500);
			
			add_events(Gdk::KEY_PRESS_MASK);
			signal_key_press_event().connect(sigc::mem_fun(*this, &AreaWindow::move_camera));
		}
		
		bool set_PlaneObjectsColection(PlaneObjectColection* new_objects)
		{
			objects = new_objects;
			
			add(*objects);
			
			objects->show();
			
			show_all_children();
			
			return 1;
		}
		
		bool move_camera(GdkEventKey *event)
		{
			if(event->keyval == 0x64)
			{
				objects->camera+=Coordenate(1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == 0x61)
			{
				objects->camera-=Coordenate(1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == 0x77)
			{
				objects->camera-=Coordenate(0,0,1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == 0x73)
			{
				objects->camera+=Coordenate(0,0,1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == 0x69)
			{
				objects->camera+=Coordenate(0,1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == 0x6B)
			{
				objects->camera-=Coordenate(0,1);
				
				objects->hide();
				
				objects->show();
			}
			
			if(event->keyval == GDK_KEY_Escape)
			{
				hide();
			}
			
			return 1;
		}
		
		virtual ~AreaWindow()
		{
		}
};

using namespace std;

int main(int argc, char** argv)
{
	Gtk::Main kit(argc, argv);
	
	PlaneObject square=PlaneObject(4,100);
	PlaneObject triangle=PlaneObject(3,100);
	PlaneObject circle1=PlaneObject(50,3);
	PlaneObject circle2=PlaneObject(50,3);
	PlaneObject circle3=PlaneObject(50,3);
	
	square.fill_color=RGBAColor(0xFF0000, 0x20);
	square.line_color=RGBAColor(0x0000FF, 0xFF);
	triangle.fill_color=RGBAColor(0x00FF00, 0x20);
	
	circle1.fill_color=RGBAColor(0xAA00AA, 0x20);
	circle2.fill_color=RGBAColor(0xAAAA00, 0x20);
	circle3.fill_color=RGBAColor(0x00AAAA, 0x20);
	
	PlaneObjectColection image;
	
	image.push_object(square,-100,0,-100);
	image.push_object(triangle,0,0,-50);
	
	image.push_object(circle1,0,0,-20);
	image.push_object(circle2,30,0,-19);
	image.push_object(circle3,15,15,-21);
	
	image.camera+=Coordenate(0,0,-30);
	
	cout << square << '\n';
	cout << triangle << '\n';
	cout << circle1 << '\n';
	
	AreaWindow win;
	
	win.set_PlaneObjectsColection(&image);
	
	Gtk::Main::run(win);
}
