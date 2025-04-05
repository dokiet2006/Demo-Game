#ifndef FUNTION_H_
#define FUNTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 20;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BBP = 32;
const int EXPLOSION_WIDTH = 590;
static bool g_game_over = false;

const int RENDER_DRAW_COLOR = 0xff;


enum MenuState {
    MENU_PLAY = 0,
    MENU_EXIT = 1,
    MENU_TOTAL = 2 // Tổng số mục trong menu
};

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define BLANK_TILE 0

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};
extern int g_score;
extern int g_high_score;

#endif //
