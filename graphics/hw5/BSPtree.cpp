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

void BSPtree :: findFirstIntersection(jhm::position ori, jhm::vector vec, Triangle* &triangle, jhm::position* &intersection) {
  // root->findFirstIntersection(ori, vec, triangle, intersection);
}
