// GIMP RGB-Image (no alpha channel)
// should be converted to alpha channel only image
// code for converting it is below (compile, then execute; converted image is printed to stdout)

#include <stdio.h>
#include <string.h>

// GIMP RGB C-Source image dump (300.c) * /

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; // 2:RGB16, 3:RGB, 4:RGBA 
  unsigned char	 pixel_data[879 * 16 * 3 + 1];
} TEMPO_FONT = {
  879, 16, 3,
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377RRRCCC\377\377\377\377\377\377\377\377\377(((\230\230\230\377"
  
  ... include GIMP export of file "300 tempofont 18pt.png" to C code here, then you can build the file ...
  
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377",
};

void main() {
int offset = 3;
unsigned int i;
for (i=0;i< TEMPO_FONT.width * TEMPO_FONT.height * TEMPO_FONT.bytes_per_pixel; i+=TEMPO_FONT.bytes_per_pixel) {
	unsigned int value = (unsigned int)TEMPO_FONT.pixel_data[i];
	value += (unsigned int)TEMPO_FONT.pixel_data[i+1];
	value += (unsigned int)TEMPO_FONT.pixel_data[i+2];
	value /= 3;
	value = 255-value;
	int was_escaped = 0;
	unsigned char val = (unsigned char)value;
		printf("\\%o",val);
		char buf[10];
		sprintf(buf,"\\%o",val);
		offset+=strlen(buf);
	if (offset > 70) {
		printf("\"\n  \"");
		offset = 3;
		}
}
}


