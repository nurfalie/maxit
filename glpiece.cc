/*
** -- Qt Includes --
*/

#include <QMouseEvent>

/*
** -- Local Includes --
*/

#include "glpiece.h"

glpiece::glpiece(QWidget *parent):QGLWidget(parent)
{
  xRot = 0;
  yRot = 0;
  zRot = 0;
  board = 0;
  clearColor = Qt::black;
  setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}

void glpiece::paintGL(void)
{
  qglClearColor(clearColor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -10.0);
  glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
  glCallList(board);
}

void glpiece::initializeGL(void)
{
  /*
  ** Initiaze OpenGL.
  */

  createPiece();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);
}

void glpiece::resizeGL(int w, int h)
{
  int side = qMin(w, h);

  glViewport((w - side) / 2, (h - side) / 2, side, side);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 0.5, 0.5, -0.5, 4.0, 15.0);
  glMatrixMode(GL_MODELVIEW);
}

void glpiece::mousePressEvent(QMouseEvent *e)
{
  (void) e;
}

void glpiece::createPiece(void)
{
  int i = 0;
  int j = 0;
  GLuint list = glGenLists(1);
  GLuint textures[6];
  static const int coords[6][4][3] =
    {
      { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
      { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
      { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
      { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
      { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
      { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

  for(j = 0; j < 6; j++)
    textures[j] = bindTexture
      (QPixmap(QString("images.d/side%1.png").arg(j + 1)),
       GL_TEXTURE_2D);

  glNewList(list, GL_COMPILE);

  for(i = 0; i < 6; i++)
    {
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glBegin(GL_QUADS);

      for(j = 0; j < 4; j++)
	{
	  glTexCoord2d(j == 0 || j == 3, j == 0 || j == 1);
	  glVertex3d(0.2 * coords[i][j][0], 0.2 * coords[i][j][1],
		     0.2 * coords[i][j][2]);
	}

      glEnd();
    }

  glEndList();
  board = list;
}
