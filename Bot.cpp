#include "Bot.h"
#include "Nhanvat.h"
#include "Map.h"

Bot::Bot()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    on_ground_ = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_BOT;
}
Bot::~Bot()
{

}
bool Bot::LoadImg(std::string path, SDL_Renderer* screen)
{
    int ret = Object::LoadImg(path, screen);
    if(ret)
    {
        width_frame_ = rect_.w / BOT_FRAME_NUM;
        height_frame_ = rect_.h;

    }
}
 void Bot::set_clips()
 {
     if(width_frame_ > 0 && height_frame_ > 0)
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
 void Bot::Show(SDL_Renderer* des)
 {
     rect_.x = x_pos_ - map_x_;
     rect_.y = y_pos_ - map_y_;
     frame_++;
     if(frame_ >= 8) frame_ = 0;

     SDL_Rect* currentClip = &frame_clip_[frame_];
     SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
     SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);

 }
 void Bot::DoPlayer(Map& map_data, SDL_Renderer* screen)
 {
     x_val_ = 0;
     y_val_ += ROI_SPEED;

     if(y_val_ >= ROI_MAX)
     {
         y_val_ = ROI_MAX;
     }
     if(input_type_.left_ == 1)  x_val_ -= BOT_SPEED;
     else if(input_type_.right_ == 1)  x_val_ += BOT_SPEED;

     CheckMap(map_data, screen);
 }

void Bot::InitBots()
{
    x_val_ = 0;
    y_val_ = 0;
    if(x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else x_pos_ = 0;
    y_pos_ = 0;
    input_type_.left_ = 1;

}

void Bot::CheckMap(Map& map_data, SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //  check ngang
    int height_min = ( height_frame_ < TILE_SIZE ) ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_ ) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_ ) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/ TILE_SIZE;

    if(x1 >0  && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) // dang di chuyen sang phai
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE - (width_frame_ + 1);
                x_val_ = 0;
                input_type_.right_ = 0;
                input_type_.left_ = 1;
                LoadImg("img//bot_left.png", screen);
            }
        }
        else if( x_val_ < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadImg("img//bot_right.png", screen);
            }
        }
    }
    //check doc

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_ ) / TILE_SIZE;
    x2 = (x_pos_ + width_min - 1) / TILE_SIZE;

    y1 = (y_pos_ + y_val_ ) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if( y_val_ > 0 )
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE - (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if( y_val_ <0)
        {
            if( map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if( x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }

}

void Bot::ImpMoveType (SDL_Renderer* screen)
{
    if(type_move_ == STATIC_BOT)
    {
        ;
    }
    else
    {
        if(on_ground_ = true)
        {
            if(x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("img//bot_left.png", screen);
            }
            else if(x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                LoadImg("img//bot_right.png", screen);
            }
        }
        else
        {
            if(input_type_.left_ == 1) LoadImg("img//bot_left.png", screen);
            if(input_type_.right_ == 1) LoadImg("img//bot_right.png", screen);
        }
    }
}



