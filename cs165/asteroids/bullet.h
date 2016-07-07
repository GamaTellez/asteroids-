/*************************************************************************
 * bullet.h
 * author: Gamaliel Tellez
 * contains the definition of the bullet class.
 *************************************************************************/

#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "point.h"
#include "flyingObject.h"

class Bullet : public FlyingObject
{
 private:
  int life;
 public:
  Bullet();
  int getLife();
  void setLife(int life);
  void advance();
  void draw();
  void fire(Point point, float angle); 
};

#endif /* bullet_h */
