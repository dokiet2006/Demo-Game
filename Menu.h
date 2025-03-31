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
    int HandleInput(SDL_Event& event); // Trả về lựa chọn của người dùng

private:
    Object menu_background; // Thêm background cho menu
    Object menu_items[MENU_TOTAL]; // Mảng chứa các mục menu
    int selected_item_; // Mục đang được chọn
};

#endif // MENU_H_
