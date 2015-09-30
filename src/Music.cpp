#include "Music.h"

CMusic::CMusic(Composition c, const RawAudio instrument, float volume) {
	this->c.n_bars = 0;
	this->c.bars = 0;
	copy_composition(this->c, c);
	this->sound = new CSound(instrument, volume);
	this->playing = false;
	this->paused = false;
	this->sound_active = false;

}

void CMusic::play() {
	this->bar = this->c.n_bars-1;
	this->note = this->c.bars[this->bar].n_notes-1;
	this->note_time_gone = this->c.bars[this->bar].notes[this->note].value-1;
	this->playing = true;
	if (this->sound_active && !this->paused) {
	    this->sound->stop();
	}
	this->paused = false;
	this->sound_active = false;
}

void CMusic::stop() {
	this->playing = false;
	if (this->sound_active && !this->paused) {
	    this->sound->stop();
	}
	this->paused = false;
	this->sound_active = false;
}

void CMusic::update(u16 ticks) {
	if (!this->playing || this->paused)
		return;
	if (this->c.bars == 0)
		return;
	if (this->c.n_bars <= this->bar)
		return;
	if (this->c.bars[this->bar].notes == 0)
		return;
	if (this->c.bars[this->bar].n_notes <= this->note)
		return;
	if (this->c.bars[this->bar].notes[note].value <= this->note_time_gone)
		return;
	while (ticks > 0) {
	
		bool stop = false;
		bool play_new = false;
		this->note_time_gone++;
		if (this->note_time_gone >= this->c.bars[this->bar].notes[note].value) {
			this->note_time_gone = 0;
			this->note++;
			play_new = true;
			if (this->note >= this->c.bars[this->bar].n_notes) {
				this->note = 0;
				this->bar++;
				if (this->bar >= this->c.n_bars) {
					this->bar = 0;
				}
			}
		}else if (this->c.bars[this->bar].notes[note].value < this->note_time_gone+SILENCE_AT_END) {
			stop = true;;
		}
		if (this->sound_active && (stop || play_new)) {
			this->sound->stop();
			this->sound_active = false;
		}
		if (play_new) {
			if (this->c.bars == 0)
				return;
			if (this->c.n_bars < this->bar)
				return;
			if (this->c.bars[this->bar].notes == 0)
				return;
			if (this->c.bars[this->bar].n_notes < this->note)
				return;
			if (this->c.bars[this->bar].notes[note].value < this->note_time_gone)
				return;
			if (this->c.bars[this->bar].notes[note].pitch != REST) {
				this->sound->play(this->c.bars[this->bar].notes[note].pitch);
				this->sound_active = true;
			}
		}
	
		ticks--;
	}
}

void CMusic::pause() {
	if (this->paused)
		return;
	this->paused = true;
	if (this->sound_active) {
		this->sound->stop();
	}
}
void CMusic::resume() {
	if (!this->paused)
		return;
	this->paused = false;
	if (this->sound_active)
		this->sound->resume();
}

CMusic::~CMusic() {
	clear_composition(this->c);
}

