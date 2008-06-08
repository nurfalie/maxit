#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void):QMainWindow()
{
  setupUi(this);
  connect((QObject *) action_Exit, SIGNAL(activated(void)),
	  qapp, SLOT(quit(void)));
  connect((QObject *) action_About, SIGNAL(activated(void)),
	  this, SLOT(slotAbout(void)));
  connect((QObject *) action_New_Game, SIGNAL(activated(void)),
	  this, SLOT(slotNewGame(void)));

  if((glboard = new gui_board(mainframe)) == NULL)
    {
      cerr << "Memory allocation error at line " << __LINE__ << "." << endl;
      exit(EXIT_FAILURE);
    }

  glboard->resize(800, 800);
  mainframe->setFixedSize(glboard->size());
  show();
}

void maxit::slotNewGame(void)
{
  QFont font("Courier", 20, false);
  QString number = "";

  playerscore->display("0");
  opponentscore->display("0");

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      {
      }
}

bool maxit::isGameOver(void)
{
  bool gameOver = true;

  for(int i = 0; i < NROWS; i++)
    {
      if(!gameOver)
	break;
    }

  if(gameOver)
    if(playerscore->intValue() >
       opponentscore->intValue())
      QMessageBox::information(this, "Game Over", "You won!");
    else if(playerscore->intValue() <
	    opponentscore->intValue())
      QMessageBox::information(this, "Game Over", "The computer won!");
    else
      QMessageBox::information(this, "Game Over", "A tie!");

  return gameOver;
}

void maxit::slotAbout(void)
{
  QMessageBox mb(this);

  mb.setWindowTitle("Maximus: About");
  mb.setTextFormat(Qt::RichText);
  mb.setText("<html>Maximus Version 1.00.<br>"
	     "Copyright (c) Alexis Megas 2007, 2008.<br><br>"
	     "Please visit "
	     "<a href=\"http://maxit.sourceforge.net\">"
	     "http://maxit.sourceforge.net</a> for "
	     "project information."
	     "</html>");
  mb.setStandardButtons(QMessageBox::Ok);
  mb.exec();
}

void maxit::computerTurn(const int I, const int J)
{
  if(action_Easy->isChecked())
    easyMove(I, J);
}

void maxit::easyMove(const int I, const int J)
{
  (void) I;
  (void) J;

  for(int i = 0; i < NROWS; i++)
    {
    }
}
