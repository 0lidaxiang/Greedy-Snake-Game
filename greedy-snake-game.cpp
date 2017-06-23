#include <iostream>
#include <thread>
#include <stdio.h>
#include <typeinfo>
#include <vector>
#include <curses.h>
#include <unistd.h>

using namespace std;

struct stone
{
  int x;
  int y;
  int asciiCode;
};

struct apple
{
  int x;
  int y;
  int asciiCode;
};

struct snakeObj {
  int length;
  vector<int> xVector;
  vector<int> yVector;

};

int widthOfFence = 50;
int heightOfFence = 50;
bool globalIsOver = false;//game is not over
int globalNumOfApplesEaten = 0;// number of apple eaten
bool globalIsStart = false;//game is not start
bool globalIsDie = false;// snake is not die
int sleepTime = 300000;

struct snakeObj snakeObj1;
struct apple appleObj;
struct stone stoneObj1;
struct stone stoneObj2;
struct stone stoneObj3;


void start()
{
  globalIsStart = true;
}

void createAppleRandom()
{
  appleObj.x =  1 + rand() % (widthOfFence - 2);
  appleObj.y =  1 + rand() % (heightOfFence - 2);
  appleObj.asciiCode = 64;
}

//create Stone  Random(in face ,it just change x,y)
void createStoneRandom()
{
  stoneObj1.x =  1 + rand() % (widthOfFence - 2);
  stoneObj1.y =  1 + rand() % (heightOfFence - 2);
  stoneObj1.asciiCode = 35;

  stoneObj2.x =  1 + rand() % (widthOfFence - 2);
  stoneObj2.y =  1 + rand() % (heightOfFence - 2);
  stoneObj2.asciiCode = 35;

  stoneObj3.x =  1 + rand() % (widthOfFence - 2);
  stoneObj3.y =  1 + rand() % (heightOfFence - 2);
  stoneObj3.asciiCode = 35;
}

//handle something  after snake eat apple
void handleSnakeAfterEatApple()
{
  int xVectorSize = snakeObj1.xVector.size();
  int yVectorSize = snakeObj1.yVector.size();
  //when the last two enums is keep same direction
  if (snakeObj1.xVector[xVectorSize - 2] == snakeObj1.xVector[xVectorSize - 1])
  {
    if (snakeObj1.yVector[xVectorSize - 2] < snakeObj1.yVector[xVectorSize - 1])
    {
      snakeObj1.xVector.push_back(snakeObj1.xVector.back() + 1);
      snakeObj1.yVector.push_back(snakeObj1.yVector.back());
    }
    else if (snakeObj1.yVector[xVectorSize - 2] > snakeObj1.yVector[xVectorSize - 1])
    {
      snakeObj1.xVector.push_back(snakeObj1.xVector.back() - 1);
      snakeObj1.yVector.push_back(snakeObj1.yVector.back());
    }
  }
  else if (snakeObj1.yVector[xVectorSize - 2] == snakeObj1.yVector[xVectorSize - 1])
  {
    if (snakeObj1.xVector[xVectorSize - 2] < snakeObj1.xVector[xVectorSize - 1])
    {
      snakeObj1.xVector.push_back(snakeObj1.xVector.back());
      snakeObj1.yVector.push_back(snakeObj1.yVector.back() + 1);
    }
    else if (snakeObj1.xVector[xVectorSize - 2] > snakeObj1.xVector[xVectorSize - 1])
    {
      snakeObj1.xVector.push_back(snakeObj1.xVector.back());
      snakeObj1.yVector.push_back(snakeObj1.yVector.back() - 1);
    }
  }
  snakeObj1.length = snakeObj1.length + 1;
}

//check and handle something  when snake eat apple
void handleEatApple()
{
  if ((snakeObj1.xVector[0] == appleObj.x) && (snakeObj1.yVector[0] == appleObj.y))
  {
    createAppleRandom();
    handleSnakeAfterEatApple();
    createStoneRandom();
    globalNumOfApplesEaten++;
  }
}

//check and handle something  when snake hit fences
void handleHitFence()
{
  if ((snakeObj1.xVector.back() > LINES) || (snakeObj1.yVector.back() > COLS))
  {
    globalIsOver = true;
    globalIsDie = true;
  }
}

//check and handle something  when snake eat stone
void handleEatStone()
{
  if ((snakeObj1.xVector[0] == stoneObj1.x) && (snakeObj1.yVector[0] == stoneObj1.y))
  {
    globalIsOver = true;
    globalIsDie = true;
  }
  else if ((snakeObj1.xVector[0] == stoneObj2.x) && (snakeObj1.yVector[0] == stoneObj2.y))
  {
    globalIsOver = true;
    globalIsDie = true;
  }
  else if ((snakeObj1.xVector[0] == stoneObj3.x) && (snakeObj1.yVector[0] == stoneObj3.y))
  {
    globalIsOver = true;
    globalIsDie = true;
  }
}

// show information when game over
void showInfoForEnd()
{
  if (start_color() == OK) //开启颜色
  {
    init_pair(1, COLOR_RED, COLOR_GREEN); //建立一个颜色对
    attron(COLOR_PAIR(1)); //开启字符输出颜色
    move((LINES / 2) - 5, (COLS / 2) - 10);
    if (globalIsDie)
    {
      waddstr(stdscr, "Your Snake Eaten Stone And DIE.");
      move(LINES / 2, (COLS / 3) - 5);
      waddstr(stdscr, "Please press any key to see your socre and exit game.");
    }
    else
    {
      waddstr(stdscr, "Game over.");
      move(LINES / 2, (COLS / 3) - 5);
      waddstr(stdscr, "Please press any key to see your socre and exit game.");
      getch();
    }
    attroff(COLOR_PAIR(1)); //关闭颜色显示
    refresh();
  }
  else
  {
    move(LINES / 2, COLS / 2);
    waddstr(stdscr, "Game over.\nPlease press key 'ESC' for see your socre and exit game.");
    refresh();
  }
}

void draw()
{
  while (!globalIsOver)
  {
    clear();
    handleEatApple();
    handleEatStone();
    handleHitFence();

    //draw snake
    for (int i = 0; i < snakeObj1.length; ++i)
    {
      mvaddch(snakeObj1.xVector[i], snakeObj1.yVector[i], 42);
    }

    //draw apple
    mvaddch(appleObj.x, appleObj.y, appleObj.asciiCode);

    //draw stones
    mvaddch(stoneObj1.x, stoneObj1.y, stoneObj1.asciiCode);
    mvaddch(stoneObj2.x, stoneObj2.y, stoneObj2.asciiCode);
    mvaddch(stoneObj3.x, stoneObj3.y, stoneObj3.asciiCode);

    refresh();
  }
  showInfoForEnd();
}

void moveNomalNomal()
{
  if (snakeObj1.xVector[0] == snakeObj1.xVector[2])
  {
    //when scake is move left
    if (snakeObj1.yVector[0] < snakeObj1.yVector[2])
    {
      snakeObj1.xVector[0] = snakeObj1.xVector[0];
      snakeObj1.yVector[0] = snakeObj1.yVector[0] - 1;
    }
    else
    {
      //when scake is move right
      snakeObj1.xVector[0] = snakeObj1.xVector[0];
      snakeObj1.yVector[0] = snakeObj1.yVector[0] + 1;
      // }
    }
  }

  else if (snakeObj1.yVector[0] == snakeObj1.yVector[2])
  {
    //when scake is move up
    if (snakeObj1.xVector[0] < snakeObj1.xVector[2])
    {
      snakeObj1.xVector[0] = snakeObj1.xVector[0] - 1;
      snakeObj1.yVector[0] = snakeObj1.yVector[0];

    }
    //when scake is move down
    else
    {
      snakeObj1.xVector[0] = snakeObj1.xVector[0] + 1;
      snakeObj1.yVector[0] = snakeObj1.yVector[0];
    }
  }
}

void moveNormal()
{
  int oldPreviousX = 0;
  int oldPreviousY = 0;
  int currenX = 0;
  int currenY = 0;


  for (int i = 0; i < snakeObj1.length; ++i)
  {
    //handle when i=0
    if (i == 0)
    {
      oldPreviousX = snakeObj1.xVector[0];
      oldPreviousY = snakeObj1.yVector[0];
      moveNomalNomal();
    }
    else {
      //hanle when i>0

      currenX = snakeObj1.xVector[i];
      currenY = snakeObj1.yVector[i];

      snakeObj1.xVector[i] = oldPreviousX + 0;
      snakeObj1.yVector[i] = oldPreviousY + 0;

      oldPreviousX = currenX;
      oldPreviousY = currenY;
    }
  }

  handleEatStone();
  usleep(sleepTime);//us, 1000us=1ms
}

void moveUp()
{
  if (snakeObj1.xVector[0] == snakeObj1.xVector[2])
  {
    int oldPreviousX = 0;
    int oldPreviousY = 0;
    int currenX = 0;
    int currenY = 0;

    for (int i = 0; i < snakeObj1.length; ++i)
    {
      //handle when i=0
      if (i == 0)
      {
        oldPreviousX = snakeObj1.xVector[0];
        oldPreviousY = snakeObj1.yVector[0];

        snakeObj1.xVector[0] = snakeObj1.xVector[0] - 1;
        snakeObj1.yVector[0] = snakeObj1.yVector[0];
      }
      else {
        //hanle when i>0
        currenX = snakeObj1.xVector[i];
        currenY = snakeObj1.yVector[i];

        snakeObj1.xVector[i] = oldPreviousX ;
        snakeObj1.yVector[i] = oldPreviousY;

        oldPreviousX = currenX;
        oldPreviousY = currenY;
      }
    }
    handleEatStone();
  }
}

void moveDown()
{
  if (snakeObj1.xVector[0] == snakeObj1.xVector[2])
  {
    int oldPreviousX = 0;
    int oldPreviousY = 0;
    int currenX = 0;
    int currenY = 0;

    for (int i = 0; i < snakeObj1.length; ++i)
    {
      //handle when i=0
      if (i == 0)
      {
        oldPreviousX = snakeObj1.xVector[0];
        oldPreviousY = snakeObj1.yVector[0];

        snakeObj1.xVector[0] = snakeObj1.xVector[0] + 1;
        snakeObj1.yVector[0] = snakeObj1.yVector[0];
      }
      else {
        //hanle when i>0
        currenX = snakeObj1.xVector[i];
        currenY = snakeObj1.yVector[i];

        snakeObj1.xVector[i] = oldPreviousX ;
        snakeObj1.yVector[i] = oldPreviousY;

        oldPreviousX = currenX;
        oldPreviousY = currenY;
      }
    }

    handleEatStone();
  }
}

void moveLeft()
{
  if (snakeObj1.yVector[0] == snakeObj1.yVector[2])
  {
    int oldPreviousX = 0;
    int oldPreviousY = 0;
    int currenX = 0;
    int currenY = 0;

    for (int i = 0; i < snakeObj1.length; ++i)
    {
      //handle when i=0
      if (i == 0)
      {
        oldPreviousX = snakeObj1.xVector[0];
        oldPreviousY = snakeObj1.yVector[0];

        snakeObj1.xVector[0] = snakeObj1.xVector[0];
        snakeObj1.yVector[0] = snakeObj1.yVector[0] - 1;
      }
      else {
        //hanle when i>0
        currenX = snakeObj1.xVector[i];
        currenY = snakeObj1.yVector[i];

        snakeObj1.xVector[i] = oldPreviousX ;
        snakeObj1.yVector[i] = oldPreviousY;

        oldPreviousX = currenX;
        oldPreviousY = currenY;
      }
    }
    handleEatStone();
  }
}

void moveRight()
{
  if (snakeObj1.yVector[0] == snakeObj1.yVector[2])
  {
    int oldPreviousX = 0;
    int oldPreviousY = 0;
    int currenX = 0;
    int currenY = 0;

    for (int i = 0; i < snakeObj1.length; ++i)
    {
      //handle when i=0
      if (i == 0)
      {
        oldPreviousX = snakeObj1.xVector[0];
        oldPreviousY = snakeObj1.yVector[0];

        snakeObj1.xVector[0] = snakeObj1.xVector[0];
        snakeObj1.yVector[0] = snakeObj1.yVector[0] + 1;
      }
      else {
        //hanle when i>0
        currenX = snakeObj1.xVector[i];
        currenY = snakeObj1.yVector[i];

        snakeObj1.xVector[i] = oldPreviousX ;
        snakeObj1.yVector[i] = oldPreviousY;

        oldPreviousX = currenX;
        oldPreviousY = currenY;
      }
    }

    handleEatStone();
  }
}

void addSpeed()
{
  if (globalIsStart)
  {
    sleepTime = sleepTime / 2;
  }
}

void slowSpeed()
{
  if (globalIsStart && (sleepTime < 3000000))
  {
    sleepTime = sleepTime * 2;
  }
}

//seconde thread for handle user input
void keysInputHandle() {
  while (!globalIsOver)
  {
    char ch;
    ch = getch();
    // cout << "ch :" << ch << endl;
    switch (ch)
    {
    case 72://H, move left,first check that it's y is changing not x,then x - 1.otherwise don't change.
      moveUp(); break;
    case 78://N, move right,first check that it's y is changing not x,then x + 1.otherwise don't change.
      moveDown(); break;
    case 66://B, move up,first check that it's x is changing not y,then y + 1.otherwise don't change.
      moveLeft(); break;
    case 77://M, move down,first check that it's x is changing not y,then y - 1.otherwise don't change.
      moveRight(); break;
    case 32://space, start snanke move
      start(); break;
    case 27://esc, stop snanke move
      globalIsOver = true; break;
    case 80://P, pause snanke move
      globalIsStart = false; break;
    case 65://A, add move speed
      addSpeed(); break;
    case 83://S, slow move speed
      slowSpeed(); break;
    default:
      break;
    }
  }
}

void initSnake()
{
  snakeObj1.length = 3;

  snakeObj1.xVector.push_back(22);
  snakeObj1.yVector.push_back(25);

  snakeObj1.xVector.push_back(22);
  snakeObj1.yVector.push_back(24);

  snakeObj1.xVector.push_back(22);
  snakeObj1.yVector.push_back(23);
}

int main(void)
{
  int score = 0;
  globalIsDie = false;

  initscr();
  cbreak();//关闭字符流的缓冲
  noecho();//关闭字符回显
  box(stdscr, ACS_VLINE, ACS_HLINE);

  initSnake();
  createAppleRandom();
  createStoneRandom();

  thread mThread1( draw );
  thread mThread2( keysInputHandle );

  //check whethe game is over
  while (!globalIsOver)
  {
    //check whethe game is start
    if (globalIsStart)
    {
      moveNormal();
      score = globalNumOfApplesEaten;
    }
  }

  //wait for other threads
  mThread1.join();
  mThread2.join();

  //close all windows
  endwin();

  cout << "Greedy Snanke Game Over." << endl;
  cout << "Your score is " << score << " !" << endl;

  return 0;
}