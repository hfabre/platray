#ifndef PLATRAY_GAME_H
#define PLATRAY_GAME_H

#include "player.h"
#include "world.h"

#define DEBUG 1

#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#define MIN(x,y) (((x) > (y)) ? (y) : (x))

// game.c
bool IsColliding(Rectangle origin, Rectangle other);
Direction  CollisionDirection(Rectangle origin, Rectangle other);

// Game loop -> main.c
void HandleCollision(Player *player, Rectangle *collider);
void GameLoop(World world, float deltaTime);
void Update(World world, float deltaTime);
void Draw(World world);
void ShowPlayerInfo(Player player);

#endif //PLATRAY_GAME_H
