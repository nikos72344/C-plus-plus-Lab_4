#include "screen.h"
#include "input.h"

Screen* MAIN_SCREEN = 0;

void Display(void) { MAIN_SCREEN->Display(); }

void Mouse(int button, int state, int x, int y) { MAIN_SCREEN->Mouse(button, state, x, y); }

void PassiveMouse(int x, int y) { MAIN_SCREEN->PassiveMouse(x, y); }

void Keybord(unsigned char key, int x, int y) { MAIN_SCREEN->Keyboard(key, x, y); }

void SpecialKeyboard(int key, int x, int y) { MAIN_SCREEN->SpecialKeyboard(key, x, y); }

void DataUpdate(void) { MAIN_SCREEN->DataUpdate(); }

void SetMainDisplay(void)
{
  glMatrixMode(GL_PROJECTION);
  glOrtho(0, MAIN_SCREEN->WinLength(), MAIN_SCREEN->WinWidth(), 0, 5, -5);
}

int main(int argc, char* argv[])
{
  int winLength = 400, winWidth = 16 * winLength / 9, winX = 50, winY = 50;
  string winTitle = "Arcanoid";
  Screen main(winLength, winWidth);
  MAIN_SCREEN = &main;

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(winLength, winWidth);
  glutInitWindowPosition(winX, winY);
  glutCreateWindow(winTitle.data());

  SetMainDisplay();
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutPassiveMotionFunc(PassiveMouse);
  glutKeyboardFunc(Keybord);
  glutSpecialFunc(SpecialKeyboard);

  Input content;
  if (!content.ReadFile(argv[1]))
    ErrorMessage(1);
  ErrorMessage(content.Translator(main));

  glutIdleFunc(DataUpdate);

  glutMainLoop();

  return 0;
}