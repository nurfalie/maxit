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
  static const int NCOLS = 7;
  static const int NROWS = 7;
  static const int HUMAN_WIN = 0;
  static const int COMPUTER_WIN = 1;
  computer(const int [][NCOLS]);
  ~computer();
  void setRowCol(const int, const int);
  QMap<QString, int> computeMove(void);

 private:
  static const int HUMAN = 0;
  static const int COMPUTER = 1;
  static const int UNCLEAR_WIN = 2;
  static const int BOTH_PARTIES_WIN = 3;
  int col;
  int row;
  int originalBoard[NROWS][NCOLS];
  QMap<QString, int> currentBoard[NROWS][NCOLS];
  int chooseMove(const int, int &, int &, int, int, const int, const int);
  int positionValue(const int, const int);
};

#endif
