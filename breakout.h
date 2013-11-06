#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <QtGui>
#include <QObject>

// This is a forward class declaration -- it says to C++ that there is
// a class named BreakoutCanvas, but we don't know any details yet
class BreakoutCanvas;

// The Breakout class manages the window, which is just a container for the
// BreakoutCanvas (where all the game logic lives) and the one control button.
class Breakout : public QWidget
{
  Q_OBJECT

 public:
  Breakout();

 private slots:
  // allow other objects (like the BreakoutCanvas) to change the button text
  void changeButtonText(QString str);

 private:
  BreakoutCanvas * canvas;
  QPushButton * controlButton;
};

#endif
