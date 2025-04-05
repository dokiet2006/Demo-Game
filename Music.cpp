#include "Music.h"
#include <iostream>

Music::Music() {
    menu_music_ = nullptr;
    game_music_ = nullptr;
//    explosion_sound_ = nullptr;
    move_sound_ = nullptr;
    jump_sound_ = nullptr;
    collision_sound_ = nullptr;
    fall_sound_ = nullptr;
    restart_sound_ = nullptr;
}

Music::~Music() {
    FreeSounds();
    Mix_CloseAudio();
}

bool Music::Init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Music::LoadSounds() {
    menu_music_ = Mix_LoadMUS("sound/menu_music.mp3");
    game_music_ = Mix_LoadMUS("sound/game_music.mp3");
//    explosion_sound_ = Mix_LoadMUS("sound/explosion.mp3");
    jump_sound_ = Mix_LoadWAV("sound/jump.wav");
    collision_sound_ = Mix_LoadWAV("sound/collision.wav");
    fall_sound_ = Mix_LoadWAV("sound/fall.wav");
    restart_sound_ = Mix_LoadWAV("sound/restart.wav");

//    if (!menu_music_ || !game_music_ || !explosion_sound_ || !move_sound_ ||
//        !jump_sound_ || !collision_sound_ || !fall_sound_ || !restart_sound_) {
//        std::cout << "Failed to load sounds: " << Mix_GetError() << std::endl;
//        return false;
//    }
    return true;
}

void Music::PlayMenuMusic() {
    if (Mix_PlayingMusic()) Mix_HaltMusic();
    Mix_PlayMusic(menu_music_, -1); // Lặp vô hạn
}

void Music::PlayGameMusic() {
    if (Mix_PlayingMusic()) Mix_HaltMusic();
    Mix_PlayMusic(game_music_, -1); // Lặp vô hạn
}

void Music::StopMusic() {
    if (Mix_PlayingMusic()) Mix_HaltMusic();
    Mix_PlayMusic(game_music_, -1); // Lặp vô hạn
}

void Music::PlayExplosionSound() {
    Mix_PlayMusic(game_music_, -1); // Lặp vô hạn
}

void Music::PlayJumpSound() {
    Mix_PlayChannel(-1, jump_sound_, 0);
}

void Music::PlayCollisionSound() {
    Mix_PlayChannel(-1, collision_sound_, 0);
}

void Music::PlayFallSound() {
    Mix_PlayChannel(-1, fall_sound_, 0);
}

void Music::PlayRestartSound() {
    Mix_PlayChannel(-1, restart_sound_, 0);
}

void Music::FreeSounds() {
    if (menu_music_) {
        Mix_FreeMusic(menu_music_);
        menu_music_ = nullptr;
    }
    if (game_music_) {
        Mix_FreeMusic(game_music_);
        game_music_ = nullptr;
    }
    if (explosion_sound_) {
        Mix_FreeMusic(explosion_sound_);
        explosion_sound_ = nullptr;
    }
    if (jump_sound_) {
        Mix_FreeChunk(jump_sound_);
        jump_sound_ = nullptr;
    }
    if (collision_sound_) {
        Mix_FreeChunk(collision_sound_);
        collision_sound_ = nullptr;
    }
    if (fall_sound_) {
        Mix_FreeChunk(fall_sound_);
        fall_sound_ = nullptr;
    }
    if (restart_sound_) {
        Mix_FreeChunk(restart_sound_);
        restart_sound_ = nullptr;
    }
}
