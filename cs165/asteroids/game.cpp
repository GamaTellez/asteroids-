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
using namespace std;

Game::Game(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
  //creatin 5 rocks, I'll probably need to change this when we start creating
  //other rocks
   if (bigRocks.empty())
     {
       for (int i = 0; i < 5; i++)
	 {
	   BigRock* newBigRock = this-> createBigRock();
	   bigRocks.push_back(this-> createBigRock());  
	   //	   cout << "new rock was created\n";
	 }
     }
   ship = NULL;
   hits = 0;
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
  for (vector <BigRock*> :: iterator rocksIt = bigRocks.begin();
       rocksIt != bigRocks.end(); rocksIt++)
    {
      BigRock* pRock = *rocksIt;
      pRock-> advance();
      //cout << "advancing rock\n";
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
  if (!bigRocks.empty())
    {
  vector <BigRock*> :: iterator rocksIt = bigRocks.begin();
  while (rocksIt != bigRocks.end())
	{
	  BigRock* pRock = *rocksIt;
	  if (pRock-> isAlive())
	    pRock-> draw();
	  *rocksIt++;
	}
    }
  else
    {
      cout << "vector is empty\n";
    }

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
	  *bulletIt++;
	}
    }
}

void Game::handleCollisions()
{
  vector<Bullet*>::iterator bulletsIt = bullets.begin();
  vector<BigRock*>::iterator bigRocksIt = bigRocks.begin();
  while (bulletsIt != bullets.end())
    {
      Bullet* bullet = *bulletsIt;
      if (bullet != NULL && bullet-> isAlive())
   	{
   	  while (bigRocksIt != bigRocks.end())
   	    {
   	      BigRock* bRock = *bigRocksIt;
   	      if (this-> getClosestDistance(bullet, bRock) < 15.0)
		{
		  bRock-> setAlive(false);
		  bullet-> setAlive(false);
		}
	      bigRocksIt++;
   	    }
   	  bulletsIt++;
   	}
      else
	{
	bulletsIt++;
	}
    }
}

void Game::cleanUpZombies()
{
  if (ship != NULL && !ship-> isAlive())
     {
       delete ship;
       ship = NULL;
     }

  vector<Bullet*>::iterator bulletIt = bullets.begin();
  //std::cout << "total of bullets: " << bullets.size() << std::endl;
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
  //std::cout << "total of bullets: " << bullets.size() << std::endl;

  vector<BigRock*>::iterator bigRockIt = bigRocks.begin();
  //std::cout << "total of rocks: " << bigRocks.size() << std::endl;
  while (bigRockIt != bigRocks.end())
    {
      BigRock* pBigRock = *bigRockIt;
      if (!pBigRock-> isAlive())
	{
	  delete pBigRock;
	  pBigRock = NULL;
	  bigRockIt = bigRocks.erase(bigRockIt);
	}
      else
	bigRockIt++;
    }
  //std::cout << "total of bullets: " << bigRocks.size() << std::endl;
}

BigRock* Game:: createBigRock()
{
  BigRock* newBigRock = NULL;
  newBigRock = new BigRock();
  return newBigRock;
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
  pNewBullet-> setLife(40);
  pNewBullet-> setAlive(true);
  return pNewBullet;
}

// You may find this function helpful...
/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const Bullet *obj1, const BigRock *obj2) const
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

