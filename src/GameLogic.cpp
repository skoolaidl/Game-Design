#include "GameLogic.h"
#include <iostream>
#include <time.h> 
#include <algorithm>
#include <cmath>

/*
GameLogic class that holds all of the game objects and detects collisions
and updates game status
*/

void GameLogic::init(int wWidth, int wHeight) {
    srand(time(NULL));
    width = wWidth;
    height = wHeight;
    gravity = 300.f;
    gameState = 0;
    player.init();  
    loader.init();
    playerShot = false;
    enemyShot = false;
    playerHit = false;
    enemyHit = false;

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
        for(int p = 0; p < projectiles.size(); ++p) {
            if ( !projectiles[p].get().checkDistance()) {
                projectiles[p].get().setAvailable();
                removeFromActorsVector(projectiles[p].get());
                projectiles.erase(projectiles.begin() + p);   
            }
            else {
				projectiles[p].get().setVelocity(timeS);
                projectiles[p].get().updateMovement();
            }
        }
       
        updatePlayerCollisionSpikesEnemy();
        updateProjectileCollisions();
        updatePlayerCollisionGirl();
        updateCountDown(timeS);
    }

}

int GameLogic::removeRandomInt(std::vector<int>& vec)
{
    int n = rand() % vec.size();
    std::swap(vec[n], vec.back());
    int randElement = vec.back();
    vec.pop_back();
    return randElement;
}

void GameLogic::setRandomEnemiesColor(std::vector<Enemy>& defaultEnemies, int enemyCount)
{
    std::vector<int> enemyTypes;
    for(int i = 0; i < enemyCount; ++i)
    {
        enemyTypes.push_back(0);
        enemyTypes.push_back(1);
        enemyTypes.push_back(2);
        enemyTypes.push_back(3);
    }
    int index = 0;
    while(!enemyTypes.empty())
    {
        int randType = removeRandomInt(enemyTypes);
        defaultEnemies[index].setColor(randType);
        index++;
    }
}

void GameLogic::setLevel(int level) {
    if(level > 4 || level < 0)
    {
        level = 0;
    }
    currentLevel = level;
    //load specified level
    setCountDown(300);
    scores[level] = 0;
    playerFail = false;
    scoreMultiplier = 1;
    player.init();
    loader.init();
    actorsVector.clear();
    platforms.clear();
    spikes.clear();
    enemies.clear();
    
    loader.loadLevel(currentLevel);
    platformVector = loader.getPlatforms();
    spikeVector = loader.getSpikes();
    enemyVector = loader.getEnemies();
    girl = loader.getGirl();
    //randomize enemy types
    if(level == 0)
    {
        setRandomEnemiesColor(enemyVector, 2);
    }
    else
    {
        setRandomEnemiesColor(enemyVector, 3);
    }

    for (int i = 0; i < platformVector.size(); i++) {
        platformVector[i].setTexture();
        actorsVector.push_back(platformVector[i]);
        platforms.push_back(platformVector[i]);
    }
    for (int i = 0; i < spikeVector.size(); i++) {
        spikeVector[i].setTexture();
        actorsVector.push_back(spikeVector[i]);
        spikes.push_back(spikeVector[i]);
    }
    for (int i = 0; i < enemyVector.size(); i++) {
        enemyVector[i].setTexture();
        actorsVector.push_back(enemyVector[i]);
        enemies.push_back(enemyVector[i]);
    }
    actorsVector.push_back(girl);
}

void GameLogic::updateCountDown(float timeS)
{
    if(countDown <= 0)
    {
        playerFail = true;
        gameState = 5;
        return;
    }
    if(currTime - startTime > 1.f)
    {
        countDown--;
        startTime = timeS;
        currTime = timeS;
    }
    currTime+=timeS;
}

bool GameLogic::getPlayerFail()
{
    return playerFail;
}

void GameLogic::setCountDown(int levelTime)
{
    countDown = levelTime;
}

int GameLogic::getCountDown()
{
    return countDown;
}

Actor& GameLogic::getGirl(){
    return girl;
}

void GameLogic::softReset() {
    //return player character to beginning of level
    player.resetPosition();
    //reset score multiplier
    scoreMultiplier = 1;
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
        if (player.getAnimatedSprite().getGlobalBounds().intersects( spikes[i].get().getSprite().getGlobalBounds() ) )
        {
            softReset();
            playerHit = true;
        }                                                                                                                                                                                          
    }
    for(int i = 0; i < enemies.size(); ++i) {
        if (player.getAnimatedSprite().getGlobalBounds().intersects( enemies[i].get().getSprite().getGlobalBounds() ) )
        {
            softReset();
            playerHit = true;
        }    
    }
    
}

void GameLogic::updatePlayerCollisionGirl() {
    if (player.getAnimatedSprite().getGlobalBounds().intersects( girl.getSprite().getGlobalBounds() ) )
        {
            playerFail = (getScore(currentLevel) < getGoalScore(currentLevel));
            gameState = 5;
        }          
}

void GameLogic::updateProjectileCollisions() {
    //loop through projectiles and check if they are hitting the player or an enemy
    for(int p = 0; p < projectiles.size(); ++p) {
        if (projectiles[p].get().getType() == 0) {
            if (projectiles[p].get().getSprite().getGlobalBounds().intersects(player.getAnimatedSprite().getGlobalBounds())) {
                softReset();
                playerHit = true;
                projectiles[p].get().setAvailable();
                removeFromActorsVector(projectiles[p].get());
                projectiles.erase(projectiles.begin() + p);
            }
        }
        else if (projectiles[p].get().getType() == 1) { //must be bullet, type is 1
            for (int e = 0; e < enemies.size(); ++e) {
                if (projectiles[p].get().getSprite().getGlobalBounds().intersects(enemies[e].get().getSprite().getGlobalBounds())) {
                    projectiles[p].get().setAvailable();
                    enemyHit = true;
                    //update score
                    if(killPreferences[enemies[e].get().getType()])
                    {
                        changeScore(currentLevel, pointsPerKill * scoreMultiplier);
                        scoreMultiplier++;
                    }
                    else
                    {
                        scoreMultiplier = 1;
                        if(scores[currentLevel] > 0)
                        {
                            changeScore(currentLevel, -1 * pointsPerKill);
                        }
                    }
                    removeFromActorsVector(enemies[e].get());
                    enemies.erase(enemies.begin() + e);
                    removeFromActorsVector(projectiles[p].get());
                    projectiles.erase(projectiles.begin() + p);                    
                }
            }
        }
    }
}

void GameLogic::removeFromActorsVector(Actor& actor) {
    for (int i = 0; i < actorsVector.size(); ++i) {
        if (actor == actorsVector[i].get()) {
            actorsVector.erase(actorsVector.begin() + i);
            return;
        }
    }
    return;
}

void GameLogic::changeScore(int level, int increase) {
    //only if using level 1 not 0 level--;
    if ( level >= 0 && level <= scores.size()-1 ) {
        scores[level] = scores[level] + increase;
    }
    else {
        //invalid level
    }
}

unsigned int GameLogic::getScore(int level) {
    if (level < 0 || level > scores.size()-1) {
        return 0;
    }
    return scores[level];
}

unsigned int GameLogic::getGoalScore(int level) {
    if (level < 0 || level > scores.size()-1) {
        return 0;
    }
    return goalScores[level];
}

bool GameLogic::setScore(int level, unsigned int score) {
    if (level < 0 || level > scores.size()-1) {
        return false;
    }
    scores[level] = score;
    return true;
}

void GameLogic::resetScores() {
    for (int i = 0; i < scores.size(); ++i) {
        scores[i] = 0;
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
        if (actor.isAnimated())
        {
            if (actor.getAnimatedSprite().getGlobalBounds().intersects(objVector[i].get().getSprite().getGlobalBounds() ) )
            {
                return true;
            }
        }
        else 
        {
            if (actor.getSprite().getGlobalBounds().intersects(objVector[i].get().getSprite().getGlobalBounds() ) )
            {
                return true;
            }
        }
        
    }
    return false;
}

bool GameLogic::updatePlatformCollisions(Actor actor)
{
    for(int i = 0; i < platforms.size(); ++i)
    {
        if (actor.getSprite().getGlobalBounds().intersects(platforms[i].get().getSprite().getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void GameLogic::updatePlayerCollision(float timeS)
{
    float playerX = player.getAnimatedSprite().getPosition().x;
    float playerY = player.getAnimatedSprite().getPosition().y;
    float playerWidth = player.getAnimatedSprite().getGlobalBounds().width;
    float playerHeight = player.getAnimatedSprite().getGlobalBounds().height;
    float bufferSpaceY = player.getStepSizeY() * timeS;
    float bufferSpaceX = player.getStepSizeX() * timeS;
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
        playerJumping++;
        player.setVelocityY((-1*player.getStepSizeY()) * timeS);
    }
    else
    {
        playerJumping = 0;
        playerFall(timeS);
    }

}

void GameLogic::playerFall(float timeS) {
    if (player.isInAir()) //if player is not going up and not on ground then fall
    {
        player.setFalling(true); //player has already jumped and needs to fall before jumping again
        player.setVelocityY(gravity * timeS);
        if (player.getAnimatedSprite().getPosition().y > 600.f) {
            softReset();
            playerHit = true;
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
    enemy.setPaused(false); 
    if (player.getAnimatedSprite().getPosition().x >= enemy.getStartX() - enemy.getMaxLeftDistance() 
        && player.getAnimatedSprite().getPosition().x <= enemy.getStartX() + enemy.getMaxRightDistance())
     {
		if (enemy.trackPlayer(player, timeS)) {
			enemyShoot(enemy);
		}
     }
}

void GameLogic::updateEnemyMovement(Enemy& enemy, float timeS) {
    //randomizes direction of enemy once he is created
    if(enemy.getVelocityX() == 0.f)
    {
        int dir = rand() % 2;
        float currVelX = ((dir == 0) ? -1 : 1) * enemy.getStepSize() * timeS;
        enemy.setVelocityX(currVelX);
        enemy.setDirection(dir);
    }
    //sets velocity to normal velocity if the delta time was unusually slow or fast
    if(std::abs(enemy.getVelocityX()) <= enemy.getStepSize() * timeS / 2.f || std::abs(enemy.getVelocityX()) >= enemy.getStepSize() * timeS * 2.f)
    {
        float normVelX = ((enemy.getDirection() == true) ? 1 : -1) * enemy.getStepSize() * timeS;
        enemy.setVelocityX(normVelX);
    }
    enemyFall(enemy, timeS);
    enemyTrack(enemy, timeS);
    enemy.updateMovement();
}

void GameLogic::playerShoot(){
    if ( player.getBullet().getIsAvailable() ) {
		sf::Vector2f pos = player.getAnimatedSprite().getPosition();
        player.getBullet().init(1,pos.x+player.getBulletOffsetX(),pos.y + player.getBulletOffsetY(), player.getDirection());
        projectiles.push_back(player.getBullet());
        actorsVector.push_back(player.getBullet());
        playerShot = true;
    }
}

void GameLogic::enemyShoot(Enemy& enemy) {
	if (enemy.getProjectile().getIsAvailable()) {
		sf::Vector2f pos = enemy.getSprite().getPosition();
		enemy.getProjectile().init(0, pos.x + enemy.getProjectileOffsetX(), pos.y + enemy.getProjectileOffsetY(), enemy.getDirection());
		projectiles.push_back(enemy.getProjectile());
		actorsVector.push_back(enemy.getProjectile());
        enemyShot = true;
	}
}


void GameLogic::addPreference(std::string pref, int type)
{
    if(pref == "Kill")
    {
        killPreferences[type] = true;
    }
    else if(pref == "Ignore")
    {
        killPreferences[type] = false;
    }
}
