/*
** -- Qt Includes --
*/

#include <QMouseEvent>

/*
** -- Local Includes --
*/

#include "glpiece.h"
#include "maxit.h"

glpiece::glpiece(QWidget *parent, glpiece *other,
		 const int valueArg, const QColor &bgColorArg,
		 const int rowArg, const int colArg, const int sideArg,
		 const int zRotArg):QGLWidget(parent, other)
{
  bgColor = bgColorArg;
  bgColorOrig = bgColorArg;
  clickable = false;
  colv = colArg;
  consumed = false;
  rowv = rowArg;
  side = sideArg;
  valuev = valueArg;
  xRot = 0;
  yRot = 0;
  zRot = zRotArg;
  setMouseTracking(true);
}

glpiece::~glpiece()
{
}

void glpiece::reset(const int valueArg)
{
  consumed = false;
  setEnabled(true);
  setValue(valueArg);

  if(side != CUBE_SIZE)
    /*
    ** If necessary, enlarge and rotate the piece.
    */

    for(int i = 0; side < CUBE_SIZE; i++)
      {
	if(i % 5 == 0)
	  growBy(8);

	if(Global::maxitptr->getViewMode() == maxit::VIEW2D)
	  rotateBy(0, 0, 15 * 10);
	else
	  rotateBy(15 * 10, -25 * 10, 15 * 10);
      }

  makeCurrent();
  resizeGL(width(), height());
  updateGL();
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
    {
      GLuint piece = createPiece();
      glCallList(piece);
      glDeleteLists(piece, 1);
    }
}

void glpiece::initializeGL(void)
{
  /*
  ** Initialize OpenGL.
  */

  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
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

void glpiece::rotate(const int xAngle, const int yAngle, const int zAngle)
{
  xRot = xAngle;
  yRot = yAngle;
  zRot = zAngle;
  updateGL();
}

void glpiece::rotateBy(const int xAngle, const int yAngle, const int zAngle)
{
  xRot += xAngle;
  yRot += yAngle;
  zRot += zAngle;

  if(Global::maxitptr->isAnimationEnabled())
    updateGL();
}

void glpiece::growBy(const int growth)
{
  side += growth;

  if(Global::maxitptr->isAnimationEnabled())
    resizeGL(width(), height());
}

void glpiece::shrinkBy(const int decrease)
{
  side -= decrease;

  if(Global::maxitptr->isAnimationEnabled())
    resizeGL(width(), height());
}

GLuint glpiece::createPiece(void)
{
  GLuint list = glGenLists(1);
  GLuint textures[6];
  QPixmap pixmap;
  QString facevalue("");
  static const int coords[6][4][3] =
    {
      {{1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}},
      {{1, 1, -1}, {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}},
      {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
      {{-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}},
      {{1, -1, 1}, {-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}},
      {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}}
    };

  if(valuev < 0)
    facevalue = "q";
  else
    facevalue = QString::number(valuev);

  for(int i = 0; i < 6; i++)
    {
#ifdef Q_OS_WIN
      pixmap = QPixmap(QString("%1\\%2.png").
		       arg(maxit::themedir()).
		       arg(facevalue));
#else
      pixmap = QPixmap(QString("%1/%2.png").
		       arg(maxit::themedir()).
		       arg(facevalue));
#endif

      if(!pixmap.isNull())
	textures[i] = bindTexture(pixmap, GL_TEXTURE_2D);
    }

  glNewList(list, GL_COMPILE);

  for(int i = 0; i < 6; i++)
    {
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glBegin(GL_QUADS);

      for(int j = 0; j < 4; j++)
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
  Q_UNUSED(e);

  if(!clickable || consumed || !isEnabled())
    return;

  /*
  ** Highlight (change the background color) the piece on a mouse-enter event.
  */

  bgColor = bgColor.lighter();
  updateGL();
}

void glpiece::leaveEvent(QEvent *e)
{
  Q_UNUSED(e);

  /*
  ** Reset the piece's background color once the mouse has exited
  ** the piece's space.
  */

  if(consumed || !isEnabled())
    return;

  bgColor = bgColorOrig;
  updateGL();
}

void glpiece::select(void)
{
  mousePressEvent(static_cast<QMouseEvent *> (0));
}

void glpiece::mousePressEvent(QMouseEvent *e)
{
  Q_UNUSED(e);

  if(consumed || !clickable)
    return;

  /*
  ** Shrink and spin the piece.
  */

  for(int i = 0; side > 0; i++)
    {
      if(i % 5 == 0)
	shrinkBy(8);

      if(Global::maxitptr->getViewMode() == maxit::VIEW2D)
	rotateBy(0, 0, -15 * 10);
      else
	rotateBy(-15 * 10, 25 * 10, -15 * 10);
    }

  consumed = true;
  bgColor = bgColorOrig;
  updateGL();

  if(e) // Ignore non-mouse events.
    Global::maxitptr->pieceSelected(this);
}

QSize glpiece::minimumSizeHint(void) const
{
  return QSize
    (side - static_cast<int> (side * 0.5),
     side - static_cast<int> (side * 0.5));
}

QSize glpiece::sizeHint(void) const
{
  return QSize(side + static_cast<int> (side * 0.5),
	       side + static_cast<int> (side * 0.5));
}

int glpiece::col(void) const
{
  return colv;
}

int glpiece::row(void) const
{
  return rowv;
}

int glpiece::value(void) const
{
  return abs(valuev);
}

void glpiece::setEnabled(const bool state)
{
  QGLWidget *widget = static_cast<QGLWidget *> (this);

  if(widget)
    widget->setEnabled(state);

  bgColor = bgColorOrig;

  if(!isEnabled())
    bgColor = bgColor.dark();

  updateGL();
}

void glpiece::setValue(const int valueArg)
{
  valuev = valueArg;
  updateGL();
}

void glpiece::hintMe(void)
{
  /*
  ** Special highlight.
  */

  if(consumed || !isEnabled())
    return;

  bgColor = bgColor.lighter(200);
  updateGL();
  bgColor = bgColorOrig;
}

void glpiece::resetBackground(void)
{
  bgColor = bgColorOrig;
  updateGL();
}

void glpiece::setClickable(const bool state)
{
  clickable = state;
}
