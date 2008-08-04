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
#include <QList>
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
  class pos
  {
  public:
    int x;
    int y;
    int total;
    bool operator<(const pos &rhs) const
    {
      return total < rhs.total;
    }
    bool operator==(const pos &rhs) const
    {
      return total == rhs.total;
    }
  };
  int bestCol;
  int bestRow;
  int playerScore;
  int computerScore;
  int originalBoard[Global::NROWS][Global::NCOLS];
  void chooseMove(int &, int &, const int, const int);
};

#endif
