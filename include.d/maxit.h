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
  static const int NCOLS = 6;
  static const int NROWS = 6;
  maxit(void);

 private:
  glpiece *glpieces[NROWS][NCOLS];
  bool isGameOver(void);
  void easyMove(const int, const int);
  void computerTurn(const int, const int);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
};

#endif
