#include "Game.hpp"

#include <kos.h>
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"

const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBlockSize = 480 / 50;

KOS_INIT_FLAGS(INIT_DEFAULT);
Game::Game() {
    
}


struct Block {
    Vector2 position;
    Color color;
};

void Game::run() {
    maple_device_t *controller;
    cont_state_t *cont;

    InitWindow(640, 480, "Block stacking puzzle game in KOS!");
    SetTargetFPS(60);

    Block block;
    block.position = {100, 100};
    block.color = RED;

    int input_cooldown = 0;

    controller = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
    int rot = 0;
    while (true)
    {
        rot++;
        if(input_cooldown > 0)
        {
            input_cooldown--;
        }
        if (input_cooldown == 0 &&  controller)
        {
            input_cooldown = 40;
            cont = (cont_state_t *)maple_dev_status(controller);
            if (cont->buttons & CONT_DPAD_UP)
            {
                block.position.y -= kBlockSize;
            }
            else if (cont->buttons & CONT_DPAD_DOWN)
            {
                block.position.y += kBlockSize;
            }
            else if (cont->buttons & CONT_DPAD_LEFT)
            {
                block.position.x -= kBlockSize;
            }
            else if (cont->buttons & CONT_DPAD_RIGHT)
            {
                block.position.x += kBlockSize;
            }
            else if (cont->buttons & CONT_A)
            {
            }
            else if (cont->buttons & CONT_START)
            {
                break;
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Rot :" + rot, 230, 240, 20, LIGHTGRAY);
        rlTranslatef(block.position.x, block.position.y, 0);
        rlRotatef(rot, 0, 0, 1);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawRectangle(0, 0, kBlockSize, kBlockSize, block.color);
        
        rlRotatef(-rot, 0, 0, 1);
        rlTranslatef(-block.position.x, -block.position.y, 0);
        EndDrawing();
    }
}