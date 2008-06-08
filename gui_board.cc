/*
** -- Qt Includes --
*/

#include <QMouseEvent>

/*
** -- Local Includes --
*/

#include "gui_board.h"

void gui_board::paintGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen.
}

void gui_board::initializeGL(void)
{
  /*
  ** Initiaze OpenGL "stuff".
  */

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glShadeModel(GL_FLAT);
}

void gui_board::resizeGL(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, w, 0.0, h);
  glMatrixMode(GL_MODELVIEW);
}

void gui_board::mousePressEvent(QMouseEvent *e)
{
  (void) e;
}

gui_board::gui_board(QWidget *parent):QGLWidget(parent)
{
  setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}
