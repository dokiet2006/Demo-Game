#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Object.h"
#include "Nhanvat.h"

class Explosion : public Object {
public:
    Explosion();
    ~Explosion();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen, int camera_x);
    void Update(); // Cập nhật vị trí vụ nổ
    void SetPosition(int x, int y);
    int GetXPos() const { return x_pos_e; }
    void Reset();
    void UpdateXPosition(int player_x);

private:
    int frame_;
    int x_pos_e; // Tọa độ thực tế của vụ nổ
    int y_pos_e;
    bool m_exploding;
    int speed_; // Tốc độ di chuyển vụ nổ
    SDL_Rect frame_clip_[8];
    const int X_OFFSET = 1000;

};

#endif // EXPLOSION_H_
