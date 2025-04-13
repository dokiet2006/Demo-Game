#ifndef MENU_H_
#define MENU_H_

#include "Function.h"
#include "Object.h"

class Menu {
public:
    Menu();
    ~Menu();

    bool LoadMenu(SDL_Renderer* screen);
    void RenderMenu(SDL_Renderer* screen);
    int HandleInput(SDL_Event& event);

private:
    Object menu_background;
    Object menu_items[MENU_TOTAL];
    int selected_item_;
};

#endif // MENU_H_
