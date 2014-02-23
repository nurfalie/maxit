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
  static int board[Global::NROWS][Global::NCOLS];
  static int computerScore;
  static int playerScore;
  static int size;

  thread(const int r, const int c)
  {
    bestCol = -1;
    bestRow = -1;
    cl = c;
    rw = r;
    total = 0;
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

  static void initThread(const int sizeArg,
			 const int pScore, const int cScore,
			 const int brd[][Global::NCOLS])
  {
    computerScore = cScore;
    playerScore = pScore;
    size = sizeArg;

    for(int i = 0; i < size; i++)
      for(int j = 0; j < size; j++)
	board[i][j] = brd[i][j];
  }

 private:
  int bestCol;
  int bestRow;
  int cl;
  int rw;
  int total;

 protected:
  void run(void)
  {
    int tmp = 0;

    total = -playerScore + computerScore;

    for(int k = 0; k < size; k++)
      for(int l = 0; l < size; l++)
	if((k == rw || l == cl) && board[k][l] > 0)
	  for(int m = 0; m < size; m++)
	    for(int n = 0; n < size; n++)
	      if((m == k || n == l) && board[m][n] > 0)
		for(int o = 0; o < size; o++)
		  for(int p = 0; p < size; p++)
		    if((o == m || p == n) && board[o][p] > 0)
		      for(int q = 0; q < size; q++)
			for(int r = 0; r < size; r++)
			  if((q == o || r == p) && board[q][r] > 0)
			    {
			      if(cl < size && rw < size)
				tmp = -playerScore + computerScore +
				  board[rw][cl] -
				  board[k][l] +
				  board[m][n] -
				  board[o][p] +
				  board[q][r];

			      if(tmp > total)
				{
				  total = tmp;
				  bestRow = rw;
				  bestCol = cl;
				}
			    }
  }
};

class computer
{
 public:
  computer(const int [][Global::NCOLS], const int, const int = 0,
	   const int = 0);
  ~computer();
  QMap<QString, int> getMove(const int, const int) const;

 private:
  enum
  {
    COMPUTER,
    COMPUTER_WIN,
    DRAW,
    HUMAN,
    HUMAN_WIN,
    UNCLEAR_WIN
  };

  int board[Global::NROWS][Global::NCOLS];
  int computerScore;
  int playerScore;
  int size;
  void chooseMove(int &, int &, const int, const int) const;
};

#endif
