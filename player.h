#ifndef PLATRAY_PLAYER_H
#define PLATRAY_PLAYER_H

#include "raylib.h"
#include "direction.h"

#define PLAYER_SPEED 100
#define PLAYER_JUMP_SPEED 400
#define FRICTION .80
#define GRAVITY 20

typedef struct Player {
    Vector2 pos;
    Vector2 speed;
    int width;
    int height;
    Color color;
} Player;

void UpdatePlayer(Player *player, float deltaTime);
void CollidePlayer(Player *player, Direction direction, Rectangle collider);
void DrawPlayer(Player player);
Rectangle PlayerRectangle(Player player);

#endif //PLATRAY_PLAYER_H
