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

#include "glpiece.h"
#include "computer.h"
#include "ui_maxit.h"

class maxit: public QMainWindow, private Ui::maxit_window
{
  Q_OBJECT

 public:
  static const int NCOLS = 7;
  static const int NROWS = 7;
  static const int VIEW2D = 0;
  static const int VIEW3D = 1;
  maxit(void);
  int getViewMode(void) const;
  int getViewSize(void) const;
  void pieceSelected(glpiece *);

 private:
  glpiece *glpieces[NROWS][NCOLS];
  QAction *action_2D;
  QAction *action_3D;
  computer *computerptr;
  QGridLayout *qgl;
  bool isGameOver(void) const;
  void prepareBoard(const bool = true);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
  void slotChangeView(void);
};

#endif
