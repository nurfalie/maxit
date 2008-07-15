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

class computer
{
 public:
  enum
    {
      NCOLS = 7,
      NROWS = 7,
      HUMAN_WIN = 0,
      COMPUTER_WIN
    };
  computer(const int [][NCOLS]);
  ~computer();
  void setRowCol(const int, const int);
  QMap<QString, int> computeMove(void);

 private:
  enum
    {
      HUMAN = 0,
      COMPUTER,
      UNCLEAR_WIN,
      BOTH_PARTIES_WIN
    };
  int col;
  int row;
  int originalBoard[NROWS][NCOLS];
  QMap<QString, int> currentBoard[NROWS][NCOLS];
  int chooseMove(const int, int &, int &, int, int, const int, const int);
  int positionValue(const int, const int);
};

#endif
