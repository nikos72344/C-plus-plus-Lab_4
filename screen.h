#ifndef __SCREEN_H
#define __SCREEN_H

#include "input.h"
#include "level.h"
#include "title.h"
#include <Windows.h>

class Input;

enum screenStatus
{
  greeting,
  playing,
  lost,
  won
};

class Screen
{
private:
  int winLength, winWidth;
  vector<Level> levels;
  unsigned int currentLevel;
  screenStatus status;
  void Background(void);
  void PositionUpdate(void);
  void BonusRotation(void);
  void MotionControl(void);
  void MovePlatform(const int& Direction);
  void LaunchAngle(const int& x, const int& y);
  void Greeting(void);
  void IsWin(void);
  void IsLost(void);
  void IsBallLost(void);
  void IsBonusCaught(void);
  void GameOver(void);
  void Winning(void);
public:
  Screen(const int& wLength, const int& wWidth) : winLength(wLength), winWidth(wWidth), currentLevel(0), status(greeting) {}
  void Display(void);
  void Mouse(const int& button, const int& state, const int& x, const int& y);
  void PassiveMouse(const int& x, const int& y);
  void Keyboard(const unsigned char& key, const int& x, const int& y);
  void SpecialKeyboard(const int& key, const int& x, const int& y);
  void DataUpdate(void);
  const int& WinLength(void) { return winLength; }
  const int& WinWidth(void) { return winWidth; }
  friend Input;
};

#endif