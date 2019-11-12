#include "GameLogic.h"
#include <iostream>
#include <time.h> 

/*
GameLogic class that holds all of the game objects and detects collisions
and updates game status
*/

GameLogic::GameLogic() {

}

void GameLogic::init(int wWidth, int wHeight) {
    width = wWidth;
    height = wHeight;
    gravity = 300.f;
    gameState = 0;
    player.init();
    enemy1.init(1000.f, 320.f);
    enemy2.init(500.f, 320.f,1);
    enemy3.init(1500.f, 320.f,2);
    enemy4.init(2500.f, 320.f);
    floor.init(5.f, 1.f, 150.f, 350.f);
    platformA.init(0.3f, 0.4f, 450.f, 280.f);
    platformB.init(2.f, 1.f, 2700.f, 280.f);
    platformC.init(1.f, 0.5f, 1000.f, 280.f);
    platformD.init(1.f,0.5f, 2500.f, 280.f);
    platformE.init(1.f,0.5f, 2900.f, 200.f);
    spike1.init(1.f,1.f, 650.f, 320.f);
    spike2.init(1.f,1.f,1200.f, 320.f);
    spike3.init(1.f,1.f,1550.f, 320.f);
    spike4.init(1.f,1.f,2100.f, 320.f);

    actorsVector.push_back(floor);
    actorsVector.push_back(platformA);
    actorsVector.push_back(platformB);
    actorsVector.push_back(platformC);
    actorsVector.push_back(platformD);
    actorsVector.push_back(platformE);
    actorsVector.push_back(enemy1);
    actorsVector.push_back(enemy2);
    actorsVector.push_back(enemy3);
    actorsVector.push_back(enemy4);
    actorsVector.push_back(spike1);
    actorsVector.push_back(spike2);
    actorsVector.push_back(spike3);
    actorsVector.push_back(spike4);
    actorsVector.push_back(girl);
    actorsVector.push_back(projectile);
    platforms.push_back(platformB);
    platforms.push_back(floor);
    platforms.push_back(platformA);
    platforms.push_back(platformC);
    platforms.push_back(platformD);
    platforms.push_back(platformE);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);
    spikes.push_back(spike1);
    spikes.push_back(spike2);
    spikes.push_back(spike3);
    spikes.push_back(spike4);
    projectiles.push_back(projectile);
    
}


void GameLogic::update(float timeS) {
    if (gameState == 1) {
        //perform game logic
        updatePlayerCollision(timeS);
        player.updateMovement(timeS);
        for(int e = 0; e < enemies.size(); ++e)
        {
            updateEnemyMovement(enemies[e].get(), timeS);
        }
        for(int p = 0; p < projectiles.size(); ++p) {
            if ( !projectiles[p].get().checkDistance()) {
                projectiles[p].get().setOffScreen();
                playerFired = false;
            }
            else {
                projectiles[p].get().updateMovement(timeS);
            }
        }
       
        updatePlayerCollisionSpikesEnemy();
        updateProjectileCollisions();
        updatePlayerCollisionGirl();
    }

}

Actor& GameLogic::getGirl(){
    return girl;
}

void GameLogic::softReset() {
    //return player character to beginning of level
    player.resetPosition();
    //reset score multiplier
}

void GameLogic::reset() {
    //restart level? or restart game?
}

int GameLogic::getGameState() {
    //gameState can be 0, uninitialized; 1, running; or others
    return gameState;
}

void GameLogic::setGameState(int newState) {
    gameState = newState;
}

void GameLogic::updatePlayerCollisionSpikesEnemy() {
    //check if player is colliding with any spikes    
    for(int i = 0; i < spikes.size(); ++i)
    {
        if (player.getSprite().getGlobalBounds().intersects( spikes[i].get().getSprite().getGlobalBounds() ) )
        {
            softReset();
        }                                                                                                                                                                                          
    }
    for(int i = 0; i < enemies.size(); ++i) {
        if (player.getSprite().getGlobalBounds().intersects( enemies[i].get().getSprite().getGlobalBounds() ) )
        {
            softReset();
        }    
    }
    
}

void GameLogic::updatePlayerCollisionGirl() {
    if (player.getSprite().getGlobalBounds().intersects( girl.getSprite().getGlobalBounds() ) )
        {
            gameState = 2;
        }          
}

void GameLogic::updateProjectileCollisions() {
    //does nothing yet, eventually loop through projectiles and 
    //check if they are hitting the player or an enemy
    for(int p = 0; p < projectiles.size(); ++p) {
            for(int e = 0; e < enemies.size(); ++e) {
                if (projectiles[p].get().getSprite().getGlobalBounds().intersects( enemies[e].get().getSprite().getGlobalBounds())) {
                    enemies[e].get().setOffScreen();
                    //eventually update score
                }    
            }            
    }
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

std::vector<std::reference_wrapper<Actor>>& GameLogic::getActors() {
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
    player.setDirection(true);
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
    player.setDirection(false);
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
        if (player.getSprite().getPosition().y > 600.f) {
            softReset();
        }
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
        enemy.trackPlayer(player, timeS);
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
    enemy.updateMovement(timeS);
}

void GameLogic::playerShoot(float timeS){
    if ( ! playerFired ) {
        playerFired = true;
        projectile.init(1,player.getSprite().getPosition().x+20,player.getSprite().getPosition().y + 15, player.getDirection());
        //projectiles.push_back(projectile);
        //actorsVector.push_back(projectile);
    }
}
