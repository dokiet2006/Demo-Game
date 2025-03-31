#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include "Function.h"
#include "Object.h"

class Object
{
public :
    Object();
    ~Object();
    void SetRect(int const &x , int const &y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    void SetRect(int x, int y, int w, int h)
    {
        rect_.x = x;
        rect_.y = y;
        rect_.w = w;
        rect_.h = h;
    }
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object_;}

    virtual bool LoadImg (std::string path, SDL_Renderer* screen);
    void Render (SDL_Renderer* des , const SDL_Rect* clip = NULL);
    void Free();

protected :
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};


#endif //
