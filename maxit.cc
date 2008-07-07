#include "maxit.h"

extern QApplication *qapp;

maxit::maxit(void):QMainWindow()
{
  int suitableH = NROWS * (static_cast<int> (glpiece::CUBE_SIZE - 0.25 *
					     glpiece::CUBE_SIZE));
  QActionGroup *ag = 0;

  setupUi(this);

  try
    {
      ag = new QActionGroup(this);
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  try
    {
      action_2D = new QAction("2D", this);
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  try
    {
      action_3D = new QAction("3D", this);
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
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
  connect(action_Exit, SIGNAL(triggered(void)), qapp, SLOT(quit(void)));
  connect(action_About, SIGNAL(triggered(void)), this, SLOT(slotAbout(void)));
  connect(action_New_Game, SIGNAL(triggered(void)), this,
	  SLOT(slotNewGame(void)));
  connect(action_2D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_3D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));

  try
    {
      qgl = new QGridLayout();
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  qgl->setSpacing(0);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      glpieces[i][j] = 0;

  prepareBoard();
  boardframe->setLayout(qgl);
  boardframe->setFixedSize(suitableH, suitableH);
  setFixedSize(minimumSize());
  show();
}

void maxit::prepareBoard(const bool createPieces)
{
  int value = 0;
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
	  try
	    {
	      glpieces[i][j] = new glpiece
		(0, glpieces[0][0], value, color, i, j);
	    }
	  catch(std::bad_alloc)
	    {
	      std::cerr << "Memory allocation error at line "
			<< __LINE__ << "." << std::endl;
	      exit(EXIT_FAILURE);
	    }
	else
	  glpieces[i][j]->reset(value);

	if(createPieces)
	  qgl->addWidget(glpieces[i][j], i, j);

	qapp->processEvents();
      }
}

void maxit::slotNewGame(void)
{
  playerscore->setText("0");
  opponentscore->setText("0");
  prepareBoard(false);
  resize(minimumSize());
}

bool maxit::isGameOver(void)
{
  bool gameOver = true;

  if(gameOver)
    if(playerscore->text().toInt() > opponentscore->text().toInt())
      QMessageBox::information(this, "Game Over", "You won!");
    else if(playerscore->text().toInt() < opponentscore->text().toInt())
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
  mb.setText("<html>Maxit Version 0.01.<br>"
	     "Copyright (c) Slurpy McMash 2007, 2008.<br><br>"
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

int maxit::getViewMode(void)
{
  if(action_2D->isChecked())
    return VIEW2D;
  else
    return VIEW3D;
}

void maxit::pieceSelected(glpiece *piece)
{
  QString sum1 = "", sum2 = "";

  sum1 = QString::number(playerscore->text().toInt() + abs(piece->value()));
  sum2 = opponentscore->text();

  if(sum1.length() > sum2.length())
    sum2 = sum2.leftJustified(sum1.length(), ' ');
  else if(sum1.length() < sum2.length())
    sum1 = sum1.leftJustified(sum2.length(), ' ');

  playerscore->setText(sum1);
  opponentscore->setText(sum2);

  for(int i = 0; i < NROWS; i++)
    for(int j = 0; j < NCOLS; j++)
      if(i == piece->row() || j == piece->col())
	glpieces[i][j]->setEnabled(true);
      else
	glpieces[i][j]->setEnabled(false);
}
