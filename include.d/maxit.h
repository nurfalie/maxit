#ifndef _MAXIT_
#define _MAXIT_

/*
** -- C Includes --
*/

#include <math.h>

/*
** -- C++ Includes --
*/

#include <iostream>

/*
** -- Qt Includes --
*/

#include <QMainWindow>
#include <QMessageBox>

/*
** -- Local Includes --
*/

#include "common.h"
#include "glpiece.h"
#include "computer.h"
#include "ui_maxit.h"

class maxit: public QMainWindow, private Ui::maxit_window
{
  Q_OBJECT

 public:
  enum
    {
      VIEW2D = 0,
      VIEW3D = 1
    };
  maxit(void);
  int getViewMode(void) const;
  int getViewSize(void) const;
  bool animatePieces(void) const;
  void pieceSelected(glpiece *);
  QString themedir(void) const;

 private:
  glpiece *glpieces[Global::NROWS][Global::NCOLS];
  QAction *action_2D;
  QAction *action_3D;
  QString themepath;
  computer *computerptr;
  QGridLayout *qgl;
  void prepareBoard(const bool = true);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
  void slotChangeView(void);
  void slotChangeTheme(void);
};

#endif
