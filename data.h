#ifndef __DATA_H
#define __DATA_H

#include <GL/glut.h>

using namespace std;

const double PI = 3.1415926535897932384626433832795;

const int WIN_LENGTH = 400, WIN_WIDTH = 16 * WIN_LENGTH / 9;

const int ROW_SIZE = 3;

struct point
{
  double x, y;
};

class GlutRGB
{
public:
  GLdouble red, green, blue;
  GlutRGB(GLdouble r = 0, GLdouble g = 0, GLdouble b = 0) : red(r / 255.0), green(g / 255.0), blue(b / 255.0) {}
};

#endif