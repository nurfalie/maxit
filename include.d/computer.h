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
#include <QThread>

/*
** -- Local Includes --
*/

#include "common.h"

class thread: public QThread
{
  Q_OBJECT

 public:
  static int playerScore;
  static int computerScore;
  static int board[Global::NROWS][Global::NCOLS];

  thread(const int r, const int c)
  {
    i = r;
    j = c;
  }

  int col(void) const
  {
    return bestCol;
  }

  int row(void) const
  {
    return bestRow;
  }

  int value(void) const
  {
    return total;
  }

  static void initThread(const int cScore, const int pScore,
			 const int brd[][Global::NCOLS])
  {
    playerScore = pScore;
    computerScore = cScore;

    for(int i = 0; i < Global::NROWS; i++)
      for(int j = 0; j < Global::NCOLS; j++)
	board[i][j] = brd[i][j];
  }

 private:
  int i;
  int j;
  int total;
  int bestCol;
  int bestRow;

 protected:
  void run(void)
  {
    int tmp = 0;

    total = -playerScore + computerScore;

    for(int k = 0; k < Global::NROWS; k++)
      for(int l = 0; l < Global::NCOLS; l++)
	if((k == i || l == j) && board[k][l] > 0)
	  for(int m = 0; m < Global::NROWS; m++)
	    for(int n = 0; n < Global::NCOLS; n++)
	      if((m == k || n == l) && board[m][n] > 0)
		for(int o = 0; o < Global::NROWS; o++)
		  for(int p = 0; p < Global::NCOLS; p++)
		    if((o == m || p == n) && board[o][p] > 0)
		      for(int q = 0; q < Global::NROWS; q++)
			for(int r = 0; r < Global::NCOLS; r++)
			  if((o == q || p == r) && board[q][r] > 0)
			    {
			      tmp = -playerScore + computerScore +
				board[i][j] -
				board[k][l] +
				board[m][n] -
				board[o][p] +
				board[q][r];

			      if(tmp > total)
				{
				  total = tmp;
				  bestRow = i;
				  bestCol = j;
				}
			    }
  }
};

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
