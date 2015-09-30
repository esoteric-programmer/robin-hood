#ifndef SOUND_INCLUDED
#define SOUND_INCLUDED

#include <3ds.h>
#include "physics.h"

typedef struct {
  unsigned int 	 encoding;
  u32		 	 frequency;
  unsigned int 	 size;
  const char*	 sound_data;
} RawAudio;

class CSound {
private:
	char* buffer;
	unsigned int encoding;
	u32 frequency;
	unsigned int size;
	u32 my_channel;
	static u32 channel;
	float volume;
	Rect display;

public:
	CSound(const RawAudio, float volume = 1.0f);
	
	void play(s16 transpose = 0);
	void set_display_area(Rect display);
	void play_if_source_is_visible(IntVector source);
	void stop();
	void resume();
	~CSound();

};

#endif

