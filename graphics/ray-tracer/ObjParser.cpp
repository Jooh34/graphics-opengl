#include "ObjParser.h"

ObjParser :: ObjParser (const char* filename, jhm::vector translation, float scale, BSPtree &tree) {
  std::ifstream File(filename);
  string Line;
  string Name;
  jhm::vector v = jhm::vector(1,1,1);
  jhm::position p = jhm::position(0,0,0);
  jhm::position prev_p = jhm::position(0,0,0);
  jhm::position prev_prev_p = jhm::position(0,0,0);

  std::vector<jhm::position> points;

  while(std::getline(File, Line)){
    if(Line == "" || Line[0] == '#')// Skip everything and continue with the next line
      continue;

    std::istringstream LineStream(Line);
    LineStream >> Name;

    if(Name == "v"){// Vertex
    	float Vertex[3];
      sscanf(Line.c_str(), "%*s %f %f %f", &Vertex[0], &Vertex[1], &Vertex[2]);
      p = jhm::position(Vertex[0], Vertex[1], Vertex[2])*scale + translation;
      points.push_back(p);
    }
  };
}
