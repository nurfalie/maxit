#include "maxit.h"

maxit::maxit(void):QMainWindow()
{
  computerlastpiece = 0;
  size = 4;

  QActionGroup *ag1 = 0;
  QActionGroup *ag2 = 0;
  QActionGroup *ag3 = 0;
  int suitableH =
    size * (static_cast<int> (glpiece::CUBE_SIZE -
			      0.25 * glpiece::CUBE_SIZE));

  setupUi(this);
#ifdef Q_OS_WIN
  themepath = QDir::currentPath() + "\\Images\\ubuntu.d\\";
#else
  themepath = QDir::currentPath() + "/Images/ubuntu.d/";
#endif
  ag1 = new QActionGroup(this);
  ag2 = new QActionGroup(this);
  ag3 = new QActionGroup(this);
  action_2D = new QAction(tr("2D"), this);
  action_3D = new QAction(tr("3D"), this);
  action_easy = new QAction(tr("Easy"), this);
  action_normal = new QAction(tr("Normal"), this);
  action_difficult = new QAction(tr("Difficult"), this);
  action_4x4 = new QAction(tr("4x4"), this);
  action_5x5 = new QAction(tr("5x5"), this);
  action_6x6 = new QAction(tr("6x6"), this);
  action_7x7 = new QAction(tr("7x7"), this);
  qgl = new QGridLayout();
  ag1->setExclusive(true);
  ag1->addAction(action_2D);
  ag1->addAction(action_3D);
  ag2->addAction(action_easy);
  ag2->addAction(action_normal);
  ag2->addAction(action_difficult);
  ag3->addAction(action_4x4);
  ag3->addAction(action_5x5);
  ag3->addAction(action_6x6);
  ag3->addAction(action_7x7);
  menu_View->addAction(action_2D);
  menu_View->addAction(action_3D);
  menu_View->addSeparator();
  menu_View->addAction(action_4x4);
  menu_View->addAction(action_5x5);
  menu_View->addAction(action_6x6);
  menu_View->addAction(action_7x7);
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
  action_4x4->setCheckable(true);
  action_5x5->setCheckable(true);
  action_6x6->setCheckable(true);
  action_7x7->setCheckable(true);
  action_4x4->setChecked(true);
  connect(action_Exit, SIGNAL(triggered(void)), Global::qapp,
	  SLOT(quit(void)));
  connect(action_About, SIGNAL(triggered(void)), this, SLOT(slotAbout(void)));
  connect(action_New_Game, SIGNAL(triggered(void)), this,
	  SLOT(slotNewGame(void)));
  connect(action_2D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_3D, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeView(void)));
  connect(action_4x4, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeSize(void)));
  connect(action_5x5, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeSize(void)));
  connect(action_6x6, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeSize(void)));
  connect(action_7x7, SIGNAL(triggered(void)), this,
	  SLOT(slotChangeSize(void)));
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
  resize(boardframe->minimumSize());
  setWindowIcon(QIcon("Images/maxit.png"));
  show();
  update();
}

void maxit::prepareBoard(const bool createPieces)
{
  QColor color = QColor(133, 99, 99);
  QMap<QString, short> map;
  int difficulty = 0;
  int i = 0;
  int j = 0;
  int side = glpiece::CUBE_SIZE;
  int value = 0;

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
	if(glpieces[i][j])
	  {
	    if(i < size && j < size)
	      {
		glpieces[i][j]->setEnabled(true);
		glpieces[i][j]->setClickable(false);
		glpieces[i][j]->setVisible(true);
	      }
	    else
	      glpieces[i][j]->setVisible(false);
	  }

  while(map.size() < size * size)
    {
      i = qrand() % qMax(1, size);
      j = qrand() % qMax(1, size);

      if(i >= size || j >= size)
	break;

      if(map.contains(QString("%1,%2").arg(i).arg(j)))
	continue;
      else
	map[QString("%1,%2").arg(i).arg(j)] = 0;

      value = qrand() % (size * size);

      if(value == 0)
	value += 1;
      else if(value > (size * size))
	value = value / 2;

      if(qrand() % difficulty == 0)
	value = -value;

      if(!glpieces[i][j])
	{
	  if((i + j) % 2 == 0)
	    glpieces[i][j] = new (std::nothrow) glpiece
	      (0, 0, value, color, i, j, side, -25 * 64);
	  else
	    glpieces[i][j] = new (std::nothrow) glpiece
	      (0, 0, value, color, i, j, side, 25 * 64);

	  if(!glpieces[i][j])
	    {
	      qDebug() << "Memory failure.";
	      continue;
	    }

	  if(getViewMode() == VIEW3D)
	    {
	      if((i + j) % 2 == 0)
		glpieces[i][j]->rotate(45 * 64, 45 * 64, -25 * 64);
	      else
		glpieces[i][j]->rotate(-45 * 64, 45 * 64, 25 * 64);
	    }

	  qgl->addWidget(glpieces[i][j], i, j);
	}
      else
	glpieces[i][j]->reset(value);

      Global::qapp->processEvents();
    }

  for(i = 0; i < size; i++)
    for(j = 0; j < size; j++)
      if(glpieces[i][j])
	glpieces[i][j]->setClickable(true);

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
  mb.setText(tr("<html>Maxit Version 1.05.<br>"
		"Copyright (c) Guess Who, 2007 - present.<br><br>"
		"Please visit "
		"<a href=\"http://maxit.sourceforge.net\">"
		"http://maxit.sourceforge.net</a> for "
		"project information."
		"</html>"));
  mb.setStandardButtons(QMessageBox::Ok);
  mb.exec();
}

void maxit::slotChangeSize(void)
{
  if(action_4x4->isChecked())
    size = 4;
  else if(action_5x5->isChecked())
    size = 5;
  else if(action_6x6->isChecked())
    size = 6;
  else
    size = 7;

  int suitableH = size * (static_cast<int> (glpiece::CUBE_SIZE - 0.25 *
					    glpiece::CUBE_SIZE));

  centralwidget->setVisible(false);
  slotNewGame();
  boardframe->setMinimumSize(suitableH, suitableH);
  centralwidget->setVisible(true);
  resize(boardframe->minimumSize());
  update();
}

void maxit::slotChangeView(void)
{
  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(getViewMode() == VIEW2D)
    {
      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if(glpieces[i][j])
	    {
	      if((i + j) % 2 == 0)
		glpieces[i][j]->rotate(0, 0, -25 * 64);
	      else
		glpieces[i][j]->rotate(0, 0, 25 * 64);
	    }
    }
  else
    {
      for(int i = 0; i < Global::NROWS; i++)
	for(int j = 0; j < Global::NCOLS; j++)
	  if(glpieces[i][j])
	    {
	      if((i + j) % 2 == 0)
		glpieces[i][j]->rotate(45 * 64, 45 * 64, -25 * 64);
	      else
		glpieces[i][j]->rotate(-45 * 64, 45 * 64, 25 * 64);
	    }
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
  QMap<QString, int> move;
  bool gameover = true;
  int board[Global::NROWS][Global::NCOLS];

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(piece)
    playerscore->setText(QString::number(playerscore->text().toInt() +
					 piece->value()));
  else
    playerscore->setText("0");

  Global::qapp->processEvents();

  if(piece)
    piece->setValue(0);

  statusBar()->showMessage(tr("Analyzing..."));

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      if(glpieces[i][j])
	{
	  glpieces[i][j]->setEnabled(false);
	  board[i][j] = glpieces[i][j]->value();
	}
      else
	board[i][j] = 0;

  computer cmptr(board, size, playerscore->text().toInt(),
		 opponentscore->text().toInt());

  if(piece)
    move = cmptr.getMove(piece->row(), piece->col());
  else
    move["row"] = move["col"] = -1;

  statusBar()->clearMessage();

  if(move["row"] > -1 && move["row"] < size &&
     move["col"] > -1 && move["col"] < size)
    {
      computerlastpiece = glpieces[move["row"]][move["col"]];

      if(computerlastpiece)
	opponentscore->setText
	  (QString::number(opponentscore->text().toInt() +
			   computerlastpiece->value()));
      else
	opponentscore->setText("0");

      Global::qapp->processEvents();

      if(computerlastpiece)
	{
	  computerlastpiece->select();
	  computerlastpiece->setValue(0);
	}

      for(int i = 0; i < size; i++)
	for(int j = 0; j < size; j++)
	  if(glpieces[i][j])
	    {
	      if(i == move["row"] || j == move["col"])
		{
		  if(glpieces[i][j]->value() > 0)
		    gameover = false;

		  glpieces[i][j]->setEnabled(true);
		}
	      else
		glpieces[i][j]->setEnabled(false);
	    }
    }

  move.clear();
  Global::qapp->restoreOverrideCursor();

  if(gameover)
    {
      for(int i = 0; i < size; i++)
	for(int j = 0; j < size; j++)
	  if(glpieces[i][j])
	    glpieces[i][j]->setEnabled(false);

      if(playerscore->text().toInt() > opponentscore->text().toInt())
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("Congratulations, you won!"));
      else if(playerscore->text().toInt() < opponentscore->text().toInt())
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("I'm sorry, but you lost! "
				    "Please play again."));
      else
	QMessageBox::information(this, tr("Maxit: Game Over"),
				 tr("Congratulations, it's a tie!"));
    }
}

void maxit::slotChangeTheme(void)
{
  QString startpath("");
  QString tmpstr("");

#ifdef Q_OS_WIN
  startpath = "\\Images\\";
#else
  startpath = "/Images/";
#endif

  if(!(tmpstr = QFileDialog::getExistingDirectory
       (this,
	tr("Maxit: Theme Selection"),
	QDir::current().path() + startpath)).isEmpty() &&
     tmpstr != (QDir::current().path() + startpath))
    {
      Global::qapp->setOverrideCursor(Qt::WaitCursor);
      themepath = tmpstr;

      for(int i = 0; i < size; i++)
	for(int j = 0; j < size; j++)
	  if(glpieces[i][j])
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
  QMessageBox *mb = findChild<QMessageBox *> ("instructions");

  if(!mb)
    mb = new QMessageBox(this);

  mb->setObjectName("instructions");
  mb->setWindowModality(Qt::NonModal);
  mb->setWindowTitle(tr("Maxit: Instructions"));
  mb->setTextFormat(Qt::RichText);
  mb->setText(tr("<ul>"
		"<li>A player may only select a piece that is located "
		"in the same column or row as the previously-selected "
		"piece.</li>"
		"<li>The game ends when all of the pieces have been "
		"selected or when all of the pieces for a given column "
		"and row are exhausted.</li>"
		"<li>The player with the highest score wins.</li>"
		"</ul>"));
  mb->setStandardButtons(QMessageBox::Ok);
  mb->show();
}

void maxit::slotChangeDifficulty(void)
{
  int difficulty = 0;
  int value = 0;

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  if(action_easy->isChecked())
    difficulty = 7;
  else if(action_normal->isChecked())
    difficulty = 3;
  else
    difficulty = 2;

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      if(glpieces[i][j] && glpieces[i][j]->value() > 0)
	{
	  value = qrand() % qMax(1, size * size);

	  if(value == 0)
	    value += 1;
	  else if(value > (size * size))
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
  QMap<QString, int> move;
  int I = -1;
  int J = -1;
  int board[Global::NROWS][Global::NCOLS];

  Global::qapp->setOverrideCursor(Qt::WaitCursor);

  for(int i = 0; i < Global::NROWS; i++)
    for(int j = 0; j < Global::NCOLS; j++)
      board[i][j] = 0;

  if(playerscore->text() == "0")
    {
      int max = 0;

      /*
      ** Find the piece with the greatest value.
      */

      for(int i = 0; i < size; i++)
	for(int j = 0; j < size; j++)
	  if(glpieces[i][j])
	    {
	      glpieces[i][j]->resetBackground();

	      if(glpieces[i][j]->value() > max)
		{
		  I = i;
		  J = j;
		  max = glpieces[i][j]->value();
		}
	    }
    }
  else
    {
      for(int i = 0; i < size; i++)
	for(int j = 0; j < size; j++)
	  if(glpieces[i][j])
	    board[i][j] = glpieces[i][j]->value();

      computer hint(board, size, playerscore->text().toInt(),
		    opponentscore->text().toInt());

      if(computerlastpiece)
	move = hint.getMove(computerlastpiece->row(), computerlastpiece->col());
      else
	move["row"] = move["col"] = -1;

      if(move["row"] > -1)
	{
	  I = move["row"];
	  J = move["col"];
	}

      move.clear();
    }

  if(I > -1 && I < size && J > -1 && J < size)
    if(glpieces[I][J])
      glpieces[I][J]->hintMe();

  Global::qapp->restoreOverrideCursor();
}
