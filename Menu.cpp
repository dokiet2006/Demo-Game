#include "Menu.h"

Menu::Menu() {
    selected_item_ = MENU_PLAY;
}

Menu::~Menu()
{
    menu_background.Free();
    for (int i = 0; i < MENU_TOTAL; i++)
    {
        menu_items[i].Free();
    }
}

bool Menu::LoadMenu(SDL_Renderer* screen)
{
    // Tải hình nền cho menu
    if (!menu_background.LoadImg("img/background8.png", screen))  return false;

    menu_background.SetRect(0, 0);

    if (!menu_items[MENU_PLAY].LoadImg("img/play_button.png", screen))
    {
        return false;
    }
    menu_items[MENU_PLAY].SetRect((SCREEN_WIDTH - 300) / 2, SCREEN_HEIGHT / 2 - 100);

    if (!menu_items[MENU_EXIT].LoadImg("img/exit_button.png", screen))
    {
        return false;
    }
    menu_items[MENU_EXIT].SetRect((SCREEN_WIDTH - 300) / 2, SCREEN_HEIGHT / 2 + 50);

    return true;
}

void Menu::RenderMenu(SDL_Renderer* screen) {

    menu_background.Render(screen);

    for (int i = 0; i < MENU_TOTAL; i++)
    {
        if (i == selected_item_)
        {
            SDL_SetTextureColorMod(menu_items[i].GetObject(), 0, 255, 255);
        }
        else
        {
            SDL_SetTextureColorMod(menu_items[i].GetObject(), 255, 255, 255);
        }
        menu_items[i].Render(screen);
    }
}

int Menu::HandleInput(SDL_Event& event)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // Kiểm tra hover
    for (int i = 0; i < MENU_TOTAL; i++)
    {
        SDL_Rect rect = menu_items[i].GetRect();
        if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
            mouse_y >= rect.y && mouse_y <= rect.y + rect.h)
        {
            selected_item_ = i;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        for (int i = 0; i < MENU_TOTAL; i++)
        {
            SDL_Rect rect = menu_items[i].GetRect();
            if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
                mouse_y >= rect.y && mouse_y <= rect.y + rect.h)
            {
                return i;
            }
        }
    }
    if (event.type == SDL_QUIT)
    {
        return MENU_EXIT;
    }
    return -1;
}
