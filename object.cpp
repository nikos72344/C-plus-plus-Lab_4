#include "object.h"

vector<point> Object::Calculations(vector<point> Dots)
{
  vector<point> xy;
  for (unsigned int i = 0; i < Dots.size(); i++)
  {
    point temp;
    temp.x = Dots[i].x * cos(angle) - Dots[i].y * sin(angle) + location.x;
    temp.y = Dots[i].x * sin(angle) + Dots[i].y * cos(angle) + location.y;
    xy.push_back(temp);
  }
  return xy;
}