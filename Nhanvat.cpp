#include "Nhanvat.h"
#include "Map.h"
#include "Explosion.h"
#include "Bot.h"

Nhanvat::Nhanvat()
{
    frame_ = 0;
    x_val = 0;
    y_val = 0;
    x_pos_ = 300;
    y_pos_ = 100;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
}

Nhanvat::~Nhanvat()
{
    Free();
}
void Nhanvat::Reset(const Map& map_data)
{
    frame_ = 0;
    x_val = 0;
    y_val = 0;

    max_random_x = map_data.max_x_ / 3;
    x_pos_ = rand() % max_random_x;
    if (x_pos_ < 0) x_pos_ = 0;

    y_pos_ = 100;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
}

bool Nhanvat::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Object::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = rect_.w / 8;
        height_frame_ = rect_.h;

    }
    return ret;
}

void Nhanvat::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < 8; i++)
        {
            frame_clip_[i].x = i * width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void Nhanvat::show(SDL_Renderer* des)
{

    if(on_ground == true)
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("img/player_left.png", des);
        }
        else
        {
            LoadImg("img/player_right.png", des);
        }
    }
    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }
    if (frame_ >= 8) frame_ = 0;

        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip_ = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, p_object_, current_clip_, &renderQuad);

}

void Nhanvat::HandelInputAction(SDL_Event events, SDL_Renderer* screen, Music& music)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            case SDLK_RIGHT:
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                input_type_.up_ = 0;
                if (on_ground == true) {
                    LoadImg("img//player_right.png", screen);
                } else {
                    LoadImg("img//jum_right.png", screen);
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                input_type_.up_ = 0;
                if (on_ground == true) {
                    LoadImg("img//player_left.png", screen);
                } else {
                    LoadImg("img//jum_left.png", screen);
                }
                break;
            case SDLK_SPACE:
                input_type_.jump_ = 1;
                if(status_ == WALK_RIGHT) LoadImg("img//jum_right.png",screen);
                else if(status_ == WALK_LEFT) LoadImg("img//jum_left.png",screen);
                music.PlayJumpSound();
                break;
            default:
                break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            case SDLK_RIGHT:
                input_type_.right_ = 0;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                input_type_.left_ = 0;
                break;
            case SDLK_SPACE:
                input_type_.jump_ = 0;
                break;
            default:
                break;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN )
    {
        if(events.button.button == SDL_BUTTON_RIGHT )
        {
            input_type_.jump_ = 1;
            if (on_ground) music.PlayJumpSound();
        }
    }
}

void Nhanvat::DoPlayer(Map& map_data, Explosion& explosion, Music& music)
{
    x_val = 0;
    y_val += ROI_SPEED;

    if(y_val >= ROI_MAX)
    {
        y_val = ROI_MAX;
    }

    if(input_type_.left_ == 1)
    {
        x_val -= PLAYER_SPEED;
        g_score -= 10;
    }
    else if(input_type_.right_ == 1)
    {
        x_val += PLAYER_SPEED;
        g_score += 10;
    }

    if(input_type_.jump_ == 1)
    {
        if(on_ground == true)
        {
            y_val = - PLAYER_JUMP_VAL ;
        }
        on_ground = false;
        input_type_.jump_ = 0;
    }
    if (x_pos_ <= explosion.GetXPos() + EXPLOSION_WIDTH)
    {
        g_game_over = true ;
    }

    CheckMap(map_data);
    CenterEntityOnMap(map_data);

}

void Nhanvat::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }
}

void Nhanvat::CheckMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //  check ngang
    int height_min = ( height_frame_ < TILE_SIZE ) ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + OFFSET_X + x_val ) / TILE_SIZE;
    x2 = (x_pos_ + x_val + width_frame_ - OFFSET_X - 1) / TILE_SIZE;

    y1 = (y_pos_ + OFFSET_Y) / TILE_SIZE;
    y2 = (y_pos_ + height_min - OFFSET_Y - 1)/ TILE_SIZE;

    if(x1 >0  && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE - (width_frame_ + 1 - OFFSET_X);
                x_val = 0;
            }
        }
        else if( x_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * TILE_SIZE - OFFSET_X;
                x_val = 0;
            }
        }
    }


    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_ + OFFSET_X) / TILE_SIZE;
    x2 = (x_pos_ + width_min - OFFSET_X - 1) / TILE_SIZE;

    y1 = (y_pos_ + y_val + OFFSET_Y) / TILE_SIZE;
    y2 = (y_pos_ + y_val - OFFSET_Y + height_frame_ - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if( y_val > 0 )
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE - (height_frame_ + 1 - OFFSET_Y);
                y_val = 0;
                on_ground = true;
            }
        }
        else if( y_val <0)
        {
            if( map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * TILE_SIZE - OFFSET_Y;
                y_val = 0;
            }
        }
    }

    x_pos_ += x_val;
    y_pos_ += y_val;

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if( x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }
    if(y_pos_ > map_data.max_y_)
    {
        g_game_over = true;
    }
}
bool Nhanvat::IsDead(const Map& map_data ) const
{
    return (y_pos_ > map_data.max_y_);
}
bool Nhanvat::IsDeadByExplosion(const Explosion& explosion) const
{
    return (x_pos_ <= explosion.GetXPos() + EXPLOSION_WIDTH);
}
bool Nhanvat::CheckCollisionWithBot(const Bot& bot) const
{
    int player_left = x_pos_;
    int player_right = x_pos_ + width_frame_;
    int player_top = y_pos_;
    int player_bottom = y_pos_ + height_frame_;

    int bot_left = bot.get_x_pos();
    int bot_right = bot.get_x_pos() + bot.get_width_frame();
    int bot_top = bot.get_y_pos();
    int bot_bottom = bot.get_y_pos() + bot.get_height_frame();

    if (player_right - 2 * OFFSET_X > bot_left && player_left - 2 * OFFSET_X < bot_right &&
        player_bottom - 2 * OFFSET_Y > bot_top && player_top - 2 * OFFSET_Y < bot_bottom)
    {
        return true;
    }
    return false;
}
