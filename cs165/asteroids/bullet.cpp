/************************************************************************
 * file: bullet.cpp
 * author: Gamaliel Tellez
 * contains the implementation of the bullet class.
 ************************************************************************/

#include "bullet.h"
#include "point.h"
#include "uiDraw.h"
#include "flyingObject.h"

/*************************************************************************
 * Bullet()
 * none defaul constructor
 *************************************************************************/
Bullet::Bullet()
{
  this-> setLife(40);
  this-> setAlive(true);
}

/*************************************************************************
 * function: setLife()
 * setter for the property life of the object
 *************************************************************************/
void Bullet::setLife(int life)
{
  this-> life = life;
}

/*************************************************************************
 * function: getLife()
 * objective: life property getter
 *************************************************************************/
int Bullet::getLife()
{
  return this-> life;
}

/*************************************************************************
 * function: advance()
 *************************************************************************/
void Bullet::advance()
{
 if (this-> getLife() == 0)
    this-> setAlive(false);
 else
   {
     this-> setLife(this-> getLife() - 1);
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
}

/*************************************************************************
 * function: draw()
 * draws the bullet at its point 
 *************************************************************************/
void Bullet::draw()
{
  drawDot(this-> getPoint());
}

/*************************************************************************
 * function: fire(point, float)
 * objective: takes a point (the starting point of the bullet) and a float 
 * angle (the angle in which the bullet is shoot)
 *************************************************************************/
void Bullet::fire(Point point, float angle)
{
  this-> setPoint(point);
  //std::cout << "rotation: " << angle << std::endl;
  float newDx = cos(this-> degreesToRadians(angle + 90));
  //std::cout << "cosine: " << newDx << std::endl;
  float newDy = sin(this-> degreesToRadians(angle + 90));
  //std::cout << "sine: " << newDy<< std::endl;
  Velocity newVelocity = Velocity(this-> getVelocity().getDx() + newDx * 5,
				  this-> getVelocity().getDy() + newDy * 5);
  this-> setVelocity(Velocity(newVelocity));
  this-> setAlive(true);
  this-> setLife(40);
}
