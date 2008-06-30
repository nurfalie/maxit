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
  Q_OBJECT

 public:
  static const int CUBE_SIZE = 128;
  glpiece(QWidget *, glpiece *, const int, const QColor &);
  ~glpiece();
  void reset(const int);
  void rotate(const int, const int, const int);
  void paintGL(void);
  void resizeGL(int, int);
  void rotateBy(const int, const int, const int);
  void initializeGL(void);
  QSize sizeHint(void);
  QSize minimumSizeHint(void);

 private:
  int side;
  int xRot;
  int yRot;
  int zRot;
  int value;
  int xRot0;
  int yRot0;
  int zRot0;
  bool consumed;
  GLuint piece;
  QColor bgColor;
  QColor bgColorOrig;;
  void growBy(const int);
  void shrinkBy(const int);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);
  GLuint createPiece(void);
};

#endif
