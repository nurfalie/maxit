#ifndef _COMPUTER_
#define _COMPUTER_

/*
** -- C++ Includes --
*/

#include <iostream>

/*
** -- Qt Includes --
*/

#include <QMap>
#include <QString>

/*
** -- Local Includes --
*/

#include "common.h"

class computer
{
 public:
  computer(void);
  ~computer();
  void updateBoard(const int [][Global::NCOLS], const int = 0, const int = 0);
  void updateBoard(const int, const int, const int = 0, const int = 0);
  QMap<QString, int> computeMove(const int, const int);

 private:
  enum
    {
      HUMAN,
      COMPUTER,
      HUMAN_WIN,
      DRAW,
      UNCLEAR_WIN,
      COMPUTER_WIN
    };
  int bestCol;
  int bestRow;
  int playerScore;
  int computerScore;
  int originalBoard[Global::NROWS][Global::NCOLS];
  void chooseMove(int &, int &, const int, const int);
};

#endif
