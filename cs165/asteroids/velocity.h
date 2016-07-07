/**************************************************************************
 * File: velocity.h
 * Author: Gamaliel Tellez
 * Description: contains the definition of the velocity class
 **************************************************************************/
#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
  private:
   float dY;
   float dX;
  public:
   Velocity();
   Velocity(float dX, float dY);
   float getDx();
   float getDy();
   void setDx(float dX);
   void setDy(float dY);
};

#endif /* velocity_h */
