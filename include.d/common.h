#ifndef _COMMON_
#define _COMMON_

class maxit;
class QApplication;

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

  static maxit *maxitptr;
  static QApplication *qapp;
};

#endif
