#include "maxit.h"

maxit::maxit(void):QMainWindow()
{
  int suitableH =
    Global::NROWS * (static_cast<int>
		     (glpiece::CUBE_SIZE - 0.25 * glpiece::CUBE_SIZE));
  QActionGroup *ag1 = 0;

  setupUi(this);

#ifdef Q_OS_WIN
  themepath = QDir::current().path() + "\images.d\ubuntu.d";
#else
  themepath = QDir::current().path() + "/images.d/ubuntu.d";
#endif
  computerptr = new computer();
  ag1 = new QActionGroup(this);
  action_2D = new QAction(tr("2D"), this);
  action_3D = new QAction(tr("3D"), this);
  qgl = new QGridLayout();
  ag1->setExclusive(true);
  ag1->addAction(action_2D);
  ag1->addAction(action_3D);
  menu_View->addAction(action_2D);
  menu_View->addAction(action_3D);
  action_2D->setCheckable(true);
  action_3D->setCheckable(true);
  action_2D->setChecked(true);
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
  connect(action_Instructions, SIGNAL(triggered(void)), this,
	  SLOT(slotInstructions(void)));
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
  int board[Global::NROWS][Global::NCOLS];
  QColor color = QColor(133, 99, 99);
  QMap<QString, short> map;

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

      if(qrand() % 3 == 0)
	value = -value;

      if(createPieces)
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
      board[i][j] = abs(value);
    }

  map.clear();
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
  mb.setText(tr("<html>Maxit Version 0.01.<br>"
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
}

int maxit::getViewMode(void) const
{
  if(action_2D->isChecked())
    return VIEW2D;
  else
    return VIEW3D;
}

bool maxit::animatePieces(void) const
{
  return action_Animate_Pieces->isChecked();
}

void maxit::pieceSelected(glpiece *piece)
{
  int board[Global::NROWS][Global::NCOLS];
  QMap<QString, int> move;

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

  computerptr->updateBoard(board, playerscore->text().toInt(),
			   opponentscore->text().toInt());
  Global::qapp->setOverrideCursor(Qt::WaitCursor);
  move = computerptr->computeMove(piece->row(), piece->col());
  Global::qapp->restoreOverrideCursor();
  statusBar()->clearMessage();

  if(move["row"] > -1 && move["col"] > -1)
    {
      opponentscore->setText
	(QString::number(opponentscore->text().toInt() +
			 glpieces[move["row"]][move["col"]]->value()));
      computerptr->updateBoard(move["row"], move["col"],
			       playerscore->text().toInt(),
			       opponentscore->text().toInt());
      glpieces[move["row"]][move["col"]]->select();
      glpieces[move["row"]][move["col"]]->setValue(0);

      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if(i == move["row"] || j == move["col"])
	    glpieces[i][j]->setEnabled(true);
	  else
	    glpieces[i][j]->setEnabled(false);
    }
  else if(playerscore->text().toInt() > opponentscore->text().toInt())
    QMessageBox::information(this, tr("Maxit: Game Over"),
			     tr("You have won!"));
  else if(playerscore->text().toInt() < opponentscore->text().toInt())
    QMessageBox::information(this, tr("Maxit: Game Over"),
			     tr("Your opponent has won!"));
  else
    QMessageBox::information(this, tr("Maxit: Game Over"),
			     tr("The game resulted in a tie!"));
}

void maxit::slotChangeTheme(void)
{
  QString tmpstr = "";
  QString startpath = "";

#ifdef Q_OS_WIN
  startpath = "\images.d";
#else
  startpath = "/images.d";
#endif

  if(!(tmpstr = QFileDialog::getExistingDirectory
       (this,
	tr("Select Theme"),
	QDir::current().path() + startpath)).isEmpty())
    {
      themepath = tmpstr;

      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  glpieces[i][j]->updateGL();
    }
}

QString maxit::themedir(void) const
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
