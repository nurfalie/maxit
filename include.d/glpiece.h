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
  enum
    {
      CUBE_SIZE = 128
    };
  glpiece(QWidget *, glpiece *, const int, const QColor &, const int,
	  const int, const int, const int);
  ~glpiece();
  int col(void) const;
  int row(void) const;
  int value(void) const;
  void reset(const int);
  void hintMe(void);
  void rotate(const int, const int, const int);
  void select(void);
  void paintGL(void);
  void resizeGL(int, int);
  void setValue(const int);
  void setEnabled(const bool);
  void setClickable(const bool);
  void initializeGL(void);
  void resetBackground(void);
  QSize sizeHint(void) const;
  QSize minimumSizeHint(void) const;

 private:
  int colv;
  int rowv;
  int side;
  int xRot;
  int yRot;
  int zRot;
  int valuev;
  bool consumed;
  bool clickable;
  QColor bgColor;
  QColor bgColorOrig;;
  void growBy(const int);
  void rotateBy(const int, const int, const int);
  void shrinkBy(const int);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);
  GLuint createPiece(void);
};

#endif
