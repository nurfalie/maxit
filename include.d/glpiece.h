#ifndef _GLPIECE_
#define _GLPIECE_

/*
** -- C++ Includes --
*/

#include <iostream>
using namespace std;

/*
** -- Qt Includes --
*/

#include <QEvent>
#include <QtOpenGL>
#include <QMouseEvent>

/*
** -- Class(es) --
*/

class glpiece: public QGLWidget
{
 public:

  /*
  ** -- Members --
  */

  /*
  ** -- Methods --
  */

  glpiece(QWidget *);
  void paintGL(void);
  void resizeGL(int, int);
  void initializeGL(void);
  void mousePressEvent(QMouseEvent *);

 private:
  int xRot;
  int yRot;
  int zRot;
  GLuint board;
  QColor clearColor;
  void createPiece(void);
};

#endif
