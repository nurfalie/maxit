#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void):QMainWindow()
{
  int i = 0;
  int j = 0;
  int value = 1;
  int suitableH =
    NROWS * ((int) (glpiece::CUBE_SIZE - 0.25 * glpiece::CUBE_SIZE));
  QColor color;
  QGridLayout *qgl = NULL;

  setupUi(this);
  connect((QObject *) action_Exit, SIGNAL(triggered(void)),
	  qapp, SLOT(quit(void)));
  connect((QObject *) action_About, SIGNAL(triggered(void)),
	  this, SLOT(slotAbout(void)));
  connect((QObject *) action_New_Game, SIGNAL(triggered(void)),
	  this, SLOT(slotNewGame(void)));

  /*
  ** Create the board.
  */

  if((qgl = new QGridLayout()) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  qgl->setSpacing(0);
  glpieces[0][0] = NULL;

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

	if((i + j ) % 2 == 0)
	  color = QColor(255, 255, 224);
	else
	  color = QColor(238, 221, 130);

	glpieces[i][j] = new glpiece(NULL, glpieces[0][0], value, color,
				     glpiece::CUBE_SIZE);

	if((i + j) % 2 == 0)
	  glpieces[i][j]->rotateBy(45 * 64, 45 * 64, -25 * 64);
	else
	  glpieces[i][j]->rotateBy(-45 * 64, 45 * 64, 25 * 64);

	qgl->addWidget(glpieces[i][j], i, j);
      }

  boardframe->setLayout(qgl);
  boardframe->setFixedSize(suitableH, suitableH);
  show();
}

void maxit::slotNewGame(void)
{
  playerscore->display("0");
  opponentscore->display("0");
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
