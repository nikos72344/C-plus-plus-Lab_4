#include "platform.h"

void Platform::Draw(void)
{
  vector<point> dots = { { -length / 2, -width / 2 } , { length / 2, -width / 2 } , { length / 2, width / 2 } , { -length / 2, width / 2 } };
  vector<point> xy = Calculations(dots);
  glBegin(GL_POLYGON);
  glColor3d(up.red, up.green, up.blue);
  for (unsigned int i = 0; i < xy.size() / 2; i++)
    glVertex3d(xy[i].x, xy[i].y, 0);
  glColor3d(bottom.red, bottom.green, bottom.blue);
  for (unsigned int i = xy.size() / 2; i < xy.size(); i++)
    glVertex3d(xy[i].x, xy[i].y, 0);
  glEnd();
}