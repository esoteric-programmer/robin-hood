#include "tracker_defines.h"

void clear_composition(Composition& c) {
	if (c.bars != 0) {
		for (u16 i=0;i<c.n_bars;i++) {
			if (c.bars[i].notes != 0) {
				delete c.bars[i].notes;
				c.bars[i].notes = 0;
			}
		}
		delete c.bars;
		c.bars = 0;
	}
	c.n_bars = 0;
}

void copy_composition(Composition& dest, Composition src) {
	clear_composition(dest);
	dest.n_bars = src.n_bars;
	dest.bars = new Bar[dest.n_bars];
	for (u16 i=0;i<dest.n_bars;i++) {
		dest.bars[i].n_notes = src.bars[i].n_notes;
		dest.bars[i].notes = new Note[dest.bars[i].n_notes];
		memcpy(dest.bars[i].notes, src.bars[i].notes, dest.bars[i].n_notes*sizeof(Note));
	}
}

/**
 * Create flute notes for Telemann's Sonata in F Major (from "Der getreue Music-Meister")
 */
Composition telemann_sonata_f() {

#define BAR(x, n, ...) { (x).n_notes = (n); Note notes[(n)] = { __VA_ARGS__ }; (x).notes = new Note[n]; memcpy((x).notes, notes, (n)*sizeof(Note)); }

Bar bar1;
BAR(bar1, 9,
  {C5, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {D5, EIGHTH_NOTE},
  {C5, QUARTER_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE});


Bar bar2;
BAR(bar2, 10,
  {A4, QUARTER_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {F4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE});

Bar bar3;
BAR(bar3, 10,
  {F4, QUARTER_NOTE},
  {C5, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE});

Bar bar4;
BAR(bar4, 10,
  {F4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, EIGHTH_NOTE},
  {A4, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE/2},{B4-1, SIXTEENTH_NOTE/2},{A4, SIXTEENTH_NOTE},
  {G4, QUARTER_NOTE},
  {REST, EIGHTH_NOTE});


Bar bar5;
BAR(bar5, 10,
  {G4, EIGHTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {A4, QUARTER_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {D4, EIGHTH_NOTE},
  {E4, EIGHTH_NOTE});

Bar bar6;
BAR(bar6, 10,
  {F4, EIGHTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {G4, QUARTER_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {C4, EIGHTH_NOTE},
  {D4, EIGHTH_NOTE});


Bar bar7;
BAR(bar7, 12,
  {E4, EIGHTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {F4, EIGHTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {A4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE});

Bar bar8;
BAR(bar8, 16,
  {B4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {D5, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {E5, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE});
  
Bar bar9;
BAR(bar9, 11,
  {B4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {D5, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F5, QUARTER_NOTE});
  
Bar bar10;
BAR(bar10, 11,
  {E5, EIGHTH_NOTE},
  {D5, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {D5, EIGHTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {B4, SIXTEENTH_NOTE},
  {C5, EIGHTH_NOTE},
  {B4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE});

Bar bar11;
BAR(bar11, 16,
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE});

Bar bar12;
BAR(bar12, 15,
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {C4, EIGHTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4, SIXTEENTH_NOTE});

Bar bar13;
BAR(bar13, 9,
  {C5, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {C5, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {C5, EIGHTH_NOTE},
  {B4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE});

Bar bar14;
BAR(bar14, 6,
  {E4, QUARTER_NOTE},
  {D4, SIXTEENTH_NOTE/2},{E4, SIXTEENTH_NOTE/2},{D4, QUARTER_NOTE-SIXTEENTH_NOTE},
  {C4, QUARTER_NOTE+EIGHTH_NOTE},
  {REST, EIGHTH_NOTE});


Bar bar15;
BAR(bar15, 6,
  {G4, EIGHTH_NOTE},
  {E4, EIGHTH_NOTE},
  {E4, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {C4+1, QUARTER_NOTE},
  {B4-1, QUARTER_NOTE});
  
Bar bar16;
BAR(bar16, 9,
  {A4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, EIGHTH_NOTE},
  {D4, QUARTER_NOTE+SIXTEENTH_NOTE},
  {REST, SIXTEENTH_NOTE});

Bar bar17;
BAR(bar17, 6,
  {C5, EIGHTH_NOTE},
  {A4, EIGHTH_NOTE},
  {A4, EIGHTH_NOTE},
  {C5, EIGHTH_NOTE},
  {F4+1, QUARTER_NOTE},
  {E5-1, QUARTER_NOTE});

Bar bar18;
BAR(bar18, 9,
  {D5, EIGHTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, EIGHTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, EIGHTH_NOTE},
  {G4, QUARTER_NOTE},
  {A4, EIGHTH_NOTE});
  
Bar bar19;
BAR(bar19, 11,
  {B4-1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {B4-1, EIGHTH_NOTE},
  {G4, QUARTER_NOTE},
  {A4, EIGHTH_NOTE});

Bar bar20;
BAR(bar20, 12,
  {B4-1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {D5, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {G5, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE});

Bar bar21;
BAR(bar21, 11,
  {B4-1, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4+1, SIXTEENTH_NOTE},
  {E4-1, SIXTEENTH_NOTE},
  {D4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE});

Bar bar22;
BAR(bar22, 6,
  {B3-1, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {A3, EIGHTH_NOTE},
  {F4+1, EIGHTH_NOTE},
  {G3, QUARTER_NOTE + EIGHTH_NOTE},
  {REST, EIGHTH_NOTE});

Bar bar23;
BAR(bar23, 13,
  {G4, QUARTER_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {D4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE});

Bar bar24;
BAR(bar24, 13,
  {C5, QUARTER_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE});

Bar bar25;
BAR(bar25, 10,
  {D5, QUARTER_NOTE},
  {C5, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {D5, SIXTEENTH_NOTE},
  {B4-1, QUARTER_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE});

Bar bar26;
BAR(bar26, 16,
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE});

Bar bar27;
BAR(bar27, 16,
  {G4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE},
  {C4, SIXTEENTH_NOTE});

Bar bar28;
BAR(bar28, 9,
  {G4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE},
  {B4-1, QUARTER_NOTE},
  {A4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {G4, EIGHTH_NOTE},
  {F4, SIXTEENTH_NOTE},
  {E4, SIXTEENTH_NOTE});

Bar bar29;
BAR(bar29, 10,
  {F4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, QUARTER_NOTE},
  {C5, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE});

Bar bar30;
BAR(bar30, 12,
  {F4, EIGHTH_NOTE},
  {C4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {F4, EIGHTH_NOTE},
  {G4, SIXTEENTH_NOTE},
  {A4, SIXTEENTH_NOTE},
  {B4-1, SIXTEENTH_NOTE},
  {C5, SIXTEENTH_NOTE},
  {D5, SIXTEENTH_NOTE},
  {E5, SIXTEENTH_NOTE});

Bar bar31;
BAR(bar31, 9,
  {F5, EIGHTH_NOTE},
  {C5, EIGHTH_NOTE},
  {F5, EIGHTH_NOTE},
  {C5, EIGHTH_NOTE},
  {F5, EIGHTH_NOTE},
  {E5, SIXTEENTH_NOTE},
  {D5, SIXTEENTH_NOTE},
  {C5, EIGHTH_NOTE},
  {B4-1, EIGHTH_NOTE});

Bar bar32;
BAR(bar32, 6,
  {A4, QUARTER_NOTE},
  {G4, SIXTEENTH_NOTE/2},{A4, SIXTEENTH_NOTE/2},{G4, QUARTER_NOTE-SIXTEENTH_NOTE},
  {F4, QUARTER_NOTE+EIGHTH_NOTE},
  {REST, EIGHTH_NOTE});

Composition c;
c.n_bars = 32;
c.bars = new Bar[32];
memcpy(c.bars, &bar1, sizeof(Bar));
memcpy(c.bars+1, &bar2, sizeof(Bar));
memcpy(c.bars+2, &bar3, sizeof(Bar));
memcpy(c.bars+3, &bar4, sizeof(Bar));
memcpy(c.bars+4, &bar5, sizeof(Bar));
memcpy(c.bars+5, &bar6, sizeof(Bar));
memcpy(c.bars+6, &bar7, sizeof(Bar));
memcpy(c.bars+7, &bar8, sizeof(Bar));
memcpy(c.bars+8, &bar9, sizeof(Bar));
memcpy(c.bars+9, &bar10, sizeof(Bar));
memcpy(c.bars+10, &bar11, sizeof(Bar));
memcpy(c.bars+11, &bar12, sizeof(Bar));
memcpy(c.bars+12, &bar13, sizeof(Bar));
memcpy(c.bars+13, &bar14, sizeof(Bar));
memcpy(c.bars+14, &bar15, sizeof(Bar));
memcpy(c.bars+15, &bar16, sizeof(Bar));
memcpy(c.bars+16, &bar17, sizeof(Bar));
memcpy(c.bars+17, &bar18, sizeof(Bar));
memcpy(c.bars+18, &bar19, sizeof(Bar));
memcpy(c.bars+19, &bar20, sizeof(Bar));
memcpy(c.bars+20, &bar21, sizeof(Bar));
memcpy(c.bars+21, &bar22, sizeof(Bar));
memcpy(c.bars+22, &bar23, sizeof(Bar));
memcpy(c.bars+23, &bar24, sizeof(Bar));
memcpy(c.bars+24, &bar25, sizeof(Bar));
memcpy(c.bars+25, &bar26, sizeof(Bar));
memcpy(c.bars+26, &bar27, sizeof(Bar));
memcpy(c.bars+27, &bar28, sizeof(Bar));
memcpy(c.bars+28, &bar29, sizeof(Bar));
memcpy(c.bars+29, &bar30, sizeof(Bar));
memcpy(c.bars+30, &bar31, sizeof(Bar));
memcpy(c.bars+31, &bar32, sizeof(Bar));
return c;
}

