# Robin Hood's Platform Game

Robin Hood's Platform Game is a single player platform game.
Can you defeat Sheriff of Nottingham's henchmen and reach the finish?


| Control | Action              |
|:-------:|:------------------- |
| Touch   | Menu Selection      |
| A       | Bounce              |
| B       | Shoot               |
| D-pad   | Move right or left  |
| Start   | Exit game           |
| Select  | Reset current level |
| L + R   | In main menu: cheat that unlocks all levels |

I tried to create almost public domain sources.
However, the clarinet sample, some images and the Makefile are (probably) not public domain (see LICENCE file).
Note that the dependencies (ctrulib, sf2d, ...) are NOT in the public domain. Therefore, the binaries wouldn't be, either.

You need to patch issue https://github.com/xerpi/sf2dlib/issues/41 in sf2dlib before compiling the game. In sf2d_texture.c change TEX\_MIN\_SIZE from 32 to 64.

Changelog :
v0.1.1
	- Makefile supports building cia
	- Updated to work with current sf2d

v0.1
	- Initial Release.
