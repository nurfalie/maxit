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
#include <QMouseEvent>
#include <QtOpenGL>

/*
** -- Class(es) --
*/

class glpiece: public QGLWidget
{
  Q_OBJECT

 public:
  enum
  {
    CUBE_SIZE = 128
  };

  glpiece(QWidget *, glpiece *, const int, const QColor &, const int,
	  const int, const int, const int);
  ~glpiece();
  QSize minimumSizeHint(void) const;
  QSize sizeHint(void) const;
  int col(void) const;
  int row(void) const;
  int value(void) const;
  void hintMe(void);
  void initializeGL(void);
  void paintGL(void);
  void reset(const int);
  void resetBackground(void);
  void resizeGL(int, int);
  void rotate(const int, const int, const int);
  void select(void);
  void setClickable(const bool);
  void setEnabled(const bool);
  void setValue(const int);

 private:
  QColor bgColor;
  QColor bgColorOrig;
  bool clickable;
  bool consumed;
  int colv;
  int rowv;
  int side;
  int valuev;
  int xRot;
  int yRot;
  int zRot;
  GLuint createPiece(void);
  void enterEvent(QEvent *);
  void growBy(const int);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);
  void rotateBy(const int, const int, const int);
  void shrinkBy(const int);
};

#endif
