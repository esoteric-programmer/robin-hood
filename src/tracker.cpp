#include "tracker.h"

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

  #define BAR(x, n, ...) { \
    (x).n_notes = (n); \
    Note notes[(n)] = { __VA_ARGS__ }; \
    (x).notes = new Note[n]; \
    memcpy((x).notes, notes, (n)*sizeof(Note)); \
  }

  Composition c;
  c.n_bars = 32;
  c.bars = new Bar[32];

  BAR(c.bars[0], 9,
    {C5, EIGHTH_NOTE},
    {F4, EIGHTH_NOTE},
    {F4, EIGHTH_NOTE},
    {D5, EIGHTH_NOTE},
    {C5, QUARTER_NOTE},
    {B4-1, SIXTEENTH_NOTE},
    {A4, SIXTEENTH_NOTE},
    {B4-1, SIXTEENTH_NOTE},
    {C5, SIXTEENTH_NOTE});


  BAR(c.bars[1], 10,
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

  BAR(c.bars[2], 10,
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

  BAR(c.bars[3], 10,
    {F4, EIGHTH_NOTE},
    {G4, SIXTEENTH_NOTE},
    {A4, SIXTEENTH_NOTE},
    {B4-1, EIGHTH_NOTE},
    {A4, EIGHTH_NOTE},
    {A4, THIRTY_SECOND_NOTE},{B4-1, THIRTY_SECOND_NOTE},{A4, SIXTEENTH_NOTE},
    {G4, QUARTER_NOTE},
    {REST, EIGHTH_NOTE});


  BAR(c.bars[4], 10,
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

  BAR(c.bars[5], 10,
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


  BAR(c.bars[6], 12,
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

  BAR(c.bars[7], 16,
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
  
  BAR(c.bars[8], 11,
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
  
  BAR(c.bars[9], 11,
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

  BAR(c.bars[10], 16,
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

  BAR(c.bars[11], 15,
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

  BAR(c.bars[12], 9,
    {C5, EIGHTH_NOTE},
    {G4, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE},
    {G4, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE},
    {B4, SIXTEENTH_NOTE},
    {A4, SIXTEENTH_NOTE},
    {G4, EIGHTH_NOTE},
    {F4, EIGHTH_NOTE});

  BAR(c.bars[13], 6,
    {E4, QUARTER_NOTE},
    {D4, THIRTY_SECOND_NOTE},{E4, THIRTY_SECOND_NOTE},{D4, QUARTER_NOTE-SIXTEENTH_NOTE},
    {C4, QUARTER_NOTE+EIGHTH_NOTE},
    {REST, EIGHTH_NOTE});


  BAR(c.bars[14], 6,
    {G4, EIGHTH_NOTE},
    {E4, EIGHTH_NOTE},
    {E4, EIGHTH_NOTE},
    {G4, EIGHTH_NOTE},
    {C4+1, QUARTER_NOTE},
    {B4-1, QUARTER_NOTE});
  
  BAR(c.bars[15], 9,
    {A4, EIGHTH_NOTE},
    {G4, SIXTEENTH_NOTE},
    {F4, SIXTEENTH_NOTE},
    {G4, EIGHTH_NOTE},
    {F4, SIXTEENTH_NOTE},
    {E4, SIXTEENTH_NOTE},
    {F4, EIGHTH_NOTE},
    {D4, QUARTER_NOTE+SIXTEENTH_NOTE},
    {REST, SIXTEENTH_NOTE});

  BAR(c.bars[16], 6,
    {C5, EIGHTH_NOTE},
    {A4, EIGHTH_NOTE},
    {A4, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE},
    {F4+1, QUARTER_NOTE},
    {E5-1, QUARTER_NOTE});

  BAR(c.bars[17], 9,
    {D5, EIGHTH_NOTE},
    {C5, SIXTEENTH_NOTE},
    {B4-1, SIXTEENTH_NOTE},
    {C5, EIGHTH_NOTE},
    {B4-1, SIXTEENTH_NOTE},
    {A4, SIXTEENTH_NOTE},
    {B4-1, EIGHTH_NOTE},
    {G4, QUARTER_NOTE},
    {A4, EIGHTH_NOTE});
  
  BAR(c.bars[18], 11,
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

  BAR(c.bars[19], 12,
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

  BAR(c.bars[20], 11,
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

  BAR(c.bars[21], 6,
    {B3-1, EIGHTH_NOTE},
    {G4, EIGHTH_NOTE},
    {A3, EIGHTH_NOTE},
    {F4+1, EIGHTH_NOTE},
    {G3, QUARTER_NOTE + EIGHTH_NOTE},
    {REST, EIGHTH_NOTE});

  BAR(c.bars[22], 13,
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

  BAR(c.bars[23], 13,
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

  BAR(c.bars[24], 10,
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

  BAR(c.bars[25], 16,
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

  BAR(c.bars[26], 16,
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

  BAR(c.bars[27], 9,
    {G4, EIGHTH_NOTE},
    {C4, EIGHTH_NOTE},
    {B4-1, QUARTER_NOTE},
    {A4, EIGHTH_NOTE},
    {G4, SIXTEENTH_NOTE},
    {F4, SIXTEENTH_NOTE},
    {G4, EIGHTH_NOTE},
    {F4, SIXTEENTH_NOTE},
    {E4, SIXTEENTH_NOTE});

  BAR(c.bars[28], 10,
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

  BAR(c.bars[29], 12,
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

  BAR(c.bars[30], 9,
    {F5, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE},
    {F5, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE},
    {F5, EIGHTH_NOTE},
    {E5, SIXTEENTH_NOTE},
    {D5, SIXTEENTH_NOTE},
    {C5, EIGHTH_NOTE},
    {B4-1, EIGHTH_NOTE});

  BAR(c.bars[31], 6,
    {A4, QUARTER_NOTE},
    {G4, THIRTY_SECOND_NOTE},{A4, THIRTY_SECOND_NOTE},{G4, QUARTER_NOTE-SIXTEENTH_NOTE},
    {F4, QUARTER_NOTE+EIGHTH_NOTE},
    {REST, EIGHTH_NOTE});

return c;
}

