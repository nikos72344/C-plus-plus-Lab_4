#include "input.h"

Line::Line(string& str)
{
  string temp;
  for (auto i : str)
  {
    if (i != ' ')
      temp += i;
    else
    {
      words.push_back(temp);
      temp.clear();
    }
  }
  words.push_back(temp);
}

Line& Line::operator+=(string& str)
{
  words.push_back(str);
  return *this;
}

Input& Input::operator+=(string& str)
{
  Line temp(str);
  this->CodeLines.push_back(str);
  return *this;
}

bool Input::ReadFile(const char* File_Name)
{
  if (File_Name == 0)
    return false;
  ifstream fin(File_Name);
  if (!fin.is_open())
    return false;
  char buff[10];
  string temp;
  while (true)
  {
    fin.getline(buff, 10);
    temp += buff;
    if (fin.eof())
    {
      *this += temp;
      break;
    }
    if (fin.fail())
      fin.clear();
    else
    {
      *this += temp;
      temp.clear();
    }
  }
  fin.close();
  return true;
}

unsigned int Input::GetCommand(string& Command)
{
  if (Command == "LEVEL")
    return 1;
  if (Command == "rows")
    return 2;
  if (Command == "durability")
    return 3;
  if (Command == "newBall")
    return 4;
  if (Command == "extension")
    return 5;
  return 0;
}

void Input::NewLevel(vector<Level>& Levels)
{
  Level newLevel;
  Platform pltfrm;
  newLevel.platform = pltfrm;
  Ball ball;
  newLevel.ball = ball;
  Arrow arrow;
  newLevel.arrow = arrow;
  Levels.push_back(newLevel);
}

bool Input::NewBricks(vector<Line>::iterator Current, vector<Level>& Levels)
{
  if (Current->words.size() != 2)
    return false;
  Level& last = Levels.back();
  int n = atoi(Current->words[1].data());
  if ((n == 0 && Current->words[1] != "0") || n < 0)
    return false;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < last.rowSize; j++)
    {
      Brick temp;
      last.bricks.push_back(temp);
    }
  last.rows += n;
  return true;
}

bool Input::SetDurability(vector<Line>::iterator Current, vector<Level>& Levels)
{
  if (Current->words.size() != 3)
    return false;
  Level& last = Levels.back();
  int durability = atoi(Current->words[1].data());
  if (durability <= 0)
    return false;
  unsigned int n = atoi(Current->words[2].data());
  if ((n == 0 && Current->words[2] != "0") || n < 0 || n > last.bricks.size())
    return false;
  srand(time(0));
  unsigned int i = 0;
  unsigned int occupied = 0;
  while (i < n && occupied <= last.bricks.size())
  {
    int j = rand() % last.bricks.size();
    if (last.bricks[j].Durability() != 1)
    {
      occupied++;
      continue;
    }
    last.bricks[j].SetDurability(durability);
    i++;
  }
  return true;
}

bool Input::NewBonus(vector<Line>::iterator Current, vector<Level>& Levels, bonusType Type)
{
  if (Current->words.size() != 2)
    return false;
  Level& last = Levels.back();
  int n = atoi(Current->words[1].data());
  if ((n == 0 && Current->words[1] != "0") || n < 0)
    return false;
  srand(time(0));
  int i = 0;
  unsigned int occupied = 0;
  while (i < n && occupied <= last.bricks.size())
  {
    int j = rand() % last.bricks.size();
    if (last.bricks[j].Bonus() != 0)
    {
      occupied++;
      continue;
    }
    Bonus* temp = 0;
    switch (Type)
    {
    case newBall: temp = new NewBall; break;
    case extension: temp = new Extension; break;
    }
    if (temp == 0)
      return false;
    last.bricks[j].SetBonus(temp);
    last.bonuses.push_back(temp);
    i++;
  }
  return true;
}

void Input::SetBrickLocation(Screen& Main)
{
  for (auto& l: Main.levels)
  {
    l.brickNum = l.bricks.size();
    for (int i = 0; i < l.rows; i++)
      for (int j = l.rowSize * i; j < l.rowSize * (i + 1); j++)
      {
        double length = l.bricks[j].Length();
        double width = l.bricks[j].Width();
        l.bricks[j].SetLocation({ length / 2 + length * (j - l.rowSize * i), width / 2 + width * i });
        if (l.bricks[j].Bonus() != 0)
          l.bricks[j].Bonus()->SetLocation({ length / 2 + length * (j - l.rowSize * i), width / 2 + width * i });
      }
  }
}

unsigned int Input::Translator(Screen& Main)
{
  auto current = CodeLines.begin();
  if (current->words[0] != "LEVEL")
    return 2;
  vector<Level> levels;
  Level temp;
  levels.push_back(temp);
  while (current != CodeLines.end())
  {
    switch (GetCommand(current->words[0]))
    {
    case 1: NewLevel(levels); break;
    case 2: if (!NewBricks(current, levels)) { return 3; } break;
    case 3: if (!SetDurability(current, levels)) { return 4; } break;
    case 4: if (!NewBonus(current, levels, newBall)) { return 5; } break;
    case 5: if (!NewBonus(current, levels, extension)) { return 6; } break;
    default: return 7;
    }
    current++;
  }
  Main.levels = levels;
  SetBrickLocation(Main);
  return 0;
}

void ErrorMessage(unsigned int Error)
{
  switch (Error)
  {
  case 0: return;
  case 1: cerr << "Couldn't open the file.\n"; exit(1);
  case 2: cerr << "Undefined first level.\n"; exit(2);
  case 3: cerr << "Incorrect rows syntax.\n"; exit(3);
  case 4: cerr << "Incorrect durability syntax.\n"; exit(4);
  case 5: cerr << "Incorrect newBall syntax.\n"; exit(5);
  case 6: cerr << "Incorrect extention syntax.\n"; exit(6);
  case 7: cerr << "Wrong command.\n"; exit(7);
  default: cerr << "Unknown error.\n"; exit(-1);
  }
}