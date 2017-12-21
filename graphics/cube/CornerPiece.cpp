#include "CornerPiece.h"

CornerPiece :: CornerPiece(int loc, int c1, int c2, int c3, float size) : Piece(size)
{
  this->loc = loc;
  this->c1 = c1;
  this->c2 = c2;
  this->c3 = c3;
  float piece_ratio = 9./10;
  float piece_size = piece_ratio * (size/2);

  switch (loc)
  {
    case UFL :
      getVertexList(-size, size, size, piece_size);
      break;

    case UFR :
      getVertexList(size, size, size, piece_size);
      rotateVertexList_Ui();
      break;

    case UBR :
      getVertexList(size, size, -size, piece_size);
      rotateVertexList_Ui();
      rotateVertexList_Ui();
      break;

    case UBL :
      getVertexList(-size, size, -size, piece_size);
      rotateVertexList_U();
      break;

    case DFL :
      getVertexList(-size, -size, size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_Ri();
      rotateVertexList_U();
      break;

    case DFR :
      getVertexList(size, -size, size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_Ri();
      rotateVertexList_U();
      rotateVertexList_U();
      break;

    case DBR :
      getVertexList(size, -size, -size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_Ri();
      rotateVertexList_Ui();
      break;

    case DBL :
      getVertexList(-size, -size, -size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_Ri();
      break;

    default :
      break;
  }
}

void CornerPiece::draw() {

  Piece::draw();

  //Top
  setColor(c1);
  int idx[4] = {0,1,2,3};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx[i])[0], vtx_list.at(idx[i])[1], vtx_list.at(idx[i])[2]);
  }

  //Front
  setColor(c3);
  int idx2[4] = {0,1,5,4};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx2[i])[0], vtx_list.at(idx2[i])[1], vtx_list.at(idx2[i])[2]);
  }

  //Left
  setColor(c2);
  int idx6[4] = {0,3,7,4};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx6[i])[0], vtx_list.at(idx6[i])[1], vtx_list.at(idx6[i])[2]);
  }
}

void CornerPiece::locRefresh(int index) {
  switch (index) {
    case 0 : // X axis
      switch (loc) {
        case UFR :
          loc = UBR;
          break;

        case UBR :
          loc = DBR;
          break;

        case DBR :
          loc = DFR;
          break;

        case DFR :
          loc = UFR;
          break;

        case UFL :
          loc = UBL;
          break;

        case UBL :
          loc = DBL;
          break;

        case DBL :
          loc = DFL;
          break;

        case DFL :
          loc = UFL;
          break;
      }
      break;

    case 1 : // X' axis
      switch (loc) {
        case UFR :
          loc = DFR;
          break;

        case DFR :
          loc = DBR;
          break;

        case DBR :
          loc = UBR;
          break;

        case UBR :
          loc = UFR;
          break;

        case UFL :
          loc = DFL;
          break;

        case DFL :
          loc = DBL;
          break;

        case DBL :
          loc = UBL;
          break;

        case UBL :
          loc = UFL;
          break;
      }
      break;

    case 2 : // Y axis
      switch (loc) {
        case UFL :
          loc = UBL;
          break;

        case UBL :
          loc = UBR;
          break;

        case UBR :
          loc = UFR;
          break;

        case UFR :
          loc = UFL;
          break;

        case DFL :
          loc = DBL;
          break;

        case DBL :
          loc = DBR;
          break;

        case DBR :
          loc = DFR;
          break;

        case DFR :
          loc = DFL;
          break;

        default :
          break;
      }
      break;

    case 3 : // Y' axis
      switch (loc) {
        case UFL :
          loc = UFR;
          break;

        case UFR :
          loc = UBR;
          break;

        case UBR :
          loc = UBL;
          break;

        case UBL :
          loc = UFL;
          break;

        case DFL :
          loc = DFR;
          break;

        case DFR :
          loc = DBR;
          break;

        case DBR :
          loc = DBL;
          break;

        case DBL :
          loc = DFL;
          break;

        default :
          break;
      }
      break;

    case 4 : // Z axis
      switch (loc) {
        case UFL :
          loc = UFR;
          break;

        case UFR :
          loc = DFR;
          break;

        case DFR :
          loc = DFL;
          break;

        case DFL :
          loc = UFL;
          break;

        case UBL :
          loc = UBR;
          break;

        case UBR :
          loc = DBR;
          break;

        case DBR :
          loc = DBL;
          break;

        case DBL :
          loc = UBL;
          break;

        default :
          break;
      }
      break;

    case 5 : // Z' axis
      switch (loc) {
        case UFL :
          loc = DFL;
          break;

        case DFL :
          loc = DFR;
          break;

        case DFR :
          loc = UFR;
          break;

        case UFR :
          loc = UFL;
          break;

        case UBL :
          loc = DBL;
          break;

        case DBL :
          loc = DBR;
          break;

        case DBR :
          loc = UBR;
          break;

        case UBR :
          loc = UBL;
          break;

        default :
          break;
      }
      break;
  }
}
