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
      {
	originalBoard[i][j] = currentBoard[i][j]["value"] = board[i][j];
	currentBoard[i][j]["player"] = -1;
      }

  playerScore = pScore;
  computerScore = cScore;
}

void computer::updateBoard(const int rowArg, const int colArg,
			   const int pScore, const int cScore)
{
  originalBoard[rowArg][colArg] = currentBoard[rowArg][colArg]["value"] = 0;
  currentBoard[rowArg][colArg]["player"] = -1;
  playerScore = pScore;
  computerScore = cScore;
}

QMap<QString, int> computer::computeMove(const int rowArg, const int colArg)
{
  int bestCol = -1;
  int bestRow = -1;
  QMap<QString, int> move;

  (void) chooseMove(COMPUTER, HUMAN_WIN, COMPUTER_WIN, bestRow, bestCol,
		    rowArg, colArg, 0);
  move["row"] = bestRow;
  move["col"] = bestCol;
  return move;
}

int computer::chooseMove(const int s, int alpha, int beta,
			 int &bestRow, int &bestCol, const int row,
			 const int col, const int depth)
{
  int opp = 0;
  int reply = 0;
  int value = 0;
  int simpleEval = UNCLEAR_WIN;

  if((simpleEval = positionValue(row, col)) != UNCLEAR_WIN)
    return simpleEval;

  if(depth >= Global::NROWS)
    return value;

  if(s == COMPUTER)
    {
      opp = HUMAN;
      value = alpha;
    }
  else
    {
      opp = COMPUTER;
      value = beta;
    }

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      if(i == row || j == col)
	if(currentBoard[i][j]["value"] > 0)
	  {
	    currentBoard[i][j]["player"] = s;
	    currentBoard[i][j]["value"] = 0;
	    reply = chooseMove(opp, alpha, beta, bestRow, bestCol, i, j,
			       depth + 1);
	    currentBoard[i][j]["player"] = -1;
	    currentBoard[i][j]["value"] = originalBoard[i][j];

	    if((s == COMPUTER && reply > value) ||
	       (s == HUMAN && reply < value))
	      {
		if(s == COMPUTER)
		  alpha = value = reply;
		else
		  beta = value = reply;

		bestRow = i;
		bestCol = j;

		if(alpha >= beta)
		  return value;
	      }
	}

  return value;
}

int computer::positionValue(const int row, const int col)
{
  int value = UNCLEAR_WIN;
  int playerTotal = 0;//playerScore;
  int computerTotal = 0;//computerScore;
  bool gameOver = true;

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      {
	if(i == row || j == col)
	  if(currentBoard[i][j]["value"] > 0)
	    gameOver = false;

	if(currentBoard[i][j]["player"] == COMPUTER)
	  computerTotal += originalBoard[i][j];
	else if(currentBoard[i][j]["player"] == HUMAN)
	  playerTotal += originalBoard[i][j];
      }

  if(gameOver)
    {
      if(computerTotal > playerTotal)
	value = COMPUTER_WIN;
      else if(computerTotal < playerTotal)
	value = HUMAN_WIN;
      else if(computerTotal == playerTotal)
	value = BOTH_PARTIES_WIN;
    }
  else
    value = UNCLEAR_WIN;

  return value;
}
