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
#include <QToolButton>

/*
** -- Local Includes --
*/

#include "ui_maxit.h"

class maxit: public QMainWindow
{
  Q_OBJECT

 public:
  maxit(void);
  static const int NCOLS = 9;
  static const int NROWS = 9;

 private:
  int board[NROWS][NCOLS];
  QToolButton *buttons[NROWS][NCOLS];
  Ui_MaxitMainWindow maxit_board;
  bool isGameOver(const int, const int);
  void easyMove(const int, const int);
  void computerTurn(const int, const int);
  void selectButton(QToolButton *);
  void addToolButtons(void);
  QToolButton *selectRandom(void);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
  void slotButtonPressed(void);
};

#endif
