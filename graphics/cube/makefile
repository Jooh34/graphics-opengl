CC = g++

# make: drawing.cpp 3dmodel.cpp
# 	g++ drawing.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass -o drawing
# 	g++ 3dmodel.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass -o 3dmodel

make:
	g++ -c main.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c exchanged_peak.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Trackball.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c Piece.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c EdgePiece.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CornerPiece.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c CenterPiece.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass
	g++ -c RotationManager.cpp -lm -lGL -lGLU -lglut -L lib -l mathclass

	g++ main.o Trackball.o Piece.o EdgePiece.o CornerPiece.o CenterPiece.o RotationManager.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o main
	g++ exchanged_peak.o Trackball.o Piece.o EdgePiece.o CornerPiece.o CenterPiece.o RotationManager.o -lm -lGL -lGLU -lglut -L lib -l mathclass -o exchanged_peak

clean:
	rm -f *.o
