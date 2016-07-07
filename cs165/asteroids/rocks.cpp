#include "rocks.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

/**************************************************************************
 * function: BigRock constructor
 **************************************************************************/

BigRock::BigRock()
{
  this-> setAlive(true);
  this-> setPoint(Point(random(-200, 200), random(-200, 200)));
  this-> setAngle(this-> degreesToRadians(random(ROCKS_MIN_ANGLE,
						       ROCKS_MAX_ANGLE)));
  this-> setVelocity(Velocity(cos(this-> getAngleRads()),
			      sin(this-> getAngleRads())));
  this-> setRotation(random(-100, 100));
  //std::cout << this-> getVelocity().getDx();
  //std::cout << this-> getVelocity().getDy();
}

/*************************************************************************
 * function: advance
 * updates the positon of the rock by updating it is point proerty based 
 * on its velocity
 *************************************************************************/
void BigRock::advance()
{
  float newX = this-> getPoint().getX() + this-> getVelocity().getDx() + 1.0;
  float newY = this-> getPoint().getY() + this-> getVelocity().getDy() + 1.0;
  if (newX > 205 + BIG_ROCK_SIZE)
    newX = -200 - BIG_ROCK_SIZE;
  if (newX < -200 - BIG_ROCK_SIZE)
    newX = 200 + BIG_ROCK_SIZE;
  if (newY > 200 + BIG_ROCK_SIZE)
    newY = -200 - BIG_ROCK_SIZE;
  if (newY < -200 - BIG_ROCK_SIZE)
    newY = 200 + BIG_ROCK_SIZE;
  this-> setPoint(Point(newX, newY));
}

/**************************************************************************
 * function: draw
 * draws the rock at its point property
 *************************************************************************/
void BigRock::draw()
{
  drawLargeAsteroid(this-> getPoint(), this-> getRotation());
  this-> setRotation(this-> getRotation() + BIG_ROCK_SPIN);
  //std::cout << this-> getRotation() << std::endl;
}
