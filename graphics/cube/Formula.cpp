#include "Formula.h"

const int Formula::cubeincube[18] = {F, L, F, Ui, R, U, F, F, L, L, Ui, Li, B, Di, Bi, L, L, U};
const int Formula::cubeincubeincube[20] = {Ui, Li, Ui, Fi, R, R, Bi, R, F, U, B, B, U, Bi, L, Ui, F, U, R, Fi};
const int Formula::exchangedpeak[19] = {F, U, U, L, F, Li, B, L, U, Bi, Ri, Li, U, Ri, Di, Fi, B, R, R};
const int Formula::spiralpattern[18] = {Li, Bi, D, U, R, Ui, Ri, D, D, R, R, D, L, Di, Li, Ri, F, U};
const int Formula::cross[20] = {R, R, Li, D, F, F, Ri, Di, Ri, L, Ui, D, R, D, B, B, Ri, U, D, D};

const int* Formula::showManual(int &size) {
  int n;
  cout << "-----------------------" << endl;
  cout << "[1] cube in cube" << endl;
  cout << "[2] cube in cube in cube" << endl;
  cout << "[3] exchanged peek" << endl;
  cout << "[4] spiralpattern" << endl;
  cout << "[5] cross" << endl;
  cout << "-----------------------" << endl;
  cout << "Enter :";
  cin >> n;

  switch (n) {
    case 1 :
      size = sizeof(cubeincube)/sizeof(*cubeincube);
      return cubeincube;
      break;

    case 2 :
      size = sizeof(cubeincubeincube)/sizeof(*cubeincubeincube);
      return cubeincubeincube;
      break;

    case 3 :
      size = sizeof(exchangedpeak)/sizeof(*exchangedpeak);
      return exchangedpeak;
      break;

    case 4 :
      size = sizeof(spiralpattern)/sizeof(*spiralpattern);
      return spiralpattern;
      break;

    case 5 :
      size = sizeof(cross)/sizeof(*cross);
      return cross;
      break;

    default :
      break;
  }
}
