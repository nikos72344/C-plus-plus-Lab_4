#include "title.h"

Title::Title(const string& Content, const  GlutRGB& Color) : location({ 0, 0 }), color(Color), content(Content)
{
  length = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)content.data());
  int n = 1;
  if (content.size() < 2)
    n = content.size();
  width = glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, content[n]);
}

void Title::Draw(void)
{
  glBegin(GL_BITMAP);
  glColor3d(color.red, color.green, color.blue);
  glRasterPos3d(location.x, location.y, 1);
  for (auto c : content)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  glEnd();
}