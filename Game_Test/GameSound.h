#pragma once
#include <fmod.hpp>
#include <iostream>
#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f


class GameSound {
private:
    enum SoundType
    {
        SOUND,
        STREAM

    }soundType;

    static FMOD::System* system; //FMOD system objectsystem;
    FMOD::Channel* channel;
    FMOD::Sound* sound;

    bool fBool;
    float volume;
public:
    GameSound(int soundType, std::string path, bool loop);
    ~GameSound();

    static int Initialize();
    static int Release();
    static int Update();
    //int Update();

    int play();
    int pause();
    int resume();
    int stop();
    int volumeUp();
    int volumeDown();

    int setVolume(float volume);


};


