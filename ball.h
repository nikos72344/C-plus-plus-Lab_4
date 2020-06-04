#ifndef __BALL_H
#define __BALL_H

#include "object.h"
#include <ctime>

enum ballStatus
{
  preLaunch,
  flight
};


class Ball : public Object
{
private:
  double radius;
  int dotNumber;
  int ballNumber;
  ballStatus status;
public:
  Ball(const GlutRGB& Up = { 240, 230, 140 }, const GlutRGB& Bottom = { 107, 142, 35 }) : Object({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 - WIN_LENGTH / 25 - 8 }, -PI / 2, 0.3, Up, Bottom), radius(WIN_LENGTH / 25), dotNumber(90), ballNumber(3), status(preLaunch) { SetColor(); }
  const double& Radius(void) { return radius; }
  const int& DotNumber(void) { return dotNumber; }
  const int& BallNumber(void) { return ballNumber; }
  const  ballStatus& Status(void) { return status; }
  void SetBallNumber(const int& Number) { ballNumber = Number; }
  void SetStatus(const ballStatus& Status) { status = Status; }
  void SetColor(void);
  virtual void Draw(void) override;
};

#endif