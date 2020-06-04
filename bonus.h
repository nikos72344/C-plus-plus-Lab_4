#ifndef __BONUS_H
#define __BONUS_H

#include "object.h"
#include "ball.h"
#include "platform.h"

enum bonusType
{
  none,
  newBall,
  extension
};

enum bonusStatus
{
  hide,
  fall,
  caught
};

class Bonus : public Object
{
protected:
  double length, width;
  bonusType type;
  bonusStatus status;
  void SetColor(void);
public:
  Bonus(const bonusType& Type = none) : Object({ 0, 0 }, PI / 2, 0.2, { 255, 255, 255 }, { 0, 0, 0 }), length(WIN_LENGTH / 25), width(WIN_LENGTH / 25), type(Type), status(hide) {}
  const double& Length(void) { return length; }
  const bonusStatus& Status(void) { return status; }
  const bonusType& Type(void) { return type; }
  void SetStatus(const bonusStatus& Status) { status = Status; }
  virtual void Draw(void) override;
  virtual void ApplyBonus(Object* Obj) = 0;
};

class NewBall : public Bonus
{
public:
  NewBall(void) : Bonus(newBall) {}
  void ApplyBonus(Object* Obj);
};

class Extension : public Bonus
{
public:
  Extension(void) : Bonus(extension) {}
  void ApplyBonus(Object* Obj);
};

#endif