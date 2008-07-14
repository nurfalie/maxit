#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void):QMainWindow()
{
  int suitableH = NROWS * (static_cast<int> (glpiece::CUBE_SIZE - 0.25 *
					     glpiece::CUBE_SIZE));
  QActionGroup *ag1 = 0;

  setupUi(this);
  computerptr = 0;
  ag1 = new QActionGroup(this);
  action_2D = new QAction("2D", this);
  action_3D = new QAction("3D", this);
  qgl = new QGridLayout();
  ag1->setExclusive(true);
  ag1->addAction(action_2D);
  ag1->addAction(action_3D);
  menu_View->addAction(action_2D);
  menu_View->addAction(action_3D);
  action_2D->setCheckable(true);
  action_3D->setCheckable(true);
  action_2D->setChecked(true);
  connect(action_Exit, SIGNAL(triggered(void)), qapp, SLOT(quit(void)));
  connect(action_About, SIGNAL(triggered(void)), this, SLOT(slotAbout(void)));
  connect(action_New_Game, SIGNAL(triggered(void)), this,
	  SLOT(slotNewGame(void)));
  connect(action_2D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_3D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  qgl->setSpacing(1);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      glpieces[i][j] = 0;

  prepareBoard();
  boardframe->setLayout(qgl);
  boardframe->setMinimumSize(suitableH, suitableH);
  resize(boardframe->size());
  show();
}

void maxit::prepareBoard(const bool createPieces)
{
  int side = glpiece::CUBE_SIZE;
  int value = 0;
  int board[NROWS][NCOLS];
  QColor color = QColor(133, 99, 99);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      {
	value = qrand() % (NROWS * NROWS);

	if(value == 0)
	  value += 1;
	else if(value > (NROWS * NROWS))
	  value = value / 2;

	if(qrand() % 3 == 0)
	  value = -value;

	if(createPieces)
	  glpieces[i][j] = new glpiece
	    (0, glpieces[0][0], value, color, i, j, side);
	else
	  glpieces[i][j]->reset(value);

	if(createPieces)
	  qgl->addWidget(glpieces[i][j], i, j);

	qapp->processEvents();
	board[i][j] = abs(value);
      }

  if(!computerptr)
    computerptr = new computer(board);
}

void maxit::slotNewGame(void)
{
  playerscore->setText("0");
  opponentscore->setText("0");
  prepareBoard(false);
}

bool maxit::isGameOver(void) const
{
  bool gameOver = false;
  return gameOver;
}

void maxit::slotAbout(void)
{
  QMessageBox mb(this);

  mb.setWindowTitle("Maxit: About");
  mb.setTextFormat(Qt::RichText);
  mb.setText("<html>Maxit Version 0.01.<br>"
	     "Copyright (c) Slurpy McNash 2007, 2008.<br><br>"
	     "Please visit "
	     "<a href=\"http://maxit.sourceforge.net\">"
	     "http://maxit.sourceforge.net</a> for "
	     "project information."
	     "</html>");
  mb.setStandardButtons(QMessageBox::Ok);
  mb.exec();
}

void maxit::slotChangeView(void)
{
  if(getViewMode() == VIEW2D)
    {
      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(0, 0, 0);
	  else
	    glpieces[i][j]->rotate(0, 0, 0);
    }
  else
    {
      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(45 * 64, 45 * 64, -25 * 64);
	  else
	    glpieces[i][j]->rotate(-45 * 64, 45 * 64, 25 * 64);
    }
}

int maxit::getViewMode(void) const
{
  if(action_2D->isChecked())
    return VIEW2D;
  else
    return VIEW3D;
}

void maxit::pieceSelected(glpiece *piece)
{
  QMap<QString, int> move;

  playerscore->setText
    (QString::number(playerscore->text().toInt() + piece->value()));
  computerptr->setRowCol(piece->row(), piece->col());
  move = computerptr->computeMove();

  if(move["row"] > -1 && move["col"] > -1)
    {
      opponentscore->setText
	(QString::number(opponentscore->text().toInt()) +
	 glpieces[move["row"]][move["col"]]->value());

      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NCOLS; j++)
	  if(i == move["row"] || j == move["col"])
	    glpieces[i][j]->setEnabled(true);
	  else
	    glpieces[i][j]->setEnabled(false);
    }

  if(isGameOver())
    if(playerscore->text().toInt() > opponentscore->text().toInt())
      QMessageBox::information(this, "Game Over", "You have won!");
    else if(playerscore->text().toInt() < opponentscore->text().toInt())
      QMessageBox::information(this, "Game Over", "Your opponent has won!");
    else
      QMessageBox::information(this, "Game Over",
			       "The game resulted in a tie!");
}
