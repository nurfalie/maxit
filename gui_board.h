#ifndef _GUI_BOARD_
#define _GUI_BOARD_

/*
** -- Qt Includes --
*/

#include <QEvent>
#include <QtOpenGL>
#include <QMouseEvent>

/*
** -- Class(es) --
*/

class gui_board: public QGLWidget
{
 public:

  /*
  ** -- Members --
  */

  /*
  ** -- Methods --
  */

  gui_board(QWidget *);
  void mousePressEvent(QMouseEvent *);
  virtual void paintGL(void);
  virtual void initializeGL(void);
  virtual void resizeGL(int, int);
};

#endif
