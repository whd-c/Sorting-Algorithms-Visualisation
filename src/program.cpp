#include "program.hpp"

Program::Program() {}

Program::~Program()
{
    CloseWindow();
}

void Program::run()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color({36, 36, 36}));
        EndDrawing();
    }
}