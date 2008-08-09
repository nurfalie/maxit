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
  QMap<QString, int> getMove(const int, const int) const;

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
  int playerScore;
  int computerScore;
  int board[Global::NROWS][Global::NCOLS];
  void chooseMove(int &, int &, const int, const int) const;
};

#endif
