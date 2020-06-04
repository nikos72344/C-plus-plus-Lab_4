#ifndef __OBJECT_H
#define __OBJECT_H

#include "data.h"
#include <vector>

class Object
{
protected:
  point location;
  double angle;
  double speed;
  GlutRGB up, bottom;
public:
  Object(const point& Loc, const double& Angle, const double& Speed, const GlutRGB& Up, const GlutRGB& Bottom) : location(Loc), angle(Angle), speed(Speed), up(Up), bottom(Bottom) {}
  const point& Location(void) { return location; }
  const double& Angle(void) { return angle; }
  const double& Speed(void) { return speed; }
  void SetLocation(const point& Loc) { location = Loc; }
  void SetAngle(const double& Angle) { angle = Angle; }
  void SetSpeed(const double& Speed) { speed = Speed; }
  vector<point> Calculations(vector<point> Dots);
  virtual void Draw(void) = 0;
};

#endif