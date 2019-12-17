#include "raylib.h"
#include "game.h"

bool IsColliding(Rectangle origin, Rectangle other) {
    return (CheckCollisionRecs(origin, other));
}

Direction  CollisionDirection(Rectangle origin, Rectangle other) {
    float left = (origin.x + origin.width) - other.x;
    float right = (other.x + other.width) - origin.x;
    float down = (origin.y + origin.height) - other.y;
    float up = (other.y + other.height) - origin.y;

    if (right < left && right < up && right < down) {
        return (RIGHT);
    } else if (left < up && left < down) {
        return (LEFT);
    } else if (up < down) {
        return (UP);
    } else {
        return (DOWN);
    }
}

