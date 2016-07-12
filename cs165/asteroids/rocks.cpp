#include "rocks.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

/**************************************************************************
 * function: getRadius
 *************************************************************************/
int Rock::getRadius() const
{
  return this-> radius;
}

/*************************************************************************
 * function: setRadius
 *************************************************************************/
void Rock::setRadius(int radius)
{
  this-> radius = radius;
}

/*************************************************************************
 * function advance:
 ************************************************************************/
void Rock::advance()
{
  
}

/************************************************************************
 *
 ************************************************************************/
void Rock::draw()
{
  
}

/**************************************************************************
 * function: BigRock constructor
 **************************************************************************/

BigRock::BigRock()
{
  this-> setAlive(true);
  this-> setPoint(Point(random(-200, 200), random(-200, 200)));
  this-> setAngle(this-> degreesToRadians(random(ROCKS_MIN_ANGLE,
						       ROCKS_MAX_ANGLE)));
  this-> setVelocity(Velocity(-cos(this-> getAngleRads()),
			      sin(this-> getAngleRads())));
  this-> setRotation(random(-100, 100));
  this-> setRadius(16);
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


/*************************************************************************
 * function: Medium Rock constructor
 * 
 *************************************************************************/
MediumRock::MediumRock(const Point &point, const Velocity &velocity)
{
  this-> setAlive(true);
  this-> setPoint(point);
  this-> setAngle(this-> degreesToRadians(random(ROCKS_MIN_ANGLE,
						       ROCKS_MAX_ANGLE)));
  this-> setRotation(random(-10, 10));
  this-> setVelocity(velocity);
  this-> setRadius(8);
}

/*************************************************************************
 * function: medium rock draw
 * draws a medium rock at the given point
 *************************************************************************/
void MediumRock::draw()
{
  drawMediumAsteroid(this-> getPoint(), this-> getRotation());
  this-> setRotation(this-> getRotation() + 5);
}

/*************************************************************************
 * function: advace
 * 
 *************************************************************************/
void MediumRock::advance()
{
  float newX = this-> getPoint().getX() + this-> getVelocity().getDx() + 1.0;
  float newY = this-> getPoint().getY() + this-> getVelocity().getDy() + 1.0;
  if (newX > 205 + MEDIUM_ROCK_SIZE)
    newX = -200 - MEDIUM_ROCK_SIZE;
  if (newX < -200 - MEDIUM_ROCK_SIZE)
    newX = 200 + MEDIUM_ROCK_SIZE;
  if (newY > 200 + MEDIUM_ROCK_SIZE)
    newY = -200 - MEDIUM_ROCK_SIZE;
  if (newY < -200 - MEDIUM_ROCK_SIZE)
    newY = 200 + MEDIUM_ROCK_SIZE;
  this-> setPoint(Point(newX, newY));
}

/***************************************************************************
* function: SmallRock
****************************************************************************/
SmallRock::SmallRock(const Point &point, const Velocity &velocity)
{
  this-> setAlive(true);
  this-> setPoint(point);
  this-> setAngle(this-> degreesToRadians(random(ROCKS_MIN_ANGLE,
						       ROCKS_MAX_ANGLE)));
  this-> setRotation(random(-10, 10));
  this-> setVelocity(velocity);
  this-> setRadius(4);
}


/***************************************************************************
 * function: draw
 **************************************************************************/
void SmallRock::draw()
{
  drawSmallAsteroid(this-> getPoint(), this-> getRotation());
  this-> setRotation(this-> getRotation() + 10);
}


/**************************************************************************
 * function: advance
 **************************************************************************/
void SmallRock::advance()
{
  float newX = this-> getPoint().getX() + this-> getVelocity().getDx() - 1.0;
  float newY = this-> getPoint().getY() + this-> getVelocity().getDy() + 1.0;
  if (newX > 205 + MEDIUM_ROCK_SIZE)
    newX = -200 - MEDIUM_ROCK_SIZE;
  if (newX < -200 - MEDIUM_ROCK_SIZE)
    newX = 200 + MEDIUM_ROCK_SIZE;
  if (newY > 200 + MEDIUM_ROCK_SIZE)
    newY = -200 - MEDIUM_ROCK_SIZE;
  if (newY < -200 - MEDIUM_ROCK_SIZE)
    newY = 200 + MEDIUM_ROCK_SIZE;
  this-> setPoint(Point(newX, newY));
}
