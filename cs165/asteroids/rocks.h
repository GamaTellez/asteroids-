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

// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock

class BigRock : public FlyingObject
{
public:
  BigRock();
  void advance();
  void draw();
};

#endif /* rocks_h */
