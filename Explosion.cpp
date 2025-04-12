#include "Explosion.h"

Explosion::Explosion()
{
    frame_ = 0;
    x_pos_e = 0;
    y_pos_e = 0;
    speed_ = 6;
}

Explosion::~Explosion()
{
    Free();
}

bool Explosion::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Object::LoadImg(path, screen);
    if (ret) {
        int frame_width = rect_.w / 8;
        int frame_height = rect_.h;
        for (int i = 0; i < 8; i++) {
            frame_clip_[i] = {i * frame_width, 0, frame_width, frame_height};
        }
    }
    return ret;
}

void Explosion::SetPosition(int x, int y)
{
    x_pos_e = x - 500;
    y_pos_e = y - 50;
}

void Explosion::Show(SDL_Renderer* screen, int camera_x, Music& music)
{

    int render_x = x_pos_e - camera_x;

    SDL_Rect renderQuad = {render_x, y_pos_e, frame_clip_[frame_].w, frame_clip_[frame_].h};
    SDL_RenderCopy(screen, p_object_, &frame_clip_[frame_], &renderQuad);
    if (frame_ == 0)  music.PlayExplosionSound();

    Update();
}

void Explosion::Update() {
    frame_ = (frame_ + 1) % 8;
    x_pos_e += speed_;
    SDL_Delay(50);
}
void Explosion::Reset(Nhanvat& player_pos_)
{
    frame_ = 0;
    m_exploding = false;
    x_pos_e = player_pos_.GetPos() - 200 - EXPLOSION_WIDTH;
    y_pos_e = 50;
    if (x_pos_e < -EXPLOSION_WIDTH)
    {
        x_pos_e = -EXPLOSION_WIDTH;
    }
}
