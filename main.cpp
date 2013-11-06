/* File: main.cpp
   Author: Richard Eisenberg (eir@cis)
   Desc: Main file to start off Breakout
*/

#include <QtGui>
#include <QObject>
#include "breakout.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Breakout breakout;
  breakout.show();

  return app.exec();
}
