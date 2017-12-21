#include "EdgePiece.h"

EdgePiece :: EdgePiece(int loc, int c1, int c2, float size) : Piece(size)
{
  this->loc = loc;
  this->c1 = c1;
  this->c2 = c2;
  float piece_ratio = 9./10;
  float piece_size = piece_ratio * (size/2);

  switch (loc)
  {
    case UF :
      getVertexList(0, size, size, piece_size);
      break;

    case UR :
      getVertexList(size, size, 0, piece_size);
      rotateVertexList_Ui();
      break;

    case UB :
      getVertexList(0, size, -size, piece_size);
      rotateVertexList_Ui();
      rotateVertexList_Ui();
      break;

    case UL :
      getVertexList(-size, size, 0, piece_size);
      rotateVertexList_U();
      break;

    case FR :
      getVertexList(size, 0, size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_Ui();
      break;

    case BR :
      getVertexList(size, 0, -size, piece_size);
      rotateVertexList_R();
      rotateVertexList_Ui();
      break;

    case BL :
      getVertexList(-size, 0, -size, piece_size);
      rotateVertexList_R();
      rotateVertexList_U();
      break;

    case FL :
      getVertexList(-size, 0, size, piece_size);
      rotateVertexList_Ri();
      rotateVertexList_U();
      break;

    case DF :
      getVertexList(0, -size, size, piece_size);
      rotateVertexList_Ri();
      break;

    case DR :
      getVertexList(size, -size, 0, piece_size);
      rotateVertexList_Ui();
      rotateVertexList_Ri();
      break;

    case DB :
      getVertexList(0, -size, -size, piece_size);
      rotateVertexList_Ui();
      rotateVertexList_Ui();
      rotateVertexList_Ri();
      break;

    case DL :
      getVertexList(-size, -size, 0, piece_size);
      rotateVertexList_U();
      rotateVertexList_Ri();
      break;

    default :
      break;
  }
}

void EdgePiece::draw() {

  Piece::draw();

  //Top
  setColor(c1);
  int idx[4] = {0,1,2,3};
  for(int i=0; i<4; i++) {
    glVertex3f(vtx_list.at(idx[i])[0], vtx_list.at(idx[i])[1], vtx_list.at(idx[i])[2]);
  }

  //Front
  setColor(c2);
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

void EdgePiece::locRefresh(int index) {
  switch (index) {
    case 0 : // X axis
      switch (loc) {
        case FR :
          loc = UR;
          break;

        case UR :
          loc = BR;
          break;

        case BR :
          loc = DR;
          break;

        case DR :
          loc = FR;
          break;

        case FL :
          loc = UL;
          break;

        case UL :
          loc = BL;
          break;

        case BL :
          loc = DL;
          break;

        case DL :
          loc = FL;
          break;
      }
      break;

    case 1 : // X'axis
      switch (loc) {
        case FR :
          loc = DR;
          break;

        case DR :
          loc = BR;
          break;

        case BR :
          loc = UR;
          break;

        case UR :
          loc = FR;
          break;

        case FL :
          loc = DL;
          break;

        case DL :
          loc = BL;
          break;

        case BL :
          loc = UL;
          break;

        case UL :
          loc = FL;
          break;
      }
      break;

    case 2 : // Y axis
      switch (loc) {
        case UF :
          loc = UL;
          break;

        case UR :
          loc = UF;
          break;

        case UB :
          loc = UR;
          break;

        case UL :
          loc = UB;
          break;

        case DF :
          loc = DL;
          break;

        case DR :
          loc = DF;
          break;

        case DB :
          loc = DR;
          break;

        case DL :
          loc = DB;
          break;

        default :
          break;
      }
      break;

    case 3 : // Y' axis
      switch (loc) {
        case UF :
          loc = UR;
          break;

        case UR :
          loc = UB;
          break;

        case UB :
          loc = UL;
          break;

        case UL :
          loc = UF;
          break;

        case DF :
          loc = DR;
          break;

        case DR :
          loc = DB;
          break;

        case DB :
          loc = DL;
          break;

        case DL :
          loc = DF;
          break;

        default :
          break;
      }
      break;

    case 4 : // Z axis
      switch (loc) {
        case UF :
          loc = FR;
          break;

        case FR :
          loc = DF;
          break;

        case DF :
          loc = FL;
          break;

        case FL :
          loc = UF;
          break;

        case UB :
          loc = BR;
          break;

        case BR :
          loc = DB;
          break;

        case DB :
          loc = BL;
          break;

        case BL :
          loc = UB;
          break;

        default :
          break;
      }
      break;

    case 5 : // Z' axis
      switch (loc) {
        case UF :
          loc = FL;
          break;

        case FL :
          loc = DF;
          break;

        case DF :
          loc = FR;
          break;

        case FR :
          loc = UF;
          break;

        case UB :
          loc = BL;
          break;

        case BL :
          loc = DB;
          break;

        case DB :
          loc = BR;
          break;

        case BR :
          loc = UB;
          break;

        default :
          break;
      }
      break;
  }
}
