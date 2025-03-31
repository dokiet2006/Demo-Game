#include "Menu.h"

Menu::Menu() {
    selected_item_ = MENU_PLAY; // Mặc định chọn "Play"
}

Menu::~Menu() {
    menu_background.Free(); // Giải phóng background
    for (int i = 0; i < MENU_TOTAL; i++) {
        menu_items[i].Free();
    }
}

bool Menu::LoadMenu(SDL_Renderer* screen) {
    // Tải hình nền cho menu
    if (!menu_background.LoadImg("img/background8.png", screen)) {
        return false;
    }
    menu_background.SetRect(0, 0); // Đặt background đầy màn hình (0, 0)

    // Tải hình ảnh cho "Play" (300x100)
    if (!menu_items[MENU_PLAY].LoadImg("img/play_button.png", screen)) {
        return false;
    }
    menu_items[MENU_PLAY].SetRect((SCREEN_WIDTH - 300) / 2, SCREEN_HEIGHT / 2 - 100); // Đặt vị trí giữa màn hình

    // Tải hình ảnh cho "Exit" (300x100)
    if (!menu_items[MENU_EXIT].LoadImg("img/exit_button.png", screen)) {
        return false;
    }
    menu_items[MENU_EXIT].SetRect((SCREEN_WIDTH - 300) / 2, SCREEN_HEIGHT / 2 + 50); // Đặt cách "Play" một khoảng

    return true;
}

void Menu::RenderMenu(SDL_Renderer* screen) {
    // Vẽ background trước
    menu_background.Render(screen);

    // Vẽ các mục menu
    for (int i = 0; i < MENU_TOTAL; i++) {
        if (i == selected_item_) {
            SDL_SetTextureColorMod(menu_items[i].GetObject(), 255, 255, 0); // Vàng khi được chọn/hover
        } else {
            SDL_SetTextureColorMod(menu_items[i].GetObject(), 255, 255, 255); // Trắng bình thường
        }
        menu_items[i].Render(screen);
    }
}

int Menu::HandleInput(SDL_Event& event) {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y); // Lấy tọa độ chuột

    // Kiểm tra hover để thay đổi selected_item_
    for (int i = 0; i < MENU_TOTAL; i++) {
        SDL_Rect rect = menu_items[i].GetRect();
        if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
            mouse_y >= rect.y && mouse_y <= rect.y + rect.h) {
            selected_item_ = i; // Cập nhật mục được chọn khi chuột hover
        }
    }

    // Xử lý sự kiện click chuột
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        for (int i = 0; i < MENU_TOTAL; i++) {
            SDL_Rect rect = menu_items[i].GetRect();
            if (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
                mouse_y >= rect.y && mouse_y <= rect.y + rect.h) {
                return i; // Trả về mục được click
            }
        }
    }

    if (event.type == SDL_QUIT) {
        return MENU_EXIT; // Thoát khi nhấn nút đóng cửa sổ
    }

    return -1; // Chưa chọn gì
}
