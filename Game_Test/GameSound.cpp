#include "GameSound.h"


FMOD::System* GameSound::system;

GameSound::GameSound(int soundType, std::string path, bool loop) {
    if (loop) {
        if (soundType == SOUND)
        {
            system->createSound(path.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
        }
        else if (soundType == STREAM)
        {
            system->createStream(path.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
        }

    }
    else {
        if (soundType == SOUND)
        {
            system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
        }
        else if (soundType == STREAM)
        {
            system->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
        }
    }

    channel = NULL;
    volume = SOUND_DEFAULT;
}

GameSound::~GameSound() {
    sound->release();
}


int GameSound::Initialize() {
    FMOD::System_Create(&system);
    system->init(100, FMOD_INIT_NORMAL, 0);

    return 0;
}

int GameSound::Release() {
    system->close();
    system->release();

    return 0;
}


int GameSound::play() {
    system->playSound(sound, NULL, false, &channel);
    return 0;
}

int GameSound::pause() {
    channel->setPaused(true);
    return 0;
}

int GameSound::resume() {
    channel->setPaused(false);
    return 0;
}

int GameSound::stop() {
    channel->stop();
    return 0;
}

int GameSound::volumeUp() {
    if (volume < SOUND_MAX) {
        volume += SOUND_WEIGHT;
    }

    channel->setVolume(volume);

    return 0;
}

int GameSound::volumeDown() {
    if (volume > SOUND_MIN) {
        volume -= SOUND_WEIGHT;
    }

    channel->setVolume(volume);

    return 0;
}


//int GameSound::Update() {
//    channel->isPlaying(&fBool);
//
//    if (fBool) 
//    {
//        system->update();
//    }
//
//    return 0;
//}


int GameSound::Update() {
    //channel->isPlaying(&fBool);

    //if (fBool) 
    {
        system->update();
    }

    return 0;
}

int GameSound::setVolume(float volume)
{
    channel->setVolume(volume);

    return 0;
}