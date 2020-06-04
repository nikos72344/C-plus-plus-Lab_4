#include "brick.h"

void Brick::SetColor(void)
{
  switch (durability)
  {
  case 1: bottom.red = 139 / 255.0, bottom.green = 0 / 255.0, bottom.blue = 139 / 255.0; break;
  case 2: bottom.red = 255 / 255.0, bottom.green = 255 / 255.0, bottom.blue = 0 / 255.0; break;
  default: bottom.red = 220 / 255.0, bottom.green = 20 / 255.0, bottom.blue = 60 / 255.0; break;
  }
}

void Brick::Draw(void)
{
  if (durability == 0)
    return;
  vector<point> dots = { { -length / 2, -width / 2 } , { length / 2, -width / 2 } , { length / 2, width / 2 },{ -length / 2, width / 2 } };
  vector<point> xy = Calculations(dots);
  SetColor();
  glBegin(GL_POLYGON);
  glColor3d(up.red, up.green, up.blue);
  for (unsigned int i = 0; i < xy.size() / 2; i++)
    glVertex3d(xy[i].x, xy[i].y, 0);
  glColor3d(bottom.red, bottom.green, bottom.blue);
  for (unsigned int i = xy.size() / 2; i < xy.size(); i++)
    glVertex3d(xy[i].x, xy[i].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (unsigned int i = 0; i < xy.size(); i++)
    glVertex3d(xy[i].x, xy[i].y, 0);
  glEnd();
}