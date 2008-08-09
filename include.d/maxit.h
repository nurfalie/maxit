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
  static QString themedir(void);

 private:
  glpiece *glpieces[Global::NROWS][Global::NCOLS];
  QAction *action_2D;
  QAction *action_3D;
  QAction *action_easy;
  QAction *action_normal;
  QAction *action_difficult;
  computer *computerptr;
  QGridLayout *qgl;
  static QString themepath;
  void prepareBoard(const bool = true);

 private slots:
  void slotAbout(void);
  void slotNewGame(void);
  void slotChangeView(void);
  void slotChangeTheme(void);
  void slotInstructions(void);
};

#endif
