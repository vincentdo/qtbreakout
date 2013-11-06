#ifndef BREAKOUT_CANVAS_H_
#define BREAKOUT_CANVAS_H_

#include <QtGui>
#include <QObject>

class BreakoutCanvas : public QWidget
{
  Q_OBJECT

 public:
  BreakoutCanvas(QWidget* parent);

 signals:
  void needsButtonChange(QString str);

 public slots:
  void buttonPress();

 protected:
  void paintEvent(QPaintEvent* event);
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent* event);

 private slots:
  void timerTicked();

 private:
  void reset(); // reset playing field

  enum State { BEFORE_PLAY, PLAYING, PAUSED, AFTER_PLAY } state;

  QTimer* timer;

  // coordinates of the left sides of the paddles
  int playerX;
  //int compX;

  QPoint ball; // coordinates of center of ball

  // direction of ball
  bool goingRight;
  bool goingDown;

  // movement of player paddle
  bool paddleLeft;
  bool paddleRight;

  // Number of bricks
  int brick_counter;

  // Size of bricks array
  static const int ROW = 3;
  static const int COL = 10;

  // Array of bricks
  bool bricks[ROW][COL];

  static const int WIDTH = 400;
  static const int HEIGHT = 300;

  static const int PADDLE_WIDTH = 100;
  static const int PADDLE_HEIGHT = 15;

  // Size of each brick
  static const int BRICK_WIDTH = WIDTH / COL;
  static const int BRICK_HEIGHT = 10;

  static const int BALL_RADIUS = 5; 
};

#endif
