/*
** Copyright (c) 2007, 2008 Alexis Megas
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** MAXIT IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
** -- C++ Includes --
*/

#include <iostream>

/*
** -- Qt Includes --
*/

#include <QApplication>

/*
** -- Local Includes --
*/

#include "maxit.h"

maxit *maxitptr = 0;
QApplication *qapp = 0;

int main(int argc, char *argv[])
{
  QApplication::setColorSpec(QApplication::CustomColor);

  try
    {
      qapp = new QApplication(argc, argv);
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  try
    {
      maxitptr = new maxit();
    }
  catch(std::bad_alloc)
    {
      std::cerr << "Memory allocation error at line "
		<< __LINE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  qapp->exec();
  delete qapp;
  std::cout << "Exiting Maxit." << std::endl;
}
