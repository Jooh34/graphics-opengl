CC = g++

# make: drawing.cpp 3dmodel.cpp
# 	g++ drawing.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass -o drawing
# 	g++ 3dmodel.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass -o 3dmodel

make:
	g++ -c app1.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c app2.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c app3.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Trackball.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CrossSection.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Model.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c BSpline_2D.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CatmullRom_2D.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c TransformManager.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Material.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Cube.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Triangle.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c BSPtree.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Node.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass

	g++ app1.o Trackball.o CrossSection.o Model.o BSpline_2D.o CatmullRom_2D.o TransformManager.o Material.o Cube.o Triangle.o BSPtree.o Node.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o app1
	g++ app2.o Trackball.o CrossSection.o Model.o BSpline_2D.o CatmullRom_2D.o TransformManager.o Material.o Cube.o Triangle.o BSPtree.o Node.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o app2
	g++ app3.o Trackball.o CrossSection.o Model.o BSpline_2D.o CatmullRom_2D.o TransformManager.o Material.o Cube.o Triangle.o BSPtree.o Node.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o app3
