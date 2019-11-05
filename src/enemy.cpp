#include "enemy.h"

/*
Basic enemy class that has actions and holds information for the
created enemy
*/

#include "shooter.h"
#include "enemy.h"
#include "Bullet.h"
#include <SFML/Graphics.cpp>
#include <vector>

Enemy::Enemy(){

}

void Enemy::init(){
  if (!texture.loadFromFile("../res/enemy.png"))
  {
      // error...
  }
  setSprite(sf::Sprite(texture));
  velocityX = 0.f;
  velocityY = 0.f;
  xpos = 600.f;
  ypos = 300.f;
  getSprite().setPosition(xpos, ypos);
}

void Enemy::setPos(sf::vector2f newPos){
  enemy.setPos(newPos);
}

void Enemy::checkCollision(Bullet bullet){
  if (bullet.getRight()>enemy.getPosition().x &&
bullet.getTop()<enemy.getPosition().y+enemy.getSize().y &&
bullet.getDown()>enemy.getPosition().y){
  enemy.setPosition(sf::Vector2f(4234432,4234423));
}
}
