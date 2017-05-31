#include "Model.h"


Model :: Model(){}

Model :: Model(std::string fileName, int nPoint, int alpha)
{
  this->nPoint = nPoint;
  this->alpha = alpha;

  ifstream fileopen;
  fileopen.open(fileName.c_str());
  string line;

  getline(fileopen, line); // get curve Type
  if(line.compare("BSPLINE") == 0) {
    curveType = 0;
  } else if (line.compare("CATMULL_ROM") == 0) {
    curveType = 1;
  } else {
    // error
  }

  getline(fileopen, line); // get numCrossSection
  numCrossSection = atoi(line.c_str());

  getline(fileopen, line); // get numControlPoint
  numControlPoint = atoi(line.c_str());

  for(int i = 0; i<numCrossSection; i++) {

    vector<jhm::position> controlPointVec;
    float scale;
    float axis[3];
    float angle;
    float position[3];

    getline(fileopen, line); // \n
    for(int j = 0; j<numControlPoint; j++) { // get control points

      getline(fileopen, line);
      vector<string> v;
      istringstream iss(line);
      for(string s; iss >> s;)
      v.push_back(s);

      controlPointVec.push_back(
        jhm::position(atof(v.at(0).c_str()), atof(v.at(1).c_str()), 0)
      );
    }

    getline(fileopen, line); // get scailing factor
    scale = atof(line.c_str());

    getline(fileopen, line); // get angle/axis[3]
    istringstream iss2(line);
    int k = 0;
    for(string s; iss2 >> s;) {
      if(k == 0) {
        angle = atof(s.c_str()) * (M_PI/180);
      }
      else {
        axis[k-1] = atof(s.c_str());
      }
      k++;
    }

    getline(fileopen, line); // get position[3]
    istringstream iss3(line);
    k = 0;
    for(string s; iss3 >> s;) {
      position[k] = atof(s.c_str());
      k++;
    }
  crossSectionVec.push_back(CrossSection(controlPointVec, numControlPoint, scale, angle, axis, position));
  }
}

void Model :: setNumPoint(int nPoint)
{
  this->nPoint = nPoint;
}

void Model :: setAlpha(float alpha)
{
  this->alpha = alpha;
}

vector<jhm::position> Model :: getCrossSection(int c_i) {

  vector<jhm::position> cs;
  if(curveType == 0) {
    BSpline_2D curve(crossSectionVec.at(c_i), nPoint);
    cs = curve.getBSplineCrossSection();
  }

  else if(curveType == 1){
    CatmullRom_2D curve(nPoint, alpha);
    cs = curve.getCatmullRomCrossSection(crossSectionVec.at(c_i));
  }

  vector<jhm::position> cs_scailed = TransformManager::scailing(crossSectionVec.at(c_i).scale, cs);
  vector<jhm::position> cs_rotated = TransformManager::multQuater(
    crossSectionVec.at(c_i).angle, crossSectionVec.at(c_i).axis, cs_scailed);
  vector<jhm::position> cs_3D = TransformManager::translation(crossSectionVec.at(c_i).position, cs_rotated);

  return cs_3D;
}

vector<vector<jhm::position> > Model :: getAllCrossSection() {

  vector<vector<jhm::position> > allcs;

  for(int c_i=0; c_i<numCrossSection; c_i++) {
    vector<jhm::position> cs = getCrossSection(c_i);
    allcs.push_back(cs);
	}

  return allcs;
}

vector<jhm::position> Model :: reflectCrossSection(
	vector<jhm::position> C1,
	vector<jhm::position> C2
) {
	vector<jhm::position> C3;
	for(int i=0; i<C1.size(); i++) {
		C3.push_back(C1.at(i) + (C1.at(i)-C2.at(i)));
	}
	return C3;
}

void Model :: fillCrossSection(int c_i,
  GLfloat R, GLfloat G, GLfloat B, GLfloat alpha)
{
  vector<jhm::position> crossSection = getCrossSection(c_i);
  glBegin(GL_POLYGON);
  glColor4f(R, G, B, alpha);
  for(int j=0; j<crossSection.size(); j++) {
    glVertex3f(crossSection.at(j)[0], crossSection.at(j)[1], crossSection.at(j)[2]);
  }
  glVertex3f(crossSection.at(0)[0], crossSection.at(0)[1], crossSection.at(0)[2]);
  glEnd();
}

void Model :: drawAllCrossSection(float lineWidth,
	GLfloat R, GLfloat G, GLfloat B) {

  for(int c_i=0; c_i<numCrossSection; c_i++) {
		vector<jhm::position> cs = getCrossSection(c_i);

		// drawing crossSection
    glBegin(GL_LINE_STRIP);
  	// glColor3f(R, G, B);
  	glLineWidth(lineWidth);
		for(int j=0; j<cs.size(); j++) {
			glVertex3f(cs.at(j)[0], cs.at(j)[1], cs.at(j)[2]);
		}
		glVertex3f(cs.at(0)[0], cs.at(0)[1], cs.at(0)[2]);
		glEnd();
	}
}

void Model :: drawSurfaceBetweenCrossSection (
  vector<jhm::position> C1,
	vector<jhm::position> C2,
	vector<jhm::position> C3,
	vector<jhm::position> C4,
	GLfloat R,
	GLfloat G,
	GLfloat B,
  GLfloat alpha)
	{
		// glColor3f(R, G, B);
		for(int i=0; i<C1.size(); i++) {
			vector<jhm::position> curve1;
			vector<jhm::position> curve2;
      vector<jhm::position> curve3;
      vector<jhm::position> curve4;

      CatmullRom_2D C_curve(nPoint, alpha);
			C_curve.catmullRomSpline(C1.at(i), C2.at(i), C3.at(i), C4.at(i), curve1);
			C_curve.catmullRomSpline(C1.at((i+1)%C1.size()),
			C2.at((i+1)%C1.size()),
			C3.at((i+1)%C1.size()),
			C4.at((i+1)%C1.size()),
			curve2
			);
      C_curve.catmullRomSpline(C1.at((i+2)%C1.size()),
			C2.at((i+2)%C1.size()),
			C3.at((i+2)%C1.size()),
			C4.at((i+2)%C1.size()),
			curve3
			);
      C_curve.catmullRomSpline(C1.at((i+3)%C1.size()),
			C2.at((i+3)%C1.size()),
			C3.at((i+3)%C1.size()),
			C4.at((i+3)%C1.size()),
			curve4
			);

			curve1.push_back(C3.at(i));
			curve2.push_back(C3.at((i+1)%C1.size()));
      curve3.push_back(C3.at((i+2)%C1.size()));
      curve4.push_back(C3.at((i+3)%C1.size()));

			glBegin(GL_TRIANGLE_STRIP);
      glColor4f(R, G, B, alpha);
			for(int j=0; j<curve1.size(); j++) {

        jhm::vector normal_2;
        jhm::vector normal_3;

        if(j==0) { // first and last
          jhm::vector NV_sur3 = -(curve2.at(j+1)-curve2.at(j)) * (curve3.at(j)-curve2.at(j)); // 4's quadrant
          jhm::vector NV_sur4 = -(curve1.at(j)-curve2.at(j)) * (curve2.at(j+1)-curve2.at(j)); // 3's quadrant

          normal_2 = (NV_sur3 + NV_sur4 + NV_sur3*NV_sur4).normalize();

          jhm::vector NV2_sur3 = -(curve3.at(j+1)-curve3.at(j)) * (curve4.at(j)-curve3.at(j)); // 4's quadrant
          jhm::vector NV2_sur4 = -(curve2.at(j)-curve3.at(j)) * (curve3.at(j+1)-curve3.at(j)); // 3's quadrant

          normal_3 = (NV2_sur3 + NV2_sur4 + NV2_sur3*NV2_sur4).normalize();

        }

        else if (j == curve1.size()-1) {
          jhm::vector NV_sur1 = -(curve2.at(j-1)-curve2.at(j)) * (curve1.at(j)-curve2.at(j)); // 2's quadrant
          jhm::vector NV_sur2 = -(curve3.at(j)-curve2.at(j)) * (curve2.at(j-1)-curve2.at(j)); // 1's quadrant

          normal_2 = (NV_sur1 + NV_sur2 + NV_sur1*NV_sur2).normalize();

          jhm::vector NV2_sur1 = -(curve3.at(j-1)-curve3.at(j)) * (curve2.at(j)-curve3.at(j)); // 2's quadrant
          jhm::vector NV2_sur2 = -(curve4.at(j)-curve3.at(j)) * (curve3.at(j-1)-curve3.at(j)); // 1's quadrant

          normal_3 = (NV2_sur1 + NV2_sur2 + -NV2_sur1*NV2_sur2).normalize();

        }
        else {
          jhm::vector NV_sur1 = -(curve2.at(j-1)-curve2.at(j)) * (curve1.at(j)-curve2.at(j)); // 2's quadrant
          jhm::vector NV_sur2 = -(curve3.at(j)-curve2.at(j)) * (curve2.at(j-1)-curve2.at(j)); // 1's quadrant
          jhm::vector NV_sur3 = -(curve2.at(j+1)-curve2.at(j)) * (curve3.at(j)-curve2.at(j)); // 4's quadrant
          jhm::vector NV_sur4 = -(curve1.at(j)-curve2.at(j)) * (curve2.at(j+1)-curve2.at(j)); // 3's quadrant

          normal_2 = (NV_sur1 + NV_sur2 + NV_sur3 + NV_sur4).normalize();

          jhm::vector NV2_sur1 = -(curve3.at(j-1)-curve3.at(j)) * (curve2.at(j)-curve3.at(j)); // 2's quadrant
          jhm::vector NV2_sur2 = -(curve4.at(j)-curve3.at(j)) * (curve3.at(j-1)-curve3.at(j)); // 1's quadrant
          jhm::vector NV2_sur3 = -(curve3.at(j+1)-curve3.at(j)) * (curve4.at(j)-curve3.at(j)); // 4's quadrant
          jhm::vector NV2_sur4 = -(curve2.at(j)-curve3.at(j)) * (curve3.at(j+1)-curve3.at(j)); // 3's quadrant

          normal_3 = (NV2_sur1 + NV2_sur2 + NV2_sur3 + NV2_sur4).normalize();
        }

        glNormal3f(normal_2[0], normal_2[1], normal_2[2]);
				glVertex3f(curve2.at(j)[0], curve2.at(j)[1], curve2.at(j)[2]);
        glNormal3f(normal_3[0], normal_3[1], normal_3[2]);
				glVertex3f(curve3.at(j)[0], curve3.at(j)[1], curve3.at(j)[2]);
			}
			glEnd();
		}
	}

void Model :: drawSurface(
  GLfloat R,
  GLfloat G,
  GLfloat B,
  GLfloat alpha)
{
  vector<vector<jhm::position> > allCrossSection = getAllCrossSection();

  for(int a_i=0; a_i<allCrossSection.size()-3; a_i++) {
		drawSurfaceBetweenCrossSection(allCrossSection.at(a_i),
		allCrossSection.at(a_i+1),
		allCrossSection.at(a_i+2),
		allCrossSection.at(a_i+3),
		R, G, B, alpha);
	}

	drawSurfaceBetweenCrossSection(
		reflectCrossSection(allCrossSection.at(0),allCrossSection.at(1)),
	allCrossSection.at(0),
	allCrossSection.at(1),
	allCrossSection.at(2),
	R, G, B, alpha);

	drawSurfaceBetweenCrossSection(allCrossSection.at(allCrossSection.size()-3),
	allCrossSection.at(allCrossSection.size()-2),
	allCrossSection.at(allCrossSection.size()-1),
	reflectCrossSection(allCrossSection.at(allCrossSection.size()-1),allCrossSection.at(allCrossSection.size()-2)),
	R, G, B, alpha);
}

void Model :: drawSurface_stripe(
	GLfloat R1, GLfloat G1, GLfloat B1, GLfloat alpha1,
	GLfloat R2, GLfloat G2, GLfloat B2, GLfloat alpha2
)
{
  vector<vector<jhm::position> > allCrossSection = getAllCrossSection();

	for(int a_i=0; a_i<allCrossSection.size()-3; a_i++) {
		if(a_i%2 == 0) {
			drawSurfaceBetweenCrossSection(allCrossSection.at(a_i),
			allCrossSection.at(a_i+1),
			allCrossSection.at(a_i+2),
			allCrossSection.at(a_i+3),
			R1, G1, B1, alpha1);
		}
		else {
			drawSurfaceBetweenCrossSection(allCrossSection.at(a_i),
			allCrossSection.at(a_i+1),
			allCrossSection.at(a_i+2),
			allCrossSection.at(a_i+3),
			R2, G2, B2, alpha2);
		}
	}

	drawSurfaceBetweenCrossSection(
		reflectCrossSection(allCrossSection.at(0),allCrossSection.at(1)),
	allCrossSection.at(0),
	allCrossSection.at(1),
	allCrossSection.at(2),
	R2, G2, B2, alpha2);

	drawSurfaceBetweenCrossSection(allCrossSection.at(allCrossSection.size()-3),
	allCrossSection.at(allCrossSection.size()-2),
	allCrossSection.at(allCrossSection.size()-1),
	reflectCrossSection(allCrossSection.at(allCrossSection.size()-1),allCrossSection.at(allCrossSection.size()-2)),
	R2, G2, B2, alpha2);
}

void Model :: stack_Surface(
  GLfloat R,
  GLfloat G,
  GLfloat B,
  GLfloat alpha)
{
  vector<vector<jhm::position> > allCrossSection = getAllCrossSection();

  for(int a_i=0; a_i<allCrossSection.size()-3; a_i++) {
		stack_SurfaceBetweenCrossSection(allCrossSection.at(a_i),
		allCrossSection.at(a_i+1),
		allCrossSection.at(a_i+2),
		allCrossSection.at(a_i+3),
		R, G, B, alpha);
	}

	stack_SurfaceBetweenCrossSection(
		reflectCrossSection(allCrossSection.at(0),allCrossSection.at(1)),
	allCrossSection.at(0),
	allCrossSection.at(1),
	allCrossSection.at(2),
	R, G, B, alpha);

	stack_SurfaceBetweenCrossSection(allCrossSection.at(allCrossSection.size()-3),
	allCrossSection.at(allCrossSection.size()-2),
	allCrossSection.at(allCrossSection.size()-1),
	reflectCrossSection(allCrossSection.at(allCrossSection.size()-1),allCrossSection.at(allCrossSection.size()-2)),
	R, G, B, alpha);
}

void Model :: stack_Surface_stripe(
	GLfloat R1, GLfloat G1, GLfloat B1, GLfloat alpha1,
	GLfloat R2, GLfloat G2, GLfloat B2, GLfloat alpha2
)
{
  vector<vector<jhm::position> > allCrossSection = getAllCrossSection();

	for(int a_i=0; a_i<allCrossSection.size()-3; a_i++) {
		if(a_i%2 == 0) {
			stack_SurfaceBetweenCrossSection(allCrossSection.at(a_i),
			allCrossSection.at(a_i+1),
			allCrossSection.at(a_i+2),
			allCrossSection.at(a_i+3),
			R1, G1, B1, alpha1);
		}
		else {
			stack_SurfaceBetweenCrossSection(allCrossSection.at(a_i),
			allCrossSection.at(a_i+1),
			allCrossSection.at(a_i+2),
			allCrossSection.at(a_i+3),
			R2, G2, B2, alpha2);
		}
	}

	stack_SurfaceBetweenCrossSection(
		reflectCrossSection(allCrossSection.at(0),allCrossSection.at(1)),
	allCrossSection.at(0),
	allCrossSection.at(1),
	allCrossSection.at(2),
	R2, G2, B2, alpha2);

	stack_SurfaceBetweenCrossSection(allCrossSection.at(allCrossSection.size()-3),
	allCrossSection.at(allCrossSection.size()-2),
	allCrossSection.at(allCrossSection.size()-1),
	reflectCrossSection(allCrossSection.at(allCrossSection.size()-1),allCrossSection.at(allCrossSection.size()-2)),
	R2, G2, B2, alpha2);

  stack_Lids(allCrossSection.at(0), allCrossSection.at(allCrossSection.size()-1));
}

void Model :: stack_SurfaceBetweenCrossSection (
  vector<jhm::position> C1,
	vector<jhm::position> C2,
	vector<jhm::position> C3,
	vector<jhm::position> C4,
	GLfloat R,
	GLfloat G,
	GLfloat B,
  GLfloat alpha)
	{
		// glColor3f(R, G, B);
		for(int i=0; i<C1.size(); i++) {
			vector<jhm::position> curve1;
			vector<jhm::position> curve2;
      vector<jhm::position> curve3;
      vector<jhm::position> curve4;

      CatmullRom_2D C_curve(nPoint, alpha);
			C_curve.catmullRomSpline(C1.at(i), C2.at(i), C3.at(i), C4.at(i), curve1);
			C_curve.catmullRomSpline(C1.at((i+1)%C1.size()),
			C2.at((i+1)%C1.size()),
			C3.at((i+1)%C1.size()),
			C4.at((i+1)%C1.size()),
			curve2
			);
      C_curve.catmullRomSpline(C1.at((i+2)%C1.size()),
			C2.at((i+2)%C1.size()),
			C3.at((i+2)%C1.size()),
			C4.at((i+2)%C1.size()),
			curve3
			);
      C_curve.catmullRomSpline(C1.at((i+3)%C1.size()),
			C2.at((i+3)%C1.size()),
			C3.at((i+3)%C1.size()),
			C4.at((i+3)%C1.size()),
			curve4
			);

			curve1.push_back(C3.at(i));
			curve2.push_back(C3.at((i+1)%C1.size()));
      curve3.push_back(C3.at((i+2)%C1.size()));
      curve4.push_back(C3.at((i+3)%C1.size()));

      jhm::position prev_prev_p;
      jhm::position prev_p;
      jhm::position p;

      jhm::vector prev_prev_v;
      jhm::vector prev_v;

			for(int j=0; j<curve1.size(); j++) {

        jhm::vector normal_2;
        jhm::vector normal_3;

        if(j==0) { // first and last
          jhm::vector NV_sur3 = -(curve2.at(j+1)-curve2.at(j)) * (curve3.at(j)-curve2.at(j)); // 4's quadrant
          jhm::vector NV_sur4 = -(curve1.at(j)-curve2.at(j)) * (curve2.at(j+1)-curve2.at(j)); // 3's quadrant

          normal_2 = (NV_sur3 + NV_sur4).normalize();

          jhm::vector NV2_sur3 = -(curve3.at(j+1)-curve3.at(j)) * (curve4.at(j)-curve3.at(j)); // 4's quadrant
          jhm::vector NV2_sur4 = -(curve2.at(j)-curve3.at(j)) * (curve3.at(j+1)-curve3.at(j)); // 3's quadrant

          normal_3 = (NV2_sur3 + NV2_sur4).normalize();

        }

        else if (j == curve1.size()-1) {
          jhm::vector NV_sur1 = -(curve2.at(j-1)-curve2.at(j)) * (curve1.at(j)-curve2.at(j)); // 2's quadrant
          jhm::vector NV_sur2 = -(curve3.at(j)-curve2.at(j)) * (curve2.at(j-1)-curve2.at(j)); // 1's quadrant

          normal_2 = (NV_sur1 + NV_sur2).normalize();

          jhm::vector NV2_sur1 = -(curve3.at(j-1)-curve3.at(j)) * (curve2.at(j)-curve3.at(j)); // 2's quadrant
          jhm::vector NV2_sur2 = -(curve4.at(j)-curve3.at(j)) * (curve3.at(j-1)-curve3.at(j)); // 1's quadrant

          normal_3 = (NV2_sur1 + NV2_sur2).normalize();

        }
        else {
          jhm::vector NV_sur1 = -(curve2.at(j-1)-curve2.at(j)) * (curve1.at(j)-curve2.at(j)); // 2's quadrant
          jhm::vector NV_sur2 = -(curve3.at(j)-curve2.at(j)) * (curve2.at(j-1)-curve2.at(j)); // 1's quadrant
          jhm::vector NV_sur3 = -(curve2.at(j+1)-curve2.at(j)) * (curve3.at(j)-curve2.at(j)); // 4's quadrant
          jhm::vector NV_sur4 = -(curve1.at(j)-curve2.at(j)) * (curve2.at(j+1)-curve2.at(j)); // 3's quadrant

          normal_2 = (NV_sur1 + NV_sur2 + NV_sur3 + NV_sur4).normalize();

          jhm::vector NV2_sur1 = -(curve3.at(j-1)-curve3.at(j)) * (curve2.at(j)-curve3.at(j)); // 2's quadrant
          jhm::vector NV2_sur2 = -(curve4.at(j)-curve3.at(j)) * (curve3.at(j-1)-curve3.at(j)); // 1's quadrant
          jhm::vector NV2_sur3 = -(curve3.at(j+1)-curve3.at(j)) * (curve4.at(j)-curve3.at(j)); // 4's quadrant
          jhm::vector NV2_sur4 = -(curve2.at(j)-curve3.at(j)) * (curve3.at(j+1)-curve3.at(j)); // 3's quadrant

          normal_3 = (NV2_sur1 + NV2_sur2 + NV2_sur3 + NV2_sur4).normalize();
        }

        if(j==0) {
          prev_p = curve2.at(j);
          p = curve3.at(j);
          prev_prev_v = normal_2;
          prev_v = normal_3;

        }
        else {
          prev_prev_p = prev_p;
          prev_p = p;
          p = curve2.at(j);
          Triangle t1(prev_prev_p, prev_p, p, prev_prev_v, prev_v, normal_2, R, G, B, alpha);

          // make stl
          std::cout << std::scientific;
          std::cout << "facet normal " << normal_2[0] <<" "<< normal_2[1] <<" "<< normal_2[2] << std::endl;
          std::cout << "  outer loop" << std::endl;
          std::cout << "    vertex " << prev_prev_p[0] <<" "<< prev_prev_p[1] <<" "<< prev_prev_p[2] << std::endl;
          std::cout << "    vertex " << prev_p[0] <<" "<< prev_p[1] <<" "<< prev_p[2] << std::endl;
          std::cout << "    vertex " << p[0] <<" "<< p[1] <<" "<< p[2] << std::endl;
          std::cout << "  endloop" << std::endl;
          std::cout << "endfacet" << std::endl;
          ///////////

          prev_prev_p = prev_p;
          prev_p = p;
          p = curve3.at(j);
          Triangle t2(prev_prev_p, prev_p, p, prev_v, normal_2, normal_3, R, G, B, alpha);

          // make stl
          std::cout << std::scientific;
          std::cout << "facet normal " << normal_3[0] <<" "<< normal_3[1] <<" "<< normal_3[2] << std::endl;
          std::cout << "  outer loop" << std::endl;
          std::cout << "    vertex " << prev_prev_p[0] <<" "<< prev_prev_p[1] <<" "<< prev_prev_p[2] << std::endl;
          std::cout << "    vertex " << prev_p[0] <<" "<< prev_p[1] <<" "<< prev_p[2] << std::endl;
          std::cout << "    vertex " << p[0] <<" "<< p[1] <<" "<< p[2] << std::endl;
          std::cout << "  endloop" << std::endl;
          std::cout << "endfacet" << std::endl;
          ///////////

          prev_prev_v = normal_2;
          prev_v = normal_3;

          tree.add(t1);
          tree.add(t2);
          // push triangle
        }
			}
			glEnd();
		}
	}

void Model :: stack_Lids(vector<jhm::position> cs1, vector<jhm::position> cs2)
{
  jhm::position prev_p;
  jhm::position p;
  for(int i=0; i<cs1.size()+1; i++) {
    if(i==0) prev_p = cs1.at(0);
    else {
      p = cs1.at(i%cs1.size());
      // make stl
      std::cout << std::scientific;
      std::cout << "facet normal " << "-1" <<" "<< "0" <<" "<< "0" << std::endl;
      std::cout << "  outer loop" << std::endl;
      std::cout << "    vertex " << "-50" <<" "<< "-25" <<" "<< "0" << std::endl;
      std::cout << "    vertex " << prev_p[0] <<" "<< prev_p[1] <<" "<< prev_p[2] << std::endl;
      std::cout << "    vertex " << p[0] <<" "<< p[1] <<" "<< p[2] << std::endl;
      std::cout << "  endloop" << std::endl;
      std::cout << "endfacet" << std::endl;
      ///////////
      prev_p = p;
    }
  }

  for(int i=0; i<cs2.size()+1; i++) {
    if(i==0) prev_p = cs2.at(0);
    else {
      p = cs2.at(i%cs2.size());
      // make stl
      std::cout << std::scientific;
      std::cout << "facet normal " << "1" <<" "<< "0" <<" "<< "0" << std::endl;
      std::cout << "  outer loop" << std::endl;
      std::cout << "    vertex " << "60" <<" "<< "-25" <<" "<< "0" << std::endl;
      std::cout << "    vertex " << prev_p[0] <<" "<< prev_p[1] <<" "<< prev_p[2] << std::endl;
      std::cout << "    vertex " << p[0] <<" "<< p[1] <<" "<< p[2] << std::endl;
      std::cout << "  endloop" << std::endl;
      std::cout << "endfacet" << std::endl;
      ///////////
      prev_p = p;
    }
  }
}

void Model :: draw_BSPdepthOrder(jhm::position eye)
{
  tree.traversal(eye);
}
