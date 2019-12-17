#include "player.h"

void UpdatePlayer(Player *player, float deltaTime) {
    if (IsKeyDown(KEY_D)) {
        player->speed.x += PLAYER_SPEED;
    }

    // A -> Q (qwerty)
    if (IsKeyDown(KEY_A)) {
        player->speed.x -= PLAYER_SPEED;;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        player->speed.y -= PLAYER_JUMP_SPEED;
    }

    // Natural forces
    player->speed.x *= FRICTION;
    player->speed.y += GRAVITY;

    // Apply forces
    player->pos.x += player->speed.x * deltaTime;
    player->pos.y += player->speed.y * deltaTime;
}

void CollidePlayer(Player *player, Direction direction, Rectangle collider) {
    switch (direction) {
        case UP:
            if (player->speed.y < 0) {
                player->speed.y = 0;
                player->pos.y = collider.y + collider.height;
            }
            break;
        case DOWN:
            if (player->speed.y > 0) {
                player->speed.y = 0;
                player->pos.y = collider.y - player->height;
            }
            break;
        case LEFT:
            if (player->speed.x > 0) {
                player->speed.x = 0;
                player->pos.x = collider.x - player->width;
            }
            break;
        case RIGHT:
            if (player->speed.x < 0) {
                player->speed.x = 0;
                player->pos.x = collider.x + collider.width;
            }
            break;
        default:
            break;
    }
}

void DrawPlayer(Player player) {
    DrawRectangle(player.pos.x, player.pos.y, player.width, player.height, player.color);
}

Rectangle PlayerRectangle(Player player) {
    Rectangle rec = { player.pos.x, player.pos.y, player.width, player.height };

    return (rec);
}
