#include "GameLogic.h"
#include <iostream>
#include<time.h> 

/*
GameLogic class that holds all of the game objects and detects collisions
and updates game status
*/

GameLogic::GameLogic() {
    
}

void GameLogic::init(int wWidth, int wHeight) {
    width = wWidth;
    height = wHeight;
    bulletSpeed = 500;
    gravity = 3.f;
    gameState = 1;
    player.init();
    enemy1.init(200.f, 320.f);
    enemy2.init(500.f, 320.f);
    floor.init(1.f, 1.5f, 150.f, 350.f);
    platformA.init(0.3f, 0.4f, 450.f, 280.f);
    spike1.init(1.f,1.f, 650.f, 350.f);
    actorsVector.push_back(floor);
    actorsVector.push_back(platformA);
    actorsVector.push_back(enemy1);
    actorsVector.push_back(enemy2);
    actorsVector.push_back(spike1);
    platforms.push_back(floor);
    platforms.push_back(platformA);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    spikes.push_back(spike1);
    
}


void GameLogic::update(float timeS) {
    if (gameState == 1) {
        //perform game logic
        updatePlayerCollision(timeS);
        player.updateMovement();
        for(int e = 0; e < enemies.size(); ++e)
        {
            updateEnemyMovement(enemies[e].get(), timeS);
        }
        updatePlayerCollisionSpikes();
        updateProjectileCollisions();
    }
    
}

void GameLogic::softReset() {
    //return player character to beginning of level
    player.resetPosition();
}

void GameLogic::reset() {
    //restart level? or restart game?
}

int GameLogic::getGameState() {
    //gameState can be 0, uninitialized; 1, running; or others
    return gameState;
}

void GameLogic::updatePlayerCollisionSpikes() {
    //check if player is colliding with any spikes    
    for(int i = 0; i < spikes.size(); ++i)
    {
        if (player.getSprite().getGlobalBounds().intersects( spikes[i].get().getSprite().getGlobalBounds() ) )
        {
            softReset();
        }                                                                                                                                                                                          
    }
    
}

void GameLogic::updateProjectileCollisions() {
    //does nothing yet, eventually loop through projectiles and 
    //check if they are hitting the player or an enemy
}

void GameLogic::increaseScore(int level, int increase) {
    level--;
    if ( level >= 0 && level <= 9 ) {
        scores[level] = scores[level] + increase;
    }  
    else {
        //invalid level
    }
}

Player& GameLogic::getPlayer() {
    return player;
}

std::vector<std::reference_wrapper<Actor>> GameLogic::getActors() {
    return actorsVector;
}

bool GameLogic::collides(Actor actor, std::vector<std::reference_wrapper<Actor>> objVector)
{
    for(int i = 0; i < objVector.size(); ++i)
    {
        if (actor.getSprite().getGlobalBounds().intersects( objVector[i].get().getSprite().getGlobalBounds() ) )
        {
            return true;
        }                                                                                                                                                                                                
    }
    return false;
}

bool GameLogic::updatePlatformCollisions(Actor actor)
{
    for(int i = 0; i < platforms.size(); ++i)
    {
        if (actor.getSprite().getGlobalBounds().intersects( platforms[i].get().getSprite().getGlobalBounds() ) )
        {
            return true;
        }                                                                                                                                                                                                
    }
    return false;
}

void GameLogic::updatePlayerCollision(float timeS)
{
    float playerX = player.getSprite().getPosition().x;
    float playerY = player.getSprite().getPosition().y;
    float playerWidth = player.getSprite().getGlobalBounds().width;
    float playerHeight = player.getSprite().getGlobalBounds().height;
    float bufferSpaceY = gravity * timeS;
    float bufferSpaceX = 2.f * timeS;
    sf::FloatRect topHitBox = sf::FloatRect(playerX, playerY, playerWidth, bufferSpaceY);
    sf::FloatRect bottomHitBox = sf::FloatRect(playerX, playerY + playerHeight - bufferSpaceY, playerWidth, bufferSpaceY);
    //left and right hit boxes are slightly in front (or behind) character sprite to detect objects
    //does not reach all the way to the ground to avoid collision when standing on a platform
    sf::FloatRect leftHitBox = sf::FloatRect(playerX - bufferSpaceX, playerY, bufferSpaceX, playerHeight - 2*bufferSpaceY);
    sf::FloatRect rightHitBox = sf::FloatRect(playerX + playerWidth, playerY, bufferSpaceX, playerHeight - 2*bufferSpaceY);
    
    for(int i = 0; i < platforms.size(); ++i)
    {
        if (bottomHitBox.intersects( platforms[i].get().getSprite().getGlobalBounds() ) )
        {
            //player on platform
            player.setFalling(false);
            player.setInAir(false);
            player.setMaxJumpHeight();
        }
        else if (topHitBox.intersects( platforms[i].get().getSprite().getGlobalBounds() ) )
        {
            //player hit his head while jumping
            player.setFalling(true);
            player.setInAir(true);
        }
        
        if (leftHitBox.intersects( platforms[i].get().getSprite().getGlobalBounds() ) 
                || rightHitBox.intersects( platforms[i].get().getSprite().getGlobalBounds() ))
        {
            //player running into object on horizontal axis
            player.setVelocityX(0.f);
        }                                                                                                                                                                                           
    }
    //if player is not colliding with any other object, he is in the air
    if(!(collides(player, actorsVector)))
    {
        player.setInAir(true);
    }
}

void GameLogic::playerMoveRight(float timeS) {
    if (player.isInAir())    //character has less directional control when in the air
    {
        player.setVelocityX((player.getStepSizeX()/2.f) * timeS);
    }
    else
    {
        player.setVelocityX(player.getStepSizeX() * timeS);
    }        
}

void GameLogic::playerMoveLeft(float timeS) {
    if (player.isInAir())    //character has less directional control when in the air
    {
        player.setVelocityX((-1*player.getStepSizeX()/2.f) * timeS);
    }
    else
    {
        player.setVelocityX((-1*player.getStepSizeX()) * timeS);
    }        
}

void GameLogic::playerJump(float timeS) {
    //character jumps only if he's on the ground or is in the middle of jumping up
    if (!player.atMaxJumpHeight() && !player.isFalling()) 
    {
        player.setVelocityY((-1*player.getStepSizeY()) * timeS);
    }
    else
    {
        playerFall(timeS);
    }
    
}

void GameLogic::playerFall(float timeS) {
    if (player.isInAir()) //if player is not going up and not on ground then fall
    {
        player.setFalling(true); //player has already jumped and needs to fall before jumping again
        player.setVelocityY(gravity * timeS);
    }
}

void GameLogic::enemyFall(Enemy& enemy, float timeS) {
    if(!(updatePlatformCollisions(enemy)))
    {
        enemy.setVelocityY(gravity * timeS);
    }
    else
    {
        enemy.setVelocityY(0.f);
        enemySetBounds(enemy);
    }
}

void GameLogic::enemySetBounds(Enemy& enemy)
{
    //sets enemy's bounds based on the bounds of the platform he is standing on
    for(int i = 0; i < platforms.size(); ++i)
    {
        if (enemy.getSprite().getGlobalBounds().intersects( platforms[i].get().getSprite().getGlobalBounds() ) )
        {
            if(enemy.getMaxLeftDistance() > enemy.getStartX() - platforms[i].get().getSprite().getPosition().x)
            {
                enemy.setMaxLeftDistance(enemy.getStartX() - platforms[i].get().getSprite().getPosition().x);
            }
            if(enemy.getMaxRightDistance() > (platforms[i].get().getSprite().getPosition().x + platforms[i].get().getSprite().getGlobalBounds().width - enemy.getSprite().getGlobalBounds().width) - enemy.getStartX())
            {
                enemy.setMaxRightDistance((platforms[i].get().getSprite().getPosition().x + platforms[i].get().getSprite().getGlobalBounds().width - enemy.getSprite().getGlobalBounds().width) - enemy.getStartX());
            }
        }                                                                                                                                                                                                
    }
}

void GameLogic::enemyTrack(Enemy& enemy, float timeS) {
    //if player within range, move towards him
    if (player.getSprite().getPosition().x >= enemy.getStartX() - enemy.getMaxLeftDistance() 
        && player.getSprite().getPosition().x <= enemy.getStartX() + enemy.getMaxRightDistance())
     {
        enemy.trackActor(player, timeS);
     }
}

void GameLogic::updateEnemyMovement(Enemy& enemy, float timeS) {
    if(enemy.getVelocityX() == 0.f)
    {
        srand(time(NULL));
        int dir = rand() % 2;
        float currVelX = ( ((dir == 0) ? (-1*enemy.getStepSize()) : enemy.getStepSize()) * timeS );
        enemy.setVelocityX(currVelX);
    }
    enemyFall(enemy, timeS);
    enemyTrack(enemy, timeS);
    enemy.updateMovement();
}