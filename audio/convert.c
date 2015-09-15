// TODO: extract .raw file from .wav files.
//       just use a hex editor to delete anything including "data????"
//       from the wave file, where "????" are four bytes indicating
//       the size of the .raw file.

#include <stdio.h>
#include <string.h>

void main() {
	int offset = 3;
	FILE* handle = fopen("clarinet22kHz.raw","rb");
	fseek(handle, 0L, SEEK_END);
	long size = ftell(handle);
	fseek(handle, 0L, SEEK_SET);
	printf("#include \"../Sound.h\"\n\nextern const CRawAudio FLUTE_SOUND = { \n\
  CSND_ENCODING_PCM16, 22050, %d,\n  \"", (unsigned int)size);
	while (!feof(handle)) {
		unsigned char val = 0;
		if (!fread(&val,1,1,handle))
			break;
		printf("\\%o",val);
		char buf[10];
		sprintf(buf,"\\%o",val);
		offset+=strlen(buf);
		if (offset > 70) {
			printf("\"\n  \"");
			offset = 3;
		}
	}
	printf("\",\n};\n");
	fclose(handle);
}

