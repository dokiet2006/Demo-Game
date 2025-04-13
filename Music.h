#ifndef MUSIC_H_
#define MUSIC_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Music {
public:
    Music();
    ~Music();

    bool Init();

    bool LoadSounds();

    void PlayMenuMusic();
    void PlayGameMusic();
    void StopMusic();

    void PlayExplosionSound();
    void PlayMoveSound();
    void PlayJumpSound();
    void PlayCollisionSound();
    void PlayFallSound();
    void PlayRestartSound();

    void FreeSounds();

private:
    Mix_Music* menu_music_;
    Mix_Music* game_music_;
    Mix_Music* explosion_sound_;
    Mix_Chunk* move_sound_;
    Mix_Chunk* jump_sound_;
    Mix_Chunk* collision_sound_;
    Mix_Chunk* fall_sound_;
    Mix_Chunk* restart_sound_;
};

#endif // MUSIC_H_
