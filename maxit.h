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

#include "ui_maxit.h"
#include "gui_board.h"

class maxit: public QMainWindow, private Ui::maxit_window
{
  Q_OBJECT

 public:
  maxit(void);
  static const int NCOLS = 9;
  static const int NROWS = 9;

 private:
  int board[NROWS][NCOLS];
  gui_board *glboard;
  bool isGameOver(void);
  void easyMove(const int, const int);
  void computerTurn(const int, const int);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
};

#endif
