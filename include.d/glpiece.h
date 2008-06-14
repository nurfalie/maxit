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

  glpiece(QWidget *, glpiece *, const int, const QColor &);
  ~glpiece();
  void paintGL(void);
  void resizeGL(int, int);
  void rotateBy(const int, const int, const int);
  void initializeGL(void);

 private:
  int xRot;
  int yRot;
  int zRot;
  int value;
  bool deleted;
  QColor bgColor;
  QColor bgColorOrig;
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);
  GLuint createPiece(void);
};

#endif
