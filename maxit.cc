#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void):QMainWindow()
{
  int i = 0;
  int j = 0;
  int suitableH = NROWS * ((int) (glpiece::CUBE_SIZE - 0.25 *
				  glpiece::CUBE_SIZE));
  QActionGroup *ag = NULL;

  setupUi(this);

  if((ag = new QActionGroup(this)) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  if((action_2D = new QAction("2D", this)) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  if((action_3D = new QAction("3D", this)) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  ag->setExclusive(true);
  ag->addAction(action_2D);
  ag->addAction(action_3D);
  menu_View->addAction(action_2D);
  menu_View->addAction(action_3D);
  action_2D->setCheckable(true);
  action_3D->setCheckable(true);
  action_2D->setChecked(true);
  connect((QObject *) action_Exit, SIGNAL(triggered(void)),
	  qapp, SLOT(quit(void)));
  connect((QObject *) action_About, SIGNAL(triggered(void)),
	  this, SLOT(slotAbout(void)));
  connect((QObject *) action_New_Game, SIGNAL(triggered(void)),
	  this, SLOT(slotNewGame(void)));
  connect((QObject *) action_2D, SIGNAL(triggered(void)),
	  this, SLOT(slotChangeView(void)));
  connect((QObject *) action_3D, SIGNAL(triggered(void)),
	  this, SLOT(slotChangeView(void)));

  if((qgl = new QGridLayout()) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  qgl->setSpacing(1);

  for(i = 0; i < NROWS; i++)
    for(j = 0; j < NCOLS; j++)
      glpieces[i][j] = NULL;

  prepareBoard();
  boardframe->setLayout(qgl);
  boardframe->setFixedSize(suitableH, suitableH);
  show();
}

void maxit::prepareBoard(const bool createPieces)
{
  int i = 0;
  int j = 0;
  int value = 0;
  QColor color = QColor(133, 99, 99);

  for(i = 0; i < NROWS; i++)
    for(j = 0; j < NCOLS; j++)
      {
	value = qrand() % (NROWS * NROWS);

	if(value == 0)
	  value += 1;
	else if(value > (NROWS * NROWS))
	  value = value / 2;

	if(qrand() % 3 == 0)
	  value = -value;

	if(createPieces)
	  glpieces[i][j] = new glpiece(NULL, glpieces[0][0], value, color);
	else
	  glpieces[i][j]->reset(value);

	if(createPieces)
	  qgl->addWidget(glpieces[i][j], i, j);
      }
}

void maxit::slotNewGame(void)
{
  playerscore->display("0");
  opponentscore->display("0");
  prepareBoard(false);
}

bool maxit::isGameOver(void)
{
  bool gameOver = true;

  if(gameOver)
    if(playerscore->intValue() >
       opponentscore->intValue())
      QMessageBox::information(this, "Game Over", "You won!");
    else if(playerscore->intValue() <
	    opponentscore->intValue())
      QMessageBox::information(this, "Game Over", "Your opponent won!");
    else
      QMessageBox::information(this, "Game Over", "A tie!");

  return gameOver;
}

void maxit::slotAbout(void)
{
  QMessageBox mb(this);

  mb.setWindowTitle("Maxit: About");
  mb.setTextFormat(Qt::RichText);
  mb.setText("<html>Maxit Version 1.00.<br>"
	     "Copyright (c) Alexis Megas 2007, 2008.<br><br>"
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
  int i = 0;
  int j = 0;

  if(getViewMode() == VIEW2D)
    {
      for(i = 0; i < NROWS; i++)
	for(j = 0; j < NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(0, 0, 0);
	  else
	    glpieces[i][j]->rotate(0, 0, 0);
    }
  else
    {
      for(i = 0; i < NROWS; i++)
	for(j = 0; j < NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(45 * 64, 45 * 64, -25 * 64);
	  else
	    glpieces[i][j]->rotate(-45 * 64, 45 * 64, 25 * 64);
    }
}

int maxit::getViewMode(void)
{
  if(action_2D->isChecked())
    return VIEW2D;
  else
    return VIEW3D;
}
