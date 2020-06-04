#include "bonus.h"

void Bonus::SetColor(void)
{
  switch (type)
  {
  case newBall: bottom.red = 255 / 255.0, bottom.green = 69 / 255.0, bottom.blue = 0 / 255.0; break;
  case extension: bottom.red = 255 / 255.0, bottom.green = 20 / 255.0, bottom.blue = 147 / 255.0; break;
  default: bottom.red = 0, bottom.green = 0, bottom.blue = 0; break;
  }
}

void Bonus::Draw(void)
{
  if (status != fall)
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
}

void NewBall::ApplyBonus(Object* Obj)
{
  Ball* ball = (Ball*)Obj;
  int ballNumber = ball->BallNumber();
  ball->SetBallNumber(ballNumber + 1);
  ball->SetColor();
}

void Extension::ApplyBonus(Object* Obj)
{
  Platform* platform = (Platform*)Obj;
  if (platform->length < WIN_WIDTH / 4)
    platform->length *= 1.25;
}