#include "Piece.h"

Piece :: Piece(float size){
  this->size = size;
  rot_nine = 0;
}

void Piece :: setColor(int c) {
  switch(c) {
    case M :
      glColor3f(0.5, 0.5, 0.5);
      break;

    case W :
      glColor3f(1, 1, 1);
      break;

    case Y :
      glColor3f(1, 1, 0);
      break;

    case B :
      glColor3f(0, 0, 1);
      break;

    case R :
      glColor3f(1, 0, 0);
      break;

    case G :
      glColor3f(0.2, 0.6, 0.2);
      break;

    case O :
      glColor3f(1, 0.5, 0);
      break;

    default :
      break;
  }
}

void Piece :: getVertexList(float x, float y, float z, float size) {
  vtx_list.push_back(jhm::position(x-size, y+size, z+size));
  vtx_list.push_back(jhm::position(x+size, y+size, z+size));
  vtx_list.push_back(jhm::position(x+size, y+size, z-size));
  vtx_list.push_back(jhm::position(x-size, y+size, z-size));
  vtx_list.push_back(jhm::position(x-size, y-size, z+size));
  vtx_list.push_back(jhm::position(x+size, y-size, z+size));
  vtx_list.push_back(jhm::position(x+size, y-size, z-size));
  vtx_list.push_back(jhm::position(x-size, y-size, z-size));
}

void Piece :: rotateVertexList_U() {
  jhm::position temp = vtx_list.at(0);
  vtx_list.at(0) = vtx_list.at(3);
  vtx_list.at(3) = vtx_list.at(2);
  vtx_list.at(2) = vtx_list.at(1);
  vtx_list.at(1) = temp;

  temp = vtx_list.at(4);
  vtx_list.at(4) = vtx_list.at(7);
  vtx_list.at(7) = vtx_list.at(6);
  vtx_list.at(6) = vtx_list.at(5);
  vtx_list.at(5) = temp;
}

void Piece :: rotateVertexList_Ui() {
  jhm::position temp = vtx_list.at(0);
  vtx_list.at(0) = vtx_list.at(1);
  vtx_list.at(1) = vtx_list.at(2);
  vtx_list.at(2) = vtx_list.at(3);
  vtx_list.at(3) = temp;

  temp = vtx_list.at(4);
  vtx_list.at(4) = vtx_list.at(5);
  vtx_list.at(5) = vtx_list.at(6);
  vtx_list.at(6) = vtx_list.at(7);
  vtx_list.at(7) = temp;
}

void Piece :: rotateVertexList_R() {
  jhm::position temp = vtx_list.at(0);
  vtx_list.at(0) = vtx_list.at(3);
  vtx_list.at(3) = vtx_list.at(7);
  vtx_list.at(7) = vtx_list.at(4);
  vtx_list.at(4) = temp;

  temp = vtx_list.at(1);
  vtx_list.at(1) = vtx_list.at(2);
  vtx_list.at(2) = vtx_list.at(6);
  vtx_list.at(6) = vtx_list.at(5);
  vtx_list.at(5) = temp;
}

void Piece :: rotateVertexList_Ri() {
  jhm::position temp = vtx_list.at(0);
  vtx_list.at(0) = vtx_list.at(4);
  vtx_list.at(4) = vtx_list.at(7);
  vtx_list.at(7) = vtx_list.at(3);
  vtx_list.at(3) = temp;

  temp = vtx_list.at(1);
  vtx_list.at(1) = vtx_list.at(5);
  vtx_list.at(5) = vtx_list.at(6);
  vtx_list.at(6) = vtx_list.at(2);
  vtx_list.at(2) = temp;
}

void Piece :: draw() {

  setColor(M);
	glBegin(GL_QUADS);

  //Right
  int idx3[4] = {1,2,6,5};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx3[i])[0], vtx_list.at(idx3[i])[1], vtx_list.at(idx3[i])[2]);
  }

  //Bottom
  int idx4[4] = {4,5,6,7};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx4[i])[0], vtx_list.at(idx4[i])[1], vtx_list.at(idx4[i])[2]);
  }

  //Back
  int idx5[4] = {2,3,7,6};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx5[i])[0], vtx_list.at(idx5[i])[1], vtx_list.at(idx5[i])[2]);
  }

  glDisable(GL_COLOR_MATERIAL);
}

void Piece :: rotate_X() {
  jhm::vector axis = jhm::vector(-1,0,0);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(0);
  }
}

void Piece :: rotate_Xi() {
  jhm::vector axis = jhm::vector(1,0,0);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(1);
  }
}

void Piece :: rotate_Y() {
  jhm::vector axis = jhm::vector(0,-1,0);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(2);
  }
}

void Piece :: rotate_Yi() {
  jhm::vector axis = jhm::vector(0,1,0);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(3);
  }
}

void Piece :: rotate_Z() {
  jhm::vector axis = jhm::vector(0,0,-1);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(4);
  }
}

void Piece :: rotate_Zi() {
  jhm::vector axis = jhm::vector(0,0,1);
  jhm::matrix m = jhm::rotation(2 * M_PI * 10./360, axis);
  for(int i = 0; i < vtx_list.size(); i++)
  vtx_list.at(i) = vtx_list.at(i) * m;

  rot_nine++;
  if(rot_nine == 9) {
    rot_nine = 0;
    locRefresh(5);
  }
}
