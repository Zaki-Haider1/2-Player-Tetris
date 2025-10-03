#pragma once
#include <raylib.h>

class bgMusic {
public:

	bgMusic(const char*);
	~bgMusic();

	Music soundTrack;

};


bgMusic::bgMusic(const char *soundTrackPath) {

	soundTrack = LoadMusicStream(soundTrackPath);

}

bgMusic::~bgMusic() {

	UnloadMusicStream(soundTrack);

}

