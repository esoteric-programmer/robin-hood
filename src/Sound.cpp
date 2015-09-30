#include <string.h>
#include <math.h>
#include "Sound.h"

u32 CSound::channel = 0x8;

CSound::CSound(const RawAudio audio, float volume) {
	this->size = audio.size;
	while (this->size % 4 != 0)
		this->size++;
	this->buffer = (char*)linearAlloc(this->size);
	memcpy(this->buffer,audio.sound_data,audio.size);
	for (u32 i=audio.size; i<this->size;i++)
		this->buffer[i] = 0;
	this->encoding = audio.encoding;
	this->frequency = audio.frequency;
	this->volume = volume;
	this->my_channel = (CSound::channel)++;
	this->display.x1 = 0;
	this->display.y1 = 0;
	this->display.x2 = 0;
	this->display.y2 = 0;
}
	
void CSound::play(s16 transpose) {
	double freq_factor = pow(2.0, ((double)transpose)/12.0);
	u32 play_freq = (u32)(((double)this->frequency) * freq_factor);
	csndPlaySound(this->my_channel, SOUND_ONE_SHOT | SOUND_FORMAT(this->encoding), play_freq, this->volume, 0.0f, this->buffer, 0, this->size);
}

void CSound::set_display_area(Rect display) {
	this->display.x1 = display.x1;
	this->display.y1 = display.y1;
	this->display.x2 = display.x2;
	this->display.y2 = display.y2;
}

void CSound::play_if_source_is_visible(IntVector source) {
	if (source.x < display.x1 || source.x >= display.x2 || source.y < display.y1 || source.y >= display.y2)
		return;
	csndPlaySound(this->my_channel, SOUND_ONE_SHOT | SOUND_FORMAT(this->encoding), this->frequency, this->volume, 0.0f, this->buffer, 0, this->size);
}
	

void CSound::stop() {
	CSND_SetPlayState(this->my_channel, 0);
	csndExecCmds(true);
}

void CSound::resume() {
	CSND_SetPlayState(this->my_channel, 1);
	csndExecCmds(true);
}


CSound::~CSound() {
	linearFree(this->buffer);
}

