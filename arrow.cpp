#include "arrow.h"

void Arrow::Draw(void)
{
  vector<point> dots = { { 0, width / 2 } , { length, width / 2 } , { length, width }, { 3 * length / 2, 0 }, { length, -width }, { length, -width / 2 }, { 0, -width / 2 } };
  vector<point> xy = Calculations(dots);
  glBegin(GL_LINE_STRIP);
  glColor3d(up.red, up.green, up.blue);
  for (auto& i : xy)
    glVertex3d(i.x, i.y, 0);
  glEnd();
}