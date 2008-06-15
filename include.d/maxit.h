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
using namespace std;

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
  maxit(void);

 private:
  glpiece *glpieces[NROWS][NCOLS];
  bool isGameOver(void);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
};

#endif
