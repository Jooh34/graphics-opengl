#include "RotationManager.h"

RotationManager :: RotationManager(std::vector<EdgePiece>& ep_list, std::vector<CornerPiece>& cp_list, std::vector<CenterPiece>& tp_list)
: EP_list(ep_list), CP_list(cp_list), TP_list(tp_list){

  rotating = false;
  timer = 0;

}

void RotationManager :: setRotate(int dir) {
  this->dir = dir;
  rotating = true;
  timer = 9;
  if(!solving) {
    if(!history.empty() && history.top() == reverse(dir)) {
      history.pop();
    }
    else {
      history.push(dir);
    }
  }
}

void RotationManager :: rotate() {
  switch(dir) {
    case U_ :
      rotate_U();
      break;

    case U_i :
      rotate_Ui();
      break;

    case D_ :
      rotate_D();
      break;

    case D_i :
      rotate_Di();
      break;

    case R_ :
      rotate_R();
      break;

    case R_i :
      rotate_Ri();
      break;

    case L_ :
      rotate_L();
      break;

    case L_i :
      rotate_Li();
      break;

    case F_ :
      rotate_F();
      break;

    case F_i :
      rotate_Fi();
      break;

    case B_ :
      rotate_B();
      break;

    case B_i :
      rotate_Bi();
      break;
  }
}

void RotationManager :: rotate_U() {
  int arr[] = {UF, UR, UB, UL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Y();
		}
	}

  int arr2[] = {UFL, UFR, UBR, UBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Y();
		}
	}

  TP_list.at(0).rotate_Y();
}

void RotationManager :: rotate_Ui() {
  int arr[] = {UF, UR, UB, UL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Yi();
		}
	}

  int arr2[] = {UFL, UFR, UBR, UBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Yi();
		}
	}

  TP_list.at(0).rotate_Yi();
}

void RotationManager :: rotate_D() {
  int arr[] = {DF, DR, DB, DL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Yi();
		}
	}

  int arr2[] = {DFL, DFR, DBR, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Yi();
		}
	}

  TP_list.at(5).rotate_Yi();
}

void RotationManager :: rotate_Di() {
  int arr[] = {DF, DR, DB, DL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Y();
		}
	}

  int arr2[] = {DFL, DFR, DBR, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Y();
		}
	}

  TP_list.at(5).rotate_Y();
}

void RotationManager :: rotate_R() {
  int arr[] = {UR, FR, BR, DR};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_X();
		}
	}

  int arr2[] = {UFR, UBR, DFR, DBR};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_X();
		}
	}

  TP_list.at(2).rotate_X();
}

void RotationManager :: rotate_Ri() {
  int arr[] = {UR, FR, BR, DR};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Xi();
		}
	}

  int arr2[] = {UFR, UBR, DFR, DBR};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Xi();
		}
	}

  TP_list.at(2).rotate_Xi();
}

void RotationManager :: rotate_L() {
  int arr[] = {UL, FL, BL, DL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Xi();
		}
	}

  int arr2[] = {UFL, UBL, DFL, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Xi();
		}
	}

  TP_list.at(3).rotate_Xi();
}

void RotationManager :: rotate_Li() {
  int arr[] = {UL, FL, BL, DL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_X();
		}
	}

  int arr2[] = {UFL, UBL, DFL, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_X();
		}
	}

  TP_list.at(3).rotate_X();
}

void RotationManager :: rotate_F() {
  int arr[] = {UF, FR, DF, FL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Z();
		}
	}

  int arr2[] = {UFL, UFR, DFR, DFL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Z();
		}
	}

  TP_list.at(1).rotate_Z();
}

void RotationManager :: rotate_Fi() {
  int arr[] = {UF, FR, DF, FL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Zi();
		}
	}

  int arr2[] = {UFL, UFR, DFR, DFL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Zi();
		}
	}

  TP_list.at(1).rotate_Zi();
}

void RotationManager :: rotate_B() {
  int arr[] = {UB, BR, DB, BL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Zi();
		}
	}

  int arr2[] = {UBL, UBR, DBR, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Zi();
		}
	}

  TP_list.at(4).rotate_Zi();
}

void RotationManager :: rotate_Bi() {
  int arr[] = {UB, BR, DB, BL};

	for(int i=0; i<EP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(EP_list.at(i).loc == arr[j]) {
				find = 1;
			}
		}

		if(find) {
			EP_list.at(i).rotate_Z();
		}
	}

  int arr2[] = {UBL, UBR, DBR, DBL};

	for(int i=0; i<CP_list.size(); i++) {
		bool find = 0;
		for(int j=0; j<4; j++) {
			if(CP_list.at(i).loc == arr2[j]) {
				find = 1;
			}
		}

		if(find) {
			CP_list.at(i).rotate_Z();
		}
	}

  TP_list.at(4).rotate_Z();
}

int* RotationManager :: getSolvingFormula(int &size) {
  size = history.size();
  int *arr = new int[size];
  for (int i = 0; i < size; i++) {
    arr[i] = reverse(history.top());
    history.pop();
  }
  solving = true;
  return arr;
}

int RotationManager :: reverse(int dir) {
  if(dir % 2 == 0)
    return dir+1;
  else
    return dir-1;
}
