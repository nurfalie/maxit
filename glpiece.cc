/*
** -- Qt Includes --
*/

#include <QMouseEvent>

/*
** -- Local Includes --
*/

#include "glpiece.h"

glpiece::glpiece(QWidget *parent, glpiece *other,
		 const int valueArg, const QColor &bgColorArg):
  QGLWidget(parent, other)
{
  xRot = 0;
  yRot = 0;
  zRot = 0;
  value = valueArg;
  bgColor = bgColorOrig = bgColorArg;
  deleted = false;
  setMouseTracking(true);
}

glpiece::~glpiece()
{
}

void glpiece::paintGL(void)
{
  qglClearColor(bgColor);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -10.0);
  glRotated(xRot / 64.0, 1.0, 0.0, 0.0);
  glRotated(yRot / 64.0, 0.0, 1.0, 0.0);
  glRotated(zRot / 64.0, 0.0, 0.0, 1.0);

  if(!deleted)
    glCallList(createPiece());
}

void glpiece::initializeGL(void)
{
  /*
  ** Initiaze OpenGL.
  */

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}

void glpiece::resizeGL(int w, int h)
{
  int side = 128;

  glViewport((w - side) / 2, (h - side) / 2, side, side);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 0.5, 0.5, -0.5, 4.0, 15.0);
  glMatrixMode(GL_MODELVIEW);
}

void glpiece::rotateBy(const int xAngle, const int yAngle, const int zAngle)
{
  xRot += xAngle;
  yRot += yAngle;
  zRot += zAngle;
  updateGL();
}

GLuint glpiece::createPiece(void)
{
  int i = 0;
  int j = 0;
  GLuint list = glGenLists(1);
  GLuint textures[6];
  static const int coords[6][4][3] =
    {
      { { 1, -1, -1 }, { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 } },
      { { 1, 1, -1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 } },
      { { 1, -1, 1 }, { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 } },
      { { -1, -1, -1 }, { -1, -1, 1 }, { -1, 1, 1 }, { -1, 1, -1 } },
      { { 1, -1, 1 }, { -1, -1, 1 }, { -1, -1, -1 }, { 1, -1, -1 } },
      { { -1, -1, 1 }, { 1, -1, 1 }, { 1, 1, 1 }, { -1, 1, 1 } }
    };

  for(j = 0; j < 6; j++)
    textures[j] = bindTexture(QPixmap(QString("images.d/%1.png").arg(value)),
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
  return list;
}

void glpiece::enterEvent(QEvent *e)
{
  (void) e;

  if(deleted)
    return;

  /*
  ** Highlight the piece.
  */

  bgColor = QColor(bgColor.red() + bgColor.red() * 0.20,
		   bgColor.green() + bgColor.green() * 0.20,
		   bgColor.blue() + bgColor.blue() * 0.20);
  updateGL();
}

void glpiece::leaveEvent(QEvent *e)
{
  (void) e;

  if(deleted)
    return;

  bgColor = bgColorOrig;
  updateGL();
}

void glpiece::mousePressEvent(QMouseEvent *e)
{
  int i = 0;

  (void) e;

  if(deleted)
    return;

  /*
  ** Spin the piece.
  */

  for(i = 0; i < 720; i++)
    rotateBy(2 * 10, 2 * 10, -1 * 10);

  deleted = true;
  bgColor = bgColorOrig;
  updateGL();
}
