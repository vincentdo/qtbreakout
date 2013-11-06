#include <QtGui>
#include "breakout_canvas.h"

BreakoutCanvas::BreakoutCanvas(QWidget* parent)
  : QWidget(parent) // This passes the constructor parameter to the superclass
{  
  timer = new QTimer(this);
  timer->setInterval(5); // an interval of 5ms
  connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));

  setFixedSize(WIDTH, HEIGHT);

  reset();
}

void BreakoutCanvas::buttonPress()
{
  switch(state)
  {
  case BEFORE_PLAY:    
    timer->start();
    reset();
    needsButtonChange("Pause");
    state = PLAYING;
    break;

  case PLAYING:
    timer->stop();
    needsButtonChange("Resume");
    state = PAUSED;
    break;

  case PAUSED:
    timer->start();
    needsButtonChange("Pause");
    state = PLAYING;
    break;

  case AFTER_PLAY:
    reset();
    needsButtonChange("Start");
    state = BEFORE_PLAY;
    break;
  }
  
  setFocus(Qt::OtherFocusReason); // make sure that the canvas gets keystrokes
}

void BreakoutCanvas::reset()
{
  brick_counter = COL * ROW;
  for (int i = 0; i < ROW; i++){
    for (int j = 0; j < COL; j++){
      bricks[i][j] = false;
    }
  }
  // center paddles and ball
  playerX = WIDTH / 2 - (PADDLE_WIDTH / 2);
  ball = QPoint(WIDTH / 2, HEIGHT / 2);

  // moving up and right
  goingDown = false;
  goingRight = true;

  // player's paddle is not moving
  paddleLeft = false;
  paddleRight = false;

  state = BEFORE_PLAY;

  // update() forces a repaint of the canvas
  update();
}

// we ignore the QPaintEvent* parameter, so we omit the name to avoid getting
// a warning
void BreakoutCanvas::paintEvent(QPaintEvent*)
{
  // create painting context -- the painting context does all the work
  QPainter p(this);

  // draw a frame around the field:
  p.drawRect(0, 0, WIDTH-1, HEIGHT-1);

  // draw the paddle
  p.fillRect(playerX, HEIGHT - PADDLE_HEIGHT,
	     PADDLE_WIDTH, PADDLE_HEIGHT, Qt::blue);

  // Repaint the bricks each time
  for (int i = 0; i < ROW; i++){
    for (int j = 0; j < COL; j++){
      if (!bricks[i][j]){
        int x = j * 40;
        int y = i * 10;
        p.setBrush(Qt::black);
        p.drawRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
        p.fillRect(x+1, y+1, BRICK_WIDTH-2, BRICK_HEIGHT-2, Qt::blue);
      }
    }
  }

  // no fillEllipse... so we need to set the brush and use drawEllipse
  p.setBrush(Qt::red); // use implicit QBrush constructor
  p.drawEllipse(ball.x() - BALL_RADIUS, ball.y() - BALL_RADIUS,
		BALL_RADIUS * 2, BALL_RADIUS * 2);

  // show that the user lost if necessary
  if(state == AFTER_PLAY)
  {
    // Print Winning Message
    if (brick_counter == 0){
      p.drawText(QRect(0, 0, WIDTH, HEIGHT), Qt::AlignCenter, "You Won!");
    }
    // Print Losing Message
    else p.drawText(QRect(0, 0, WIDTH, HEIGHT), Qt::AlignCenter, "Game over!");
  }
}

void BreakoutCanvas::timerTicked()
{
  // this will get called every 50 milliseconds

  // first, move the ball:
  if(goingRight)
  {
    ball.rx()++;
  }
  else
  {
    ball.rx()--;
  }

  if(goingDown)
  {
    ball.ry()++;
  }
  else
  {
    ball.ry()--;
  }

  // should the ball bounce?
  if(ball.x() + BALL_RADIUS >= WIDTH)
  {
    goingRight = false;
  }
  if(ball.x() - BALL_RADIUS <= 0)
  {
    goingRight = true;
  }

  int y = ball.y() - BALL_RADIUS;
  // If the ball comes into contact with the brick
  // then it should bounce in the opposite direction.
  // The brick is then destroyed and the counter is 
  // decremented
  if (y <= ROW * 10 - 1 && y > 0)
  {
    int column = (ball.x() - BALL_RADIUS)/40;
    int row = (ball.y() - BALL_RADIUS)/10;
    if(!bricks[row][column]){
      if ( (ball.x() - BALL_RADIUS) % 40 == 0){
        goingRight = !goingRight;
      }
      goingDown = !goingDown;
      bricks[row][column] = true;
      brick_counter--;
    }    
  }


  if (y <= 0){
    goingDown = true;
  }
  // but the player's paddle might not be -- check
  if(ball.y() + BALL_RADIUS >= HEIGHT - PADDLE_HEIGHT &&
     ball.x() >= playerX &&
     ball.x() <= playerX + PADDLE_WIDTH)
  {
    goingDown = false;
  }

  // move the player's paddle:
  if(paddleLeft)
  {
    playerX--;
  }
  if(paddleRight)
  {
    playerX++;
  }
  if(playerX <= 0)
  {
    playerX = 0;
  }
  if(playerX + PADDLE_WIDTH >= WIDTH)
  {
    playerX = WIDTH - PADDLE_WIDTH;
  }

  // did the player lose?
  if(ball.y() >= HEIGHT || brick_counter == 0)
  {
    timer->stop();
    state = AFTER_PLAY;
    needsButtonChange("Restart");
  }

  update(); // force a redraw
}

void BreakoutCanvas::keyPressEvent(QKeyEvent* event)
{
  if(event->key() == Qt::Key_Left)
  {
    paddleLeft = true;
  }
  if(event->key() == Qt::Key_Right)
  {
    paddleRight = true;
  }
}

void BreakoutCanvas::keyReleaseEvent(QKeyEvent*)
{
  paddleLeft = paddleRight = false;
}
