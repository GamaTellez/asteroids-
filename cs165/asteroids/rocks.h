/*********************************************************************
 * rocks.h
 * author: Gamaliel Tellez
 * description: contains the definition of bigRock, mediumRock, 
 * and bigRock class
 ********************************************************************/

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define ROCKS_MAX_ANGLE 360
#define ROCKS_MIN_ANGLE -360

#include "flyingObject.h"

class Rock : public FlyingObject
{
 private:
  int radius;

 public:
  int getRadius() const;
  void setRadius(int radius);
  virtual void advance();
  virtual void draw();
};

class BigRock : public Rock
{  
public:
  BigRock();
  void advance();
  void draw();
};


class MediumRock : public Rock
{
 private:
  int newDirection;
  
 public:
  MediumRock(const Point &point, const Velocity &velocity);
  void setNewDirection(int direction);
  void draw();
  void advance();
};

class SmallRock : public Rock
{
 public:
  SmallRock(const Point &point, const Velocity &velocity);
  void draw();
  void advance();
};

#endif /* rocks_h */
