#include "maxit.h"

maxit::maxit(void):QMainWindow()
{
  int suitableH =
    Global::NROWS * (static_cast<int>
		     (glpiece::CUBE_SIZE - 0.25 * glpiece::CUBE_SIZE));
  QActionGroup *ag1 = 0;
  QActionGroup *ag2 = 0;

  setupUi(this);
#ifdef Q_OS_WIN
  themepath = QDir::current().path() + "\\images.d\\ubuntu.d";
#else
  themepath = QDir::current().path() + "/images.d/ubuntu.d";
#endif
  ag1 = new QActionGroup(this);
  ag2 = new QActionGroup(this);
  action_2D = new QAction(tr("2D"), this);
  action_3D = new QAction(tr("3D"), this);
  action_easy = new QAction(tr("Easy"), this);
  action_normal = new QAction(tr("Normal"), this);
  action_difficult = new QAction(tr("Difficult"), this);
  qgl = new QGridLayout();
  ag1->setExclusive(true);
  ag1->addAction(action_2D);
  ag1->addAction(action_3D);
  ag2->addAction(action_easy);
  ag2->addAction(action_normal);
  ag2->addAction(action_difficult);
  menu_View->addAction(action_2D);
  menu_View->addAction(action_3D);
  menu_Difficulty->addAction(action_easy);
  menu_Difficulty->addAction(action_normal);
  menu_Difficulty->addAction(action_difficult);
  action_2D->setCheckable(true);
  action_3D->setCheckable(true);
  action_2D->setChecked(true);
  action_easy->setCheckable(true);
  action_normal->setCheckable(true);
  action_difficult->setCheckable(true);
  action_easy->setChecked(true);
  connect(action_Exit, SIGNAL(triggered(void)), Global::qapp,
	  SLOT(quit(void)));
  connect(action_About, SIGNAL(triggered(void)), this, SLOT(slotAbout(void)));
  connect(action_New_Game, SIGNAL(triggered(void)), this,
	  SLOT(slotNewGame(void)));
  connect(action_2D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_3D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_Select_Theme, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeTheme(void)));
  connect(action_easy, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeDifficulty(void)));
  connect(action_normal, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeDifficulty(void)));
  connect(action_difficult, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeDifficulty(void)));
  connect(action_Instructions, SIGNAL(triggered(void)), this,
	  SLOT(slotInstructions(void)));
  connect(action_Show_Hint, SIGNAL(triggered(void)), this,
	  SLOT(slotShowHint(void)));
  qgl->setSpacing(1);

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      glpieces[i][j] = 0;

  prepareBoard();
  boardframe->setLayout(qgl);
  boardframe->setMinimumSize(suitableH, suitableH);
  resize(boardframe->size());
  show();
}

void maxit::prepareBoard(const bool createPieces)
{
  int i = 0;
  int j = 0;
  int side = glpiece::CUBE_SIZE;
  int value = 0;
  int difficulty = 0;
  QColor color = QColor(133, 99, 99);
  QMap<QString, short> map;

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(action_easy->isChecked())
    difficulty = 7;
  else if(action_normal->isChecked())
    difficulty = 3;
  else
    difficulty = 2;

  if(!createPieces)
    for(i = 0; i < Global::NROWS; i++)
      for(j = 0; j < Global::NCOLS; j++)
	glpieces[i][j]->setEnabled(true);

  while(map.size() < Global::NROWS * Global::NCOLS)
    {
      i = qrand() % Global::NROWS;
      j = qrand() % Global::NCOLS;

      if(map.contains(QString("%1,%2").arg(i).arg(j)))
	continue;
      else
	map[QString("%1,%2").arg(i).arg(j)] = 0;

      value = qrand() % (Global::NROWS * Global::NROWS);

      if(value == 0)
	value += 1;
      else if(value > (Global::NROWS * Global::NROWS))
	value = value / 2;

      if(qrand() % difficulty == 0)
	value = -value;

      if(createPieces && !glpieces[i][j])
	{
	  if((i + j) % 2 == 0)
	    glpieces[i][j] = new glpiece
	      (0, glpieces[0][0], value, color, i, j, side, -25 * 64);
	  else
	    glpieces[i][j] = new glpiece
	      (0, glpieces[0][0], value, color, i, j, side, 25 * 64);
	}
      else
	glpieces[i][j]->reset(value);

      if(createPieces)
	qgl->addWidget(glpieces[i][j], i, j);

      Global::qapp->processEvents();
    }

  map.clear();
  Global::qapp->restoreOverrideCursor();
}

void maxit::slotNewGame(void)
{
  playerscore->setText(tr("0"));
  opponentscore->setText(tr("0"));
  prepareBoard(false);
}

void maxit::slotAbout(void)
{
  QMessageBox mb(this);

  mb.setWindowTitle(tr("Maxit: About"));
  mb.setTextFormat(Qt::RichText);
  mb.setText(tr("<html>Maxit Version 0.03.<br>"
		"Copyright (c) Slurpy McNash 2007, 2008.<br><br>"
		"Please visit "
		"<a href=\"http://maxit.sourceforge.net\">"
		"http://maxit.sourceforge.net</a> for "
		"project information."
		"</html>"));
  mb.setStandardButtons(QMessageBox::Ok);
  mb.exec();
}

void maxit::slotChangeView(void)
{
  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(getViewMode() == VIEW2D)
    {
      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(0, 0, -25 * 64);
	  else
	    glpieces[i][j]->rotate(0, 0, 25 * 64);
    }
  else
    {
      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if((i + j) % 2 == 0)
	    glpieces[i][j]->rotate(45 * 64, 45 * 64, -25 * 64);
	  else
	    glpieces[i][j]->rotate(-45 * 64, 45 * 64, 25 * 64);
    }

  Global::qapp->restoreOverrideCursor();
}

int maxit::getViewMode(void) const
{
  if(action_2D->isChecked())
    return VIEW2D;
  else
    return VIEW3D;
}

bool maxit::isAnimationEnabled(void) const
{
  return action_Animate_Pieces->isChecked();
}

void maxit::pieceSelected(glpiece *piece)
{
  int board[Global::NROWS][Global::NCOLS];
  bool gameover = true;
  QMap<QString, int> move;

  Global::qapp->setOverrideCursor(Qt::WaitCursor);
  playerscore->setText(QString::number(playerscore->text().toInt() +
				       piece->value()));
  Global::qapp->processEvents();
  piece->setValue(0);
  statusBar()->showMessage(tr("Analyzing..."));

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      {
	glpieces[i][j]->setEnabled(false);
	board[i][j] = glpieces[i][j]->value();  
      }

  computer cmptr(board, playerscore->text().toInt(),
		 opponentscore->text().toInt());
  move = cmptr.getMove(piece->row(), piece->col());
  statusBar()->clearMessage();

  if(move["row"] > -1)
    {
      computerlastpiece = glpieces[move["row"]][move["col"]];
      opponentscore->setText
	(QString::number(opponentscore->text().toInt() +
			 computerlastpiece->value()));
      computerlastpiece->select();
      computerlastpiece->setValue(0);

      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if(i == move["row"] || j == move["col"])
	    glpieces[i][j]->setEnabled(true);
	  else
	    glpieces[i][j]->setEnabled(false);

      for(int i = 0; i < Global::NROWS && gameover; i++)
	for(int j = 0; j < Global::NCOLS && gameover; j++)
	  if(i == move["row"] || j == move["col"])
	    if(glpieces[i][j]->value() > 0)
	      gameover = false;
    }

  move.clear();
  Global::qapp->restoreOverrideCursor();

  if(gameover)
    {
      for(int i = 0; i < Global::NROWS && gameover; i++)
	for(int j = 0; j < Global::NCOLS && gameover; j++)
	  glpieces[i][j]->setEnabled(false);

      if(playerscore->text().toInt() > opponentscore->text().toInt())
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("Congratulations, you won!"));
      else if(playerscore->text().toInt() < opponentscore->text().toInt())
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("I'm sorry, but you lost!"));
      else
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("Congratulations, it's a tie!"));
    }
}

void maxit::slotChangeTheme(void)
{
  QString tmpstr("");
  QString startpath("");

#ifdef Q_OS_WIN
  startpath = "\\images.d";
#else
  startpath = "/images.d";
#endif

  if(!(tmpstr = QFileDialog::getExistingDirectory
       (this,
	tr("Maxit: Theme Selection"),
	QDir::current().path() + startpath)).isEmpty())
    {
      Global::qapp->setOverrideCursor(Qt::WaitCursor);
      themepath = tmpstr;

      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  glpieces[i][j]->updateGL();

      Global::qapp->restoreOverrideCursor();
    }
}

QString maxit::themedir(void)
{
  return themepath;
}

void maxit::slotInstructions(void)
{
  QMessageBox mb(this);

  mb.setWindowTitle(tr("Maxit: Instructions"));
  mb.setTextFormat(Qt::RichText);
  mb.setText(tr("<ul>"
		"<li>The first player must initiate the game.</li>"
		"<li>A player may only select a piece that is located "
		"in the same column or row as the previously-selected "
		"piece.</li>"
		"<li>The game ends when all of the pieces have been "
		"selected or when there are no pieces to select in accordance "
		"with the second rule.</li>"
		"<li>The player with the highest score wins.</li>"
		"</ul>"));
  mb.setStandardButtons(QMessageBox::Ok);
  mb.exec();
}

void maxit::slotChangeDifficulty(void)
{
  int value = 0;
  int difficulty = 0;

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(action_easy->isChecked())
    difficulty = 7;
  else if(action_normal->isChecked())
    difficulty = 3;
  else
    difficulty = 2;

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      if(glpieces[i][j]->value() > 0)
	{
	  value = qrand() % (Global::NROWS * Global::NROWS);

	  if(value == 0)
	    value += 1;
	  else if(value > (Global::NROWS * Global::NROWS))
	    value = value / 2;

	  if(qrand() % difficulty == 0)
	    value = -value;

	  glpieces[i][j]->setValue(value);
	  Global::qapp->processEvents();
	}

  Global::qapp->restoreOverrideCursor();
}

void maxit::slotShowHint(void)
{
  int I = -1;
  int J = -1;
  int max = 0;
  int board[Global::NROWS][Global::NCOLS];
  QMap<QString, int> move;

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(playerscore->text() == "0")
    {
      /*
      ** Find the piece with the greatest value.
      */

      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if(glpieces[i][j]->value() > max)
	    {
	      I = i;
	      J = j;
	      max = glpieces[i][j]->value();
	    }
    }
  else
    {
      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  board[i][j] = glpieces[i][j]->value();  

      computer hint(board, playerscore->text().toInt(),
		    opponentscore->text().toInt());
      move = hint.getMove(computerlastpiece->row(), computerlastpiece->col());

      if(move["row"] > -1)
	{
	  I = move["row"];
	  J = move["col"];
	}

      move.clear();
    }

  if(I > -1)
    glpieces[I][J]->hintMe();

  Global::qapp->restoreOverrideCursor();
}
