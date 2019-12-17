#include "raylib.h"
#include "player.h"
#include "game.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    Player player = { 10, 10, 0, 0, 10, 10, DARKGRAY };
    Rectangle ground = { 0, 400, 800, 50 };
    Rectangle platform = { 0, 350, 300, 20 };
    Rectangle platform2 = { 600, 380, 100, 20 };
    World world = { &player, &ground, &platform, &platform2 };

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

void Update(World world, float deltaTime) {
    UpdatePlayer(world.player, deltaTime);
    HandleCollision(world.player, world.ground);
    HandleCollision(world.player, world.platform);
    HandleCollision(world.player, world.platform2);
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

    DrawPlayer(*world.player);
    DrawRectangleRec(*world.ground, DARKGREEN);
    DrawRectangleRec(*world.platform, DARKGREEN);
    DrawRectangleRec(*world.platform2, DARKGREEN);

    if (DEBUG) {
        DrawFPS(10, 10);
        ShowPlayerInfo(*world.player);
    }

    EndDrawing();
}

void ShowPlayerInfo(Player player) {
    int FPSOffset = 40;

    DrawText(FormatText("Position: %f - %f\n", player.pos.x, player.pos.y), 10, FPSOffset, 10, RED);
    DrawText(FormatText("Speed: %f - %f\n", player.speed.x, player.speed.y), 10, FPSOffset + 10, 10, RED);
}