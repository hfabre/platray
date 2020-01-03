#include "raylib.h"
#include "player.h"
#include "game.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    EntityNode *entities = 0;

    Player player = { 10, 10, 0, 0, 10, 10, DARKGRAY };
    Entity playerEntity = { &player, PLAYER };

    Rectangle ground = { 0, 400, 800, 50 };
    Entity groundEntity = { &ground, RECTANGLE };

    Rectangle platform = { 0, 350, 300, 20 };
    Entity platformEntity = { &platform, RECTANGLE };

    Rectangle platform2 = { 600, 380, 100, 20 };
    Entity platform2Entity = { &platform2, RECTANGLE };

    AddEntity(&entities, &playerEntity);
    AddEntity(&entities, &groundEntity);
    AddEntity(&entities, &platformEntity);
    AddEntity(&entities, &platform2Entity);

    World world = { entities };

    InitWindow(screenWidth, screenHeight, "platray");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        GameLoop(world, deltaTime);
    }

    CloseWindow();
    return (0);
}

void GameLoop(World world, float deltaTime) {
    Update(world, deltaTime);
    Draw(world);
}

// TODO: Optimize...
void Update(World world, float deltaTime) {
    EntityNode *currNode = world.entities;

    // First pass to calculate new positions
    while (currNode) {
        Entity *currEntity = currNode->entity;

        switch (currEntity->kind) {
            case PLAYER:
                UpdatePlayer(currEntity->object, deltaTime);
                break;
            case RECTANGLE:
                break;
        }

        currNode = currNode->next;
    }

    currNode = world.entities;

    // Second pass to handle collisions
    while (currNode) {
        Entity *currEntity = currNode->entity;
        EntityNode *currObstacle = world.entities;

        switch (currEntity->kind) {
            case PLAYER:
                while (currObstacle) {
                    if (currObstacle->entity->kind != PLAYER) {
                        HandleCollision(currEntity->object, currObstacle->entity->object);
                    }

                    currObstacle = currObstacle->next;
                }
                break;
            case RECTANGLE:
                break;
        }

        currNode = currNode->next;
    }
}

void HandleCollision(Player *player, Rectangle *collider) {
    Rectangle playerBody = PlayerRectangle(*player);

    if (IsColliding(playerBody, *collider)) {
        Direction direction = CollisionDirection(playerBody, *collider);

        CollidePlayer(player, direction, *collider);
    }
}

void Draw(World world) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    EntityNode *currNode = world.entities;

    // Third pass to draw
    while (currNode) {
        Entity *currEntity = currNode->entity;

        switch (currEntity->kind) {
            case PLAYER:
                DrawPlayer(*(Player *)currEntity->object);
                break;
            case RECTANGLE:
                DrawRectangleRec(*(Rectangle *)currEntity->object, DARKGREEN);
                break;
        }

        currNode = currNode->next;
    }

    if (DEBUG) {
        DrawFPS(10, 10);
        ShowPlayerInfo(*GetPlayer(world.entities));
    }

    EndDrawing();
}

void ShowPlayerInfo(Player player) {
    int FPSOffset = 40;

    DrawText(FormatText("Position: %f - %f\n", player.pos.x, player.pos.y), 10, FPSOffset, 10, RED);
    DrawText(FormatText("Speed: %f - %f\n", player.speed.x, player.speed.y), 10, FPSOffset + 10, 10, RED);
}