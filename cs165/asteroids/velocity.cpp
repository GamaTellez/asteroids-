/************************************************************
 * File: velocity.cpp
 * Author: Gamaliel Tellez
 * Description: contains the implementation of the velocity
 * class
 ***********************************************************/
#include "velocity.h"

/************************************************************
 * function: Velocity()
 * Description: default constructor of the object
 ***********************************************************/
Velocity::Velocity(){}

/************************************************************
 * Function: Velocity(float, float)
 * Non-default constructor of the object, takes two floats as
 * parameter dx and dy
 ***********************************************************/
Velocity::Velocity(float dX, float dY)
{
    this-> dX = dX;
    this-> dY = dY;
}

/************************************************************
 * Function: getDx()
 * dX property getter
 ***********************************************************/
float Velocity::getDx()
{
   return this-> dX;
}

/************************************************************
 * Funtion: getDy()
 * dY property getter
 ***********************************************************/
float Velocity::getDy()
{
   return this-> dY;
}

/************************************************************
 * Function: setDx(float)
 * Setter for the dX propert of velocity, it takes a float 
 * parameter
 ***********************************************************/
void Velocity::setDx(float dX)
{
   this-> dX = dX;
}

/************************************************************
 * Function: setDy(float)
 * setter for the dY property object
 ***********************************************************/
void Velocity::setDy(float dY)
{
   this-> dY = dY;
}


