#ifndef _COMMON_
#define _COMMON_

class QApplication;
class maxit;

class Global
{
 private:
  Global(void) {}

 public:
  enum
    {
      NCOLS = 7,
      NROWS = 7
    };

  static QApplication *qapp;
  static maxit *maxitptr;
};

#endif
