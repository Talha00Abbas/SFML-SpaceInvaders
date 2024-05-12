// project name : Space Invaders
// coder : Agha Talha
// purpose of code: This is the code for the base enemy logic, all the standard functions which enemies use are stated here

#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include "Bomb.h"
using namespace std;
using namespace sf;

class Enemy 
{
public:
    
    Texture tex;
	Sprite sprite;
	int health;
	bool isDead;
    
    // Destructor
    virtual ~Enemy();
    
    // Virtual functions
    virtual void fire(vector<Bomb>& bullets);
    virtual bool getDead();
    
    virtual void move();
    
    virtual void reduceHealth(int h);
    virtual int getHealth() const;
    
    virtual void checkHealthStatus();
	
};

Enemy::~Enemy() {}

void Enemy::fire(vector<Bomb>& bullets) {}

bool Enemy::getDead() { return false; }

void Enemy::reduceHealth(int h) {}

void Enemy::move(){}

int Enemy::getHealth() const {return health;}

void Enemy::checkHealthStatus(){}
 
