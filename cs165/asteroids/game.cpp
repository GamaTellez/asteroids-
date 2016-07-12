/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include <vector>
// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include "rocks.h"

using namespace std;

Game::Game(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
   if (rocks.empty())
     {
       for (int i = 0; i < 5; i++)
	 {
	   rocks.push_back(this-> createBigRock());
	 }
     }
   ship = NULL;
   rocks.reserve(80);
}

Game::~Game()
{
}

void Game::handleInput(const Interface &ui)
{
  if (ship-> isAlive())
    {
      if (ui.isLeft())
	{
	  ship-> setRotation(ship-> getRotation() + 6);
	}
      if (ui.isRight())
	{
	  ship-> setRotation(ship-> getRotation() - 6);
	}
	if (ui.isUp())
	{
	  ship-> setThrust(true);
	  ship-> updateVelocity();
	}
      if (ui.isSpace())
	{
	  Bullet* newBullet = this-> createBullet();
	  newBullet-> setVelocity(ship-> getVelocity());
	  newBullet-> fire(ship-> getPoint(), ship-> getRotation());
	  bullets.push_back(newBullet);
	}
    }
}

void Game::advance()
{
  this-> advanceRocks();
  this-> advanceShip();
  this-> advanceBullets();
  this-> handleCollisions();
  this-> cleanUpZombies();
}

void Game::advanceRocks()
{
  vector<Rock*>::iterator rocksIt = rocks.begin();
  while (rocksIt != rocks.end())
    {
      Rock* theRock = *rocksIt;
      theRock-> advance();
      rocksIt++;
    }
}

void Game::advanceBullets()
{
  for (vector <Bullet*>::iterator bulletsIt = bullets.begin();
       bulletsIt != bullets.end(); bulletsIt++)
    {
      Bullet* aBullet = *bulletsIt;
      aBullet-> advance();
    }
}

void Game::advanceShip()
{
  if (ship == NULL)
    {
      ship = this-> createShip();
    }
  else
    {
      if (ship-> isAlive())
	{
	  ship-> advance();
	}    
    }
}

void Game::draw(const Interface &ui)
{      
  if (ship != NULL && ship-> isAlive())
    ship-> draw();
    
    if (!bullets.empty())
      {
	vector<Bullet*>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	  {
	    Bullet* aBullet = *bulletIt;
	    if(aBullet-> isAlive())
	      aBullet-> draw();
	    bulletIt++;
	  }
      }

    if (!rocks.empty())
      {
	vector<Rock*>::iterator rocksIt =rocks.begin();
	while (rocksIt != rocks.end())
	  {
	    Rock* theRock = *rocksIt;
	    if (theRock-> isAlive())
	      theRock-> draw();
	    rocksIt++;
	  }
      }
}

void Game::handleCollisions()
{
      vector<Rock*>::iterator itRock = rocks.begin();
      while (itRock != rocks.end())
	{
	  Rock* aRock = *itRock;
	  if (this-> getClosestDistance(ship, aRock) <= 20)
	    ship-> setAlive(false);
	  itRock++;
	}
  
  if (!bullets.empty())
    {
      vector<Rock*>::iterator rocksIt = rocks.begin();
      vector<Bullet*>::iterator bulletIt = bullets.begin();
      while (bulletIt != bullets.end())
	{
	  Bullet* aBullet = *bulletIt;
	  while (rocksIt != rocks.end())
	    {
	      Rock* theRock = *rocksIt;	   
	      if (this-> getClosestDistance(aBullet, theRock) <= theRock-> getRadius() + 10)
		{
		  theRock-> setAlive(false);
		  aBullet-> setAlive(false);
		  int rockRadius = theRock-> getRadius();
		  switch(rockRadius)
		    {
		    case 16:
		      rocks.push_back(this-> createMediumRock(theRock-> getPoint(), theRock-> getVelocity()));
		      rocks.push_back(this-> createMediumRock(theRock-> getPoint(),
							      Velocity(theRock-> getVelocity().getDx() * -1,
								       theRock-> getVelocity().getDy())));
		      rocks.push_back(this-> createSmallRock(theRock-> getPoint(), theRock-> getVelocity()));
		      break;
		    case 8:
		      rocks.push_back(this-> createSmallRock(theRock-> getPoint(),
							     Velocity(theRock-> getVelocity().getDx() * -1,
								      theRock-> getVelocity().getDy())));
		      rocks.push_back(this-> createSmallRock(theRock-> getPoint(), theRock-> getVelocity()));
		      break;  
		  break;
		    default:
		  break;
		    }
		}
	       rocksIt++;
	    }
	  bulletIt++;
	}
    }
}

void Game::cleanUpZombies()
{
   // if (ship != NULL && !ship-> isAlive())
   //   {
   //       delete ship;
   //       ship = NULL;
   //     }

  vector<Bullet*>::iterator bulletIt = bullets.begin();
  while (bulletIt != bullets.end())
    {
      Bullet* aBullet = *bulletIt;
      if (!aBullet-> isAlive())
	{
	  delete aBullet;
	  aBullet = NULL;
	  bulletIt = bullets.erase(bulletIt);
	}
      else
	  bulletIt++;
    }
 
  vector<Rock*>::iterator rocksIt = rocks.begin();
  while (rocksIt != rocks.end())
    {
      Rock *aRock = *rocksIt;
      if (!aRock-> isAlive())
	{
	  delete aRock;
	  aRock = NULL;
	  rocksIt = rocks.erase(rocksIt);
	}
      else
	rocksIt++;
    }
}

BigRock* Game:: createBigRock()
{
  BigRock* newBigRock = NULL;
  newBigRock = new BigRock();
  return newBigRock;
}

MediumRock* Game::createMediumRock(Point point, Velocity velocity)
{
  MediumRock* mediumRock = NULL;
  return new MediumRock(point, velocity);
}

SmallRock* Game::createSmallRock(Point point, Velocity velocity)
{
  SmallRock* sRock = NULL;
  return new SmallRock(point, velocity);
}

Ship* Game::createShip()
{
  Ship* pNewShip = NULL;
  pNewShip = new Ship();
  return pNewShip;
}

Bullet* Game::createBullet()
{
  Bullet* pNewBullet = NULL;
  pNewBullet = new Bullet();
  return pNewBullet;
}

// You may find this function helpful...
/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject *obj1, const FlyingObject *obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1-> getVelocity().getDx()), abs(obj1-> getVelocity().getDy()));
   dMax = max(dMax, abs(obj2-> getVelocity().getDx()));
   dMax = max(dMax, abs(obj2-> getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1-> getPoint().getX() + (obj1-> getVelocity().getDx() * i / dMax),
                     obj1-> getPoint().getY() + (obj1-> getVelocity().getDy() * i / dMax));
      Point point2(obj2-> getPoint().getX() + (obj2-> getVelocity().getDx() * i / dMax),
                     obj2-> getPoint().getY() + (obj2-> getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

