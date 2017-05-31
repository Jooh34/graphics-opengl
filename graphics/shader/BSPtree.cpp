#include "BSPtree.h"

BSPtree :: BSPtree(){}

void BSPtree :: add(Triangle t) {
  triangles.push_back(t);
}

void BSPtree :: buildBSPtree() {
  std::cout << "building BSP tree ..." << std::endl;

  root = new Node(triangles);
  root->split();

  std::cout << "build DONE" << std::endl;
}

void BSPtree :: traversal(jhm::position eye) {
  root->traversal(eye);
}
