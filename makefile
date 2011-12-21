all:
	@g++ -Wall -c main.cpp `pkg-config --libs --cflags cairomm-1.0 gtkmm-3.0`
	@g++ -Wall -c PlaneObject.cpp
	@g++ -Wall -c Coordenate.cpp
	@g++ -Wall -c RGBColor.cpp
	@g++ -Wall -c RGBAColor.cpp
	@g++ -Wall -o main main.o Coordenate.o PlaneObject.o RGBColor.o RGBAColor.o `pkg-config --libs --cflags cairomm-1.0 gtkmm-3.0`

clean:
	@rm main main.o PlaneObject.o Coordenate.o RGBColor.o RGBAColor.o
