/*
** -- Qt Includes --
*/

#include <QMouseEvent>

/*
** -- Local Includes --
*/

#include "glpiece.h"

glpiece::glpiece(QWidget *parent, glpiece *other,
		 const int valueArg, const QColor &bgColorArg,
		 const int sideArg):
  QGLWidget(parent, other)
{
  xRot = 0;
  yRot = 0;
  zRot = 0;
  side = sideArg;
  value = valueArg;
  bgColor = bgColorOrig = bgColorArg;
  consumed = false;
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

  if(!consumed)
    glCallList(createPiece());
}

void glpiece::initializeGL(void)
{
  /*
  ** Initialize OpenGL.
  */

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}

void glpiece::resizeGL(int w, int h)
{
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

void glpiece::shrinkBy(const int percentage)
{
  side = (int) (side - (side * percentage) / 100.0);
  resizeGL(width(), height());
}

GLuint glpiece::createPiece(void)
{
  int i = 0;
  int j = 0;
  GLuint list = glGenLists(1);
  GLuint textures[6];
  QString facevalue = "";
  static const int coords[6][4][3] =
    {
      {{1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}},
      {{1, 1, -1}, {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}},
      {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
      {{-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}},
      {{1, -1, 1}, {-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}},
      {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}}
    };

  if(value < 0)
    facevalue = "q";
  else
    facevalue = QString::number(value);

  for(j = 0; j < 6; j++)
    textures[j] = bindTexture
      (QPixmap(QString("images.d/ubuntu.d/%1.png").arg(facevalue)),
       GL_TEXTURE_2D);

  glNewList(list, GL_COMPILE);

  for(i = 0; i < 6; i++)
    {
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glBegin(GL_QUADS);

      for(j = 0; j < 4; j++)
	{
	  glTexCoord2d(j == 0 || j == 3, j == 0 || j == 1);
	  glVertex3d(0.21 * coords[i][j][0], 0.21 * coords[i][j][1],
		     0.21 * coords[i][j][2]);
	}

      glEnd();
    }

  glEndList();
  return list;
}

void glpiece::enterEvent(QEvent *e)
{
  (void) e;

  if(consumed)
    return;

  /*
  ** Highlight the piece.
  */

  if(bgColor == Qt::black)
    bgColor = Qt::gray;
  else
    bgColor = QColor(abs((int) (bgColor.red() - bgColor.red() * 0.25)),
		     abs((int) (bgColor.green() - bgColor.green() * 0.25)),
		     abs((int) (bgColor.blue() - bgColor.blue() * 0.25)));

  updateGL();
}

void glpiece::leaveEvent(QEvent *e)
{
  (void) e;

  if(consumed)
    return;

  bgColor = bgColorOrig;
  updateGL();
}

void glpiece::mousePressEvent(QMouseEvent *e)
{
  int i = 0;
  (void) e;

  if(consumed)
    return;

  /*
  ** Shrink and spin the piece.
  */

  while(side > 0)
    {
      i += 1;

      if(i % 12 == 0)
	shrinkBy(5);

      rotateBy(-5 * 10, 25 * 10, -5 * 10);
    }

  consumed = true;
  bgColor = bgColorOrig;
  updateGL();
}

QSize glpiece::minimumSizeHint(void)
{
  return QSize(side - (int) (side * 0.5), side - (int) (side * 0.5));
}

QSize glpiece::sizeHint(void)
{
  return QSize(side + (int) (side * 0.5), side + (int) (side * 0.5));
}
