/********************************************************************
 * file: flyingObject.h
 * contains the base clase of all flaying objects (rocks, ship, 
 * bullets)
 *******************************************************************/
#include "point.h"
#include "velocity.h"

#ifndef FlyingObject_h
#define FlyingObject_h

class FlyingObject
{
 private:
  Point point;
  Velocity velocity;
  bool alive;  
  float angleRads;
  int rotation;
  
 public:
  FlyingObject();
  Point getPoint() const;
  Velocity getVelocity() const;
  float getAngleRads() const;
  bool isAlive() const;
  int getRotation() const;
  void setPoint(Point point);
  void setVelocity(Velocity velocity);
  void setAlive(bool alive);
  void setAngle(float angle);//in degrees
  void setRotation(int rotation);
  void kill();
  float degreesToRadians(float degrees);
  virtual void advance() = 0;
  virtual void draw() = 0;  
};

#endif /* FlyingObject_h */
