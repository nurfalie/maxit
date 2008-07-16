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
      NCOLS = 4,
      NROWS = 4
    };
  computer(void);
  ~computer();
  void updateBoard(const int [][NCOLS], const int = 0, const int = 0);
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
  int playerScore;
  int computerScore;
  int originalBoard[NROWS][NCOLS];
  QMap<QString, int> currentBoard[NROWS][NCOLS];
  int chooseMove(const int, int &, int &, int, int, const int, const int,
		 const int);
  int positionValue(const int, const int);
};

#endif
