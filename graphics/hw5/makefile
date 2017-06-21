CC = g++

make:
	g++ -c main.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Object.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Sphere.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Polygon.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Texture.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass

	g++ main.o Object.o Sphere.o Polygon.o Texture.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o main
