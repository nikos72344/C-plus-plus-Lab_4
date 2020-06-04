#ifndef __INPUT_H
#define __INPUT_H

#include "screen.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ErrorMessage(unsigned int Error);

class Line
{
public:
  vector<string> words;
  Line(string& str);
  Line& operator+=(string& str);
};

enum bonusType;

class Screen;

class Level;

class Input
{
private:
  vector<Line> CodeLines;
  unsigned int GetCommand(string& Command);
  Input& operator+=(string& str);
  void NewLevel(vector<Level>& Levels);
  bool NewBricks(vector<Line>::iterator Current, vector<Level>& Levels);
  bool SetDurability(vector<Line>::iterator Current, vector<Level>& Levels);
  bool NewBonus(vector<Line>::iterator Current, vector<Level>& Levels, bonusType Type);
  void SetBrickLocation(Screen& Main);
public:
  bool ReadFile(const char* File_Name);
  unsigned int Translator(Screen& Main);
};

#endif