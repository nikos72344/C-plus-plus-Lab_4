#include "screen.h"

void Screen::Background(void)
{
  glBegin(GL_QUADS);
  glColor3d(176 / 255.0, 224 / 255.0, 230 / 255.0);
  glVertex3d(0, 0, -5);
  glColor3d(72 / 255.0, 209 / 255.0, 240 / 255.0);
  glVertex3d(winLength, 0, -5);
  glColor3d(175 / 255.0, 238 / 255.0, 238 / 255.0);
  glVertex3d(winLength, winWidth, -5);
  glColor3d(224 / 255.0, 255 / 255.0, 255 / 255.0);
  glVertex3d(0, winWidth, -5);
  glEnd();
}

void Screen::PositionUpdate(void)
{
  Ball& ball = levels[currentLevel].ball;
  vector<Bonus*>& bonuses = levels[currentLevel].bonuses;
  static long long previous = 0;
  long long current, freq;
  double dt = 0;
  QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
  QueryPerformanceCounter((LARGE_INTEGER*)&current);
  dt = (double)((current - previous) * 1.0 / freq * 1000000);
  if (dt >= 300)
  {
    for (Bonus* i : bonuses)
    {
      point oldLoc = i->Location();
      if (i->Status() == fall && oldLoc.y <= winWidth + i->Length())
      {
        double speed = i->Speed();
        point newLoc = { oldLoc.x, oldLoc.y + speed };
        i->SetLocation(newLoc);
      }
    }
    if (ball.Status() == flight)
    {
      MotionControl();
      point oldLoc = ball.Location();
      double speed = ball.Speed();
      double angle = ball.Angle();
      point newLoc = { oldLoc.x + speed * cos(angle), oldLoc.y + speed * sin(angle) };
      ball.SetLocation(newLoc);
    }
  }
  QueryPerformanceCounter((LARGE_INTEGER*)&previous);
}

void Screen::BonusRotation(void)
{
  static long long previous = 0;
  long long current, freq;
  double dt = 0;
  QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
  QueryPerformanceCounter((LARGE_INTEGER*)&current);
  dt = (double)((current - previous) * 1.0 / freq * 1000000);
  if (dt >= 500)
    for (Bonus* i : levels[currentLevel].bonuses)
    {
      point loc = i->Location();
      if (i->Status() == fall && loc.y <= winWidth + i->Length())
      {
        double angle = i->Angle();
        i->SetAngle(angle + PI / 180);
      }
    }
  QueryPerformanceCounter((LARGE_INTEGER*)&previous);
}

void Screen::MotionControl(void)
{
  Ball& ball = levels[currentLevel].ball;
  if (ball.Status() == preLaunch)
    return;
  Platform& platform = levels[currentLevel].platform;
  for (int i = 0; i < ball.DotNumber(); i++)
  {
    point dot = { ball.Location().x + ball.Radius() * cos(2 * PI * i / ball.DotNumber() + ball.Angle()), ball.Location().y + ball.Radius() * sin(2 * PI * i / ball.DotNumber() + ball.Angle()) };
    if (dot.x <= 0 || dot.x >= winLength || dot.y <= 0)
    {
      srand(time(0));
      double angle = ball.Angle();
      int error = rand() % 5 + 1;
      ball.SetAngle(angle + PI / 2 + error * PI / 180);
      return;
    }
    if (dot.x >= platform.Location().x - platform.Length() / 2 && dot.x <= platform.Location().x + platform.Length() / 2 && dot.y >= platform.Location().y - platform.Width() / 2 && dot.y <= platform.Location().y + platform.Width() / 2)
    {
      double angle = ball.Angle();
      srand(time(0));
      int error = rand() % 21 - 10;
      ball.SetAngle(angle + PI / 3 + error * PI / 180);
      return;
    }
    for (Brick& j : levels[currentLevel].bricks)
      if (j.Durability() > 0 && dot.x >= j.Location().x - j.Length() / 2 && dot.x <= j.Location().x + j.Length() / 2 && dot.y >= j.Location().y - j.Width() / 2 && dot.y <= j.Location().y + j.Width() / 2)
      {
        double angle = ball.Angle();
        ball.SetAngle(angle + PI);
        int newDurability = j.Durability() - 1;
        j.SetDurability(newDurability);
        if (newDurability == 0)
        {
          levels[currentLevel].brickNum--;
          if (j.Bonus() != 0)
            j.Bonus()->SetStatus(fall);
        }
        return;
      }
  }
}

void Screen::MovePlatform(const int& Direction)
{
  Platform& platform = levels[currentLevel].platform;
  point oldPlatformLoc = platform.Location();
  if (oldPlatformLoc.x <= platform.Length() / 2 && Direction == -1)
    return;
  if (oldPlatformLoc.x >= winLength - platform.Length() / 2 && Direction == 1)
    return;
  point newPlatformLoc = { oldPlatformLoc.x + Direction * platform.Speed(), oldPlatformLoc.y };
  platform.SetLocation(newPlatformLoc);
  Arrow& arrow = levels[currentLevel].arrow;
  point newArrowLoc = { newPlatformLoc.x, arrow.Location().y };
  levels[currentLevel].arrow.SetLocation(newArrowLoc);
  if (levels[currentLevel].ball.Status() == preLaunch)
    levels[currentLevel].ball.SetLocation(newArrowLoc);
}

void Screen::LaunchAngle(const int& x, const int& y)
{
  Ball& ball = levels[currentLevel].ball;
  if (ball.Status() == flight)
    return;
  double angle = -atan2(ball.Location().y - y, x - ball.Location().x);
  ball.SetAngle(angle);
  levels[currentLevel].arrow.SetAngle(angle);
}

void Screen::Greeting(void)
{
  if (currentLevel == 0)
  {
    Title main("Welcome to Arcanoid!");
    Title tip("Click to start");
    main.SetLocation({ ((double)winLength - main.Length()) / 2, (double)winWidth / 2 });
    tip.SetLocation({ ((double)winLength - tip.Length()) / 2, (double)winWidth / 2 + 25 + main.Width() });
    main.Draw();
    tip.Draw();
  }
  else
  {
    char temp[3];
    _itoa_s(currentLevel, temp, 10);
    string number(temp);
    string level = "Level ";
    Title main(level + number);
    Title tip("Click to start");
    main.SetLocation({ ((double)winLength - main.Length()) / 2, (double)winWidth / 2 });
    tip.SetLocation({ ((double)winLength - tip.Length()) / 2, (double)winWidth / 2 + 25 + main.Width() });
    main.Draw();
    tip.Draw();
  }
}

void Screen::IsWin(void)
{
  if (status == playing && levels[currentLevel].brickNum <= 0)
  {
    status = greeting;
    currentLevel++;
    if (currentLevel >= levels.size())
      status = won;
  }
}

void Screen::IsLost(void)
{
  if (status == playing && levels[currentLevel].ball.BallNumber() <= 0)
    status = lost;
}

void Screen::IsBallLost(void)
{
  Ball& ball = levels[currentLevel].ball;
  if ((ball.Location().y - 2 * ball.Radius() - 8) > winWidth)
  {
    levels[currentLevel].platform.SetLocation({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 });
    Arrow& arrow = levels[currentLevel].arrow;
    arrow.SetLocation({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 - WIN_LENGTH / 25 - 8 });
    ball.SetLocation({ WIN_LENGTH / 2, WIN_WIDTH - WIN_LENGTH / 25 - 5 - WIN_LENGTH / 25 - 8 });
    ball.SetAngle(arrow.Angle());
    ball.SetStatus(preLaunch);
    int number = ball.BallNumber();
    ball.SetBallNumber(number - 1);
    ball.SetColor();
    for (Bonus* i : levels[currentLevel].bonuses)
      if (i->Status() == flight)
        i->SetStatus(caught);
  }
}

void Screen::IsBonusCaught(void)
{
  Platform& platform = levels[currentLevel].platform;
  for (Bonus* i : levels[currentLevel].bonuses)
    if (i->Status() == flight && i->Location().x >= platform.Location().x - platform.Length() / 2 && i->Location().x <= platform.Location().x + platform.Length() / 2 && i->Location().y >= platform.Location().y - platform.Width() / 2 && i->Location().y <= platform.Location().y + platform.Width() / 2)
    {
      switch (i->Type())
      {
      case newBall: i->ApplyBonus(&levels[currentLevel].ball); break;
      case extension: i->ApplyBonus(&platform); break;
      }
      i->SetStatus(caught);
    }
}

void Screen::GameOver(void)
{
  Title main("Game Over!");
  Title tip(":(");
  main.SetLocation({ ((double)winLength - main.Length()) / 2, (double)winWidth / 2 });
  tip.SetLocation({ ((double)winLength - tip.Length()) / 2, (double)winWidth / 2 + 25 + main.Width() });
  main.Draw();
  tip.Draw();
}

void Screen::Winning(void)
{
  Title main("Congratulations!");
  Title tip("You won this game!");
  main.SetLocation({ ((double)winLength - main.Length()) / 2, (double)winWidth / 2 });
  tip.SetLocation({ ((double)winLength - tip.Length()) / 2, (double)winWidth / 2 + 25 + main.Width() });
  main.Draw();
  tip.Draw();
}

void Screen::Display(void)
{
  Background();
  if (status == greeting)
    Greeting();
  if (status == playing)
  {
    for (Brick& i : levels[currentLevel].bricks)
      i.Draw();
    for (Bonus* i : levels[currentLevel].bonuses)
      i->Draw();
    levels[currentLevel].platform.Draw();
    if (levels[currentLevel].ball.Status() == preLaunch)
      levels[currentLevel].arrow.Draw();
    levels[currentLevel].ball.Draw();
  }
  if (status == lost)
    GameOver();
  if (status == won)
    Winning();
  glutSwapBuffers();
}

void Screen::Mouse(const int& button, const int& state, const int& x, const int& y)
{
  if (status == greeting && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
    status = playing;
    return;
  }
  if (status == playing)
  {
    Ball& ball = levels[currentLevel].ball;
    if (ball.Status() == preLaunch && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
      ball.SetStatus(flight);
    return;
  }
}

void Screen::PassiveMouse(const int& x, const int& y)
{
  if (status != won)
  {
    LaunchAngle(x, y);
    glutPostRedisplay();
  }
}

void Screen::Keyboard(const unsigned char& key, const int& x, const int& y)
{
  if (key == 27)
    exit(27);
}

void Screen::SpecialKeyboard(const int& key, const int& x, const  int& y)
{
  if (status != won)
  {
    switch (key)
    {
    case GLUT_KEY_LEFT: MovePlatform(-1); break;
    case GLUT_KEY_RIGHT: MovePlatform(1); break;
    }
    LaunchAngle(x, y);
    glutPostRedisplay();
  }
}

void Screen::DataUpdate(void)
{
  if (status != won)
  {
    BonusRotation();
    IsBonusCaught();
    PositionUpdate();
    IsBallLost();
    IsWin();
    IsLost();
    glutPostRedisplay();
  }
}