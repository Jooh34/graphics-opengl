#include "Node.h"

Node :: Node(std::vector<Triangle> triangles)
{
  this->triangles = triangles;
  middle.clear();
  this->left = NULL;
  this->right = NULL;
}

Triangle Node :: findBiggestTriangle() {

  float max = 0;
  int index;

  for(int i=0; i<triangles.size(); i++) {
    float a = triangles.at(i).getArea();
    if(a>max) {
      max=a;
      index = i;
    }
  }
  return triangles.at(index);
}

void Node :: split() {
  Triangle spliter = findBiggestTriangle();

  std::vector<Triangle> l;
  std::vector<Triangle> r;
  l.clear();
  r.clear();
  // split
  for(int i=0; i<triangles.size(); i++) {
    discriminate(spliter, triangles.at(i), l, r);
  }

  std::cout << r.size() << "," << middle.size() << "," << r.size() << std::endl;

  if (l.size() > 0) {
    this->left = new Node(l);
    left->split();
    std::cout << "l node ++" << std::endl;
  }
  if (r.size() > 0) {
    this->right = new Node(r);
    right->split();
    std::cout << "r node ++" << std::endl;
  }
}

void Node :: discriminate(
  Triangle spliter,
  Triangle triangle,
  std::vector<Triangle> &l,
  std::vector<Triangle> &r
)
  {
    float eps = 0.01;

    std::vector<int> sequence;
    int nNeg = 0;
    int nZero = 0;
    int nPos = 0;

    for (int i=0; i < 3; i++) {
      float t = spliter.getPlane(triangle.p[i]);
      if (t < -eps) {
        nNeg++;
        sequence.push_back(-1);
      } else if (t > eps) {
        nPos++;
        sequence.push_back(1);
      } else {
        nZero++;
        sequence.push_back(0);
      }
    }

    if(nZero == 3) {
      middle.push_back(triangle);
    }
    else if (nPos == 0) {
      l.push_back(triangle);
    }
    else if (nNeg == 0) {
      r.push_back(triangle);
    }
    else if (nZero == 1) { // splitted 2 triangles
      int zero_index;
      int pos_index;
      int neg_index;

      for(int i=0; i<3; i++) {
        if(sequence[i] == 0) {
          zero_index = i;
        }
        else if(sequence[i] < 0) {
          neg_index = i;
        }
        else {
          pos_index = i;
        }
      }

      jhm::position pos_p = triangle.p[pos_index];
      jhm::position neg_p = triangle.p[neg_index];
      jhm::position zero_p = triangle.p[zero_index];

      jhm::vector pos_v = triangle.v[pos_index];
      jhm::vector neg_v = triangle.v[neg_index];
      jhm::vector zero_v = triangle.v[zero_index];

      float d1 = triangle.getDistance(pos_p);
      float d2 = triangle.getDistance(neg_p);

      float portion = d2/(d1+d2);

      jhm::position new_p = neg_p + portion * (pos_p - neg_p);
      jhm::vector new_v = pos_v * portion + neg_v * (1-portion);

      Triangle t1(new_p, neg_p, zero_p, new_v, neg_v, zero_v, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      l.push_back(t1);
      Triangle t2(new_p, zero_p, pos_p, new_v, zero_v, pos_v, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      r.push_back(t2);
    }
    else if (nPos == 2) { // splitted square , triangle

      int pos1_index;
      int pos2_index;
      int neg_index;

      if(sequence[0] == -1) {
        neg_index = 0;
        pos1_index = 1;
        pos2_index = 2;
      }
      else if(sequence[1] == -1) {
        neg_index = 1;
        pos1_index = 0;
        pos2_index = 2;
      }
      else {
        neg_index = 2;
        pos1_index = 0;
        pos2_index = 1;
      }

      jhm::position pos1_p = triangle.p[pos1_index];
      jhm::position pos2_p = triangle.p[pos2_index];
      jhm::position neg_p = triangle.p[neg_index];

      jhm::vector pos1_v = triangle.v[pos1_index];
      jhm::vector pos2_v = triangle.v[pos2_index];
      jhm::vector neg_v = triangle.v[neg_index];

      float d1 = triangle.getDistance(pos1_p);
      float d2 = triangle.getDistance(neg_p);

      float portion = d2/(d1+d2);

      jhm::position new_p1 = neg_p + portion * (pos1_p - neg_p);
      jhm::vector new_v1 = pos1_v * portion + neg_v * (1-portion);

      float d3 = triangle.getDistance(pos2_p);
      float d4 = triangle.getDistance(neg_p);

      float portion2 = d4/(d3+d4);

      jhm::position new_p2 = neg_p + portion * (pos2_p - neg_p);
      jhm::vector new_v2 = pos2_v * portion + neg_v * (1-portion);

      Triangle t1(neg_p, new_p1, new_p2, neg_v, new_v1, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      l.push_back(t1);

      Triangle t2(pos1_p, new_p1, new_p2, pos1_v, new_v1, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      Triangle t3(pos1_p, pos2_p, new_p2, pos1_v, pos2_v, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      r.push_back(t2);
      r.push_back(t3);
    }
    else if (nNeg == 2) { // splitted square , triangle

      int neg1_index;
      int neg2_index;
      int pos_index;

      if(sequence[0] == -1) {
        pos_index = 0;
        neg1_index = 1;
        neg2_index = 2;
      }
      else if(sequence[1] == -1) {
        pos_index = 1;
        neg1_index = 0;
        neg2_index = 2;
      }
      else {
        pos_index = 2;
        neg1_index = 0;
        neg2_index = 1;
      }

      jhm::position neg1_p = triangle.p[neg1_index];
      jhm::position neg2_p = triangle.p[neg2_index];
      jhm::position pos_p = triangle.p[pos_index];

      jhm::vector neg1_v = triangle.v[neg1_index];
      jhm::vector neg2_v = triangle.v[neg2_index];
      jhm::vector pos_v = triangle.v[pos_index];

      float d1 = triangle.getDistance(neg1_p);
      float d2 = triangle.getDistance(pos_p);

      float portion = d2/(d1+d2);

      jhm::position new_p1 = pos_p + portion * (neg1_p - pos_p);
      jhm::vector new_v1 = neg1_v * portion + pos_v * (1-portion);

      float d3 = triangle.getDistance(neg2_p);
      float d4 = triangle.getDistance(pos_p);

      float portion2 = d4/(d3+d4);

      jhm::position new_p2 = pos_p + portion * (neg2_p - pos_p);
      jhm::vector new_v2 = neg2_v * portion + pos_v * (1-portion);

      Triangle t1(pos_p, new_p1, new_p2, pos_v, new_v1, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      r.push_back(t1);

      Triangle t2(neg1_p, new_p1, new_p2, neg1_v, new_v1, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      Triangle t3(neg1_p, neg2_p, new_p2, neg1_v, neg2_v, new_v2, triangle.color[0], triangle.color[1], triangle.color[2], triangle.color[3]);
      l.push_back(t2);
      l.push_back(t3);
    }
  }

void Node :: traversal(jhm::position eye)
{
  Node* back;
  Node* front;

  float t = middle.at(0).getPlane(eye);

  if(t > 0) { // positive position
    back = left;
    front = right;
  }
  else {
    back = right;
    front = left;
  }

  if(back != NULL) {
    back->traversal(eye);
  }

  for(int i=0; i<middle.size(); i++) { // draw middle triangles
    middle.at(i).draw();
  }
  if(front) {
    front->traversal(eye);
  }
}
