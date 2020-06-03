/* StarFire! by Topi Mansikkaviita, started 10. 3. 2001 */

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#define MAX_SCORE 210         // MAXIMUM score that can be acquired in game
#define OBJECTS 5             // MAX objects (people) in room
#define TALKING 12            // MAXIMUM of talkable objects in game
#define CTRL(X) ((X) & 0x1F)  // CTRL characters
#define TOPIC 9               // color for topics
#define TEXT 14  					// color for standard text
#define SCREEN 2 					// color for screen

/* screen map */
char **map;
int max_x = 0, max_y = 0;
char ter, char_temp[80], args[80], temp[10]; // for itoa or atoi
int int_temp = 0;
bool debug = true, read_error = false;
int update_all_windows();
int parse_window(char*);
int talk_daemon(char *msg, int i, bool ask);
int create_map();

struct savefile // savefile for player
{
	char name[10];
   struct time_variables
   {
      int talking[TALKING];
   	int minutes, hours, days, sleep;
      int light, night_x, night_y, old_x, old_y;
      bool indoors, day;
      int area_x1, area_y1, area_y2, area_x3;
      char place[15];
   } time;
   struct player_skills
   {
   	int Resist, Swimming, Haggling, Alchemy, Stars, Fame;
   } skill;
   struct inventory_variables // simple boolean values to define
   {									// if player has an item
   	int corn, cure;
      bool scythe, scarecrow, animated_scarecrow, sleeping_bag, wax_apples, mage_keys;
		bool history_book, incarnate_book, necro_book, poem_book, horn, flute, jewels;
      bool roses, vira, zar, tarn, dural, white_orb, black_orb, moonstone, terastone;
	} item, picked;
   struct player_stats
   {
   	int Str, Con, Wis, Mag, Luck;
   } stat;
   struct magic_spells
   {
   	char spell;
      bool frosty_way, bestial_speech, reinforce, gateway; // check if gotten
      int duration;
   } magic;
   struct game_variables
   {
   	int money, score, food, hp, max_hp, sp, max_sp, vision; // triggered visions
      int salary; // money that comes to granary
      bool anyaca, vis4; // meet Sorceress Anyaca
      int alchemy[17]; // save file for herbs and potions   
   } var;
   struct quit_recovery
   {
   	int x, y, big_x, big_y;
   } quit;
} player;

struct virtual_screen // screens and objects
{
	int x[OBJECTS], y[OBJECTS];
	int new_obj, max_obj;
	char area_map[20];
   struct parse_screen
   {
   	char line1[70], line2[70], line3[70], line4[70], line5[70];
  } parser;
	struct drawings
   {
		int color[OBJECTS];
      char sign[OBJECTS];
      bool alive[OBJECTS], seen[OBJECTS];
      int big_x, big_y;
   } draw;
} screen;

int myrand(int lim) // random function
{
	static int seed = 0;
	int result = 0;

	if(lim == 0)
		return 0;
	if(!seed)
   {
		seed = (int)time(0);
		srand(seed);
	}
	result = rand() % lim;
	return result;
}

/* IMPORTANT FUNCTIONS */
#include "datasave.h" // write_screen
#include "map.h" // read_map, calc_xsiz/ysiz etc.
#include "tools.h" // surdraw/surter/test_ascii/draw etc.
#include "timeworld.h" // time updates and such

int check_location(int x, int y)
{
	if(true_x(x) == 156 && true_y(y) == 14) // Get one star from here.
   {
		create_map();
		strcpy(player.time.place, "Waterfall");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 149; // muurien ulkopuolelta
      player.time.area_y1 = 41; // otetut mitat
      player.time.area_y2 = 47; // eli § merkeiltä
      player.time.area_x3 = 160;
      player.time.indoors = true;
      screen.x[0] = 15;
      screen.y[0] = 3;
   	parse_window("You go under the Waterfall.");
		update_all_windows();
      reset_objects();
      return 0;
   }
	if(strcmp(player.time.place, "Waterfall") == 0 && screen.x[0] == 15 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Elf Land");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You come back from the Waterfall.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 69 && true_y(y) == 4) // Salamander volcano
   {
		create_map();
		strcpy(player.time.place, "Volcano");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 149; // muurien ulkopuolelta
      player.time.area_y1 = 41; // otetut mitat
      player.time.area_y2 = 47; // eli § merkeiltä
      player.time.area_x3 = 160;
      player.time.indoors = true;
      screen.x[0] = 14;
      screen.y[0] = 4;
   	parse_window("You descend down to the volcano.");
		update_all_windows();
      reset_objects();
      create_object(14, 6, 'S', 4, false); // Salamander King
      return 0;
   }
	if(strcmp(player.time.place, "Volcano") == 0 && screen.x[0] == 15 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You ascend to the surface.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 45 && true_y(y) == 45)
   {
		create_map();
		strcpy(player.time.place, "Village");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 149; // muurien ulkopuolelta
      player.time.area_y1 = 41; // otetut mitat
      player.time.area_y2 = 47; // eli § merkeiltä
      player.time.area_x3 = 160;
      player.time.indoors = true;
      screen.x[0] = 15;
      screen.y[0] = 3;
   	parse_window("You enter the Jungle Village.");
		update_all_windows();
      reset_objects();
      create_object(16, 5, '@', 14, false); // Chief
      return 0;
   }
	if(strcmp(player.time.place, "Village") == 0 && screen.x[0] == 15 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Jungle Village.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 57 && true_y(y) == 34)
   {
		create_map();
		strcpy(player.time.place, "Cemetery");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 149; // muurien ulkopuolelta
      player.time.area_y1 = 41; // otetut mitat
      player.time.area_y2 = 47; // eli § merkeiltä
      player.time.area_x3 = 160;
      player.time.indoors = true;
      screen.x[0] = 15;
      screen.y[0] = 3;
   	parse_window("You enter the Cemetery.");
		update_all_windows();
      reset_objects();
      create_object(16, 5, 'G', 15, false); // grave
      create_object(13, 4, 'C', 15, false); // crypt
      create_object(19, 4, 'M', 15, false); // mausoleum
      return 0;
   }
	if(strcmp(player.time.place, "Cemetery") == 0 && screen.x[0] == 15 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Cemetery.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
   if(strcmp(player.time.place, "Market") == 0 && screen.x[0] == 14 && screen.y[0] == 3)
   {
   	if(player.item.mage_keys == false)
      {
      	parse_window("The door to mages' guild are locked.");
         return 0;
      }
		create_map();
		strcpy(player.time.place, "Guild");
      clear_area();
      screen.x[0] = 19;
      screen.y[0] = 9;
      player.time.area_x1 = 152;
      player.time.area_y1 = 22;
      player.time.area_y2 = 32;
      player.time.area_x3 = 171;
      player.time.indoors = true;
      reset_objects();
		update_all_windows();
		parse_window("You open the door with your key, and enter guild.");
      parse_window("This place looks very odd, doesn't look like guild.");
		create_object(19, 6, '@', 4, false); // Guildmaster
	 	return 0;
   }
   if(strcmp(player.time.place, "Guild") == 0 && screen.x[0] == 19 && screen.y[0] == 9)
   {
   	create_map();
      strcpy(player.time.place, "Market");
      clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 151;
      player.time.area_y1 = 32;
      player.time.area_y2 = 41;
      player.time.area_x3 = 163;
      screen.x[0] = 14;
      screen.y[0] = 3;
      reset_objects();
      update_all_windows();
      parse_window("You leave the magician's guild.");
      return 0;
   }
	if(strcmp(player.time.place, "Granary") == 0 && screen.x[0] == 14 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Granary.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(strcmp(player.time.place, "Bailiff") == 0 && screen.x[0] == 16 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Bailiff's office.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
   if(true_x(x) == 98 && true_y(y) == 24)
   {
   	if(close_place(17, 9)) return 0;
		create_map();
		strcpy(player.time.place, "Bailiff");
      clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      screen.x[0] = 16;
      screen.y[0] = 3;
      player.time.area_x1 = 136;
      player.time.area_y1 = 24;
      player.time.area_y2 = 31;
      player.time.area_x3 = 149;
      player.time.indoors = true;
      reset_objects();
		update_all_windows();
		parse_window("You enter the Bailiff's office.");
		create_object(16, 6, '@', 9, false); // Bailiff
	 	return 0;
   }
   if(true_x(x) == 69 && true_y(y) == 18)
   {
   	if(close_place(21, 10)) return 0;
		create_map();
		strcpy(player.time.place, "Circus");
      clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      screen.x[0] = 19;
      screen.y[0] = 9;
      player.time.area_x1 = 152;
      player.time.area_y1 = 22;
      player.time.area_y2 = 32;
      player.time.area_x3 = 171;
      player.time.indoors = true;
      reset_objects();
		update_all_windows();
		parse_window("You enter an extremely large circus tent.");
		create_object(12, 3, 'J', 13, false); // Juggler
      create_object(25, 5, 'T', 14, false); // Liontamer
      create_object(26, 5, 'L', 6, false); // Lion
	 	return 0;
   }
	if(strcmp(player.time.place, "Circus") == 0 && screen.x[0] == 19 && screen.y[0] == 9)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Circus tent.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 95 && true_y(y) == 19)
   {
		create_map();
		strcpy(player.time.place, "Granary");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 125; // muurien ulkopuolelta
      player.time.area_y1 = 24; // otetut mitat
      player.time.area_y2 = 29; // eli § merkeiltä
      player.time.area_x3 = 134;
      player.time.indoors = true;
      screen.x[0] = 14;
      screen.y[0] = 3;
   	parse_window("You enter the Granary.");
		update_all_windows();
      reset_objects();
      return 0;
   }
	if(strcmp(player.time.place, "Hill Inn") == 0 && screen.x[0] == 14 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the Hill Inn.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 43 && true_y(y) == 22)
   {
		create_map();
		strcpy(player.time.place, "Hill Inn");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 125; // muurien ulkopuolelta
      player.time.area_y1 = 24; // otetut mitat
      player.time.area_y2 = 29; // eli § merkeiltä
      player.time.area_x3 = 134;
      player.time.indoors = true;
      screen.x[0] = 14;
      screen.y[0] = 3;
   	parse_window("You enter the Hill Inn!");
		update_all_windows();
      reset_objects();
      return 0;
   }
	if(true_x(x) == 88 && true_y(y) == 31)
   {
		create_map();
		strcpy(player.time.place, "Geyser");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 135; // muurien ulkopuolelta
      player.time.area_y1 = 38; // otetut mitat
      player.time.area_y2 = 44; // eli § merkeiltä
      player.time.area_x3 = 145;
      player.time.indoors = true;
      screen.x[0] = 12;
      screen.y[0] = 3;
   	parse_window("You visit a geyser.");
		update_all_windows();
      reset_objects();
   	if(player.time.talking[6] > 0 && (player.time.hours > 22 || player.time.hours < 3)) create_object(14, 3, 'A', 13, false); // Anyaca
      if(player.time.talking[6] >= 9) create_object(14, 3, 'A', 13, false); // Anyaca
      return 0;
   }
	if(strcmp(player.time.place, "Geyser") == 0 && screen.x[0] == 12 && screen.y[0] == 3)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the geyser.");
		if(player.time.talking[6] == 10)
      {
      	dialogue("Those mountains...They're coming back?");
         dialogue("What a wicked archwizard.");
         player.time.talking[6] = 11;
      }
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
  	if(strcmp(player.time.place, "Deserras") == 0 && screen.x[0] == 21 && screen.y[0] == 5)
   {
		if(player.time.talking[6] >= 9)
      {
      	parse_window("Rune bomb explodes to your face.");
         hurt(player.var.hp + 1);
         return 0;
      }
   	if(close_place(16, 10)) return 0;
      if(player.skill.Fame < 5)
      {
			parse_window("Guard comes to stop you.");
         dialogue("Who are you?", "Guard");
         dialogue("I don't know, so, no trespassing.", "Guard");
         return 0;
      }
		create_map();
		strcpy(player.time.place, "Council");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 136;
      player.time.area_y1 = 24;
      player.time.area_y2 = 31;
      player.time.area_x3 = 149;
      screen.x[0] = 16;
      screen.y[0] = 3;
   	parse_window("You enter the Council of Deserras.");
		update_all_windows();
      reset_objects();
		create_object(18, 5, 'D', 13, false); // Darol
      create_object(14, 5, 'T', 9, false); // Tof
      return 0;
	}
	if(strcmp(player.time.place, "Library") == 0 && screen.x[0] == 16 && screen.y[0] == 3)
   {
   	if(player.item.necro_book == true)
      {
      	dialogue("Please leave that reserved book in here.", "Librarian");
         dialogue("Which of these?");
         dialogue("'Hauntings from the grave'", "Librarian");
         return 0;
      }
		create_map();
		strcpy(player.time.place, "Deserras");
      clear_area();
      screen.x[0] = 12;
      screen.y[0] = 5;
      player.time.area_x1 = 136; // muurien ulkopuolelta
      player.time.area_y1 = 31; // otetut mitat
      player.time.area_y2 = 38; // eli § merkeiltä
      player.time.area_x3 = 149;
      player.time.indoors = true;
		parse_window("You leave the library.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
  	if(strcmp(player.time.place, "Deserras") == 0 && screen.x[0] == 12 && screen.y[0] == 5)
   {
   	if(close_place(18, 11)) return 0;
		create_map();
		strcpy(player.time.place, "Library");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 136;
      player.time.area_y1 = 24;
      player.time.area_y2 = 31;
      player.time.area_x3 = 149;
      screen.x[0] = 16;
      screen.y[0] = 3;
   	parse_window("You enter the library.");
		update_all_windows();
      reset_objects();
		create_object(14, 5, '@', 5, false);
      return 0;
	}
	if(strcmp(player.time.place, "Council") == 0 && screen.x[0] == 16 && screen.y[0] == 3)
   {
		create_map();
		strcpy(player.time.place, "Deserras");
      clear_area();
      screen.x[0] = 21;
      screen.y[0] = 5;
      player.time.area_x1 = 136; // muurien ulkopuolelta
      player.time.area_y1 = 31; // otetut mitat
      player.time.area_y2 = 38; // eli § merkeiltä
      player.time.area_x3 = 149;
      player.time.indoors = true;
		parse_window("You leave the Council of Deserras.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
  	if(strcmp(player.time.place, "Deserras") == 0 && screen.x[0] == 16 && screen.y[0] == 3)
   {
		create_map();
		strcpy(player.time.place, "Market");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 151;
      player.time.area_y1 = 32;
      player.time.area_y2 = 41;
      player.time.area_x3 = 163;
      screen.x[0] = 20;
      screen.y[0] = 8;
   	parse_window("You enter the streets of Deserras.");
		update_all_windows();
      reset_objects();
      if(player.var.anyaca == true) create_object(15, 5, 'A', 13, false);
      return 0;
	}
	if(strcmp(player.time.place, "Market") == 0 && screen.x[0] == 20 && screen.y[0] == 8)
   {
		create_map();
		strcpy(player.time.place, "Deserras");
      clear_area();
      screen.x[0] = 16;
      screen.y[0] = 3;
      player.time.area_x1 = 136; // muurien ulkopuolelta
      player.time.area_y1 = 31; // otetut mitat
      player.time.area_y2 = 38; // eli § merkeiltä
      player.time.area_x3 = 149;
      player.time.indoors = true;
		parse_window("You leave the streets of Deserras.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
  	if(strcmp(player.time.place, "Market") == 0 && screen.x[0] == 12 && screen.y[0] == 7)
   {
   	if(close_place()) return 0;
		create_map();
		strcpy(player.time.place, "Musique");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 124;
      player.time.area_y1 = 29;
      player.time.area_y2 = 35;
      player.time.area_x3 = 133;
      screen.x[0] = 14;
      screen.y[0] = 5;
   	parse_window("You enter the Mandal's Musique shop.");
		update_all_windows();
      reset_objects();
		create_object(15, 3, '@', 10, false);
      return 0;
	}
  	if(strcmp(player.time.place, "Market") == 0 && screen.x[0] == 17 && screen.y[0] == 3)
   {
   	if(close_place()) return 0;
		create_map();
		strcpy(player.time.place, "Lab");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 124;
      player.time.area_y1 = 29;
      player.time.area_y2 = 35;
      player.time.area_x3 = 133;
      screen.x[0] = 14;
      screen.y[0] = 5;
   	parse_window("You enter the Alchemy Laboratory.");
		update_all_windows();
      reset_objects();
      return 0;
	}
	if(strcmp(player.time.place, "Lab") == 0 && screen.x[0] == 14 && screen.y[0] == 5)
   {
		create_map();
		strcpy(player.time.place, "Market");
      clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 151;
      player.time.area_y1 = 32;
      player.time.area_y2 = 41;
      player.time.area_x3 = 163;
      screen.x[0] = 17;
      screen.y[0] = 3;
		parse_window("You leave the Alchemy Laboratory.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(strcmp(player.time.place, "Musique") == 0 && screen.x[0] == 14 && screen.y[0] == 5)
   {
		create_map();
		strcpy(player.time.place, "Market");
      clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 151;
      player.time.area_y1 = 32;
      player.time.area_y2 = 41;
      player.time.area_x3 = 163;
      screen.x[0] = 12;
      screen.y[0] = 7;
		parse_window("You leave Mandal's Musique shop.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
  	if(strcmp(player.time.place, "Market") == 0 && screen.x[0] == 12 && screen.y[0] == 5)
   {
   	if(close_place()) return 0;
		create_map();
		strcpy(player.time.place, "Gift Shop");
		clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 124;
      player.time.area_y1 = 29;
      player.time.area_y2 = 35;
      player.time.area_x3 = 133;
      screen.x[0] = 14;
      screen.y[0] = 5;
   	parse_window("You enter the Local Gift Shop.");
		update_all_windows();
      reset_objects();
		create_object(14, 3, '@', 10, false); // gift seller
      return 0;
	}
	if(strcmp(player.time.place, "Gift Shop") == 0 && screen.x[0] == 14 && screen.y[0] == 5)
   {
		create_map();
		strcpy(player.time.place, "Market");
      clear_area();
      player.time.indoors = true;
      player.time.area_x1 = 151;
      player.time.area_y1 = 32;
      player.time.area_y2 = 41;
      player.time.area_x3 = 163;
      screen.x[0] = 12;
      screen.y[0] = 5;
		parse_window("You leave the Local Gift Shop.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
	if(true_x(x) == 60 && true_y(y) == 25)
   {
		create_map();
		strcpy(player.time.place, "Deserras");
		clear_area();
		player.time.old_x = screen.x[0];
      player.time.old_y = screen.y[0];
      player.time.area_x1 = 136; // muurien ulkopuolelta
      player.time.area_y1 = 31; // otetut mitat
      player.time.area_y2 = 38; // eli § merkeiltä
      player.time.area_x3 = 149;
      player.time.indoors = true;
      screen.x[0] = 16;
      screen.y[0] = 6;
   	parse_window("You enter the city of Deserras.");
		update_all_windows();
      reset_objects();
      return 0;
   }
	if(strcmp(player.time.place, "Deserras") == 0 && screen.x[0] == 16 && screen.y[0] == 6)
   {
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      player.time.indoors = false;
		parse_window("You leave the city of Deserras.");
		update_all_windows();
      reset_objects();
      create_map();
	 	return 0;
   }
   parse_window("There is no place to enter.");
   return 0;
}

int virt_map() // player command handler
{
	char cmd = 0, extended = 0;
	bool player_move = false, screen_move = false;
	bool north = false, west = false, east = false, south = false;
	if(player.quit.x > 0 && player.quit.y > 0)
   {
		screen.draw.big_x = player.quit.big_x;
      screen.draw.big_y = player.quit.big_y;
   	screen.x[0] = player.quit.x;
   	screen.y[0] = player.quit.y;
      player.quit.x = 0;
      player.quit.y = 0;
      player.quit.big_x = 0;
      player.quit.big_y = 0;
      create_map();
      draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   }
  	cmd = getch();
   if(!cmd)
   	extended = getch();
	time_update();
   if(cmd == CTRL('L') && debug == true) // debug command for location
   {
		strcpy(char_temp, "X: ");
      itoa(screen.x[0], temp, 10);
      strcat(char_temp, temp);
      itoa(screen.y[0], temp, 10);
      strcat(char_temp, ", Y: ");
      strcat(char_temp, temp);
      parse_window(char_temp);
      strcpy(char_temp, "Big X: ");
      itoa(screen.draw.big_x, temp, 10);
      strcat(char_temp, temp);
		itoa(screen.draw.big_y, temp, 10);
      strcat(char_temp, ", Y: ");
      strcat(char_temp, temp);
      parse_window(char_temp);
      itoa(true_x(screen.x[0]), temp, 10);
      strcpy(char_temp, "True X: ");
      strcat(char_temp, temp);
      itoa(true_y(screen.y[0]), temp, 10);
      strcat(char_temp, ", Y: ");
      strcat(char_temp, temp);
      parse_window(char_temp);
	}

	if(cmd == '>')
   {
		/* this moves player from place to another */
      check_location(screen.x[0], screen.y[0]);
   }
	if(!extended && cmd == 'm') // magic
   {
   	magic();
   }
   if(!extended && cmd == 'a') // alchemy
   {
   	alchemy();
   }
	if(!extended && cmd == 'i') // show inventory
   {
   	show_inventory('i');
   }
   if(!extended && cmd == 'c') // combine items
   {
   	show_inventory('c');
   }
   if(!extended && cmd == 'u') // use item
   {
   	show_inventory('u');
   }
   if(!extended && cmd == 'b') // bless item
   {
   	show_inventory('b');
   }
   if(!extended && cmd == 'e') // examine item
   {
   	show_inventory('e');
   }
	if(!extended && cmd == 's') // surroundings
   {
		look_around();
   }
   if(!extended && cmd == 'p') // pick up items
   {
   	pick_up();
   }
	if(!extended && cmd == 'g') // give item
   {
	   show_inventory('g');
	}
   if(!extended && cmd == 't') // talk person
   {
		int_temp = 0;
		for(int i = 1; i < OBJECTS; i++)
      {
      	if(screen.x[0] == (screen.x[i] - 1) && screen.y[0] == screen.y[i] - 1) int_temp = i;
      	if(screen.x[0] == (screen.x[i] - 1) && screen.y[0] == screen.y[i] + 1) int_temp = i;
      	if(screen.x[0] == (screen.x[i] - 1) && screen.y[0] == screen.y[i]) int_temp = i;
      	if(screen.x[0] == (screen.x[i] + 1) && screen.y[0] == screen.y[i]) int_temp = i;
      	if(screen.x[0] == (screen.x[i] + 1) && screen.y[0] == screen.y[i] - 1) int_temp = i;
      	if(screen.x[0] == (screen.x[i] + 1) && screen.y[0] == screen.y[i] + 1) int_temp = i;
      	if(screen.x[0] == (screen.x[i]) && screen.y[0] == screen.y[i] - 1) int_temp = i;
      	if(screen.x[0] == (screen.x[i]) && screen.y[0] == screen.y[i] + 1) int_temp = i;
      }
      if(int_temp == 0)
      {
      	parse_window("Talk to who?");
      }
      else
      {
	   	talk(screen.draw.sign[int_temp], player.time.place);
   	}
   }
	if(!extended && cmd == 'q') // quit and save
   {
		strcpy(char_temp, "players\\");
		if(player.time.indoors == true)
      {
      	parse_window("Cannot quit/save when moving indoors.");
      }
      else
      {
			system("cls");
	      printf("Your character has been saved. See you later.\n");
			strcat(char_temp, player.name);
	      player.quit.x = screen.x[0];
   	   player.quit.y = screen.y[0];
	      player.quit.big_x = screen.draw.big_x;
   	   player.quit.big_y = screen.draw.big_y;
			write_savefile(char_temp, player);
			exit(0);
      }
   }
	if(cmd == CTRL('S'))
   {
		strcpy(char_temp, "players\\");
		if(player.time.indoors == true)
      {
      	parse_window("Cannot save when moving indoors.");
      }
      else
      {
			parse_window("Your character has been saved.");
			strcat(char_temp, player.name);
	      player.quit.x = screen.x[0];
   	   player.quit.y = screen.y[0];
	      player.quit.big_x = screen.draw.big_x;
   	   player.quit.big_y = screen.draw.big_y;
			write_savefile(char_temp, player);
      }
   }
   if(cmd == CTRL('Q'))
   {
		parse_window("Are you sure you want to quit without saving?[y/n]: ");
      ter = getch();
      if(ter == 'y' || ter == 'Y') exit(1);
	}
   if(!extended && cmd == '0' || !cmd && extended == 'R') // show time
   {
   	show_time();
   }
   if(!extended && cmd == '7' || !cmd && extended == 'G') // move northwest
   {
   	screen.x[0]--;
      screen.y[0]--;
      player_move = true;
      west = true;
      north = true;
   }
   if(!extended && cmd == '9' || !cmd && extended == 'I') // move northeast
   {
   	screen.x[0]++;
      screen.y[0]--;
      player_move = true;
      east = true;
      north = true;
   }
   if(!extended && cmd == '1' || !cmd && extended == 'O') // move southwest
   {
   	screen.x[0]--;
      screen.y[0]++;
      player_move = true;
      west = true;
      south = true;
   }
   if(!extended && cmd == '3' || !cmd && extended == 'Q') // move southeast
   {
   	screen.x[0]++;
      screen.y[0]++;
      player_move = true;
      east = true;
      south = true;
   }
   if(!extended && cmd == '4' || !cmd && extended == 'K') // move west
   {
	  	screen.x[0]--;
      player_move = true;
      west = true;
      if(screen.x[0] == 10 && screen.draw.big_x > 0)
      {
      	screen.draw.big_x--;
 			for(int_temp = 0; int_temp < screen.max_obj; int_temp++)
	         screen.x[int_temp] += 40;
         screen_move = true;
         create_map();
      }
   }
   if(!extended && cmd == '2' || !cmd && extended == 'P') // move south
   {
	  	screen.y[0]++;
      player_move = true;
      south = true;
      if(screen.y[0] == 16 && screen.draw.big_y < 25)
      {
      	screen.draw.big_y++;
			for(int_temp = 0; int_temp < screen.max_obj; int_temp++)
         	screen.y[int_temp] -= 9;
         screen_move = true;
         create_map();
      }
   }
   if(!extended && cmd == '8' || !cmd && extended == 'H') // move north
   {
   	screen.y[0]--;
      player_move = true;
      north = true;
      if(screen.y[0] == 1 && screen.draw.big_y > 0)
      {
      	screen.draw.big_y--;
 			for(int_temp = 0; int_temp < screen.max_obj; int_temp++)
	         screen.y[int_temp] += 9;
         screen_move = true;
         create_map();
      }
   }
   if(!extended && cmd == '6' || !cmd && extended == 'M') // move south
   {
   	screen.x[0]++;
      player_move = true;
      east = true;
      if(screen.x[0] == 79 && screen.draw.big_x < 25)
      {
      	screen.draw.big_x++;
 			for(int_temp = 0; int_temp < screen.max_obj; int_temp++)
	         screen.x[int_temp] -= 40;
         screen_move = true;
         create_map();
      }
   }
	if(player.time.indoors == false && map[true_y(screen.y[0])][true_x(screen.x[0])] == '#') // can't go through '#'- sign
   {
      if(north == true) screen.y[0]++;
      if(south == true) screen.y[0]--;
     	if(east == true) screen.x[0]--;
	   if(west == true) screen.x[0]++;
   }
	for(int_temp = 1; int_temp < screen.max_obj; int_temp++)
   {
		if(screen.x[0] == screen.x[int_temp] && screen.y[0] == screen.y[int_temp])
   	{
			/* this reveals hiding monsters */
			draw(screen.x[int_temp], screen.y[int_temp], screen.draw.sign[int_temp], screen.draw.color[int_temp]);
 		   if(north == true) screen.y[0]++;
   	   if(south == true) screen.y[0]--;
      	if(east == true) screen.x[0]--;
	      if(west == true) screen.x[0]++;
   	}
   }
	map_field_boundaries();
	if(player_move == false) erase_old_obj(0, player_move, screen_move);
   draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   surter(screen.x[0], screen.y[0]);
	if(player.time.indoors == true)
   {
		if(screen.x[0] < 12) screen.x[0] = 12;
      if(screen.y[0] < 3) screen.y[0] = 3;
		if(screen.x[0] > (player.time.area_x3 - player.time.area_x1) + 8) screen.x[0] = player.time.area_x3 - player.time.area_x1 + 8;
      if(screen.y[0] > (player.time.area_y2 - player.time.area_y1) - 1) screen.y[0] = player.time.area_y2 - player.time.area_y1 - 1;
		draw_area(player.time.area_x1, player.time.area_y1, player.time.area_y2, player.time.area_x3);
   	draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   }
	monster_move(screen_move);
   return 0;
}

int number(int min)
{
   int_temp = 0;
   strcpy(char_temp, "");
	cin.getline(char_temp, sizeof(char_temp) - 1);

   int_temp = atoi(char_temp);
   if(int_temp < min) int_temp = min;
	return int_temp;
}

int roll_stats()
{
	do
   {
		player.stat.Str = myrand(5) + 3;
   	player.stat.Con = myrand(5) + 3;
	   player.stat.Wis = myrand(5) + 3;
   	player.stat.Mag = myrand(5) + 3;
	   player.stat.Luck = myrand(5) + 3;
		clrscr();
   	textcolor(TOPIC);
	   cprintf("STAR PATTERN\n");
		textcolor(15);
	 	for(int_temp = 0; int_temp < player.stat.Str; int_temp++)
   	{
	     gotoxy(myrand(5) + (5*int_temp) + 3, 3);
   	  cprintf("*");
	   }
   	for(int_temp = 0; int_temp < player.stat.Con; int_temp++)
	   {
   	  gotoxy(myrand(5) + (5*int_temp) + 3, 4);
	     cprintf("*");
   	}
		for(int_temp = 0; int_temp < player.stat.Wis; int_temp++)
   	{
	     gotoxy(myrand(5) + (5*int_temp) + 3, 5);
   	  cprintf("*");
	   }
		for(int_temp = 0; int_temp < player.stat.Mag; int_temp++)
	   {
   	  gotoxy(myrand(5) + (5*int_temp) + 3, 6);
	     cprintf("*");
   	}
		for(int_temp = 0; int_temp < player.stat.Luck; int_temp++)
   	{
	     gotoxy(myrand(5) + (5*int_temp) + 3, 7);
   	  cprintf("*");
	   }
      textcolor(TOPIC);
      gotoxy(1, 10);
      cprintf("Accept pattern [y/n]: ");
   	ter = getch();
   } while(ter != 'y' && ter != 'Y');
	return 0;
}

int getnum()
{
	cin.getline(temp, sizeof(temp) - 1);
   if(atoi(temp) < 0) return 0;
   if(atoi(temp) > 100) { int_temp -= 100; return 100; }
   int_temp -= atoi(temp);
   return (atoi(temp));
}

int roll_skills(int points)
{
	textcolor(TOPIC);
	clrscr();
 	gotoxy(1, 1);
   cprintf("Give percentages for six different skills.\n");
   gotoxy(1, 2);
   cprintf("Total percentage must be 100%c\n", 37);
	do
   {
	   int_temp = 100;
      textcolor(TEXT);
		gotoxy(1, 3); cprintf("Give percentage for resist (%d%c left)  : ", int_temp, 37); player.skill.Resist = getnum();
		gotoxy(1, 4); cprintf("Give percentage for swimming (%d%c left): ", int_temp, 37); player.skill.Swimming = getnum();
		gotoxy(1, 5); cprintf("Give percentage for haggling (%d%c left): ", int_temp, 37); player.skill.Haggling = getnum();
		gotoxy(1, 6); cprintf("Give percentage for alchemy (%d%c left) : ", int_temp, 37); player.skill.Alchemy = getnum();
		gotoxy(1, 7); cprintf("Give percentage for stars (%d%c left)   : ", int_temp, 37); player.skill.Stars  = getnum();
		gotoxy(1, 8); cprintf("Give percentage for fame (%d%c left)  : ", int_temp, 37); player.skill.Fame = getnum();
		if(int_temp != 0)
      {
      	textcolor(4);
         cprintf("\rPercentages must be 100%c! %d%c is now used.\n", 37, (100-int_temp), 37);
         cprintf("\rPress any key to continue.\n\r");
         getch();
         clrscr();
      }
   } while(int_temp != 0);
	player.skill.Resist = (player.skill.Resist * points) / 100;
	player.skill.Swimming = (player.skill.Swimming * points) / 100;
   player.skill.Haggling = (player.skill.Haggling * points) / 100;
   player.skill.Alchemy = (player.skill.Alchemy * points) / 100;
   player.skill.Stars = (player.skill.Stars * points) / 100;
   player.skill.Fame = (player.skill.Fame * points) / 100;
   return 0;
}

int character_creation()
{
	clrscr();
	textcolor(TEXT);
	do
   {
		cprintf("\rWhat is your name: ");
		cin.getline(player.name, sizeof(player.name) - 1);
   } while(strlen(player.name) < 2);
	player.var.money = 3;
   player.var.salary = 0;
   player.var.score = 0;
   player.var.food = 10;
   roll_stats(); // star pattern
   roll_skills(myrand(10) + 25); // Amount of points available
   player.var.max_hp = count_max_hp();
   player.var.max_sp = count_max_sp();
   player.var.hp = player.var.max_hp;
   player.var.sp = player.var.max_sp;
   player.time.indoors = false;
	/* resetting objects */
	player.var.vision = 0;
   for(int_temp = 0; int_temp < TALKING; int_temp++)
   {
   	player.time.talking[int_temp] = 0;
   }
   for(int_temp = 0; int_temp < 17; int_temp++)
   {
   	player.var.alchemy[int_temp] = 0;
   }
   player.var.vis4 = false;
	player.item.corn = 3;
   player.item.scythe = false;
   player.item.scarecrow = false;
   player.item.animated_scarecrow = false;
   player.item.sleeping_bag = false;
   player.item.wax_apples = false;
   player.item.history_book = false;
   player.item.incarnate_book = false;
   player.item.necro_book = false;
   player.item.poem_book = false;
   player.item.horn = false;
   player.item.flute = false;
   player.item.jewels = false;
   player.item.mage_keys = false;
   player.item.roses = false;
   player.item.vira = false;
   player.item.zar = false;
   player.item.tarn = false;
   player.item.dural = false;
   player.item.cure = 0;
   player.item.moonstone = false;
   player.item.terastone = false;
   player.item.black_orb = false;
   player.item.white_orb = false;
   player.picked.scythe = false;
   player.picked.scarecrow = false;
   player.picked.animated_scarecrow = false;
   player.picked.sleeping_bag = false;
   player.picked.wax_apples = false;
   player.picked.history_book = false;
   player.picked.incarnate_book = false;
   player.picked.necro_book = false;
   player.picked.poem_book = false;
   player.picked.horn = false;
   player.picked.flute = false;
   player.picked.jewels = false;
   player.picked.mage_keys = false;
   player.picked.roses = false;
   player.picked.vira = false;
   player.picked.zar = false;
   player.picked.tarn = false;
   player.picked.dural = false;
   player.picked.cure = 0;
   player.picked.moonstone = false;
   player.picked.terastone = false;
   player.picked.black_orb = false;
   player.picked.white_orb = false;
   player.magic.frosty_way = false;
   player.magic.bestial_speech = false;
   player.magic.reinforce = false;
   player.magic.gateway = false;
	return 0;
}

int welcome_screen()
{
	bool option = false;
	char cmd = 0;
	int x = 0, y = 0;

	clrscr();
	textcolor(2);
	gotoxy(1, wherey());
	textcolor(11);
   cprintf("\rWelcome to\n");
	textcolor(15);
	cprintf("\r      -_-/    ,                /\\                /\\       \n");
	cprintf("\r     (_ /    ||    _          ||   '             \\/       *       Mountain\n");
	cprintf("\r    (_ --_  =||=  < \\, ,._-_ =||= \\\\ ,._-_  _-_  }{    * * * *    range\n");
	cprintf("\r      --_ )  ||   /-||  ||    ||  ||  ||   || \\\\ \\/     *   *     tramplers\n");
	cprintf("\r     _/  ))  ||  (( ||  ||    ||  ||  ||   ||/         * * * *       \n");
	cprintf("\r    (_-_-    \\\\,  \\/\\\\  \\\\,   \\\\, \\\\  \\\\,  \\\\,/  <>       *    \n");
	textcolor(11);
	cprintf("\r                                        by Topi Mansikkaviita\n");

	textcolor(TOPIC);
   cprintf("\r          (1) New game\n");
   cprintf("\r          (2) Load game\n");
   cprintf("\r          (X) Exit game\n");
	do
   {
		textcolor(TOPIC);
	   cprintf("\r          Choice: ");
      if(x == 0) x = wherex();
      if(y == 0) y = wherey();
      textcolor(TEXT);
		cmd = getch();
      cout << cmd;
      if(cmd == 'X' || cmd == 'x') exit(1);
      if(cmd == '1')
      {
			character_creation();
         introduction();
		   reset_time();
			screen.draw.big_y = 1;
		   screen.draw.big_x = 1;
		   screen.new_obj = 0;
		   screen.max_obj = 0;
		   strcpy(player.time.place, "Cornland");
			create_object(58, 10, '@', 15, false);
			/* fast monologue, can't use dialogue() */
			strcpy(char_temp, player.name);
         strcat(char_temp, ": ");
         strcat(char_temp, "Here I am, working for the viscount. I wish that someday");
         strcpy(screen.parser.line2, char_temp);
			strcpy(screen.parser.line3, "I can buy a farm of my own. I live at Hill Inn west of Deserras.");
         strcpy(screen.parser.line4, "I'm supposed to work on any of the viscount's cornfields scaring");
			strcpy(screen.parser.line5, "crows. During the day, bailiff sometimes comes to check my work.");
         option = true;
      }
      if(cmd == '2')
      {
			read_error = false;
			textcolor(TEXT);
         cprintf("\r\n          Your name: ");
         clreol();
      	strcpy(args, "players\\");
         cin.getline(char_temp, sizeof(char_temp) - 1);
         strcat(args, char_temp);
      	player = read_savefile(args);
         if(read_error == false)
         {
	  			create_object(50, 18, '@', 15, false);
   	      option = true;
         }
      }
      gotoxy(x, y);
   } while(option == false);
   return 0;
}

int main(void)
{
	welcome_screen();
	clrscr();
	write_screen("new_scr.dat", screen);
   write_screen("pre_scr.dat", screen);
 	map = read_map("corn.map", &max_x, &max_y);
	create_map();
	update_all_windows();
 	for(;;)
		virt_map();
}

