// Licence of this file: CC0 1.0 (public domain).

// ugly code in main() function. sorry for that!

// TODO: timing
//       u64 osGetTime(); returns number of milliseconds since 1st Jan 1900 00:00.
// TODO: Level 4: Add clouds and nature (trees, flowers, stones)
// TODO: always check success of allocating memory
// TODO: buffer "Highscore: %d"-texture.
// TODO: enable 3D (clouds in background)
// TODO: add piano to background music (cf. Telemann's Sonata in F Major)
// TODO: use more constants and put them into a header file

// TODO: when Robin shot an arrow, he should take a new one from the quiver (add an animation!)


#include <stdio.h>
#include <string.h>

#include <3ds.h>
#include <sf2d.h>

#include "defines.h"
#include "Texture.h"
#include "Animated.h"
#include "Robin.h"
#include "ArrowList.h"
#include "Landscape.h"
#include "LandscapeList.h"
#include "Enemy.h"
#include "EnemyList.h"
#include "ButtonArray.h"
#include "ButtonsForwardsBackwards.h"
#include "TempoFont.h"
#include "Sound.h"
#include "Music.h"



RawImage BACKGROUND;
extern const CRawImage SPLASH_SCREEN;
extern const CRawImage ROBIN_RIGHT;
extern const CRawImage ROBIN_WALKING_RIGHT;
extern const CRawImage GRASS;
extern const CRawImage GRASS_LEFT;
extern const CRawImage GRASS_RIGHT;
extern const CRawImage GRASS_LEFT_RIGHT;
extern const CRawImage FINISH;
extern const CRawImage FINISH_GERMAN;
extern const CRawImage ENEMY_RIGHT;
extern const CRawImage ENEMY_WALKING_RIGHT;
extern const CRawImage ARROW;
extern const CRawImage SOLID_BLOCK;
extern const CRawImage ENEMY_ATTACK;

extern const CRawImage FLOWER1_1;
extern const CRawImage FLOWER1_2;
extern const CRawImage TREE;
extern const CRawImage STONES;

extern const CRawImage CLOUD_1;
extern const CRawImage CLOUD_2;
extern const CRawImage CLOUD_3;

extern const CRawImage TOUCH_BG;
extern const CRawImage BUTTON;
extern const CRawImage BUTTON_ACTIVE;
extern const CRawImage TEXT_START;
extern const CRawImage TEXT_START_ACTIVE;
extern const CRawImage TEXT_LEVEL_SELECT;
extern const CRawImage TEXT_LEVEL_SELECT_ACTIVE;
extern const CRawImage TEXT_EXIT;
extern const CRawImage TEXT_EXIT_ACTIVE;
extern const CRawImage TEXT_GIVE_UP;
extern const CRawImage TEXT_GIVE_UP_ACTIVE;
extern const CRawImage TEXT_PAUSE;
extern const CRawImage TEXT_PAUSE_ACTIVE;
extern const CRawImage TEXT_RESUME;
extern const CRawImage TEXT_RESUME_ACTIVE;
extern const CRawImage TEXT_PLAY;
extern const CRawImage TEXT_PLAY_ACTIVE;
extern const CRawImage TEXT_BACK;
extern const CRawImage TEXT_BACK_ACTIVE;
extern const CRawImage NEXT;
extern const CRawImage NEXT_ACTIVE;
extern const CRawImage TEXT_LEVEL;
extern const CRawImage TEXT_CONTINUE;
extern const CRawImage TEXT_CONTINUE_ACTIVE;
extern const CRawImage TEXT_QUIT;
extern const CRawImage TEXT_QUIT_ACTIVE;

extern const CRawImage INFOBOX;
extern const CRawImage TEXT_NEW_HIGHSCORE;
extern const CRawImage TEXT_YOUR_SCORE;

extern const CRawImage TEMPO_FONT_NUMBERS_BIG;
extern const CRawImage TEMPO_FONT;

extern const CRawAudio JUMP_SOUND;
extern const CRawAudio SHOOTING_SOUND;
extern const CRawAudio THROWING_KNIFE_SOUND;
extern const CRawAudio CLARINET_SOUND;

sf2d_texture* tempo_font_numbers_big_texture = 0;

CTexture* grass_texture[4];
CTexture* cloud_texture[3];
CTexture* solid_block_texture;
CTexture* enemy_anim_textures[2];
CTexture* flower1_anim_textures[2];
CTexture* tree_texture;
CTexture* stones_texture;

bool load_level(u16 level, CLandscapeList* landscapelist, CLandscapeList* naturelist, CLandscapeList* cloudlist, CCollidable* finish, CEnemyList* enemylist, CArrowList* attacks, CRobin* robin, CArrowList* arrows, s16& level_width, s16& level_height, u16& score, u16& bonus, CSound* enemy_attack_snd, u16& current_highscore, FILE* handle);

u16 draw_number_big(s16 x, s16 y, u16 number, bool get_width);

/*
u64 last_tick = 0;
u32 time_left() {
	u64 cur_tick = osGetTime();
	if (last_tick == 0)
		last_tick = cur_tick;
	u32 left = (u32)((cur_tick-last_tick)*7/100);
	u32 tmp = ((cur_tick-last_tick)*7%100);
	last_tick = cur_tick;
	return left;
}
*/

int main() {
	//srand(osGetTime()); // needs stdlib.h
	sf2d_init();
	csndInit();
	
	bool in_game = false;
	bool show_score = false;
	bool new_highscore = false;
	bool in_level_select_menu = false;
	bool paused = false;
	u16 current_highscore = 0;

	BACKGROUND.width=32;
	BACKGROUND.height=SCREEN_HEIGHT;
	BACKGROUND.bytes_per_pixel = 4;
	char* data = new char[32*SCREEN_HEIGHT*4];
	for (u16 i=0; i<SCREEN_HEIGHT; i++) {
		for (u16 j=0; j<32; j++) {
			data[(i*BACKGROUND.width + j)*4] = 0;
			data[(i*BACKGROUND.width + j)*4+1] = (255*i)/SCREEN_HEIGHT;
			data[(i*BACKGROUND.width + j)*4+2] = 255;
			data[(i*BACKGROUND.width + j)*4+3] = 255;
		}
	}
	BACKGROUND.pixel_data = data;

	CTexture* background_texture = new CTexture(BACKGROUND);
	CAnimated background(0, 0, &background_texture, 1, 1);
	
	CTexture* splash_texture = new CTexture(SPLASH_SCREEN);
	CAnimated splash(0, 0, &splash_texture, 1, 1);

	//Sprites
	grass_texture[0] = new CTexture(GRASS);
	grass_texture[1] = new CTexture(GRASS_LEFT);
	grass_texture[2] = new CTexture(GRASS_RIGHT);
	grass_texture[3] = new CTexture(GRASS_LEFT_RIGHT);
	solid_block_texture = new CTexture(SOLID_BLOCK);
	
	cloud_texture[0] = new CTexture(CLOUD_1);
	cloud_texture[1] = new CTexture(CLOUD_2);
	cloud_texture[2] = new CTexture(CLOUD_3);
	
	CTexture* finish_texture = new CTexture(FINISH);
	Rect finish_bounding_box = {0,0,(s16)FINISH.width,(s16)FINISH.height};
	
	CTexture* arrow_texture = new CTexture(ARROW);
	Rect arrow_bounding_box = {0,0,(s16)ARROW.width,(s16)ARROW.height};
	CArrowList* arrowlist = new CArrowList(70, &arrow_texture, 1, 1, arrow_bounding_box, 2.0f);
	
	CTexture* enemy_attack_texture = new CTexture(ENEMY_ATTACK);
	Rect enemy_attack_bounding_box = {0,0,(s16)ENEMY_ATTACK.width,(s16)ENEMY_ATTACK.height};
	CArrowList* attacklist = new CArrowList(70, &enemy_attack_texture, 1, 1, enemy_attack_bounding_box, 2.0f);
	
	CTexture* robin_anim_textures[2];
	robin_anim_textures[0] = new CTexture(ROBIN_RIGHT);
	robin_anim_textures[1] = new CTexture(ROBIN_WALKING_RIGHT);
	Rect robin_bounding_box = {13,0,35,48};
	
	enemy_anim_textures[0] = new CTexture(ENEMY_RIGHT);
	enemy_anim_textures[1] = new CTexture(ENEMY_WALKING_RIGHT);
	
	flower1_anim_textures[0] = new CTexture(FLOWER1_1);
	flower1_anim_textures[1] = new CTexture(FLOWER1_2);
	tree_texture = new CTexture(TREE);
	stones_texture = new CTexture(STONES);
	
	Color dark_green = {27,64,52};
	tempo_font_numbers_big_texture = sf2d_create_texture(TEMPO_FONT_NUMBERS_BIG.width, TEMPO_FONT_NUMBERS_BIG.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	sf2d_fill_texture_from_RGBA8(tempo_font_numbers_big_texture, TEMPO_FONT_NUMBERS_BIG.pixel_data, TEMPO_FONT_NUMBERS_BIG.width, TEMPO_FONT_NUMBERS_BIG.height);
	sf2d_texture_tile32(tempo_font_numbers_big_texture);
	
	// Level
	s16 level_width = 960;
	s16 level_height = 256;
	CLandscapeList* landscapelist = new CLandscapeList;
	CLandscapeList* naturelist = new CLandscapeList;
	CLandscapeList* cloudlist = new CLandscapeList;
	CCollidable* finish = new CCollidable(928, -32-FINISH.height, &finish_texture, 1, 1, finish_bounding_box);
	
	CSound* jump = new CSound(JUMP_SOUND, 0.5f);
	CSound* shoot = new CSound(SHOOTING_SOUND, 1.0f);
	CSound* enemy_attack = new CSound(THROWING_KNIFE_SOUND, 1.0f);
	CRobin robin(0, -32-ROBIN_RIGHT.height, robin_anim_textures, 2, 15, robin_bounding_box, 1.4f, landscapelist, level_width, level_height, 0.15f, arrowlist, 35, jump, shoot);
	
	CEnemyList* enemylist = new CEnemyList(arrowlist);
	
	CTexture* touch_background = new CTexture(TOUCH_BG);
	CTexture* button_textures[2];
	button_textures[0] = new CTexture(BUTTON);
	button_textures[1] = new CTexture(BUTTON_ACTIVE);
	CTexture* text_start_textures[2];
	text_start_textures[0] = new CTexture(TEXT_START);
	text_start_textures[1] = new CTexture(TEXT_START_ACTIVE);
	CTexture* text_level_select_textures[2];
	text_level_select_textures[0] = new CTexture(TEXT_LEVEL_SELECT);
	text_level_select_textures[1] = new CTexture(TEXT_LEVEL_SELECT_ACTIVE);
	CTexture* text_exit_textures[2];
	text_exit_textures[0] = new CTexture(TEXT_EXIT);
	text_exit_textures[1] = new CTexture(TEXT_EXIT_ACTIVE);
	CTexture* text_pause_textures[2];
	text_pause_textures[0] = new CTexture(TEXT_PAUSE);
	text_pause_textures[1] = new CTexture(TEXT_PAUSE_ACTIVE);
	CTexture* text_resume_textures[2];
	text_resume_textures[0] = new CTexture(TEXT_RESUME);
	text_resume_textures[1] = new CTexture(TEXT_RESUME_ACTIVE);
	CTexture* text_play_textures[2];
	text_play_textures[0] = new CTexture(TEXT_PLAY);
	text_play_textures[1] = new CTexture(TEXT_PLAY_ACTIVE);
	CTexture* text_back_textures[2];
	text_back_textures[0] = new CTexture(TEXT_BACK);
	text_back_textures[1] = new CTexture(TEXT_BACK_ACTIVE);
	CTexture* text_give_up_textures[2];
	text_give_up_textures[0] = new CTexture(TEXT_GIVE_UP);
	text_give_up_textures[1] = new CTexture(TEXT_GIVE_UP_ACTIVE);
	CTexture* text_continue_textures[2];
	text_continue_textures[0] = new CTexture(TEXT_CONTINUE);
	text_continue_textures[1] = new CTexture(TEXT_CONTINUE_ACTIVE);
	CTexture* text_quit_textures[2];
	text_quit_textures[0] = new CTexture(TEXT_QUIT);
	text_quit_textures[1] = new CTexture(TEXT_QUIT_ACTIVE);
	CButtonArray* touch_buttons = new CButtonArray(button_textures, 2);

	CTexture* infobox_texture = new CTexture(INFOBOX);
	CTexture* text_new_highscore_texture = new CTexture(TEXT_NEW_HIGHSCORE);
	CTexture* text_your_score_texture = new CTexture(TEXT_YOUR_SCORE);
	
	u16 unlocked_level = 1;
	FILE* handle = fopen("savegame.dat","r+b");
	if (handle != 0) {
		fread(&unlocked_level,sizeof(u16),1,handle);
	}else{
		handle = fopen("savegame.dat","w+b");
	}
	if (unlocked_level < 1)
		unlocked_level = 1;
	
	touch_buttons->set_button(0, text_start_textures, 2);
	if (unlocked_level>1) {
		touch_buttons->set_button(1, text_level_select_textures, 2);
	}else{
		touch_buttons->set_button(1, 0, 0);
	}
	touch_buttons->set_button(2, text_exit_textures, 2);


	CTexture* text_level_texture;
	text_level_texture = new CTexture(TEXT_LEVEL);
	CTexture* next_textures[2];
	next_textures[0] = new CTexture(NEXT);
	next_textures[1] = new CTexture(NEXT_ACTIVE);
	CButtonsForwardsBackwards* fwbw_buttons = new CButtonsForwardsBackwards(next_textures, 2, TOUCH_SCREEN_WIDTH - NEXT.width - 20);

	
	//touch_buttons->set_enabled(1, unlocked_level>1);
	

	u16 current_level = 1;
	u16 score = 0;
	u16 bonus = 0;
	bool redraw_bonus_or_score = true;
	u16 ticks = 0;

	Font tempo_font = create_tempo_font();
	Rect four_digits_rect = get_string_bounding_box("0000", tempo_font, true);
	#define N_TMP_TEXT 4
	CTexture* tmp_text[N_TMP_TEXT];
	for (u16 i=0; i<N_TMP_TEXT; i++) {
		tmp_text[i] = 0;
	}
	Rect tmp_text_bb_i[N_TMP_TEXT];
	Rect tmp_text_bb_o[N_TMP_TEXT];
	tmp_text_bb_i[0].x2 = 0;
	

	Composition telemann = telemann_sonata_f();
	CMusic* music = new CMusic(telemann, CLARINET_SOUND, 0.1f);
	clear_composition(telemann);
	
	u32 kDown;
	u32 kHeld;
	//u32 kUp;
	touchPosition stylus;
	bool left_pressed;
	bool right_pressed;
	bool b_pressed;
	bool a_pressed;
	
	
	//mode_debug = true;
	//mode_game = true;
	while (aptMainLoop())
	{
		//gspWaitForVBlank(); // timing?? <- osGetTime();
		u32 ticks_left = 1;//time_left();
		hidScanInput();

		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		//kUp = hidKeysUp();
		s16 btn_pushed = -1;

		hidTouchRead(&stylus);

		left_pressed = (((kDown | kHeld) & KEY_LEFT) != 0);
		right_pressed = (((kDown | kHeld) & KEY_RIGHT) != 0);
		a_pressed = (((kDown | kHeld) & KEY_A) != 0);
		b_pressed = (((kDown | kHeld) & KEY_B) != 0);
		
		if (in_game && !show_score) {
		
			btn_pushed = touch_buttons->update(stylus, ((kHeld | kDown) & KEY_TOUCH)!=0, false, false, false, 0);
	
		
		if ((kDown & KEY_START)!=0 || btn_pushed == 2) {
			// LEAVE GAME
			in_game = false;
			music->stop();
			jump->stop();
			shoot->stop();
			enemy_attack->stop();
			paused = false;
			for (u16 i=0; i<N_TMP_TEXT; i++) {
				if (tmp_text[i] != 0) {
					delete tmp_text[i];
					tmp_text[i] = 0;
				}
			}
			if (in_level_select_menu) {
				touch_buttons->set_button(0, 0, 0);
				touch_buttons->set_button(1, text_play_textures, 2);
				touch_buttons->set_button(2, text_back_textures, 2);
				load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle);
			}else{
				touch_buttons->set_button(0, text_start_textures, 2);
				if (unlocked_level>1) {
					touch_buttons->set_button(1, text_level_select_textures, 2);
				}else{
					touch_buttons->set_button(1, 0, 0);
				}
				touch_buttons->set_button(2, text_exit_textures, 2);

				//touch_buttons->set_enabled(1, unlocked_level>1);
			}
			continue;
		}
		
		if ((kDown & KEY_SELECT) != 0 || btn_pushed == 1) {
			// PAUSE/RESUME GAME
			paused = !paused;
			if (paused) {
				music->pause();
				jump->stop();
				shoot->stop();
				enemy_attack->stop();
			}else{
				music->resume();
			}
			touch_buttons->set_button(1, paused?text_resume_textures:text_pause_textures, 2);
		}
		
		if (!paused) {
			if (robin.left_landscape()) {
				// LOST LIVE; RESET LEVEL
				jump->stop();
				shoot->stop();
				enemy_attack->stop();
				if (!load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle)) {
					// unexpected error; quit application...
					break;
				}
				redraw_bonus_or_score = true;
				ticks = 0;
			}
		
			if (robin.check_collision(finish)) {
				// WON!
				jump->stop();
				shoot->stop();
				enemy_attack->stop();
				if (unlocked_level < current_level+1) {
					unlocked_level = current_level+1;
					if (handle != 0) {
						fseek(handle,0,SEEK_SET);
						fwrite(&unlocked_level,sizeof(u16),1,handle);
						fflush(handle);
					}
				}
				// TODO: stop and show score; check for highscore
				
				// CHECK FOR HIGHSCORE
				new_highscore = false;
				if (score + bonus > current_highscore) {
					// SAVE HIGHSCORE!
					u16 new_score = score + bonus;
					new_highscore = true;
					if (handle != 0) {
						if (fseek(handle,0,SEEK_END) == 0) {
							u32 filesize = ftell(handle);
							while (filesize < current_level*sizeof(u16)) {
								u16 zero = 0;
								fwrite(&zero, sizeof(u16),1,handle);
								filesize += sizeof(u16);
							}
							if (fseek(handle,current_level*sizeof(u16),SEEK_SET)==0) {
								fwrite(&new_score,sizeof(u16),1,handle);
								fflush(handle);
							}
						}
					}
				}
				show_score = true;
				// change buttons...
				touch_buttons->set_button(1, text_continue_textures, 2);
				touch_buttons->set_button(2, text_quit_textures, 2);
				continue;
			}
		
				arrowlist->update(ticks_left);
				u16 destroyed_enemies = 0;
				enemylist->update(ticks_left, &destroyed_enemies);
				score += destroyed_enemies*100;
				attacklist->update(ticks_left);
				//landscapelist->update(1);
				naturelist->update(ticks_left);
				cloudlist->update(ticks_left);

				if (right_pressed)
					robin.walk(1.0f);
				else if (left_pressed)
					robin.walk(-1.0f);
				else
					robin.walk(0.0f);
				if (b_pressed)
					robin.shoot();
				if (a_pressed)
					robin.jump();
				robin.update(ticks_left);
				if (attacklist->collide(&robin)) {
					robin.force_dying();
				}
				if (enemylist->check_collision(&robin)) {
					robin.force_dying();
				}
				ticks+=ticks_left;
				if (ticks >= 20) {
					if (bonus >= ticks/20) {
						redraw_bonus_or_score = true;
						bonus -= ticks/20;
					} else if (bonus > 0) {
						redraw_bonus_or_score = true;
						bonus = 0;
					}
					ticks%=20;
				}
			}
		}else if (!in_game && !in_level_select_menu){
		
			btn_pushed = touch_buttons->update(stylus, ((kHeld | kDown) & KEY_TOUCH)!=0, false, false, false, 0);
		
			if (btn_pushed == 0) {
				current_level = 1;
				if (load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle)) {
					redraw_bonus_or_score = true;
					for (u16 i=0; i<N_TMP_TEXT; i++) {
						if (tmp_text[i] != 0) {
							delete tmp_text[i];
							tmp_text[i] = 0;
						}
					}
					ticks = 0;
					in_game = true;
					music->play();
					Rect screen = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, 0};
					enemy_attack->set_display_area(screen);
					paused = false;
					touch_buttons->set_button(0, 0, 0);
					touch_buttons->set_button(1, text_pause_textures, 2);
					touch_buttons->set_button(2, text_give_up_textures, 2);
					continue;
				}
			}
			
			if (btn_pushed == 1) {
				//Show Level Select submenu
				in_level_select_menu = true;
				touch_buttons->set_button(0, 0, 0);
				touch_buttons->set_button(1, text_play_textures, 2);
				touch_buttons->set_button(2, text_back_textures, 2);
				//fwbw_buttons->set_distance(240);
				load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle);
				continue;
			}
			
			if ((kDown & KEY_START) != 0 || btn_pushed == 2) {
				break;
			}
			
			if ((((kDown | kHeld) & KEY_L) != 0) && (((kDown | kHeld) & KEY_R) != 0)) {
				unlocked_level = 5;
				if (handle != 0) {
					fseek(handle,0,SEEK_SET);
					fwrite(&unlocked_level,sizeof(u16),1,handle);
					fflush(handle);
				}
				touch_buttons->set_button(1, text_level_select_textures, 2);
			}
			
		} else if (!in_game) {
			// in_level_select_menu
			btn_pushed = touch_buttons->update(stylus, ((kHeld | kDown) & KEY_TOUCH)!=0, false, false, false, 0);
		
			if (btn_pushed == 1 || (kDown & KEY_A) != 0) {
				if (load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle)) {
					redraw_bonus_or_score = true;
					for (u16 i=0; i<N_TMP_TEXT; i++) {
						if (tmp_text[i] != 0) {
							delete tmp_text[i];
							tmp_text[i] = 0;
						}
					}
					ticks = 0;
					in_game = true;
					music->play();
					Rect screen = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, 0};
					enemy_attack->set_display_area(screen);
					paused = false;
					touch_buttons->set_button(0, 0, 0);
					touch_buttons->set_button(1, text_pause_textures, 2);
					touch_buttons->set_button(2, text_give_up_textures, 2);
					continue;
				}
			}
			
			if (btn_pushed == 2 || (kDown & KEY_START) != 0 || (kDown & KEY_B) != 0) {
				// BACK TO MAIN MENU
				in_level_select_menu = false;
				touch_buttons->set_button(0, text_start_textures, 2);
				if (unlocked_level>1) {
					touch_buttons->set_button(1, text_level_select_textures, 2);
				}else{
					touch_buttons->set_button(1, 0, 0);
				}
				touch_buttons->set_button(2, text_exit_textures, 2);
				continue;
			}
			
			s16 fwbw_pushed = fwbw_buttons->update(stylus, ((kHeld | kDown) & KEY_TOUCH)!=0, 0);
			if (fwbw_pushed == 0 || (kDown & KEY_LEFT) != 0) {
				// level: backwards
				current_level--;
				if (current_level <= 0) {
					current_level = unlocked_level;
					while (!load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle) && current_level > 1)
						current_level--;
				} else {
					load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle);
				}
			}
			if (fwbw_pushed == 1 || (kDown & KEY_RIGHT) != 0) {
				// level: forwards
				current_level++;
				if (current_level > unlocked_level) {
					current_level = 1;
					load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle);
				} else if (!load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle)) {
					current_level = 1;
					load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle);
				}
			}
		}else{
			// in_game && show_score
			btn_pushed = touch_buttons->update(stylus, ((kHeld | kDown) & KEY_TOUCH)!=0, false, false, false, 0);
			bool back_to_menu = false;
			if ((kDown & KEY_A) != 0 || btn_pushed == 1) {
				// CONTINUE
				touch_buttons->set_button(1, text_pause_textures, 2);
				touch_buttons->set_button(2, text_give_up_textures, 2);
				show_score = false;
				back_to_menu = true;
				in_level_select_menu = false;
				current_level++;
				if (load_level(current_level, landscapelist, naturelist, cloudlist, finish, enemylist, attacklist, &robin, arrowlist, level_width, level_height, score, bonus, enemy_attack, current_highscore, handle)) {
					// LOAD NEXT LEVEL
					back_to_menu = false;
					redraw_bonus_or_score = true;
					if (tmp_text[1] != 0) {
						delete tmp_text[1];
						tmp_text[1] = 0;
					}
					ticks = 0;
				}else{
					current_level = 1;
				}
				

			}
			if ((kDown & (KEY_B | KEY_START)) != 0 || btn_pushed == 2) {
				// EXIT
				show_score = false;
				back_to_menu = true;
			}
			
				if (back_to_menu) {
					// WON LAST LEVEL (or selected level)! => RETURN TO MENU
					in_game = false;
					music->stop();
					jump->stop();
					shoot->stop();
					enemy_attack->stop();
					for (u16 i=0; i<N_TMP_TEXT; i++) { // delete at least current level, highscore, bonus and score textures
						if (tmp_text[i] != 0) {
							delete tmp_text[i];
							tmp_text[i] = 0;
						}
					}
					
				if (in_level_select_menu) {
				touch_buttons->set_button(0, 0, 0);
				touch_buttons->set_button(1, text_play_textures, 2);
				touch_buttons->set_button(2, text_back_textures, 2);
					}else{
						touch_buttons->set_button(0, text_start_textures, 2);
						if (unlocked_level>1) {
							touch_buttons->set_button(1, text_level_select_textures, 2);
						}else{
							touch_buttons->set_button(1, 0, 0);
						}
						touch_buttons->set_button(2, text_exit_textures, 2);
						//touch_buttons->set_enabled(1, unlocked_level>1);
				}
				
					continue;
				}
		}
		music->update(1);
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		for (s16 i=0; i<SCREEN_WIDTH/32+1; i++)
			background.draw(-32*i,0);
		
		if (in_game || in_level_select_menu) {
			s16 start_left = (s16)(robin.get_middle_point().x - SCREEN_WIDTH*0.5f);
			s16 start_top = (s16)(robin.get_middle_point().y - SCREEN_HEIGHT*0.5f);
			if (start_left > level_width - SCREEN_WIDTH)
				start_left = level_width - SCREEN_WIDTH;
			if (start_left < 0)
				start_left = 0;
			if (start_top < -level_height)
				start_top = -level_height;
			if (start_top > -SCREEN_HEIGHT)
				start_top = -SCREEN_HEIGHT;
			Rect screen = {start_left, start_top, start_left + SCREEN_WIDTH, start_top + SCREEN_HEIGHT};
			enemy_attack->set_display_area(screen);
			
			cloudlist->draw(start_left / 2, (start_top-SCREEN_HEIGHT)/2);
			landscapelist->draw(start_left,start_top);
			naturelist->draw(start_left,start_top);
			finish->draw(start_left,start_top);
			enemylist->draw(start_left,start_top);
			attacklist->draw(start_left,start_top);
			robin.draw(start_left,start_top);
			arrowlist->draw(start_left,start_top);
			
			if (show_score) {
				// DRAW SCORE BOX!
				infobox_texture->draw((SCREEN_WIDTH-INFOBOX.width)/2,(SCREEN_HEIGHT-INFOBOX.height)/2);
				u16 text_height = 0;
				if (new_highscore) {
					text_new_highscore_texture->draw((SCREEN_WIDTH-TEXT_NEW_HIGHSCORE.width)/2,(SCREEN_HEIGHT-INFOBOX.height)/2+10);
					text_height = TEXT_NEW_HIGHSCORE.height;
				}else{
					text_your_score_texture->draw((SCREEN_WIDTH-TEXT_YOUR_SCORE.width)/2,(SCREEN_HEIGHT-INFOBOX.height)/2+10);
					text_height = TEXT_YOUR_SCORE.height;
				}
				u16 userscore = score + bonus;
				// print score!
				u16 score_width = draw_number_big(0, 0, userscore, true);
				draw_number_big((SCREEN_WIDTH-score_width)/2,(SCREEN_HEIGHT+text_height-TEMPO_FONT_NUMBERS_BIG.height)/2 + 4,userscore, false);
			}
		} else {
			splash.draw(0,0);
		}
		sf2d_end_frame();


		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		touch_background->draw(0,0);
		touch_buttons->draw(0);
		CTexture* tmp_hsc_tex = 0; // TODO: buffer this texture until "Highscore: %d" changes, don't create it every frame
		if (!in_game && in_level_select_menu) {
			fwbw_buttons->draw(0);
			
			u16 num_width = draw_number_big(TOUCH_SCREEN_WIDTH/2, NEXT.height / 4, current_level, true);
			draw_number_big((TOUCH_SCREEN_WIDTH+text_level_texture->get_width()-num_width)/2, NEXT.height / 4, current_level, false);
			text_level_texture->draw((TOUCH_SCREEN_WIDTH-text_level_texture->get_width()-num_width)/2,NEXT.height / 4);
			char tmp_num[20];
			sprintf(tmp_num,"Highscore: %d", current_highscore);
			Rect hsc = get_string_bounding_box(tmp_num, tempo_font, false);
			tmp_hsc_tex = draw_string(tmp_num, tempo_font, dark_green, TOUCH_SCREEN_WIDTH/2, 5*NEXT.height / 4 - hsc.y2, Alignment::CENTER);
		}
		
		if (in_game) {
			// DRAW STATE: Level, Highscore, Bonus, Score
			char tmp_num[20];
			
			if (tmp_text[0] == 0) {
				tmp_text[0] = draw_string("Level", tempo_font, dark_green, 10, 10);
				tmp_text_bb_i[0] = get_string_bounding_box("Level ", tempo_font, true);
				tmp_text_bb_o[0] = get_string_bounding_box("Level ", tempo_font, false);
			} else {
				tmp_text[0]->draw(10 + tmp_text_bb_o[0].x1, 10 + tmp_text_bb_o[0].y1);
				// align right: add to x-coord: - tmp_text_bb_i[0].x2
			}
			sprintf(tmp_num,"Highscore: %d", current_highscore);
			//Rect hsc = get_string_bounding_box(tmp_num, tempo_font, false);
			tmp_hsc_tex = draw_string(tmp_num, tempo_font, dark_green, 10, 10 + 5*tmp_text_bb_i[0].y2/4, Alignment::LEFT);
			
			if (tmp_text[1] == 0) {
				sprintf(tmp_num, "%d", current_level);
				tmp_text[1] = draw_string(tmp_num, tempo_font, dark_green, 10 + tmp_text_bb_i[0].x2, 10);
				tmp_text_bb_i[1] = get_string_bounding_box(tmp_num, tempo_font, true);
				tmp_text_bb_o[1] = get_string_bounding_box(tmp_num, tempo_font, false);
			} else {
				tmp_text[1]->draw(10 + tmp_text_bb_i[0].x2 + tmp_text_bb_o[1].x1, 10 + tmp_text_bb_o[1].y1);
				// align right: add to x-coord: - tmp_text_bb_i[1].x2
			}
			
			if (tmp_text[2] == 0) {
				tmp_text[2] = draw_string("Bonus: \nScore: ", tempo_font, dark_green, TOUCH_SCREEN_WIDTH - 10 - four_digits_rect.x2, 10, Alignment::RIGHT);
				tmp_text_bb_i[2] = get_string_bounding_box("Bonus: \nScore: ", tempo_font, true);
				tmp_text_bb_o[2] = get_string_bounding_box("Bonus: \nScore: ", tempo_font, false);
			} else {
				tmp_text[2]->draw(TOUCH_SCREEN_WIDTH - 10 - four_digits_rect.x2 + tmp_text_bb_o[2].x1 - tmp_text_bb_i[2].x2, 10 + tmp_text_bb_o[2].y1);
				// align right: add to x-coord: - tmp_text_bb_i[2].x2
			}
			
			if (tmp_text[3] == 0 || redraw_bonus_or_score) {
				if (tmp_text[3] != 0) {
					delete tmp_text[3];
				}
				sprintf(tmp_num, "%d\n%d", bonus,score);
				tmp_text[3] = draw_string(tmp_num, tempo_font, dark_green, TOUCH_SCREEN_WIDTH - 10, 10, Alignment::RIGHT);
				tmp_text_bb_i[3] = get_string_bounding_box(tmp_num, tempo_font, true);
				tmp_text_bb_o[3] = get_string_bounding_box(tmp_num, tempo_font, false);
				redraw_bonus_or_score = false;
			}else{
				tmp_text[3]->draw(TOUCH_SCREEN_WIDTH - 10 + tmp_text_bb_o[3].x1 - tmp_text_bb_i[3].x2, 10 + tmp_text_bb_o[3].y1);
			}
		}
		sf2d_end_frame();

		sf2d_swapbuffers();
		if (tmp_hsc_tex != 0) {
			delete tmp_hsc_tex;
			tmp_hsc_tex = 0;
		}
	}
	
	if (handle != 0) {
		fclose(handle);
		handle = 0;
	}

	delete splash_texture;
	delete finish;
	delete finish_texture;
	delete robin_anim_textures[0];
	delete robin_anim_textures[1];
	delete enemylist;
	delete enemy_anim_textures[0];
	delete enemy_anim_textures[1];
	delete background_texture;
	delete arrowlist;
	delete arrow_texture;
	delete attacklist;
	delete enemy_attack_texture;
	delete landscapelist;
	delete naturelist;
	delete cloudlist;
	delete grass_texture[0];
	delete grass_texture[1];
	delete grass_texture[2];
	delete grass_texture[3];
	delete cloud_texture[0];
	delete cloud_texture[1];
	delete cloud_texture[2];
	delete solid_block_texture;
	delete flower1_anim_textures[0];
	delete flower1_anim_textures[1];
	delete tree_texture;
	delete stones_texture;
	sf2d_free_texture(tempo_font_numbers_big_texture);
	
	delete touch_buttons;
	delete fwbw_buttons;
	delete text_level_texture;
	delete touch_background;
	delete button_textures[0];
	delete button_textures[1];
	delete next_textures[0];
	delete next_textures[1];
	delete text_start_textures[0];
	delete text_start_textures[1];
	delete text_level_select_textures[0];
	delete text_level_select_textures[1];
	delete text_exit_textures[0];
	delete text_exit_textures[1];
	delete text_pause_textures[0];
	delete text_pause_textures[1];
	delete text_resume_textures[0];
	delete text_resume_textures[1];
	delete text_play_textures[0];
	delete text_play_textures[1];
	delete text_back_textures[0];
	delete text_back_textures[1];
	delete text_give_up_textures[0];
	delete text_give_up_textures[1];
	delete text_continue_textures[0];
	delete text_continue_textures[1];
	delete text_quit_textures[0];
	delete text_quit_textures[1];
	delete infobox_texture;
	delete text_new_highscore_texture;
	delete text_your_score_texture;
	for (u16 i=0; i<N_TMP_TEXT; i++) {
		if (tmp_text[i] != 0)
			delete tmp_text[i];
	}
	
	delete data;
	delete music;
	delete jump;
	delete shoot;
	delete enemy_attack;

	csndExit();
	sf2d_fini();
	return 0;
}




bool load_level(u16 level, CLandscapeList* landscapelist, CLandscapeList* naturelist, CLandscapeList* cloudlist, CCollidable* finish, CEnemyList* enemylist, CArrowList* attacks, CRobin* robin, CArrowList* arrows, s16& level_width, s16& level_height, u16& score, u16& bonus, CSound* enemy_attack_snd, u16& current_highscore, FILE* handle) {

	// GENERAL

	score = 0;
	landscapelist->clear();
	naturelist->clear();
	cloudlist->clear();
	enemylist->clear();
	attacks->clear();
	arrows->clear();

	
	Rect landscape_bounding_box = {0,0,(s16)GRASS.width,(s16)GRASS.height};
	Rect nature_bounding_box = {0,0,0,0};
	Rect enemy_bounding_box = {10,0,30,43};
	
	typedef struct {
		s16 x;
		s16 y;
		s16 type;
		// landscape: 0: NORMAL, 1: LEFT,            2: RIGHT, 3: LEFT/RIGHT, 4: SOLID
		// nature:    0: flower, 1: flower mirrored, 2: tree,  3: stones
	} LandscapeObject;
	typedef struct {
		s16 x;
		s16 y;
		s16 left_border;
		s16 right_border;
		float attacking_pause;
		s16 walking_pixels_per_second;
	} EnemyObject;
	
	LandscapeObject* _landscape = 0;
	u16 n_landscape = 0;
	LandscapeObject* _nature = 0;
	u16 n_nature = 0;
	LandscapeObject* _clouds = 0;
	u16 n_clouds = 0;
	EnemyObject* _enemies = 0;
	u16 n_enemies = 0;
	level_width = 0;
	level_height = 0;
	bonus = 0;
	
	s16 start_x=0;
	s16 start_y=32;

	#define LEVEL_SIZE(x,y) level_width = (x); level_height = (y);
	#define START(x,y) start_x = (x); start_y = (y);
	#define FINISH(x,y) finish->set_position((x), -(y)-FINISH.height);
	#define BONUS(x) bonus = (x);
	#define LANDSCAPE(x, ...) n_landscape = (x); LandscapeObject landscape[(x)] = { __VA_ARGS__ }; _landscape = new LandscapeObject[n_landscape]; memcpy(_landscape, landscape, n_landscape*sizeof(LandscapeObject));
	#define NATURE(x, ...) n_nature = (x); LandscapeObject nature[(x)] = { __VA_ARGS__ }; _nature = new LandscapeObject[n_nature]; memcpy(_nature, nature, n_nature*sizeof(LandscapeObject));
	#define CLOUDS(x, ...) n_clouds = (x); LandscapeObject clouds[(x)] = { __VA_ARGS__ }; _clouds = new LandscapeObject[n_clouds]; memcpy(_clouds, clouds, n_clouds*sizeof(LandscapeObject));
	#define ENEMIES(x, ...) n_enemies = (x); EnemyObject enemies[(x)] = { __VA_ARGS__ }; _enemies = new EnemyObject[n_enemies]; memcpy(_enemies, enemies, n_enemies*sizeof(EnemyObject));
	#define DEVELOPER_HIGHSCORE(x) { };
	/**
Maybe add some of these macros:
PREVIEW_ROBIN(128,96,false,true) <- x, y, mirrored, walking-sprite
PREVIEW_ENEMY(0,216,32,false,true) <- enemy-id, x, y, mirrored, walking-sprite (other enemies unchanged)
PREVIEW_ARROWS(2, {200,62,false}, {260,62,false}) <- number of arrows; per arrow: x, y, mirrored
PREVIEW_KNIFES(3, {130,52,true}, {200, 52, false}, {230,52,false}) <- like arrows
PREVIEW_SCREEN_OFFSET(30,0,FIXED) // bottom left corner relative to (0,0)
PREVIEW_SCREEN_OFFSET(0,-10,RELATIVE) // bottom left corner relative to in-game scrolling (therefore relative to centered Robin Hood)
	*/

	// LOAD LEVEL CONTENT
	switch (level) {
		#include "levels.inc"
		default: {
			return false;
		}
	}
	
	if (level_width <= 0 || level_height <= 0) {
		if (_landscape != 0)
			delete _landscape;
		if (_nature != 0)
			delete _nature;
		if (_clouds != 0)
			delete _clouds;
		if (_enemies != 0)
			delete _enemies;
		return false;
	}

	// CREATE LEVEL
	for (u16 i=0;i<n_landscape;i++) {
		if (_landscape[i].type >= 0 && _landscape[i].type <= 3) {
			landscapelist->add_object(new CLandscape(_landscape[i].x,-_landscape[i].y-GRASS.height, grass_texture[_landscape[i].type], landscape_bounding_box), false);
		} else if (_landscape[i].type == 4) {
			landscapelist->add_object(new CLandscape(_landscape[i].x,-_landscape[i].y-GRASS.height, solid_block_texture, landscape_bounding_box), true);
		}
	}
	for (u16 i=0;i<n_nature;i++) {
		const RawImage* raw_img = 0;
		CTexture** tex = 0;
		u16 frames = 0;
		u16 duration = 35;
		bool mirrored = false;
		switch (_nature[i].type) {
			case 0:
				raw_img = &FLOWER1_1;
				tex = flower1_anim_textures;
				frames = 2;
				break;
			case 1:
				raw_img = &FLOWER1_1;
				tex = flower1_anim_textures;
				frames = 2;
				mirrored = true;
				break;
			case 2:
				raw_img = &TREE;
				tex = &tree_texture;
				frames = 1;
				break;
			case 3:
				raw_img = &STONES;
				tex = &stones_texture;
				frames = 1;
				break;
		};
		if (raw_img == 0 || tex == 0)
			continue;
		naturelist->add_object(new CCollidable(_nature[i].x,-_nature[i].y-raw_img->height+1, tex, frames, duration, nature_bounding_box, mirrored), false);
	}
	for (u16 i=0;i<n_clouds;i++) {
		if (_clouds[i].type >= 0 && _clouds[i].type <= 5) {
			s16 height = 0;
			switch (_clouds[i].type % 3){case 0: height = CLOUD_1.height; break;case 1: height = CLOUD_2.height; break;case 2: height = CLOUD_3.height; break;}
			cloudlist->add_object(new CCollidable(_clouds[i].x,-_clouds[i].y-height, cloud_texture+(_clouds[i].type % 3), 1, 1, nature_bounding_box, (_clouds[i].type>=3)), false);
		}
	}
	for (u16 i=0;i<n_enemies;i++) {
		enemylist->add_object(new CEnemy(_enemies[i].x, -_enemies[i].y-ENEMY_RIGHT.height, enemy_anim_textures, 2, 15, enemy_bounding_box, ((float)_enemies[i].walking_pixels_per_second)/60.0f, landscapelist, _enemies[i].left_border, _enemies[i].right_border, 0.15f, attacks, (_enemies[i].attacking_pause>0.0f?((u16)(70.0f*_enemies[i].attacking_pause)):0), false, enemy_attack_snd));
	}
	if (_landscape != 0)
		delete _landscape;
	if (_nature != 0)
		delete _nature;
	if (_enemies != 0)
		delete _enemies;
		
	robin->reset(start_x, -start_y-ROBIN_RIGHT.height, level_width, level_height);
	
	current_highscore = 0;
	if (handle != 0) {
		if (fseek(handle,level*sizeof(u16),SEEK_SET)==0) {
			fread(&current_highscore,sizeof(u16),1,handle);
		}
	}
	
	return true;
}

u16 draw_number_big(s16 x, s16 y, u16 number, bool get_width) {
	u16 digits = 0;
	u16 tmp = number;
	while (tmp > 0) {
		digits++;
		tmp /= 10;
	}
	if (digits == 0)
		digits++;
	s16 width = digits*TEMPO_FONT_NUMBERS_BIG.width / 10;
	if (get_width)
		return width;
	x += width - TEMPO_FONT_NUMBERS_BIG.width / 10;
	while (digits > 0) {
		u16 digit = number % 10;
		// draw digit at x,y
		if (tempo_font_numbers_big_texture != 0) {
			sf2d_draw_texture_part(tempo_font_numbers_big_texture, x, y, TEMPO_FONT_NUMBERS_BIG.width/10*digit, 0, TEMPO_FONT_NUMBERS_BIG.width/10, TEMPO_FONT_NUMBERS_BIG.height);
		}
		x -= TEMPO_FONT_NUMBERS_BIG.width / 10;
		number/=10;
		digits--;
	}
	return width;
}


