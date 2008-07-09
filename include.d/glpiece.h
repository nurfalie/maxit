#ifndef _GLPIECE_
#define _GLPIECE_

/*
** -- C++ Includes --
*/

#include <iostream>

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
  static const int SMALL_CUBE_SIZE = 100;
  static const int NORMAL_CUBE_SIZE = 200;
  glpiece(QWidget *, glpiece *, const int, const QColor &, const int,
	  const int, const int);
  ~glpiece();
  int col(void) const;
  int row(void) const;
  int value(void) const;
  void reset(const int);
  void rotate(const int, const int, const int);
  void paintGL(void);
  void resizeGL(int, int);
  void rotateBy(const int, const int, const int);
  void setEnabled(const bool);
  void initializeGL(void);
  QSize sizeHint(void) const;
  QSize minimumSizeHint(void) const;

 private:
  int colv;
  int rowv;
  int side;
  int xRot;
  int yRot;
  int zRot;
  int xRot0;
  int yRot0;
  int zRot0;
  int valuev;
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
