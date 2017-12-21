#include "CenterPiece.h"

CenterPiece :: CenterPiece(int loc, int c1, float size) : Piece(size)
{
  this->loc = loc;
  this->c1 = c1;
  float piece_ratio = 9./10;
  float piece_size = piece_ratio * (size/2);

  switch (loc)
  {
    case U :
      getVertexList(0, size, 0, piece_size);
      break;

    case F :
      getVertexList(0, 0, size, piece_size);
      rotateVertexList_Ri();
      break;

    case R :
      getVertexList(size, 0, 0, piece_size);
      rotateVertexList_U();
      rotateVertexList_R();
      break;

    case L :
      getVertexList(-size, 0, 0, piece_size);
      rotateVertexList_U();
      rotateVertexList_Ri();
      break;

    case B :
      getVertexList(0, 0, -size, piece_size);
      rotateVertexList_R();
      break;

    case D :
      getVertexList(0, -size, 0, piece_size);
      rotateVertexList_R();
      rotateVertexList_R();
      break;

    default :
      break;
  }
}

void CenterPiece::draw() {

  Piece::draw();

  //Top
  setColor(c1);
  int idx[4] = {0,1,2,3};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx[i])[0], vtx_list.at(idx[i])[1], vtx_list.at(idx[i])[2]);
  }

  //Front
  setColor(M);
  int idx2[4] = {0,1,5,4};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx2[i])[0], vtx_list.at(idx2[i])[1], vtx_list.at(idx2[i])[2]);
  }

  //Left
  setColor(M);
  int idx6[4] = {0,3,7,4};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx6[i])[0], vtx_list.at(idx6[i])[1], vtx_list.at(idx6[i])[2]);
  }
}

void CenterPiece::locRefresh(int index) {}
