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
#include "ui_maxit.h"

class maxit: public QMainWindow, private Ui::maxit_window
{
  Q_OBJECT

 public:
  static const int NCOLS = 7;
  static const int NROWS = 7;
  static const int VIEW2D = 0;
  static const int VIEW3D = 1;
  static const int SMALLVIEW = 0;
  static const int NORMALVIEW = 1;
  maxit(void);
  int getViewMode(void);
  int getViewSize(void);
  void pieceSelected(glpiece *);

 private:
  glpiece *glpieces[NROWS][NCOLS];
  QAction *action_2D;
  QAction *action_3D;
  QAction *smallSize;
  QAction *normalSize;
  QGridLayout *qgl;
  bool isGameOver(void);
  void prepareBoard(const bool = true);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
  void slotChangeSize(void);
  void slotChangeView(void);
};

#endif
