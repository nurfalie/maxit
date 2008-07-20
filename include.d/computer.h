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
      HUMAN = 0,
      COMPUTER,
      HUMAN_WIN,
      UNCLEAR_WIN,
      COMPUTER_WIN,
      BOTH_PARTIES_WIN
    };
  int bestCol;
  int bestRow;
  int playerScore;
  int computerScore;
  int originalBoard[Global::NROWS][Global::NCOLS];
  QMap<QString, int> currentBoard[Global::NROWS][Global::NCOLS];
  int chooseMove(const int, int, int, int &, int &,
		 const int, const int, const int);
  int positionValue(const int, const int);
};

#endif
