/************************************************************************
 * file: flyingObject.cpp
 * autor: Gamaliel Tellez
 * objective: contains the definition of the base class flayongObject.
 ************************************************************************/

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"


FlyingObject::FlyingObject()
{
}

/***********************************************************************
 * function: getAnlgeRads()
 * function: getter for the angleRads property.
 ***********************************************************************/
float FlyingObject::getAngleRads() const
{
  return this-> angleRads;
}

/***********************************************************************
 * function: getPint()
 * function: getter for the point property.
 ***********************************************************************/
Point FlyingObject::getPoint() const
{
  return this-> point;
}

/***********************************************************************
 * function: getVelocity()
 * function: getter for the velocity property.
 ***********************************************************************/
Velocity FlyingObject::getVelocity() const
{
  return this-> velocity;
}

/***********************************************************************
 * function: getRotation()
 * function: getter for the rotation property.
 ***********************************************************************/
int FlyingObject::getRotation() const
{
  return this-> rotation;
}

/***********************************************************************
 * function: isAlive()
 * function: getter for the alive property.
 ***********************************************************************/
bool FlyingObject::isAlive() const
{
  return this-> alive;
}

/***********************************************************************
 * function: setRotation(int)
 * function: getter for the alive property.
 ***********************************************************************/
void FlyingObject::setRotation(int rotation)
{
    this-> rotation = rotation;
}

/***********************************************************************
 * function: setAngle(float)
 * function: takes a float and sets is the angle in degrees
 ***********************************************************************/
void FlyingObject::setAngle(float angleRads)
{
  this-> angleRads = angleRads;
}

/***********************************************************************
 * function: setPoint()
 * function: setter for the point property, takes a Point obj as param.
 ***********************************************************************/
void FlyingObject::setPoint(Point point)
{
  this-> point = point;
}

/***********************************************************************
 * function: setVelocity()
 * function: setter for the velocity property, takes a Velocity object
 ***********************************************************************/
void FlyingObject::setVelocity(Velocity velocity)
{
  this-> velocity = velocity;
}

/***********************************************************************
 * function: setAlive(bool)
 * function: setter for the alive property, takes a bool as param
 ***********************************************************************/
void FlyingObject::setAlive(bool alive)
{
  this-> alive = alive;
}

/***********************************************************************
 * function: kill()
 * function: sets the alive property to false, killing the object
 ***********************************************************************/
void FlyingObject::kill()
{
  this-> alive = false;
}

/***********************************************************************
 * function: degreesToRadians
 * function: converts the angle to radians
 ***********************************************************************/
float FlyingObject::degreesToRadians(float degrees)
{
  return (3.1415926536/180) * (degrees);
}

