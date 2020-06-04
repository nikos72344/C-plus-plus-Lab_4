#ifndef __LEVEL_H
#define __LEVEL_H

#include "arrow.h"
#include "brick.h"
#include "input.h"
#include "screen.h"
#include <vector>

class Screen;

class Input;

class Level
{
private:
  vector<Brick> bricks;
  int brickNum;
  int rows;
  int rowSize;
  vector<Bonus*> bonuses;
  Platform platform;
  Ball ball;
  Arrow arrow;
public:
  Level(void) : brickNum(0), rows(0), rowSize(ROW_SIZE) {}
  friend Screen;
  friend Input;
};

#endif