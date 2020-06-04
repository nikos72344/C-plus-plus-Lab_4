#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "object.h"
#include "bonus.h"

class Extension;

class Platform : public Object
{
private:
  double length, width;
public:
  Platform(const GlutRGB& Up = { 210, 180, 140 }, const GlutRGB& Bottom = { 139, 69, 19 }) : Object({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 }, 0, 20, Up, Bottom), length(WIN_LENGTH / 4), width(WIN_LENGTH / 25) {}
  const double& Length(void) { return length; }
  const double& Width(void) { return width; }
  virtual void Draw(void) override;
  friend Extension;
};

#endif