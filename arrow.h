#ifndef __ARROW_H
#define __ARROW_H

#include "object.h"

class Arrow : public Object
{
private:
  double length, width;
public:
  Arrow(void) : Object({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 - WIN_LENGTH / 25 - 8 }, -PI / 2, 20, { 0, 0, 0 }, { 0, 0, 0 }), length(2 * WIN_LENGTH / 25), width(WIN_LENGTH / 25) {}
  virtual void Draw(void) override;
};

#endif