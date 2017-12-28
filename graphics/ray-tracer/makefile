CC = g++

make:
	g++ -c main.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Object.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Sphere.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Polygon.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Texture.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Model.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Node.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c BSPtree.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Triangle.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CrossSection.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c BSpline_2D.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CatmullRom_2D.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c TransformManager.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c ObjParser.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c EasyBMP.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass

	g++ main.o Object.o Sphere.o Polygon.o Texture.o Model.o Node.o BSPtree.o Triangle.o BSpline_2D.o CatmullRom_2D.o TransformManager.o CrossSection.o ObjParser.o EasyBMP.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o main

clean:
	rm -f *.o
