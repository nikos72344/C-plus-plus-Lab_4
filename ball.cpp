#include "ball.h"

void Ball::SetColor(void)
{
  switch (ballNumber)
  {
  case 1: up.red = 128 / 255.0, up.green = 0 / 255.0, up.blue = 0 / 255.0;
    bottom.red = 255 / 255.0, bottom.green = 222 / 255.0, bottom.blue = 173 / 255.0;
    break;
  case 2: up.red = 255 / 255.0, up.green = 215 / 255.0, up.blue = 0 / 255.0;
    bottom.red = 255 / 255.0, bottom.green = 127 / 255.0, bottom.blue = 80 / 255.0;
    break;
  case 3: up.red = 240 / 255.0, up.green = 230 / 255.0, up.blue = 140 / 255.0;
    bottom.red = 107 / 255.0, bottom.green = 142 / 255.0, bottom.blue = 35 / 255.0;
    break;
  default: srand(time(0));
    up.red = rand() % 255 / 255.0, up.green = rand() % 255 / 255.0, up.blue = rand() % 255 / 255.0;
    bottom.red = rand() % 255 / 255.0, bottom.green = rand() % 255 / 255.0, bottom.blue = rand() % 255 / 255.0;
    break;
  }
}

void Ball::Draw(void)
{
  glBegin(GL_POLYGON);
  for (int i = 0; i < dotNumber; i++)
  {
    glColor3d((up.red * i + bottom.red * (dotNumber - i)) / dotNumber, (up.green * i + bottom.green * (dotNumber - i)) / dotNumber, (up.blue * i + bottom.blue * (dotNumber - i)) / dotNumber);
    glVertex3d(location.x + radius * cos(2 * PI * i / dotNumber + angle), location.y + radius * sin(2 * PI * i / dotNumber + angle), 0);
  }
  glEnd();
}