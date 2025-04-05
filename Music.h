#ifndef MUSIC_H_
#define MUSIC_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Music {
public:
    Music();
    ~Music();

    // Khởi tạo SDL_mixer
    bool Init();

    // Tải tất cả âm thanh
    bool LoadSounds();

    // Phát nhạc nền
    void PlayMenuMusic();
    void PlayGameMusic();
    void StopMusic();

    // Phát hiệu ứng âm thanh
    void PlayExplosionSound();
    void PlayMoveSound();
    void PlayJumpSound();
    void PlayCollisionSound();
    void PlayFallSound();
    void PlayRestartSound();

    // Giải phóng tài nguyên âm thanh
    void FreeSounds();

private:
    Mix_Music* menu_music_;       // Nhạc nền menu
    Mix_Music* game_music_;       // Nhạc nền game
    Mix_Music* explosion_sound_;  // Âm thanh vụ nổ
    Mix_Chunk* move_sound_;       // Âm thanh di chuyển
    Mix_Chunk* jump_sound_;       // Âm thanh nhảy
    Mix_Chunk* collision_sound_;  // Âm thanh va chạm vụ nổ
    Mix_Chunk* fall_sound_;       // Âm thanh rơi xuống vực
    Mix_Chunk* restart_sound_;    // Âm thanh khi restart
};

#endif // MUSIC_H_
