/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "uiDraw.h"
#include "rocks.h"
#include <vector>
#include "ship.h"
#include "bullet.h"
class Game
{

 public:
  Game(Point tl, Point br);
  ~Game();
  void handleInput(const Interface &ui);
  void advance();
  void draw(const Interface &ui);

 private:
  Point topLeft;
  Point bottomRight;

  std::vector<Rock*> rocks;
  
  BigRock* createBigRock();
  MediumRock* createMediumRock(Point point, Velocity velocity);
  SmallRock* createSmallRock(Point point, Velocity velocity);
  void advanceRocks();

  std::vector<Bullet*> bullets;
  Bullet* createBullet();
  void advanceBullets();
  
  Ship* ship;
  Ship* createShip();
  void advanceShip();

  void handleCollisions();
  void cleanUpZombies();
  float getClosestDistance(const FlyingObject *obj1,
			   const FlyingObject *obj2) const;
};

#endif /* GAME_H */
