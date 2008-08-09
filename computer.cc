#include "computer.h"

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
  int tmp = 0;
  int total = -playerScore + computerScore;

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      if((i == row || j == col) && board[i][j] > 0)
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
