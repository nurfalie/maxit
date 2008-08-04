#include "computer.h"

computer::computer(void)
{
}

computer::~computer()
{
}

void computer::updateBoard(const int board[][Global::NCOLS], const int pScore,
			   const int cScore)
{
  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      originalBoard[i][j] = board[i][j];

  playerScore = pScore;
  computerScore = cScore;
}

void computer::updateBoard(const int rowArg, const int colArg,
			   const int pScore, const int cScore)
{
  originalBoard[rowArg][colArg] = 0;
  playerScore = pScore;
  computerScore = cScore;
}

QMap<QString, int> computer::computeMove(const int rowArg, const int colArg)
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
			  const int col)
{
  int tmp = 0;
  int total = -playerScore + computerScore;

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      if((i == row || j == col) && originalBoard[i][j] > 0)
	for(int k = 0; k < Global::NROWS; k++)
	  for(int l = 0; l < Global::NCOLS; l++)
	    if((k == i || l == j) && originalBoard[k][l] > 0)
	      for(int m = 0; m < Global::NROWS; m++)
		for(int n = 0; n < Global::NCOLS; n++)
		  if((m == k || n == l) && originalBoard[m][n] > 0)
		    for(int o = 0; o < Global::NROWS; o++)
		      for(int p = 0; p < Global::NCOLS; p++)
			if((o == m || p == n) && originalBoard[o][p] > 0)
			  for(int q = 0; q < Global::NROWS; q++)
			    for(int r = 0; r < Global::NCOLS; r++)
			      if((o == q || p == r) && originalBoard[q][r] > 0)
				{
				  tmp = -playerScore + computerScore +
				    originalBoard[i][j] -
				    originalBoard[k][l] +
				    originalBoard[m][n] -
				    originalBoard[o][p] +
				    originalBoard[q][r];

				  if(tmp > total)
				    {
				      total = tmp;
				      bestRow = i;
				      bestCol = j;
				    }
				}
}
