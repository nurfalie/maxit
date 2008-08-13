#include "computer.h"

int thread::playerScore = 0;
int thread::computerScore = 0;
int thread::board[Global::NROWS][Global::NCOLS];

computer::computer(void)
{
}

computer::~computer()
{
}

void computer::updateBoard(const int boardArg[][Global::NCOLS],
			   const int pScore, const int cScore)
{
  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      board[i][j] = boardArg[i][j];

  thread::initThread(pScore, cScore, board);
  playerScore = pScore;
  computerScore = cScore;
}

QMap<QString, int> computer::getMove(const int rowArg, const int colArg) const
{
  int bestCol = -1;
  int bestRow = -1;
  QMap<QString, int> move;

  chooseMove(bestRow, bestCol, rowArg, colArg);
  move["row"] = bestRow;
  move["col"] = bestCol;
  return move;
}

void computer::chooseMove(int &bestRow, int &bestCol, const int row,
			  const int col) const
{
  int total = 0;
  thread *t = 0;
  QList<thread *> threads;

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      if((i == row || j == col) && board[i][j] > 0)
	{
	  t = new thread(i, j);
	  t->start();
	  threads.append(t);
	}

  /*
  ** Wait.
  */

  for(int i = 0; i < threads.size();)
    {
      if(threads.at(i)->isRunning())
	{
	  threads.at(i)->wait(250);
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
    delete threads.takeFirst();
}
