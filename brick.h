#ifndef __BRICK_H
#define __BRICK_H

#include "object.h"
#include "bonus.h"

class Brick : public Object
{
private:
  double length, width;
  int durability;
  Bonus* bonus;
  void SetColor(void);
public:
  Brick(void) : Object({ 0, 0 }, 0, 0, { 255, 255, 255 }, { 139, 0, 139 }), length(WIN_LENGTH / ROW_SIZE), width(WIN_LENGTH / 10), durability(1), bonus(0) {}
  void SetLocation(const point& Loc) { location = Loc; }
  void SetDurability(const int& Durability) { durability = Durability; }
  void SetBonus(Bonus* bns) { bonus = bns; }
  const double& Length(void) { return length; }
  const double& Width(void) { return width; }
  const int& Durability(void) { return durability; }
  Bonus* Bonus(void) { return bonus; }
  virtual void Draw(void) override;
};

#endif