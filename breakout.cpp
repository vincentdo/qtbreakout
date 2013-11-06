#include <QtGui>
#include "breakout.h"
#include "breakout_canvas.h"

Breakout::Breakout()
{
  setWindowTitle("Breakout!");

  // there are only two widgets, and they're stacked vertically
  QVBoxLayout* layout = new QVBoxLayout(this);
  canvas = new BreakoutCanvas(this);
  layout->addWidget(canvas);

  controlButton = new QPushButton("Start", this);
  layout->addWidget(controlButton);

  // the button directly controls the canvas
  connect(controlButton, SIGNAL(clicked()), canvas, SLOT(buttonPress()));

  // the canvas can control the button
  connect(canvas, SIGNAL(needsButtonChange(QString)),
	  this, SLOT(changeButtonText(QString)));
}

void Breakout::changeButtonText(QString str)
{
  controlButton->setText(str);
}
