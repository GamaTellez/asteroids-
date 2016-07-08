#include "ship.h"
#include "uiDraw.h"
#include "flyingObject.h"
Ship::Ship()
{
  this-> setAlive(true);
  this-> setRotation(0);
  this-> setPoint(Point(50,50));
  this-> setThrust(false);
  this-> setVelocity(Velocity(0,0));
}

bool Ship::getThrust() const
{
  return this-> thrust;
}

void Ship::setThrust(bool thrust)
{
  this-> thrust = thrust;
}

void Ship::advance()
{
  float newX = this-> getPoint().getX() + this-> getVelocity().getDx();
  float newY = this-> getPoint().getY() + this-> getVelocity().getDy();
  if (newX > 200)
    newX = -200;
  if (newX < -200)
    newX = 200;
  if (newY > 200)
    newY = -200;
  if (newY < -200)
    newY = 200;
  this-> setPoint(Point(newX, newY));  
}

void Ship::draw()
{
  drawShip(this-> getPoint(), this-> getRotation(), this-> getThrust());
  if (this-> getThrust())
    this-> setThrust(false);
}

void Ship::updateVelocity()
{
  float newDx = cos(this-> degreesToRadians(this-> getRotation() + 90));
  float newDy = sin(this-> degreesToRadians(this-> getRotation() + 90));
  Velocity newVelocity = Velocity(this-> getVelocity().getDx() +
				  newDx * 0.5,
				  this-> getVelocity().getDy() +
				  newDy * 0.5);
  this-> setVelocity(newVelocity);
}
