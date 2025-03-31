#include <fstream>
#include "Function.h"
#include "Object.h"
#include "Map.h"
#include "Nhanvat.h"
#include "Timer.h"
#include "Explosion.h"
#include "Menu.h"
#include "Text.h"

Object g_background;
Object game_over_image;

bool InitData() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Demo Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        success = false;
    } else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success = false;
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) success = false;

            if (TTF_Init() == -1) {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            if (!game_over_image.LoadImg("img/gameover.png", g_screen)) {
                printf("Failed to load game over image!\n");
                success = false;
            }
            game_over_image.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    std::ifstream highscore_file("highscore.txt");
    if (highscore_file.is_open()) {
        highscore_file >> g_high_score;
        highscore_file.close();
    }

    return success;
}

void SaveHighScore() {
    std::ofstream highscore_file("highscore.txt");
    if (highscore_file.is_open()) {
        highscore_file << g_high_score;
        highscore_file.close();
    }
}

bool LoadBackground() {
    bool ret = g_background.LoadImg("img/background4.png", g_screen);
    if (ret == false) return false;
    return true;
}

void close() {
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!InitData()) return -1;

    Text score_text;
    if (!score_text.LoadFont("Arial.ttf", 26)) {
        printf("Failed to load font!\n");
        return -1;
    }

    SDL_Color text_color = {255, 255, 255, 255};
    Menu start_menu;
    if (!start_menu.LoadMenu(g_screen)) return -1;

    bool in_menu = true;
    int menu_choice = -1;

    while (in_menu) {
        while (SDL_PollEvent(&g_event) != 0) {
            menu_choice = start_menu.HandleInput(g_event);
            if (menu_choice != -1) {
                in_menu = false;
            }
        }

        SDL_RenderClear(g_screen);
        start_menu.RenderMenu(g_screen);
        SDL_RenderPresent(g_screen);
    }

    if (menu_choice == MENU_EXIT) {
        close();
        return 0;
    }

    if (!LoadBackground()) return -1;

    Timer fps_timer;
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    Nhanvat p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();

    Explosion explosionEffect;
    explosionEffect.LoadImg("img/explosion_spritesheet.png", g_screen);
    explosionEffect.SetPosition(0, 100);

    bool is_quit = false;
    bool game_over = false;
    bool game_restart = false;

while (!is_quit) {
    fps_timer.start();

    while (SDL_PollEvent(&g_event) != 0) {
        if (g_event.type == SDL_QUIT) {
            is_quit = true;
        }

        if (game_over) {
            if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_SPACE) {
                // Reset toàn bộ trạng thái game
                game_over = false;
                g_game_over = false;
                game_restart = true;
            }
        } else {
            p_player.HandelInputAction(g_event, g_screen);
        }
    }

    // Xử lý restart game
    if (game_restart) {
        // Reset điểm số (nếu muốn, hoặc giữ nguyên điểm tùy logic game)
        g_score = 0;

        // Reset player
        p_player.Reset();
        p_player.LoadImg("img//player_right.png", g_screen);
        p_player.set_clips();

        // Reset map (tải lại map từ đầu)
        game_map.LoadMap("map/map01.dat");

        // Reset explosion
        explosionEffect.Reset();


        game_restart = false;
    }

    // Render game
    SDL_RenderClear(g_screen);

    if (!game_over) {
        // Render game bình thường
        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data, explosionEffect);
        p_player.show(g_screen);

        game_map.setMap(map_data);
        game_map.DrawMap(g_screen);

        explosionEffect.Show(g_screen, map_data.start_x_);

        // Hiển thị điểm số
        std::string score_str = "Score: " + std::to_string(g_score);
        score_text.RenderText(g_screen, score_str, 20, 20, text_color);

        std::string high_score_str = "High Score: " + std::to_string(g_high_score);
        score_text.RenderText(g_screen, high_score_str, 20, 50, text_color);

        // Kiểm tra game over
        if (p_player.IsDead(map_data) || p_player.IsDeadByExplosion(explosionEffect)) {
            game_over = true;
            if (g_score > g_high_score) {
                g_high_score = g_score;
                SaveHighScore();
            }
        }
    } else {
        // Hiển thị màn hình game over
        game_over_image.Render(g_screen);

        // Hiển thị hướng dẫn nhấn Space để chơi lại (màu đen)
        SDL_Color white_color = {255, 255, 255, 255};

        std::string score_str = "Score: " + std::to_string(g_score);
        score_text.RenderText(g_screen, score_str,
                        SCREEN_WIDTH / 2 - 50,
                        SCREEN_HEIGHT / 2 + 180,
                        white_color);

        std::string restart_text = "Press SPACE to restart";
        score_text.RenderText(g_screen, restart_text,
                            SCREEN_WIDTH / 2 - 100,
                            SCREEN_HEIGHT / 2 + 230,
                            white_color);
    }

    SDL_RenderPresent(g_screen);

    // Giới hạn FPS
    int real_time = fps_timer.get_ticks();
    int time_one_frame = 1000 / FRAME_PER_SECOND;
    if (real_time < time_one_frame) {
        SDL_Delay(time_one_frame - real_time);
    }
}


    SaveHighScore();
    close();
    return 0;
}

