#ifndef MUSIC_INCLUDED
#define MUSIC_INCLUDED

#include "tracker_defines.h"
#include "Sound.h"

class CMusic {
private:
	CSound* sound;
	Composition c;
	u16 bar;
	u16 note;
	u16 note_time_gone;
	bool playing;
	bool paused;
	bool sound_active;

public:
	CMusic(Composition c, CRawAudio instrument, float volume = 0.2f);
	void update(u16 ticks);
	void play();
	void pause();
	void resume();
	void stop();
	~CMusic();
};

#endif

