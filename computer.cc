#include <QtDebug>

#include "computer.h"

int thread::board[Global::NROWS][Global::NCOLS];
int thread::computerScore = 0;
int thread::playerScore = 0;
int thread::size = 4;

computer::computer(const int brd[][Global::NCOLS], const int sizeArg,
		   const int pScore, const int cScore)
{
  size = sizeArg;

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      board[i][j] = brd[i][j];

  thread::initThread(size, pScore, cScore, board);
  playerScore = pScore;
  computerScore = cScore;
}

computer::~computer()
{
}

QMap<QString, int> computer::getMove(const int rowArg, const int colArg) const
{
  QMap<QString, int> move;
  int bestCol = -1;
  int bestRow = -1;

  chooseMove(bestRow, bestCol, rowArg, colArg);
  move["row"] = bestRow;
  move["col"] = bestCol;
  return move;
}

void computer::chooseMove(int &bestRow, int &bestCol, const int row,
			  const int col) const
{
  QList<thread *> threads;
  int total = -playerScore + computerScore;

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      if((i == row || j == col) && board[i][j] > 0)
	{
	  thread *t = new (std::nothrow) thread(i, j);

	  if(t)
	    {
	      t->start();
	      threads.append(t);
	    }
	  else
	    qDebug() << "Memory failure.";
	}

  /*
  ** Find the best move.
  */

  for(int i = 0; i < threads.size();)
    {
      if(threads.at(i)->isRunning())
	{
	  /*
	  ** Thread i hasn't completed. Wait and test the next thread.
	  */

	  threads.at(i)->wait(50);
	  continue;
	}

      if(threads.at(i)->value() > total)
	{
	  total = threads.at(i)->value();
	  bestCol = threads.at(i)->col();
	  bestRow = threads.at(i)->row();
	}

      i += 1;
    }

  while(!threads.isEmpty())
    threads.takeFirst()->deleteLater();
}
