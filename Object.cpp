#include "Object.h"

Object::Object()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
Object::~Object()
{
    Free();
}
bool Object::LoadImg (std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface -> w;
            rect_.h = load_surface -> h;
        }

        SDL_FreeSurface(load_surface);
    }
    p_object_ = new_texture;

    return p_object_ != NULL;
}
void Object::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void Object::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

