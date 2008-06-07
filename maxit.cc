#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void)
{
  maxit_board.setupUi(this);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      buttons[i][j] = NULL;

  addToolButtons();
  connect(maxit_board.action_Exit, SIGNAL(activated(void)),
	  qapp, SLOT(quit(void)));
  connect(maxit_board.action_About, SIGNAL(activated(void)),
	  this, SLOT(slotAbout(void)));
  connect(maxit_board.action_New_Game, SIGNAL(activated(void)),
	  this, SLOT(slotNewGame(void)));
  show();
}

void maxit::addToolButtons(void)
{
  QFont font("Courier", 20);
  QString number = "";

  ((QGridLayout *) maxit_board.mainframe->layout())->setSpacing(0);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      if(buttons[i][j] == NULL)
	if((buttons[i][j] = new QToolButton()) == NULL)
	  {
	    cerr << "Memory allocation error at line " << __LINE__
		 << "." << endl;
	    exit(EXIT_FAILURE);
	  }
	else
	  {
	    connect(buttons[i][j], SIGNAL(clicked(void)), this,
		    SLOT(slotButtonPressed(void)));
	    buttons[i][j]->setFont(font);
	    buttons[i][j]->setCheckable(true);
	    ((QGridLayout *) maxit_board.mainframe->layout())->addWidget
	      (buttons[i][j], i, j, Qt::AlignCenter);
	  }

  slotNewGame();

  /*
  ** Randomly select a position.
  */

  selectButton(selectRandom());
}

void maxit::slotNewGame(void)
{
  QFont font("Courier", 20, false);
  QString number = "";

  maxit_board.playerscore->display("0");
  maxit_board.computerscore->display("0");

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      {
	buttons[i][j]->setFont(font);
	number = QString("%1").arg
	  (QString::number(((qrand() % NROWS) * NROWS + 1) *
			   pow(-1, qrand() % 2)), 3);
	buttons[i][j]->setText(number);
	buttons[i][j]->setMinimumSize(buttons[i][j]->sizeHint().width(),
				      buttons[i][j]->sizeHint().width());
      }

  /*
  ** Randomly select a position.
  */

  selectButton(selectRandom());
}

void maxit::selectButton(QToolButton *button)
{
  int I = 0;
  int J = 0;
  QFont font("Courier", 20);

  if(button != NULL)
    {
      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NCOLS; j++)
	  if(buttons[i][j] == button)
	    {
	      I = i;
	      J = j;
	      goto done_label;
	    }

    done_label:

      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NROWS; j++)
	  if(i != I && j != J)
	    {
	      buttons[i][j]->setEnabled(false);
	      font.setBold(false);
	      font.setPointSize(15);
	      buttons[i][j]->setFont(font);
	      buttons[i][j]->setChecked(true);
	    }
	  else
	    {
	      if(!buttons[i][j]->text().isEmpty())
		buttons[i][j]->setEnabled(true);

	      buttons[i][j]->setChecked(false);
	      font.setBold(true);
	      font.setPointSize(20);
	      buttons[i][j]->setFont(font);
	    }
    }
}

bool maxit::isGameOver(const int I, const int J)
{
  bool gameOver = true;

  for(int i = 0; i < NROWS; i++)
    {
      if(buttons[I][i]->text().toInt() != 0)
	gameOver = false;

      if(buttons[i][J]->text().toInt() != 0)
	gameOver = false;

      if(!gameOver)
	break;
    }

  if(gameOver)
    if(maxit_board.playerscore->intValue() >
       maxit_board.computerscore->intValue())
      QMessageBox::information(this, "Game Over", "You won!");
    else if(maxit_board.playerscore->intValue() <
	    maxit_board.computerscore->intValue())
      QMessageBox::information(this, "Game Over", "The computer won!");
    else
      QMessageBox::information(this, "Game Over", "A tie!");

  return gameOver;
}

QToolButton *maxit::selectRandom(void)
{
  return buttons[qrand() % NROWS][qrand() % NCOLS];
}

void maxit::slotButtonPressed(void)
{
  int I = 0;
  int J = 0;
  QToolButton *button = qobject_cast<QToolButton *>(sender());

  if(button != NULL)
    {
      maxit_board.playerscore->display
	(maxit_board.playerscore->intValue() + button->text().toInt());
      button->setText("");
      button->setEnabled(false);

      for(int i = 0; i < NROWS; i++)
	for(int j = 0; j < NCOLS; j++)
	  if(button == buttons[i][j])
	    {
	      I = i;
	      J = j;
	      goto done_label;
	    }

    done_label:

      if(!isGameOver(I, J))
	computerTurn(I, J);
    }
}

void maxit::slotAbout(void)
{
  QMessageBox::information(this, "About",
			   "Maxit Version 1.00.\n"
			   "Copyright (c) Diana Megas 2007.\n\n"
			   "For more information, please visit "
			   "http:://maxit.sourceforge.net.");
}

void maxit::computerTurn(const int I, const int J)
{
  if(maxit_board.action_Easy->isChecked())
    easyMove(I, J);
}

void maxit::easyMove(const int I, const int J)
{
  int c = 0;
  int r = 0;
  int max = 0;

  for(int i = 0; i < NROWS; i++)
    {
      if(buttons[I][i]->text().toInt() > max)
	{
	  max = buttons[I][i]->text().toInt();
	  r = I;
	  c = i;
	}

      if(buttons[i][J]->text().toInt() > max)
	{
	  max = buttons[i][J]->text().toInt();
	  r = i;
	  c = J;
	}
    }

  maxit_board.computerscore->display
    (maxit_board.computerscore->intValue() + buttons[r][c]->text().toInt());
  buttons[r][c]->setText("");
  buttons[r][c]->setEnabled(false);
  selectButton(buttons[r][c]);
}
