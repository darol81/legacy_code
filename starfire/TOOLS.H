int close_place(int close_h = 18, int open_h = 9) // close places at night
{
   if(player.time.hours > close_h || player.time.hours < open_h)
   {
   	parse_window("The doors are closed at this time.");
      return 1;
   }
   return 0;
}

int delay_text(char *msg)
{
	textcolor(TEXT);
	cprintf("\r");
	for(int_temp = 0; int_temp < strlen(msg); int_temp++)
   {
    	delay(100);
    	cprintf("%c", msg[int_temp]);
   }
	return 0;
}

int rand_poem()
{
	int_temp = myrand(3) + 1;
	clrscr();
   switch(int_temp)
   {
    	case 1:  delay_text("Eyes of the night, shadows of the past,\n");
   				delay_text("Disperser of the light, eternity at last,\n");
					delay_text("My body, my heart, both hurt and shattered,\n");
					delay_text("Drunken passion, all lust, but I'm flattered,\n");
					delay_text("I'm your harlot, alone, taste of the weak,\n");
					delay_text("But your doom, I'm the chaos you wreak,\n");
					delay_text("Your deed as horrible, makes me wonder,\n");
					delay_text("My soul and body, will be cut asunder,\n");
					delay_text("This is my day, tomorrow it's night,\n");
					delay_text("Yet I won't surrender, without a fight,\n");
					delay_text("My resistance's weak, though I'm witch,\n");
					delay_text("When the day is dawning, I lie at ditch,\n");
					delay_text("Motionless, my hair is wet from dew,\n");
					delay_text("But I'm not there, I'm reborn as new.\n");
      			break;
	case 2:		delay_text("Farmers, smiths and all of kind,\n");
					delay_text("They work for the food, that's hard to find,\n");
					delay_text("Counts, Dukes and Barons and all,\n");
					delay_text("They sit at castles, until it's fall,\n");
					delay_text("Spending time, waiting for the harvest,\n");
					delay_text("To take from the peasants, to rob them of their dearest.\n");
         		break;
	default: 	delay_text("Years will come, years go by,\n");
					delay_text("It will be bright, it isn't a lie,\n");
					delay_text("Pattern is one, it shall not break,\n");
					delay_text("Your time will come, you're the lake,\n");
					delay_text("Six deaths in a row, coming your aprons,\n");
					delay_text("Six women give a vow, 'We are the patrons'\n");
               break;
   }
   getch();
   clrscr();
   create_map();
   update_all_windows();
   return 0;
}


int show_vision(int i)
{
	if(i == 0) return 0;
	parse_window("You see a vision.");
	getch();
	clrscr();
	if(i == 1)
   {
		delay_text("In your vision, you see a young woman riding a horse. She smiles, but looks\n");
		delay_text("puzzled. She unmounts her horse, and walks to a geyser to drink water.\n");
		delay_text("Suddenly two ugly creatures appear. Those are the exact same ugly\n");
		delay_text("creatures that captured your father. You wake up as the voice of the woman\n");
		delay_text("shouts 'TRAMPLERS!' You see the woman dropping a flute under a rock.\n\r");
      player.stat.Luck += 1;
      getch();
      player.var.vision = 0;
		clrscr();
      player.var.score += 7;
      update_all_windows();
   }
   if(i == 2)
   {
		delay_text("You see yourself walking on the streets of the city. You come to a bazaar,\n");
      delay_text("and there's the woman you already saw in your previous vision. She comes\n");
      delay_text("to you saying 'I have been expecting you. Something tells me you have\n");
      delay_text("something that belongs to me.'\n\r");
      player.stat.Luck += 1;
      getch();
      player.var.vision = 0;
      clrscr();
      player.var.score += 7;
      player.var.anyaca = true; // meet Anyaca in Deserras
      update_all_windows();
   }
   if(i == 3)
   {
   	delay_text("You see a strange vision. You see two tramplers coming in from your window.\n");
      delay_text("You can hear the sounds very clearly...that's odd. You realize something \n");
      delay_text("horrible. This is not a dream, this is pure reality. Suddenly something \n");
      delay_text("touches you and throws you out of the window. You crawl back to the Hill Inn.\n\r");
      getch();
      player.var.vision = 0;
      clrscr();
		player.var.anyaca = false;
      player.item.flute = false;
      player.var.hp = 3;
      update_all_windows();
   }
   if(i == 4 && player.var.vis4 == false)
   {
		delay_text("You imagine yourself walking in the wilderness at night. It is nearly \n");
      delay_text("midnight. You are starting to feel exhausted and tired. You start walking\n");
      delay_text("towards a geyser near the mountains. You arrive to the geyser, drink some\n");
      delay_text("water and see sorceress Anyaca sitting next to you. She doesn't speak,\n");
      delay_text("she just looks on the sky, looking a bit sad.\n\r");
      player.var.vis4 = true;
      getch();
   }
   if(i == 5)
   {
		delay_text("You hear lovely music. It is Sorceress Anyaca playing her flute. Suddenly a\n");
		delay_text("man dressed as a black knight arrives on his horse. He comes off the saddle,\n");
		delay_text("and starts talking to Anyaca.\n");
		delay_text("Anyaca  : 'Oh viscount, I see you have finally answered my summons.'\n");
		delay_text("Viscount: 'If I understood right, you have requested me to use my power to\n");
		delay_text("           persuade the city elders to remove the mountain range?'\n");
		delay_text("Anyaca  : 'Yes, my lord.'\n");
		delay_text("Viscount: 'I'm interested. It would surely open more connections to this dead\n");
		delay_text("           valley.'\n");
		delay_text("Anyaca  : 'Perhaps this alliance is then sealed?'\n");
		delay_text("Viscount: 'That shall it be. I will give my word, that the elders will remove\n");
		delay_text(" 	       the mountain range soon, but that is up to you.'\n");
      delay_text("\n\nSuddenly you wake up in the middle of the night.\n\n");
		delay_text("You suddenly realize that the black knight was the viscount himself, and he\n");
		delay_text("made an alliance with Sorceress Anyaca as they both are striving to remove\n");
		delay_text("the mountain range that for sixteen years has prevented tramplers from\n");
		delay_text("invading the valley. Have they forgotten the tramplers completely? That must\n");
		delay_text("not happen, or it will directly lead to a war.\n");
		getch();
      clrscr();
      player.var.vision = 0;
		player.time.talking[6] = 5; // Anyaca talk changed
      player.var.score += 12;
      update_all_windows();
   }
   return 0;
}
int end_game()
{
	clrscr();
	cprintf("\rTo be continued...\n");
	textcolor(15);
	cprintf("\r      -_-/    ,                /\\                /\\       \n");
	cprintf("\r     (_ /    ||    _          ||   '             \\/       *       -Elven   \n");
	cprintf("\r    (_ --_  =||=  < \\, ,._-_ =||= \\\\ ,._-_  _-_  }{    * * * *     Longbow\n");
	cprintf("\r      --_ )  ||   /-||  ||    ||  ||  ||   || \\\\ \\/     *   *              \n");
	cprintf("\r     _/  ))  ||  (( ||  ||    ||  ||  ||   ||/         * * * *       \n");
	cprintf("\r    (_-_-    \\\\,  \\/\\\\  \\\\,   \\\\, \\\\  \\\\,  \\\\,/  <>       *    \n");
	textcolor(2);
	cprintf("\r\n\Your score was %d points out of %d\n", player.var.score, MAX_SCORE);
   cprintf("\r%s saved for Starfire II - Elven Longbow.\n", player.name);
 	strcpy(char_temp, "players\\");
   strcat(char_temp, player.name);
	write_savefile(char_temp, player);
   exit(0);
   return 0;
}

int introduction()
{
	cout <<"Do you want to read introduction? [y/n]: ";
   ter = getch();
   if(ter != 'y' && ter != 'Y') return 0;
	clrscr();
	delay_text("You have always had a very good memory. You remember events from the past\n");
	delay_text("very clearly, the details also. You are now an adult, but horrifying memories\n");
	delay_text("from the past are still troubling you. You clearly remember the rumours about\n");
	delay_text("war 16 years ago. That happened when you were five years old. Your mother\n");
	delay_text("was constantly telling that there won't be a war, but you remember that each\n");
	delay_text("and every day at those times, you cried until you fell asleep. You remember\n");
	delay_text("waking up at nights screaming just to realize that you had seen nightmares.\n");
	delay_text("You still remember those nights, even the dreams. One night, you saw a dream,\n");
	delay_text("in which your father was captured by ugly looking creatures while you were\n");
	delay_text("overwhelmed by fear unable to do anything. You woke up acting hysterically.\n");
	delay_text("'It was just a dream', your father said, but you knew it wasn't. Year later,\n");
	delay_text("that happened, just like you had pictured it. Your father wasn't the only\n");
	delay_text("one captured, and so the town elders gathered to have a meeting. They cast\n");
	delay_text("a mystical spell that caused mountains to grow higher to the skies, to\n");
	delay_text("prevent monsters from attacking the peaceloving town. There was no longer\n");
	delay_text("exits to the other world. Next night was hell. You had more nightmares about\n");
	delay_text("those ugly creatures. You can't say which was more horrifying: to realize\n");
	delay_text("that you had an ability to see in future, or to know that those mountains\n");
	delay_text("would not be created to last. Sixteen years have gone by, but lately you have\n");
   delay_text("started to see new visions and are afraid of upcoming war. You also have a\n");
   delay_text("very special talent. You have been able to know people without having to meet\n");
   delay_text("them beforehand. Sometimes you know people's names also.\n");
   delay_text("But now, press any key to start.\n\r");
   getch();
   return 0;
}

int count_max_hp()
{
	int_temp = 0;
   int_temp = (player.stat.Str * 2.5);
   int_temp += (player.stat.Con * 3.3);
   return int_temp;
}

int count_max_sp()
{
	int_temp = 0;
   int_temp = (player.stat.Wis * 2.7);
   int_temp += (player.stat.Mag * 2.2);
   return int_temp;
}

int hurt(int num)
{
	if(player.skill.Resist > myrand(20))
   {
   	parse_window("You avoid damage with your high resist skill.");
      return 0;
   }
	player.var.hp -= num;
	update_all_windows();
   if(player.var.hp < 1)
   {
		parse_window("When you were born, you knew your days would be numbered but");
		parse_window("you just didn't know the days of your life were now behind. Your");
		parse_window("death remained as a mystery that was never solved. You will be ");
      parse_window("remembered as a legend.");
      exit(0);
   }
	return 0;
}

int frame_crossings()
{
	textcolor(SCREEN);
	gotoxy(10, 1);
   cprintf("+");
   gotoxy(79, 1);
   cprintf("+");
	gotoxy(10, 16);
   cprintf("+");
   gotoxy(10, 22);
   cprintf("+");
	gotoxy(79, 16);
   cprintf("+");
   gotoxy(79, 22);
   cprintf("+");
   gotoxy(12, 24);
	return 0;
}

int dialogue(const char *msg, const char* name = player.name)
{
	char parsed_msg[80];
	strcpy(parsed_msg, name);
   strcat(parsed_msg, ": ");
   strcat(parsed_msg, msg);
   parse_window(parsed_msg);
   getch();
	return 0;
}

int parse_window(char msg[70])
{
   strcpy(screen.parser.line1, screen.parser.line2);
   strcpy(screen.parser.line2, screen.parser.line3);
   strcpy(screen.parser.line3, screen.parser.line4);
   strcpy(screen.parser.line4, screen.parser.line5);
   strcpy(screen.parser.line5, msg);
	textcolor(7);
	gotoxy(12, 17);
   clreol();
   cprintf("%s", screen.parser.line1);
	gotoxy(12, 18);
   clreol();
   cprintf("%s", screen.parser.line2);
	gotoxy(12, 19);
   clreol();
   cprintf("%s", screen.parser.line3);
	gotoxy(12, 20);
   clreol();
   cprintf("%s", screen.parser.line4);
	gotoxy(12, 21);
   clreol();
   cprintf("%s", screen.parser.line5);
	textcolor(SCREEN);
   for(int y = 1; y < 25; y++)
   {
   	gotoxy(79, y);
      cprintf("|");
   }
	frame_crossings();
	return 0;
}

int map_color(char c, char usage[20])
{
	int color = 0;
	switch(c)
   {
   	case 't': color = 8; break;
		case 'M': color = 8; break;
      case 'h': color = 7; break;
      case 'd': color = 14; break;
      case 'v': color = 10; break;
      case 'a': color = 15; break;
      case 'm': color = 7; break;
      case 'f': color = 2; break;
      case 'F': color = 2; break;
		case 'j': color = 2; break;
      case 'J': color = 10; break;
      case 'S': color = 10; break;
		case 'z': color = 14; break;
      case 'Z': color = 14; break;
      case 'g': color = 6; break;
		case '.': color = 6; break;
		case '|': color = 6; break;
      case '\\': color = 6; break;
      case '/': color = 6; break;
		case '=': color = 6; break;
      case '-': color = 6; break;
		case '%': color = 3; break;
      case 'c': color = 4; break;
		case 'G': color = 9; break;
	   case '+': color = 6; break;
   	case 'H': color = 7; break;
		case 'r': color = 1; break;
      case 'R': color = 1; break;
      case 'L': color = 1; break;
		case '*': color = 1; break;
      case 'l': color = 1; break;
      case '~': color = 1; break;
		case 'Y': color = 6; break;
      case 'p': color = 10; break;
		case 's': color = 11; break;
		case '#': color = 4; break;
      case 'V': color = 4; break;
		case '@': color = 3; break;
      case '!': color = 15; break;
      case '?': color = 15; break;
      case '0': color = 14; break;
      case '<': color = 15; break;
      case '>': color = 15; break;
      default: color = 0; break;
   }
	/* dusk and dawn */
	if(player.time.indoors == false)
   {
		switch(player.time.light)
  		{
  			case 0: break;
	      case 1: color = 12; break;
  		   case 2: color = 7; break;
      	case 3: color = 8; break;
	      default: if(player.magic.spell == 'a' && player.magic.duration > 0 && !strcmp(usage, "create_map") == 0) break;color = 8; if(strcmp(usage, "create_map") == 0) color = 0; break;
  		}
   }
	return color;
}

int land_desc()
{
	char c;
   c = map[true_y(screen.y[0])][true_x(screen.x[0])];
   switch(c)
   {
   	case 't': parse_window("You are walking on tundra."); break;
		case 'M': parse_window("You are walking on mountains."); break;
      case 'h': parse_window("You are walking on hills."); break;
      case 'd': parse_window("You are walking on desert."); break;
      case 'v': parse_window("You are walking on valley."); break;
      case 'a': parse_window("You are climbing an arctic hill."); break;
      case 'm': parse_window("You are walking on meadow."); break;
      case 'f': parse_window("You are walking in evergreen forest."); break;
      case 'F': parse_window("You are walking in forest."); break;
		case 'j': parse_window("You are in jungle."); break;
      case 'J': parse_window("You are in rainforest."); break;
      case 'S': parse_window("You are in savanna."); break;
		case 'z': parse_window("You are in shore."); break;
      case 'Z': parse_window("You are in beach."); break;
      case 'g': parse_window("You are walking on grasslands."); break;
		case '.': parse_window("There's a lovely path in here."); break;
		case '|': parse_window("You are walking on road."); break;
      case '\\':parse_window("You are walking on road."); break;
      case '/': parse_window("You are walking on road."); break;
		case '=': parse_window("You are walking on bridge."); break;
      case '-': parse_window("You are walking on road."); break;
		case '%': parse_window("There is a city in here."); break;
      case 'c': parse_window("The city walls rise very high."); break;
		case 'G': parse_window("You are walking on glacier."); break;
	   case '+': parse_window("You are standing at crossing of roads."); break;
   	case 'H': parse_window("You are walking on highlands."); break;
		case 'r': parse_window("You are wading in river."); break;
      case 'R': parse_window("You are swimming in deep river."); break;
      case 'L': parse_window("You are swimming in deep lake."); break;
		case '*': parse_window("You are standing next to a waterfall."); break;
      case 'l': parse_window("You are swimming in shallow lake."); break;
      case '~': parse_window("You are swimming in ocean."); break;
		case 'Y': parse_window("You are walking on cornfields."); break;
      case 'p': parse_window("You are walking on plains."); break;
		case 's': parse_window("You are walking at swamp."); break;
      case 'V': parse_window("There's a volcano in here."); break;
      case '!': parse_window("You are standing next to a geyser."); break;
      case '?': parse_window("There must be something special in here."); break;
      case '<': parse_window("There must be something special in here."); break;
      case '>': parse_window("There must be something special in here."); break;
      case '@': parse_window("There must be something special in here."); break;
   }
   return 0;
}

int cast_spell(char *spell)
{
	if(player.magic.duration > 0)
   {
		parse_window("The effect of your previous spell stops.");
      player.magic.duration = 0;
   }
	if(strcmp(spell, "bestial speech") == 0)
   {
   	if(player.var.sp < 4)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
		parse_window("You concentrate very hard and call for the animals");
      parse_window("of the wilderness with your shouts. You attract bobcats");
      parse_window("and wolves, and make coyotes howl at you from afar.");
      parse_window("Suddenly the howls of the coyotes make sense, as they");
      parse_window("become understandable to you.");
      player.magic.duration = player.stat.Mag * 2;
      player.magic.spell = 'f';
      player.var.sp -= 4;
   }
   if(strcmp(spell, "frosty way") == 0)
   {
   	if(player.var.sp < 5)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
		parse_window("You concentrate very hard and start thinking about warm");
      parse_window("thoughts. You can feel the change in your body as the");
      parse_window("warmth starts to gather in your body. You also notice");
      parse_window("that everything around is getting very cold. That gives");
      parse_window("you a shiverish feeling.");
      player.magic.duration = player.stat.Mag * 5;
      player.magic.spell = 'e';
      player.var.sp -= 5;
   }
   if(strcmp(spell, "mourning from beyond") == 0)
   {
   	if(player.var.sp < 7)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
		parse_window("You concentrate very hard and call for the lost souls");
      parse_window("in order to solemnize your magic. You hear a knocking");
      parse_window("sound in your ears. You feel like you have achieved");
      parse_window("another spiritual level.");
      player.magic.duration = player.stat.Mag * 2;
      player.magic.spell = 'd';
      player.var.sp -= 7;
   }
	if(strcmp(spell, "light") == 0)
   {
		if(player.var.sp < 2)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
      parse_window("You cast a spell and your clothes start to radiate ");
      parse_window("white light all around you.");
      player.magic.duration = player.stat.Mag * 20;
      player.magic.spell = 'a';
      player.var.sp -= 2;
   }
   if(strcmp(spell, "animate") == 0)
   {
   	if(player.var.sp < 8)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
      parse_window("You search for small rocks and juggle them around in the air");
      parse_window("until you're hands are glowing white. Then you concentrate");
      parse_window("and channel your magical powers. You have now the ability ");
      parse_window("to bless items with 'animation'");
      player.var.sp -= 8;
      player.magic.duration = player.stat.Mag;
      player.magic.spell = 'c';
   }
   if(strcmp(spell, "gateway") == 0)
   {
      if(player.var.sp < 5)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
      player.var.sp -= 8;
      if(true_x(screen.x[0]) == 104 && true_y(screen.y[0]) == 6)
      {
      	strcpy(player.time.place, "Elf Land");
			screen.draw.big_x = 2;
         screen.draw.big_y = 0;
         screen.x[0] = 54;
         screen.y[0] = 4;
			parse_window("You knock the Plane of World, and activate it");
         parse_window("with your magic. Suddenly you find yourself");
         parse_window("from elven dimension.");
         getch();
         create_map();
         update_all_windows();
      }
      else if(true_x(screen.x[0]) == 134 && true_y(screen.y[0]) == 4)
      {
      	strcpy(player.time.place, "Cornland");
			screen.draw.big_x = 1;
         screen.draw.big_y = 0;
         screen.x[0] = 64;
         screen.y[0] = 6;
			parse_window("You knock the Plane of World, and activate it");
         parse_window("with your magic. Suddenly you find yourself");
         parse_window("back from Cornland.");
         getch();
         create_map();
         update_all_windows();
      }
      else
      {
      	parse_window("You failed to activate a gateway.");
      }
      update_all_windows();
   }
   if(strcmp(spell, "reinforce") == 0)
   {
   	if(player.var.sp < 7)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
		parse_window("You concentrate very hard and clap your hands many times");
      parse_window("until they start to crackle. Your hands are flaming as ");
      parse_window("you keep clapping your hands. You have the ability to ");
      parse_window("reinforce by touch.");
      player.var.sp -= 7;
      player.magic.duration = player.stat.Mag;
      player.magic.spell = 'h';
   }
   if(strcmp(spell, "dim path") == 0)
   {
   	if(player.var.sp < 3)
      {
      	parse_window("You lack magical power.");
         return 0;
      }
      parse_window("Suddenly you are surrounded by colourful Will O'Wisps.");
      parse_window("They follow you but some of them stay behind to emit ");
      parse_window("dim light to the terrain.");
      player.magic.duration = player.stat.Mag * 20;
      player.magic.spell = 'b';
      player.var.sp -= 3;
   }
   update_all_windows();
   return 0;
}

int pick_up()
{
	char place1[20], place2[20], place3[20], place4[20], place5[20];
   char prep[10], parsed[50], searching[20];
	char search = 0;
	strcpy(parsed, "Pick up");
	strcpy(place1, "");
	strcpy(place2, "");
	strcpy(place3, "");
	strcpy(place4, "");
	strcpy(place5, "");
   /* Places to search */
	if(strcmp(player.time.place, "Waterfall") == 0)
   {
   	strcpy(place1, "altar");
   }
	if(strcmp(player.time.place, "Library") == 0)
   {
   	strcpy(place1, "table");
      strcpy(place2, "'poems' shelf");
      strcpy(place3, "'necromancy' shelf");
      strcpy(place4, "'history' shelf");
   }
   if(strcmp(player.time.place, "Geyser") == 0)
	{
   	strcpy(place1, "lake");
      strcpy(place2, "geyser");
      strcpy(place3, "rock");
      strcpy(place4, "grass");
   }
   if(strcmp(player.time.place, "Cemetery") == 0)
   {
   	strcpy(place1, "mausoleum");
      strcpy(place2, "crypt");
      strcpy(place3, "grave");
   }
	if(strcmp(player.time.place, "Granary") == 0)
   {
		strcpy(place1, "floor");
      strcpy(place2, "barrel");
      strcpy(place3, "table");
   }
   if(strcmp(player.time.place, "Hill Inn") == 0)
   {
   	strcpy(place1, "table");
      strcpy(place2, "closet");
      strcpy(place3, "floor");
   }
   if(strlen(place1) < 1)
   {
   	parse_window("It seems like there's nothing special here.");
   	return 0;
   }
	strcpy(parsed, "Searching: 1) ");
	strcat(parsed, place1);
	if(strlen(place1) > 0) parse_window(parsed);
   strcpy(parsed, "           2) ");
   strcat(parsed, place2);
   if(strlen(place2) > 0) parse_window(parsed);
   strcpy(parsed, "           3) ");
   strcat(parsed, place3);
   if(strlen(place3) > 0) parse_window(parsed);
   strcpy(parsed, "           4) ");
   strcat(parsed, place4);
   if(strlen(place4) > 0) parse_window(parsed);
   strcpy(parsed, "           5) ");
   strcat(parsed, place5);
   if(strlen(place5) > 0) parse_window(parsed);
	do
   {
		parse_window("Search what (Esc aborts): ");
		search = getch();
		if(search == 49) search = 1; // searching slot 1
		if(search == 50) search = 2; // searching slot 2
		if(search == 51) search = 3; // searching slot 3
		if(search == 52) search = 4; // searching slot 4
		if(search == 53) search = 5; // searching slot 5
   } while(search < 1 || search > 5 && search != 27);
   if(search == 27 || search == 0)
   {
   	parse_window("Aborted.");
      return 0;
   }
	switch(search)
   {
   	case 1: strcpy(searching, place1); break;
   	case 2: strcpy(searching, place2); break;
   	case 3: strcpy(searching, place3); break;
   	case 4: strcpy(searching, place4); break;
   	case 5: strcpy(searching, place5); break;
   }
   strcpy(parsed, "1) Search on ");
   strcat(parsed, searching);
   parse_window(parsed);
   strcpy(parsed, "2) Search in ");
   strcat(parsed, searching);
   parse_window(parsed);
   strcpy(parsed, "3) Search under ");
   strcat(parsed, searching);
   parse_window(parsed);
	do
   {
		parse_window("Choose (Esc aborts): ");
		search = getch();
		if(search == 49) search = 1; // searching slot 1
		if(search == 50) search = 2; // searching slot 2
		if(search == 51) search = 3; // searching slot 3
   } while(search < 1 || search > 3 && search != 27);
   if(search == 27 || search == 0)
   {
   	parse_window("Aborted.");
      return 0;
   }
	switch(search)
   {
   	case 1: strcpy(prep, "on"); break;
      case 2: strcpy(prep, "in"); break;
      case 3: strcpy(prep, "under"); break;
   }
	strcpy(parsed, "Searching ");
   strcat(parsed, player.time.place);
   strcat(parsed, " for items ");
   strcat(parsed, prep);
   strcat(parsed, " ");
   strcat(parsed, searching);
	/* All searchable items */
	if(strcmp(parsed, "Searching Waterfall for items on altar") == 0 && player.picked.vira == false)
   {
   	parse_window("You walk to the altar. There seems to be a piece of Vira");
      parse_window("star on it. You decide to take Vira star with you.");
      player.var.score += 3;
      player.item.vira = true;
      player.picked.vira = true;
      update_all_windows();
      return 0;
   }
	if(strcmp(parsed, "Searching Cemetery for items on grave") == 0 && player.picked.roses == false)
   {
   	parse_window("You walk to the grave and notice some beautiful red roses.");
      parse_window("Those have been left to respect somebody. Nonetheless, they");
      parse_window("look so beautiful, that you take them with you.");
      player.var.score += 2;
      player.item.roses = true;
      player.picked.roses = true;
      update_all_windows();
      return 0;
   }
   if(strcmp(parsed, "Searching Geyser for items under rock") == 0 && player.time.talking[0] > 0 && player.picked.flute == false)
   {
		parse_window("You remember seeing a woman drop her flute under a rock, so it");
      parse_window("was quite easy for you. You pick up the flute.");
      player.var.score += 8;
      player.var.vision = 2; // Anyaca appears in vision, wishing to get her flute back
      player.picked.flute = true;
      player.item.flute = true;
      update_all_windows();
      return 0; 
   }
	if(strcmp(parsed, "Searching Library for items in 'history' shelf") == 0 && player.picked.history_book == false)
   {
		parse_window("You search around the bookshelves and find a book that looks very ");
      parse_window("valuable. The book is very big and it contains biographies of");
      parse_window("heroes of our lifetime. This must be an epic to use if looking for");
      parse_window("information on some very important person.");
      parse_window("You go sign your name on the book.");
      player.picked.history_book = true;
      player.item.history_book = true;
      player.var.score += 1;
      update_all_windows();
      return 0;
   }
	if(strcmp(parsed, "Searching Library for items in 'necromancy' shelf") == 0 && player.picked.necro_book == false)
   {
   	parse_window("You search around the bookshelves and find a book that is made from");
      parse_window("leather. The deck of book is labelled 'Hauntings from the grave'");
      parse_window("It sounds interesting, so you take it with you. When you go to sign");
      parse_window("your name to book when librarian says that it is reserved for the");
      parse_window("viscount. You can't leave the library with this book.");
      player.picked.necro_book = true;
      player.item.necro_book = true;
      player.var.score += 1;
      update_all_windows();
		return 0;
   }
	if(strcmp(parsed, "Searching Library for items in 'poems' shelf") == 0 && player.picked.poem_book == false)
   {
   	parse_window("You search around and find book of poems written by ");
      parse_window("anonymous people. You believe you could find some time");
      parse_window("to look that out. You go sign your name on the book.");
      player.picked.poem_book = true;
      player.item.poem_book = true;
      player.var.score += 1;
      update_all_windows();
      return 0;
   }
	if(strcmp(parsed, "Searching Library for items on table") == 0 && player.picked.incarnate_book == false)
   {
		parse_window("You look at table. There is a small sign labelled 'Returned books'.");
      parse_window("Somebody has been careless and you notice that there is a book that ");
      parse_window("is not placed to the correct place and the librarian hasn't noticed");
      parse_window("it yet. You become curious and take the book.");
      player.item.incarnate_book = true;
      player.picked.incarnate_book = true;
      player.var.score += 1;
      update_all_windows();
      return 0;
   }
	if(strcmp(parsed, "Searching Hill Inn for items on table") == 0 && player.picked.wax_apples == false)
   {
   	parse_window("You look at the table. You see a big fruit bowl that ");
      parse_window("contains many delicious looking fruits. You think about");
      parse_window("tasting them, but notice they're made of wax. It is just");
      parse_window("a decoration. Apples look very nice, so you slip a few");
      parse_window("wax apples to your pocket.");
      player.item.wax_apples = true;
      player.picked.wax_apples = true;
      player.var.score += 3;
      update_all_windows();
      return 0;
   }
   if(strcmp(parsed, "Searching Hill Inn for items in closet") == 0 && player.picked.sleeping_bag == false)
   {
		parse_window("You open the closet and you see a sleeping bag in there.");
      parse_window("There's a small paper saying 'Free for adventurers'.");
      parse_window("You decide to grab the sleeping bag with you.");
      player.item.sleeping_bag = true;
      player.picked.sleeping_bag = true;
      player.var.score += 2;
      update_all_windows();
      return 0;
   }
   if(strcmp(parsed, "Searching Granary for items in barrel") == 0)
   {
		if(player.time.talking[6] > 5) // magical winter
      {
      	parse_window("The barrel is empty. There used to be corn.");
         return 0;
      }
		parse_window("There's only some corn-cobs in the barrel.");
      parse_window("And the better ones are still in the field.");
      return 0;
   }
   if(strcmp(parsed, "Searching Granary for items on table") == 0)
   {
   	if(player.var.salary == 0)
      {
      	parse_window("The table is empty.");
         return 0;
      }
      parse_window("There are some crowns on the table left by the bailiff.");
      parse_window("You take them with you. Seems like the scarecrow is doing its job");
      parse_window("very well.");
      player.var.money += player.var.salary;
      player.var.salary = 0;
      update_all_windows();
		return 0;
   }
   if(strcmp(parsed, "Searching Granary for items on floor") == 0 && player.picked.scythe == false && player.picked.scarecrow == false)
   {
   	parse_window("You look around and find an old scarecrow that is wielding scythe.");
      dialogue("But that scythe helps me to collect those corn-cobs.");
      dialogue("I wonder if I can take that scarecrow to the cornfields.");
      dialogue("Then I wouldn't have to run over the fields.");
      player.var.score += 2;
      player.item.scythe = true;
      player.item.scarecrow = true;
      player.picked.scythe = true;
      player.picked.scarecrow = true;
      update_all_windows();
   	return 0;
   }
	parse_window(parsed);
   parse_window("...but nothing found.");
	return 0;
}

int look_around()
{
	if(strcmp(player.time.place, "Lab") == 0)
   {
   	parse_window("There are some formulas written on a blackboard.");
      parse_window("Mandrake root + bird egg = gold");
      parse_window("Muddy goo + spider web = Food");
      parse_window("'As a homework, study alchemy by yourself' --Maral");
		dialogue("Aha! This is alchemy school, and Maral must be teacher.");
   }
	if(strcmp(player.time.place, "Waterfall") == 0)
   {
   	parse_window("These are the world's biggest waterfalls, you guess. ");
      parse_window("You have never seen anything like this during your");
      parse_window("whole life. It's a massive monument of nature");
      parse_window("and it releases a royal sound as the water");
      parse_window("splashes to the ground.");
   }
	if(strcmp(player.time.place, "Village") == 0)
   {
      parse_window("This place looks like a deserted village. There doesn't ");
      parse_window("seem to be anyone living in those jungle huts. This looks");
      parse_window("very tropical, so you don't really understand why people");
      parse_window("would leave this kind of place.");
   }
   if(strcmp(player.time.place, "Volcano") == 0)
   {
   	parse_window("This is the volcano of the salamanders. Salamanders were");
      parse_window("once considered to be the gods of fire, but lately people");
      parse_window("have started to realize that they're just normal magical");
      parse_window("creatures who enjoy being next to fire.");
   }
   if(strcmp(player.time.place, "Elf Land") == 0)
   {
   	parse_window("This is the elves dimension. You don't really know what's");
      parse_window("the name of this world, so you call it the 'Elf Land'. It");
      parse_window("looks very lovely. There are lots of woods in here, when");
      parse_window("compared to Cornland, where most the terrain is mountains.");
   }
	if(strcmp(player.time.place, "Cemetery") == 0)
   {
   	parse_window("This is the cemetery of Deserras. All the dead people are");
      parse_window("buried in here. There are lots of small graves but then you");
      parse_window("three very massive graves. Those are very eye-catching and ");
      parse_window("you believe that those graves belong to very important");
      parse_window("people.");
   }
	if(strcmp(player.time.place, "Gift Shop") == 0)
   {
   	parse_window("This is the local gift and antique shop. Everything you see ");
      parse_window("in here is quite old and ornamental. There are wooden shelves");
      parse_window("that are full of decorative items and perhapse there are ");
      parse_window("some priceless artifacts also.");
   }
	if(strcmp(player.time.place, "Geyser") == 0)
   {
   	parse_window("This place seems extraordinary. There is a hot geyser that");
      parse_window("is sprinkling water to the sky with awesome power. There ");
      parse_window("is the mountain range starting from next to it also, and ");
      parse_window("there's a warm lake getting its water from the geyser.");
   }
	if(strcmp(player.time.place, "Musique") == 0)
   {
   	parse_window("This is Mandal, the bard's respected Musique Shop. Mandal ");
      parse_window("is a retired bard who nowadays makes musical instruments");
      parse_window("by himself, and he also teaches how to play those if newbies");
      parse_window("wish to learn the skills of a minstrel.");
   }
	if(strcmp(player.time.place, "Library") == 0)
   {
   	parse_window("These large quarters belong the library of Deserras. Deserras'");
      parse_window("library is relatively big, and there are many kinds of books");
      parse_window("and tomes that contain so much information that one person");
      parse_window("could not be able to read during his or her lifetime. If you");
		parse_window("are looking for something special, you can be sure you find it.");
   }
	if(strcmp(player.time.place, "Council") == 0)
   {
		parse_window("This is the council of the city of Deserras. Deserras is the capital");
      parse_window("city of Cornland, and in fact, the only city. Deserras is financially");
      parse_window("very stable place, and thanks belong to the council. Council in ");
      parse_window("Deserras is based on three wise persons, who make the decisions");
      parse_window("for the city.");
   }
   if(strcmp(player.time.place, "Market") == 0)
   {
   	parse_window("You have arrived to the streets of Deserras. Deserras, renowned for ");
      parse_window("its sightseens and marketing caravans has also become famous for ");
      parse_window("its mystical culture and vast collection of antique. Even though ");
      parse_window("Deserras has been isolated for nearly twenty years, it seems like");
      parse_window("it hasn't damage the city a bit."); 
   }
   if(strcmp(player.time.place, "Deserras") == 0)
   {
   	parse_window("Deserras is a very lovely place and it is the only city of Cornland.");
      parse_window("Its sightseens vary but there are a lot to see in Deserras. Deserras");
      parse_window("is the city of magicians, and one might also say that it is the city");
      parse_window("of merchants and thieves. Nonetheless, some people say that the");
      parse_window("merchants are better robbers than thieves.");
   }
   if(strcmp(player.time.place, "Cornland") == 0)
   {
		if(player.time.light == 0)
      {
			parse_window("This is Cornland. This used to be a lovely valley when you were ");
   	   parse_window("a small kid, but since those mountains were raised by elders, the ");
			parse_window("scenery is not as magnificent as it used to be. Nowadays everything");
	      parse_window("is so colossal, and grey. You really miss the days you were kid.");
   	   land_desc();
      }
      else
      {
      	if(player.var.sp < 1)
         {
         	parse_window("You lack magical power.");
            return 0;
         }
      	if(player.time.talking[6] == 7)
         {
         	if(player.skill.Stars < 4)
            {
            	parse_window("You fail to find Vira and Tarn or Zar and Dural.");
               parse_window("You think you should learn more about astrology.");
            }
            else
            {
            	if(player.picked.vira == false)
               {
                 	parse_window("You locate Vira in another dimension.");
	               parse_window("You see MASSIVE waterfalls.");
               }
               if(player.picked.zar == false)
               {
	               parse_window("You locate Zar in the volcano of salamanders.");
               }
               if(player.picked.tarn == false)
               {
	               parse_window("You locate Tarn in village on south island.");
               }
               if(player.picked.dural == false)
               {
                 parse_window("You can't locate Dural.");
                 getch();
                 parse_window("Suddenly Dural star falls.");
                 parse_window("You pick it up.");
                 dialogue("Hmm..what was that all about?");
                 player.picked.dural = true;
                 player.item.dural = true;
                 player.var.score += 2;
                 update_all_windows();
               }
            }
         }
         else
         {
         	talk_daemon("Dear stars, guide me!", 1, false);
            talk_daemon("Dear stars, make me legend!", 2, false);
            switch(talk_daemon("Dear stars, give me a gift!", 3, true))
            {
            	case 1: if(myrand(player.skill.Stars) > myrand(5))
               		  {
                       		player.time.light = 0;
		               		create_map();
                           player.var.sp = -9;
                           player.var.sp += player.stat.Luck;
                           update_all_windows();
                       }
                       else
                       {
                       	   player.var.sp = -9;
                           player.var.sp += player.stat.Luck;
                           update_all_windows();
								   parse_window("You try to but fail.");
                       }
                       break;
               case 2: if(myrand(player.skill.Stars) > myrand(5))
               		  {
                       		player.var.sp = -9;
                           player.var.sp += player.stat.Luck;
                           if(player.skill.Fame < 8) player.skill.Fame++;
                           update_all_windows();
                           parse_window("You feel famous.");
                       }
                       else
                       {
                       	   player.var.sp = -9;
                           player.var.sp += player.stat.Luck;
                           parse_window("You try but fail.");
                           update_all_windows();
                       }
                       break;
               case 3: if(player.picked.dural == true)
               		  {
                       	   parse_window("Stars ignore you.");
                           break;
                       }
               		  player.picked.dural = true;
               		  player.item.dural = true;
                       parse_window("Piece of Dural star drops from the sky.");
                       parse_window("You pick it up.");
                       player.var.score += 4;
                       update_all_windows();
                       break;
            }
         }
      }
   }
	if(strcmp(player.time.place, "Bailiff") == 0)
   {
   	parse_window("You are now in Bailiff's office. The bailiff works here and");
		parse_window("does some paper work and sometimes comes to check the results");
      parse_window("of your work also. This place is filled with mooseheads and");
      parse_window("different pelts. It's like a room of death.");
   }
   if(strcmp(player.time.place, "Hill Inn") == 0)
   {
   	parse_window("This is a lovely place where you stay your nights. It is ");
      parse_window("especially known for its visitors, who usually are errant");
      parse_window("knights or people who don't stay long there. It also offers");
      parse_window("rooms that are available for persons for free donations only.");
      parse_window("Some knights give large sums of crowns, so it becomes profitable.");
   }
	if(strcmp(player.time.place, "Circus") == 0)
   {
   	parse_window("This is an extremely big circus tent. It is just a tent that");
      parse_window("has been set so that there is no bottom at all. There is only");
      parse_window("grassfield under you. There is two small water ponds in the");
      parse_window("middle of the circus area. This tent truly is HUGE.");
   }
   if(strcmp(player.time.place, "Granary") == 0)
   {
   	parse_window("This is the granary where all the corn-cobs are saved for ");
      parse_window("the people for the winter. There are also some tools that can be");
      parse_window("used when working on a farm. Sometimes you wonder how the");
      parse_window("corn saves here in this kind of hot place, but the past few years");
      parse_window("show that somehow it saves. There are some wooden barrels in here.");
   }
	return 0;
}

int surdraw(int x, int y, char c, int color) // draws random surrounding screen
{
	switch(myrand(8) + 1) // random surrounding screen
   {
		case 1: y--; break;
      case 2: y--; x++; break;
      case 3: x++; break;
      case 4: y++; x++; break;
      case 5: y++; break;
      case 6: y++; x--; break;
      case 7: x--; break;
      default: y++; x--; break;
   }
	/* doesn't draw over game screen */
	if(x < 11) x = 11;
   if(y > 16) y = 16;
   if(x > 78) x = 78;
   if(y < 2) y = 2;
	/* works like draw from this on */
	gotoxy(x, y);
	textcolor(color);
  	cprintf("%c", c);
   gotoxy(12, 24);
   return 0;
}


int draw(int x, int y, char c, int color) /* draws simple sign */
{
	/* doesn't draw over game screen */
	if(x < 11) x = 11;
   if(y > 16) y = 16;
   if(x > 78) x = 78;
   if(y < 2) y = 2;
	gotoxy(x, y);
	textcolor(color);
 	cprintf("%c", c);
   gotoxy(12, 24);
	return 0;
}

int test_surter(int x, int y)
{
	bool deny_draw = false;
	for(int i = 0; i < screen.max_obj; i++)
   {
   	if(x == screen.x[i] && y == screen.y[i]) deny_draw = true;
   }
   return deny_draw;
}

int surnight(int x, int y) // surrounds coordinates with black terrain
{
	bool north = false, south = false, east = false, west = false;
	char c;
	/* these are border settings */
	if(player.time.night_x == 0 || player.time.night_y == 0)	return 0;
   if(player.magic.spell == 'b' && player.magic.duration > 0) return 0;
	if(player.time.light < 4) return 0;
	if(y < 3) north = true;
   if(y > 14) south = true;
   if(x < 12) west = true;
   if(x > 77) east = true;
	/* big_x and big_y are because of world updating */
	if(north == false && west == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y-1) == 0) draw(x-1, y-1, c, 0); }
   if(north == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)]; if(test_surter(x, y-1) == 0) draw(x, y-1, c, 0); }
   if(north == false && east == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y-1) == 0) draw(x+1, y-1, c, 0); }
   if(west == false) { c = map[y + (screen.draw.big_y * 8)][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y) == 0) draw(x-1, y, c, 0); }
   if(east == false) { c = map[y + (screen.draw.big_y * 8)][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y) == 0) draw(x+1, y, c, 0); }
   if(south == false && west == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y+1) == 0) draw(x-1, y+1, c, 0); }
   if(south == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)]; if(test_surter(x, y+1) == 0) draw(x, y+1, c, 0); }
   if(south == false && east == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y+1) == 0) draw(x+1, y+1, c, 0); }
   player.time.night_x = x;
   player.time.night_y = y;
	return 0;
}

int surter(int x, int y) // surrounds coordinates with terrain
{
	bool north = false, south = false, east = false, west = false;
	char c;
	if(player.time.indoors == true) return 0;
	/* these are border settings */
	if(player.time.light == 4)
   {
   	if(x != screen.x[0] || y != screen.y[0]) return 0;
		surnight(player.time.night_x, player.time.night_y);
   }
	if(y < 3) north = true;
   if(y > 14) south = true;
   if(x < 12) west = true;
   if(x > 77) east = true;
	/* big_x and big_y are because of world updating */
	if(north == false && west == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y-1) == 0) draw(x-1, y-1, c, map_color(c, "surter")); }
   if(north == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)]; if(test_surter(x, y-1) == 0) draw(x, y-1, c, map_color(c, "surter")); }
   if(north == false && east == false) { c = map[y + (screen.draw.big_y * 8)-1][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y-1) == 0) draw(x+1, y-1, c, map_color(c, "surter")); }
   if(west == false) { c = map[y + (screen.draw.big_y * 8)][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y) == 0) draw(x-1, y, c, map_color(c, "surter")); }
   if(east == false) { c = map[y + (screen.draw.big_y * 8)][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y) == 0) draw(x+1, y, c, map_color(c, "surter")); }
   if(south == false && west == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)-1]; if(test_surter(x-1, y+1) == 0) draw(x-1, y+1, c, map_color(c, "surter")); }
   if(south == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)]; if(test_surter(x, y+1) == 0) draw(x, y+1, c, map_color(c, "surter")); }
   if(south == false && east == false) { c = map[y + (screen.draw.big_y * 8)+1][x + (screen.draw.big_x * 40)+1]; if(test_surter(x+1, y+1) == 0) draw(x+1, y+1, c, map_color(c, "surter")); }
   player.time.night_x = x;
   player.time.night_y = y;
	return 0;
}


int reset_objects()
{
	for(int_temp = 1; int_temp < screen.max_obj; int_temp++)
   {
		screen.draw.alive[int_temp] = false;
   	screen.draw.seen[int_temp] = false;
		screen.draw.sign[int_temp] = ' ';
   	screen.draw.color[int_temp] = 0;
	   screen.x[int_temp] = 0;
   	screen.y[int_temp] = 0;
   }
   screen.max_obj = 1;
   screen.new_obj = 1;
	return 0;
}

int delete_object(int num)
{
	screen.draw.alive[num] = false;
   screen.draw.seen[num] = false;
	screen.draw.sign[num] = ' ';
   screen.draw.color[num] = 0;
   screen.x[num] = 0;
   screen.y[num] = 0;
	if(num == screen.max_obj)
   {
		screen.new_obj--;
      screen.max_obj--;
   }
   else
   {
	   screen.new_obj = num;
   	screen.max_obj--;
   }
	return 0;
}

int create_object(int x, int y, char monster, int color, bool alive)
{
	screen.draw.alive[screen.new_obj] = alive;
   screen.draw.seen[screen.new_obj] = false;
   screen.draw.sign[screen.new_obj] = monster;
   screen.draw.color[screen.new_obj] = color;
   screen.x[screen.new_obj] = x;
   screen.y[screen.new_obj] = y;
	if(screen.new_obj == screen.max_obj)
   {
   	screen.new_obj++;
      screen.max_obj++;
   }
   else
   {
      screen.new_obj = screen.max_obj;
   }
	return 0;
}

int upper_window()
{
	gotoxy(1, 1);
   textcolor(TOPIC);
   cprintf("ABILITIES");
	gotoxy(1, 2);
	textcolor(TEXT);
   cprintf("Str: %d", player.stat.Str);
   gotoxy(1, 3);
   cprintf("Con: %d", player.stat.Con);
   gotoxy(1, 4);
   cprintf("Wis: %d", player.stat.Wis);
   gotoxy(1, 5);
   cprintf("Mag: %d", player.stat.Mag);
   gotoxy(1, 6);
   cprintf("Luck:%d", player.stat.Luck);
   gotoxy(1, 7);
   textcolor(TOPIC);
   cprintf("SKILLS");
   textcolor(TEXT);
   gotoxy(1, 8);
   cprintf("Resist:%d", player.skill.Resist);
   gotoxy(1, 9);
   cprintf("Swim:  %d", player.skill.Swimming);
   gotoxy(1, 10);
   cprintf("Haggle:%d", player.skill.Haggling);
   gotoxy(1, 11);
	cprintf("Alch:  %d", player.skill.Alchemy);
	gotoxy(1, 12);
   cprintf("Stars: %d", player.skill.Stars);
   gotoxy(1, 13);
   cprintf("Fame:  %d", player.skill.Fame);
   gotoxy(1, 14);
   textcolor(TOPIC);
	cprintf("LOCATION");
	gotoxy(1, 15);
   textcolor(0);
   cprintf("          ");
   textcolor(TEXT);
   gotoxy(1, 15);
   cprintf("%s", player.time.place);
	gotoxy(10, 1);
	textcolor(SCREEN);
	for(int y = 1; y < 25; y++)
   {
   	gotoxy(10, y);
      cprintf("|");
   }
   for(int y = 1; y < 25; y++)
   {
   	gotoxy(79, y);
      cprintf("|");
   }
   return 0;
}


int lower_window()
{
	textcolor(TOPIC);
   gotoxy(1, 17);
   cprintf("CURRENT");
   textcolor(0);
   gotoxy(1, 18);
	cprintf("          ");
 	textcolor(TEXT);
	gotoxy(1, 18);
   cprintf("Hp: %d/%d", player.var.hp, player.var.max_hp);
	gotoxy(1, 19);
   textcolor(0);
	cprintf("          ");
	gotoxy(1, 19);
   textcolor(TEXT);
   cprintf("Sp: %d/%d", player.var.sp, player.var.max_sp);
	gotoxy(1, 20);
   cprintf("Crowns:%d", player.var.money);
	gotoxy(1, 21);
   textcolor(0);
	cprintf("          ");
	textcolor(TEXT);
   gotoxy(1, 21);
   cprintf("Food: %d", player.var.food);
	textcolor(TOPIC);
   gotoxy(1, 22);
	cprintf("ADVENTURE");
   textcolor(TEXT);
   gotoxy(1, 23);
   cprintf("Score:%d", player.var.score);
   gotoxy(1, 24);
   cprintf("Max:  %d", MAX_SCORE);
   textcolor(SCREEN);
	for(int x = 10; x < 80; x++)
   {
   	gotoxy(x, 1);
      cprintf("-");
   }
	for(int x = 1; x < 80; x++)
   {
   	gotoxy(x, 16);
      cprintf("-");
   }
	for(int x = 10; x < 80; x++)
   {
   	gotoxy(x, 22);
      cprintf("-");
   }
   return 0;
}

int update_all_windows() // small function to call other update functions
{
   lower_window();
	upper_window();
   frame_crossings();
   return 0;
}

int clear(int x, int y) // clears room, used by erase_old_obj();
{
	gotoxy(x, y);
	textcolor(0);
	cprintf(" ");
   return 0;
}

int erase_old_obj(int obj, bool move, bool date_screen) // clears screen
{
	if(obj == 0 && move == false) return 0; // player didn't move
	write_screen("new_scr.dat", screen);
	screen = read_screen("pre_scr.dat");
	if(date_screen == false)
	clear(screen.x[obj], screen.y[obj]);
   gotoxy(12, 24);
	screen = read_screen("new_scr.dat");
  	write_screen("pre_scr.dat", screen);
   return 0;
}


int map_field_boundaries()
{
	for(int_temp = 0; int_temp < screen.max_obj; int_temp++)
   {
   	if(screen.x[int_temp] < 11) screen.x[int_temp] = 11;
      if(screen.y[int_temp] > 15) screen.y[int_temp] = 15;
		if(screen.x[int_temp] > 78) screen.x[int_temp] = 78;
 	   if(screen.y[int_temp] < 2) screen.y[int_temp] = 2;
   }
	return 0;
}

int search_new_obj()
{
	for(int_temp = OBJECTS; int_temp > 0; int_temp--)
	{
   	if(screen.x[int_temp] == 0 && screen.y[int_temp] == 0) screen.new_obj = int_temp;
   }
	return 0;
}

int search_max_obj()
{
	for(int_temp = 0; int_temp < OBJECTS; int_temp++)
   {
   	if(screen.x[int_temp] > 0 && screen.y[int_temp] > 0) screen.max_obj = int_temp;
   }
   return 0;
}

int clear_area()
{
	int X = 0, Y = 0;
  	do
   {
		Y++;
		for(X = 11; X < 79; X++)
   	{
			draw(X, Y, '!' , 0);
		}
   } while(Y < 16);
   return 0;
}

int draw_area(int first_x, int first_y, int var_y, int var_x)
{
	int draw_x = 10, draw_y = 1, counter = 0;
   char c;
	do
   {
		draw_y++;
   	for(int_temp = 0; int_temp < (var_x - first_x); int_temp++)
      {
      	draw_x++;
         c = map[first_y+counter][first_x+int_temp];
		  	draw(draw_x, draw_y, c, map_color(c, "create_map"));
      }
      draw_x = 10;
      counter++;
   } while(counter < (var_y - first_y));
	return 0;
}

int create_map()
{
	int x = 0, y = 0, deleted = 0;
	char c;
	if(player.time.indoors == true) return 0;
  	do
   {
		y++;
		for(x = 11; x < 79; x++)
   	{
	   	c = map[y + (screen.draw.big_y * 8)][x + (screen.draw.big_x * 40)]; // reversed order in here, code from another source
         gotoxy(x, y);
         if(c == 'M' && player.time.talking[6] >= 10) // mountain range removed
         {
				draw(x, y, 'F', 2);
         }
         else
         {
				draw(x, y, c, map_color(c, "create_map"));
         }
		}
   } while(y < 15);
	for(int_temp = screen.max_obj; int_temp > 0; int_temp--)
   {
   	if(screen.draw.alive[int_temp] == false && screen.draw.seen[int_temp] == true)
      {
			deleted++;
         if(deleted == 1) screen.new_obj = int_temp;
			screen.draw.alive[int_temp] = false;
			screen.draw.seen[int_temp] = false;
			screen.draw.sign[int_temp] = ' ';
		   screen.draw.color[int_temp] = 0;
		   screen.x[int_temp] = 0;
		   screen.y[int_temp] = 0;
      }
   }
   if(deleted >= 2)
   {
   	search_new_obj();
      search_max_obj();
   }
	return 0;
}

int identify(char c, char place[20])
{
	strcpy(args, "");
	if(strcmp(place, "Volcano") == 0) // Volcano of salamander
   {
   	switch(c)
      {
      	case 'S': strcat(args, "Salamander King"); break;
      }
   }
	if(strcmp(place, "Village") == 0) // jungle village in south island
   {
   	switch(c)
      {
      	case '@': strcat(args, "Village Chief"); break;
      }
   }
	if(strcmp(place, "Guild") == 0) // mage guild
   {
   	switch(c)
      {
      	case '@': strcat(args, "Guildmaster"); break;
      }
   }
	if(strcmp(place, "Cemetery") == 0)
   {
   	switch(c)
      {
      	case 'C': strcat(args, "a crypt"); break;
         case 'G': strcat(args, "a massive grave"); break;
         case 'M': strcat(args, "a mausoleum"); break;
      }
   }
	if(strcmp(place, "Gift Shop") == 0)
   {
   	switch(c)
      {
      	case '@': strcat(args, "Salesman"); break;
      }
   }
	if(strcmp(place, "Musique") == 0)
   {
   	switch(c)
      {
      	case '@': strcat(args, "Mandal, the bard"); break;
      }
   }
   if(strcmp(place, "Market") == 0)
   {
   	switch(c)
      {
      	case 'A': strcat(args, "Sorceress Anyaca"); break;
      }
   }
	if(strcmp(place, "Geyser") == 0)
	{
   	switch(c)
      {
      	case 'A': strcat(args, "Sorceress Anyaca"); break;
      }
  	}
	if(strcmp(place, "Library") == 0)
   {
   	switch(c)
      {
      	case '@': strcat(args, "Librarian"); break;
      }
   }

	if(strcmp(place, "Circus") == 0)
   {
		switch(c)
      {
	   	case 'L': strcat(args, "Lion"); break;
   	   case 'T': strcat(args, "Liontamer"); break;
      	case 'J': strcat(args, "Juggler"); break;
      }
   }
	if(strcmp(place, "Council") == 0)
   {
   	switch(c)
      {
      	case 'D': strcat(args, "Darol, the Dauntless"); break;
         case 'T': strcat(args, "Tof, Archwizard of the Winter"); break;
      }
   }
	if(strcmp(place, "Bailiff") == 0)
   {
   	switch(c)
      {
      	case '@': strcat(args, "Bailiff"); break;
      }
   }
	return 0;
}


int give_item(char item[20])
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
     	parse_window("There's no one around.");
      return 0;
   }
	identify(screen.draw.sign[int_temp], player.time.place);

   if(strcmp(args, "Village Chief") == 0 && strcmp(item, "cure for death") == 0 && player.item.cure > 0)
	{
   	if(player.picked.tarn == true)
      {
      	dialogue("More vodka? Thanks!", "Chief");
         dialogue("Here's 5 crowns for that!", "Chief");
	      dialogue("Thank you.");
         player.var.money += 5;
         player.item.cure -= 1;
         update_all_windows();
         return 0;
      }
   	parse_window("You give your Cure for Death potion to chief.");
      dialogue("I can try, but I don't think it helps.", "Chief");
      dialogue("Tastes like vodka! I feel better already!", "Chief");
		dialogue("Take the Tarn-Star!", "Chief");
      dialogue("Thank you.");
      player.item.cure -= 1;
      player.picked.tarn = true;
      player.item.tarn = true;
      player.var.score += 6;
      update_all_windows();
		return 0;
   }
   if(strcmp(args, "Tof, Archwizard of the Winter") == 0 && strcmp(item, "terastone") == 0 && player.item.terastone == true)
   {
   	parse_window("You give terastone to Tof.");
      dialogue("That's bright, and colorful, what is this?", "Tof");
      parse_window("As Tof touches the terastone, you feel you share thoughts.");
      parse_window("Anyaca didn't tell anything about that.");
      parse_window("But you guess that the terastone is working.");
      getch();
      dialogue("A TERASTONE, EH? POSSESSOR STONE, EH?", "Tof");
      dialogue("Domaja! I call you for the blizzard!", "Tof");
		parse_window("You are still sharing thoughts. You read Tof's mind");
      parse_window("and find out he is going to kill you.");
      getch();
		dialogue("Domaja! You betrayer!", "Tof");
      talk_daemon("Domaja belongs to me now.", 1, false);
      talk_daemon("You're powerless without your spirit.", 2, false);
   	switch(talk_daemon("This is our only chance.", 3, true))
      {
      	case 1: dialogue("Really?", "Tof");
                 dialogue("I've been watching you 16 years.", "Tof");
					  dialogue("Do you know your source of power, boy?", "Tof");
                 dialogue("Umm...");
                 dialogue("Terastone gave it to me.", "Tof");
                 dialogue("Your source is, I mean was, Draal.", "Tof");
                 dialogue("DRAAL?");
                 dialogue("Yes, Draal wasn't a human.", "Tof");
                 dialogue("Now I withstand you with power of runes!", "Tof");
                 dialogue("Prepare to die!", "Tof");
                 break;
         case 2: dialogue("But I have your spirit, boy.", "Tof");
         		  dialogue("What?");
                 dialogue("Terastone works both ways.", "Tof");
                 dialogue("I withstand you with the power of runes.", "Tof");
                 dialogue("Runes?");
                 dialogue("Yes, my source of power is Draal.", "Tof");
                 dialogue("I thought Draal was dead!");
                 dialogue("He NEVER lived!", "Tof");
                 dialogue("Prepare to die!", "Tof");
         		  break;
         case 3: dialogue("We'll die anyway!", "Tof");
         		  dialogue("Then we can at least save the elves!");
                 dialogue("I hate elves!", "Tof");
                 dialogue("Prepare to die in the name of Draal!", "Tof");
                 dialogue("Draal?");
                 dialogue("Yes, he is the source of runes.", "Tof");
                 dialogue("But he is DEAD!");
                 dialogue("Soon you're alike!", "Tof");
                 break;
      }
      parse_window("Tof starts humming something.");
      parse_window("A runed spear launches from his hands at you.");
		parse_window("Suddenly your surroundings change.");
      parse_window("You feel voice echoing in your ears.");
      dialogue("I'll meet you at the geyser.", "Anyaca");
      player.var.score += 11;
		player.time.talking[6] = 9;
      player.item.terastone = false;
      player.time.indoors = false;
		strcpy(player.time.place, "Cornland");
      screen.x[0] = player.time.old_x;
      screen.y[0] = player.time.old_y;
      getch();
      reset_objects();
      create_map();
      update_all_windows();
      return 0;
 	}
	if(strcmp(args, "Sorceress Anyaca") == 0 && strcmp(item, "terastone") == 0 && player.item.terastone == true)
   {
   	dialogue("Hah! You're not possessing me with it.", "Anyaca");
      return 0;
   }
	if(strcmp(args, "Sorceress Anyaca") == 0 && strcmp(item, "red roses") == 0 && player.item.roses == true)
   {
		if(player.time.talking[6] != 3) // can be given when she is mad
      {
      	dialogue("Am I trying to hit on her?");
         dialogue("She might misunderstand me.");
         dialogue("Perhaps I shouldn't do this.");
         return 0;
      }
		dialogue("Anyaca.");
      dialogue("I don't want to talk to you.", "Anyaca");
      dialogue("I have something for you.");
      dialogue("I'm not interested.", "Anyaca");
      dialogue("I'm sorry about what I did.");
      dialogue("Please accept these beautiful roses as an apology.");
      parse_window("You give the roses to Anyaca.");
      dialogue("So you brought me roses?", "Anyaca");
		if(player.picked.jewels == true && player.item.jewels == false) // jewels donated to Anyaca
      {
      	dialogue("First jewelry, then roses.", "Anyaca");
         dialogue("I guess you're not that bad after all.", "Anyaca");
         player.time.talking[6] = 4;
      }
      else
      {
      	dialogue("They are beautiful roses. I like them.", "Anyaca");
         dialogue("I'm glad to hear it.");
         dialogue("But you can't expect I forgive you for that.", "Anyaca");
      }
      player.item.roses = false;
      player.var.score += 2;
      update_all_windows();
      return 0;
   }
	if(strcmp(args, "Sorceress Anyaca") == 0 && strcmp(item, "jewels") == 0 && player.item.jewels == true)
   {
		if(player.time.talking[6] != 3) // can be given when she is mad
      {
      	dialogue("Am I trying to hit on her?");
         dialogue("She might misunderstand me.");
         dialogue("Perhaps I shouldn't do this.");
         return 0;
      }
		dialogue("I'm sorry Anyaca.");
      dialogue("Do you even know what are you sorry for?", "Anyaca");
      dialogue("I do.");
      dialogue("Well, what is it then?", "Anyaca");
      dialogue("I'm sorry for hurting you like that.");
      dialogue("Like how?", "Anyaca");
      dialogue("You know that Anyaca, don't play childish.");
      dialogue("So, now you say I'm childish?", "Anyaca");
      dialogue("No, no, no...");
      dialogue("Please, leave me alone.", "Anyaca");
      dialogue("I'm sorry, I'm sorry, but I brought you something.");
      dialogue("What!?", "Anyaca");
		dialogue("I decided to give you these lovely rubies.");
      dialogue("Rubies for me?", "Anyaca");
      parse_window("You give the sparkling rubies to Anyaca.");
		if(player.picked.roses == true && player.item.roses == false) // roses donated to Anyaca
      {
			dialogue("First those beautiful flowers. Now this.", "Anyaca");
         dialogue("These are valuable. But you still give these to me.", "Anyaca");
         dialogue("I'm flattered. These are beautiful.", "Anyaca");
         dialogue("I guess I have to forgive you now.", "Anyaca");
         player.time.talking[6] = 4;
      }
      else
      {
			dialogue("These are beautiful, but you can't buy me.", "Anyaca");
         dialogue("I didn't mean to buy you.");
			dialogue("I like these rubies, but I don't like you.", "Anyaca");
         dialogue("You hurt my feelings, these stones won't change that.", "Anyaca");
      }
      player.item.roses = false;
      player.var.score += 2;
      update_all_windows();
      return 0;
   }
	if(strcmp(args, "Mandal, the bard") == 0 && strcmp(item, "elven flute") == 0 && player.item.flute == true)
   {
		dialogue("What is this?", "Mandal");
      dialogue("It is a flute I found.");
      dialogue("Let me see that.", "Mandal");
      parse_window("You give the flute to Mandal.");
      dialogue("There is something carved in it.", "Mandal");
      dialogue("What does it say?");
      dialogue("It is written in elven language.", "Mandal");
      dialogue("It is woman's name.", "Mandal");
      dialogue("It says 'Anyaca'", "Mandal");
      parse_window("Mandal gives the flute back to you.");
      return 0;
   }
	if(strcmp(args, "Guildmaster") == 0 && strcmp(item, "money purse") == 0)
   {
		dialogue("What would you like to buy?", "Guildmaster");
		talk_daemon("I want to buy 'reinforce'", 1, false);
      talk_daemon("I want to buy 'gateway'", 2, false);
      switch(talk_daemon("Nothing right now.", 3, true))
      {
			case 1: if(player.var.money < 2)
         		  {
                 		dialogue("You can't afford it.", "Guildmaster");
                     break;
                 }
                 if(player.magic.reinforce == true)
                 {
                 		dialogue("You already have that spell.", "Guildmaster");
                     break;
                 }
                 dialogue("That's a good choice.", "Guildmaster");
                 dialogue("Two crowns.", "Guildmaster");
                 player.var.money -= 2;
         		  if(player.skill.Haggling > myrand(15))
                 {
                 		dialogue("How about 1 crown?");
                     dialogue("Quite a haggler you are, but I accept.", "Guildmaster");
                     player.var.money += 1; // bargain
                 }
                 parse_window("You learn 'reinforce'.");
                 player.magic.reinforce = true;
                 player.var.score += 2;
                 update_all_windows();
                 break;
			case 2: if(player.var.money < 3)
         		  {
                 		dialogue("You can't afford it.", "Guildmaster");
                     break;
                 }
                 if(player.magic.gateway == true)
                 {
                 		dialogue("You already have that spell.", "Guildmaster");
                     break;
                 }
                 dialogue("That's a good choice.", "Guildmaster");
                 dialogue("Three crowns.", "Guildmaster");
                 player.var.money -= 3;
         		  if(player.skill.Haggling > myrand(15))
                 {
                 		dialogue("How about 2 crowns?");
                     dialogue("Quite a haggler you are, but I accept.", "Guildmaster");
                     player.var.money += 1; // bargain
                 }
                 parse_window("You learn 'gateway'.");
                 player.magic.gateway = true;
                 player.var.score += 2;
                 update_all_windows();
                 break;
      	case 3: dialogue("Some other time then.", "Guildmaster");
         		  break;
      }
      return 0;
   }
	if(strcmp(args, "Salesman") == 0 && strcmp(item, "money purse") == 0)
   {
   	if(player.picked.jewels == true)
      {
      	dialogue("I have no more cheap presents.", "Salesman");
         dialogue("Or are you interested on my antique furniture?", "Salesman");
         dialogue("Not today..perhaps...never.");
         return 0;
      }
      dialogue("You are here for the jewels? Only 15 crowns.", "Salesman");
		talk_daemon("Yes, sell me those jewels.", 1, false);
      switch(talk_daemon("Perhaps later.", 2, true))
      {
      	case 1: dialogue("That will be 15 crowns.", "Salesman");
         		  if(player.var.money < 15)
                 {
                 		dialogue("I can't afford them now.");
                     dialogue("Come back later then.", "Salesman");
                     break;
                 }
                 player.var.money -= 15;
         		  if(player.skill.Haggling > myrand(15))
                 {
                 		dialogue("How about 10 crowns?");
                     dialogue("You're killing me, but I accept your offer.", "Salesman");
                     player.var.money += 5; // bargain
                 }
                 dialogue("Here's your crowns.");
                 dialogue("And here's something that belong to king's crown.", "Salesman");
                 parse_window("You buy the jewels.");
                 player.item.jewels = true;
                 player.picked.jewels = true;
                 player.var.score += 2;
                 update_all_windows();
                 break;
         case 2: dialogue("Yes, perhaps later then.", "Salesman");
         		  break;
      }
      update_all_windows();
      return 0;
   }
	if(strcmp(args, "Mandal, the bard") == 0 && strcmp(item, "money purse") == 0)
   {
		if(player.picked.horn == true)
      {
      	dialogue("I think I have nothing that interests you.", "Mandal");
         return 0;
      }
   	dialogue("So, would you like to buy a war horn from me?", "Mandal");
		talk_daemon("Yes, I want to buy that horn.", 1, false);
      switch(talk_daemon("No, I'm not interested.", 2, true))
      {
      	case 1: dialogue("That will be 3 crowns.", "Mandal");
					  if(player.var.money < 3)
                 {
                 		dialogue("You can't afford it.", "Mandal");
                     break;
                 }
                 player.var.money -= 3;
         		  if(player.skill.Haggling > myrand(15))
                 {
                 		dialogue("How about 2 crowns?");
                     dialogue("Well, alright.", "Mandal");
                     player.var.money += 1; // bargain
                 }
                 dialogue("Here you are.");
                 parse_window("You pay for the war horn.");
                 dialogue("Thank you, my friend.", "Mandal");
                 dialogue("It is good to see that such people adore the art of music.", "Mandal");
                 player.var.score += 2;
                 player.picked.horn = true;
                 player.item.horn = true;
                 player.time.talking[5] = 2; 
                 break;
         case 2: dialogue("Alright. Goodbye then.", "Mandal"); break;
      }
      update_all_windows();
      return 0;
   }
	if(strcmp(args, "Librarian") == 0 && strcmp(item, "return book") == 0 && player.item.incarnate_book == true)
   {
		parse_window("You hand the 'Incarnations and Creations' to the librarian.");
		dialogue("Oh, is it you Oria?", "Librarian");
      dialogue("That viscount sure is a fast reader.", "Librarian");
      dialogue("Thank you for bringing that book so fast.", "Librarian");
      parse_window("So, that book was loaned by the viscount himself?");
      parse_window("But why would a viscount read books about incarnations?");
      parse_window("You feel puzzled, but curious.");
		player.item.incarnate_book = false;
      player.var.score += 4;
      update_all_windows();
      return 0;
   }
	if(strcmp(args, "Juggler") == 0 && strcmp(item, "wax apples") == 0 && player.item.wax_apples == true)
   {
   	parse_window("You give six wax apples to Juggler.");
      dialogue("What are these?", "Juggler");
      dialogue("Those are wax apples. Those are durable and optimal size.");
      dialogue("Hmm...perhaps I could juggle with these.", "Juggle");
      dialogue("I thought so too.");
      dialogue("Well..thanks.", "Juggler");
      dialogue("You're welcome.");
      player.time.talking[1] = 3;
      player.var.score += 4;
      update_all_windows();
      player.item.wax_apples = false;
      return 0;
   }
	parse_window("Perhaps not.");
   return 0;
}

int talk_daemon(char *msg, int i, bool ask)
{
	static char choice[5][80];
	itoa(i, char_temp, 10);
   strcat(char_temp, ": ");
   strcat(char_temp, msg);
   parse_window(char_temp);
   strcpy(choice[i], msg);
   if(ask == true)
   {
		do
      {
      	i = getch();
			i -= 48; // ascii code for 0 is 48
      } while(i < 1 || i > 4);
	   dialogue(choice[i]);
      return i;
   }
	return 0;
}

int talk(char c, char place[20])
{
	identify(c, place);

	if(strcmp(args, "Salamander King") == 0)
   {
		if(player.magic.bestial_speech == true)
      {
      	parse_window("You automatically cast 'bestial speech'.");
         parse_window("You passively maintain the ability.");
      }
      else
      {
      	dialogue("Yarataka durra!", "Salamander");
			parse_window("You don't know what the salamander is saying.");
         return 0;
      }
    	if(player.time.talking[6] < 7)
      {
      	dialogue("Go away! This is private volcano!", "Salamander.");
         parse_window("Salamander looks angry, you should go.");
         return 0;
      }
		if(player.picked.zar == true)
      {
      	dialogue("Thank you for taking that cold stone away.", "Salamander");
         return 0;
      }
     	dialogue("I know why you're here.", "Salamander");
     	dialogue("I know about the predictions.", "Salamander");
      dialogue("But you're not taking Zar-star with you.", "Salamander");
  	   dialogue("Why do you want to keep the star?");
      dialogue("It provides heat to the volcano.", "Salamander");
   	if(player.magic.duration > 0 && player.magic.spell == 'e' && player.picked.zar == false)
      {
      	dialogue("Why is it so cold in here?", "Salamander");
         dialogue("Perhaps Zar-star has lost its power.");
         parse_window("Salamander King touches the Zar-star.");
         dialogue("It is emitting cold now!", "Salamander");
         dialogue("Take it away quickly!", "Salamander");
         parse_window("You take the Zar-star.");
         player.picked.zar = true;
         player.item.zar = true;
         player.var.score += 4;
         update_all_windows();
      }
      else
      {
   	   dialogue("No it doesn't.");
      	dialogue("Yes it does, and I don't give it to you.", "Salamander");
      }
   }
	if(strcmp(args, "Village Chief") == 0)
   {
     	talk_daemon("Who are you?", 1, false);
      switch(talk_daemon("Do you live here alone?", 2, true))
      {
       	case 1: dialogue("I'm the Chief.");
         		  dialogue("You don't look that good.");
                 dialogue("I'm sick, I'm dying soon.", "Chief");
                 dialogue("Like you I can see in future.", "Chief");
                 dialogue("If you heal me, I give you Tarn-star.", "Chief");
                 dialogue("You will need it someday.", "Chief");
                 break;
         case 2: dialogue("Yes, my people left me to die.", "Chief");
          		  dialogue("They didn't want to get this death disease.", "Chief");
                 break;
      }
   }
	if(strcmp(args, "Guildmaster") == 0)
   {
   	if(player.time.talking[9] == 0)
      {
      	talk_daemon("Is this the mages guild?", 1, false);
         talk_daemon("Can I learn new spells in here?", 2, false);
         switch(talk_daemon("Why does this look like a circus tent?", 3, true))
         {
         	case 1: dialogue("Yes it is, you're in correct place.", "Guildmaster"); break;
            case 2: dialogue("You can buy spells from me.", "Guildmaster");
              		  dialogue("What spells do you have for sale?");
						  dialogue("'Gateway' for 3 crowns, 'reinforce' for 2 crowns.", "Guildmaster");
                    dialogue("What do those do?");
                    dialogue("Gateway can be used to activate teleportation devices.", "Guildmaster");
                    dialogue("Gateway is not teleport spell, but allows use of them.", "Guildmaster");
                    dialogue("Reinforce can be used to craft items.", "Guildmaster");
                    dialogue("You can make swords last forever, or mud from clay.", "Guildmaster");
						  dialogue("It cannot be used at liquids.", "Guildmaster");
                    break;
            case 3: dialogue("The surroundings depend from your thoughts.", "Guildmaster");
            		  dialogue("I don't know why you're thinking about circus.", "Guildmaster");
                    dialogue("Hum..");
                    break;
         }
      }
   }
	if(strcmp(args, "a mausoleum") == 0)
   {
   	if(player.magic.duration > 0 && player.magic.spell == 'd')
      {
      	if(player.time.talking[8] == 2)
         {
         	dialogue("Anything new from the surface?", "Corpse");
            dialogue("Not really.");
         }
			if(player.time.talking[8] == 1)
         {
         	dialogue("Well, it was nice talking to you.");
            dialogue("Do come back anytime.", "Corpse");
				dialogue("I won't go anywhere. Hah hah!", "Corpse");
            dialogue("Unless somebody robs my grave!", "Corpse");
            dialogue("But that would be a grave error!", "Corpse");
            dialogue("By the way? Do you listen to 'Grateful Dead'?", "Corpse");
            dialogue("Hilarious...well..bye..");
            dialogue("Wait don't go yet!", "Corpse");
            dialogue("I have something for you!", "Corpse");
            dialogue("What is it?");
            dialogue("Keys to mages' guild, I don't need them anymore.", "Corpse");
				dialogue("Alright.");
            parse_window("Suddenly a hand appears from the grave.");
            dialogue("Huh! That was creepy.");
            parse_window("You take the keys.");
            player.item.mage_keys = true;
            player.time.talking[8] = 2;
            player.var.score += 4;
            update_all_windows();
         }
      	if(player.time.talking[8] == 0)
         {
	      	parse_window("You establish connection to the corpse in mausoleum.");
   	      dialogue("Who are you?");
      	   dialogue("I'm Draal, Runelord of Savas, or I was. ", "Corpse");
            dialogue("What happened to you?");
            dialogue("I can tell. I don't really have anything else to do.", "Corpse");
            dialogue("Sure.");
            dialogue("I was walking on the cornfields when I heard lovely music.", "Corpse");
            dialogue("I followed the music, it came from the lake.", "Corpse");
            dialogue("I saw a young elf girl playing a flute. She was beautiful.", "Corpse");
            dialogue("Then something happened. Two tramplers came from bushes.", "Corpse");
            dialogue("Tramplers?");
            dialogue("Furry creatures. They attacked me and girl just played.", "Corpse");
            dialogue("She gave me the look that said 'I'm sorry.'", "Corpse");
            dialogue("Those tramplers killed me there.", "Corpse");
            dialogue("What happened then?");
            dialogue("How should I know? I died!", "Corpse");
            player.time.talking[8] = 1;
            player.var.score += 3;
            update_all_windows();
         }
      }
   	else
      {
      	parse_window("Talk to who?");
      }
   }
	if(strcmp(args, "a massive grave") == 0)
   {
   	if(player.magic.duration > 0 && player.magic.spell == 'd')
      {
      	parse_window("You establish connection to the corpse in grave.");
         dialogue("Who are you?");
         dialogue("Does it matter anymore?", "Corpse");
         dialogue("Well, guess you're right.");
      }
      else
      {
      	parse_window("Talk to who?");
      }
   }
   if(strcmp(args, "a crypt") == 0)
   {
   	if(player.magic.duration > 0 && player.magic.spell == 'd')
      {
      	parse_window("You establish connection to the corpse in crypt.");
         dialogue("Who are you?");
         dialogue("I'm Duke Hammars! Now go away! Respect the dead!", "Corpse");
      }
      else
      {
      	parse_window("Talk to who?");
      }
   }
	if(strcmp(args, "Salesman") == 0)
   {
		if(player.time.talking[7] == 1)
      {
         talk_daemon("What do you sell in here?", 1, false);
         talk_daemon("No, I'm just browsing right now.", 2, false);
         switch(talk_daemon("What would you recommend?", 3, true))
			{
         	case 1: dialogue("We sell all kinds of items.", "Salesman");
            		  dialogue("We sell antique, furniture and jewels.", "Salesman");
                    break;
            case 2: dialogue("Well, tell me if there's anything I can do for you.", "Salesman");
                    break;
            case 3: dialogue("Jewels are a good gift if you don't have much to spend.", "Salesman");
            		  dialogue("So what do they cost?");
                    dialogue("15 crowns.", "Salesman");
                    dialogue("It is cheap compared to furniture that cost 400 crowns.", "Salesman");
                    break;
         }
      }
   	if(player.time.talking[7] == 0)
      {
      	dialogue("Hello. Welcome to my humble Gift Shop.", "Salesman");
         dialogue("Is there anything I can do to help you?", "Salesman");
         player.time.talking[7] = 1;
      }
   }
	if(strcmp(args, "Sorceress Anyaca") == 0)
   {
		if(player.time.talking[6] == 11)
      {
      	dialogue("Those mountains are coming back.");
         dialogue("But sometimes the forests come back.", "Anyaca");
         dialogue("We've created some kind of mystical paradox.", "Anyaca");
         dialogue("But that will help my people significantly.", "Anyaca");
			dialogue("I was thinking about the tramplers...");
         dialogue("What about them?", "Anyaca");
         dialogue("They can't come now, because mountains come back.");
         dialogue("True, and I saved my people.", "Anyaca");
         dialogue("All well that ends well!");
			dialogue("Although..", "Anyaca");
         dialogue("Is something troubling you?");
         dialogue("Yes..", "Anyaca");
         dialogue("What is it?");
         dialogue("The symbol of peace, elven longbow has been stolen...", "Anyaca");
			end_game();
      }
		if(player.time.talking[6] == 10)
      {
      	parse_window("You start casting the spell to remove the mountain range.");
         parse_window("With the aid of Anyaca, the spell is completed.");
         parse_window("The mountains turn into forests. Yet it will be seen");
         parse_window("if the bloodthirsty tramplers are going to attack the");
         parse_window("Cornland.");
   		getch();
			parse_window("After removing the mountains, Anyaca quickly recovers her");
         parse_window("magical powers and is able to cancel the snowstorm.");
         parse_window("You discuss Anyaca about the fear of tramplers, but she");
         parse_window("says it is not her problem. She promised to remove the ");
         parse_window("winter, nothing else. She leaves without saying a word.");
         reset_objects();
         player.var.score += 15;
         update_all_windows();
      }
		if(player.time.talking[6] == 9)
      {
      	parse_window("Anyaca smiles calmly.");
      	dialogue("Did Tof get angry at you?", "Anyaca");
 			talk_daemon("He tried to kill me.", 1, false);
         switch(talk_daemon("Yes, but I possess Domaja.", 2, true))
         {
         	case 1: dialogue("We are safe here.", "Anyaca");
            		  dialogue("But I wouldn't advice going to Deserras.", "Anyaca");
                    break;
				case 2: dialogue("Great, then we can remove the mountains.", "Anyaca");
            		  dialogue("Can you remove the winter then?");
                    dialogue("Yes.", "Anyaca");
                    break;
         }
         dialogue("Let us start the ritual.", "Anyaca");
         player.time.talking[6] = 10;
      }
		if(player.time.talking[6] == 8)
      {
      	dialogue("So you were able to make a terastone.", "Anyaca");
         dialogue("Yes.");
         dialogue("Now we have to give it to Tof.", "Anyaca");
      }
		if(player.time.talking[6] == 7)
      {
			dialogue("I wish you luck in your search.", "Anyaca");
      }
		if(player.time.talking[6] == 6)
      {
      	talk_daemon("Why are you doing this, Anyaca?", 1, false);
         switch(talk_daemon("Please, cancel this winter.", 2, true))
			{
            case 1: dialogue("Well..I have no other choice.", "Anyaca");
            		  dialogue("My race will die because of the mountains.", "Anyaca");
                    dialogue("What?!? How?");
                    dialogue("We elves withdraw our power from the woods.", "Anyaca");
                    dialogue("When the mountains were raised, it affected our world.", "Anyaca");
                    dialogue("Your mountains suppress our magic, and we will die.", "Anyaca");
                    dialogue("Magic is our way. Without magic, we will die out.", "Anyaca");
                    dialogue("And that's why you're here?");
                    dialogue("Yes, I came to compress the mountains into nothingness.", "Anyaca");
                    dialogue("But thy this alliance with the viscount?");
                    dialogue("Only the person who created mountains, can remove them.", "Anyaca");
                    dialogue("Viscount has power, so he is a good ally.", "Anyaca");
                    dialogue("Why does the viscount want to get rid of mountains?");
                    dialogue("It would open trade connections.", "Anyaca");
                    dialogue("What about tramplers? They can attack Cornland then!");
                    dialogue("It's my people, or your people. I'm sorry.", "Anyaca");
                    dialogue("I'm sorry, but I have to stop you.");
                    dialogue("Forgive me.", "Anyaca");
                    break;
            case 2: dialogue("I won't cancel the snowstorm.", "Anyaca");
            		  dialogue("Then humans will die, and elves will too.");
                    dialogue("Remove the mountains and I'll remove winter.", "Anyaca");
                    dialogue("Tof, the archwizard is not removing mountains.");
                    dialogue("Then I won't remove my enchantment.", "Anyaca");
                    dialogue("Besides, I can't remove winter.", "Anyaca");
                    dialogue("What? Why?");
                    dialogue("Like you know, elves withdraw their magic from woods.", "Anyaca");
                    dialogue("Yes..");
                    dialogue("The mountains have suppressed my magic.", "Anyaca");
                    dialogue("I can't gather enough power to cancel the storm.", "Anyaca");
                    dialogue("Remove the mountains, so I get my magic back.", "Anyaca");
                    dialogue("We're doomed. Tof will never remove mountains.");
                    dialogue("There's an option.", "Anyaca");
                    dialogue("What is it?");
                    dialogue("A terastone.", "Anyaca");
                    dialogue("What is a terastone?");
                    dialogue("It is a stone that allows a possession of spirit.", "Anyaca");
                    dialogue("Tof's source of power is the winter spirit Domaja.", "Anyaca");
						  dialogue("Possess Domaja and then you can remove mountains.", "Anyaca");
                    dialogue("That's it?");
                    dialogue("No. Terastone works both ways. Tof possesses you also.", "Anyaca");
                    dialogue("What is your source of power?", "Anyaca");
                    dialogue("I don't know..");
                    dialogue("Well, we don't even have a terastone.", "Anyaca");
                    dialogue("It must be created from pieces and reinforced together.", "Anyaca");
                    dialogue("You need to find these stars: Tarn, Zar, Vira and Dural.", "Anyaca");
                    dialogue("Use your skills of seer to find them.", "Anyaca");
                    player.time.talking[6] = 7;
                    break;
         }
      }
		if(player.time.talking[6] == 5)
      {
      	talk_daemon("I know about your alliance with the viscount.", 1, false);
         talk_daemon("Why do you want to remove the mountain range?", 2, false);
         switch(talk_daemon("You can't remove the mountain range!", 3, true))
         {
         	case 1: dialogue("I'm sorry. I have no choice.", "Anyaca");
                    dialogue("Please, leave me alone.", "Anyaca");
                    break;
            case 2: dialogue("Well..I have no other choice.", "Anyaca");
            		  dialogue("My race will die because of the mountains.", "Anyaca");
                    dialogue("What?!? How?");
                    dialogue("We elves withdraw our power from the woods.", "Anyaca");
                    dialogue("When the mountains were raised, it affected our world.", "Anyaca");
                    dialogue("Your mountains suppress our magic, and we will die.", "Anyaca");
                    dialogue("Magic is our way. Without magic, we will die out.", "Anyaca");
                    dialogue("And that's why you're here?");
                    dialogue("Yes, I came to compress the mountains into nothingness.", "Anyaca");
                    dialogue("But thy this alliance with the viscount?");
                    dialogue("Only the person who created mountains, can remove them.", "Anyaca");
                    dialogue("Viscount has power, so he is a good ally.", "Anyaca");
                    dialogue("Why does the viscount want to get rid of mountains?");
                    dialogue("It would open trade connections.", "Anyaca");
                    dialogue("What about tramplers? They can attack Cornland then!");
                    dialogue("It's my people, or your people. I'm sorry.", "Anyaca");
                    dialogue("I'm sorry, but I have to stop you.");
                    dialogue("Forgive me.", "Anyaca");
                    break;
            case 3: dialogue("I'm sorry, but I have no choice.", "Anyaca");
            		  dialogue("Please go.", "Anyaca");
                    break;
         }
      }
   	if(player.time.talking[6] == 4) // no longer mad, teaches spell (if not acquired)
      {
         dialogue("I've been doing some thinking...", "Anyaca");
         dialogue("What have you been thinking?");
         dialogue("I've been very hard on you.", "Anyaca");
         dialogue("I'm sorry too.");
         if(player.magic.bestial_speech == false)
         {
         	dialogue("I want to thank you somehow.", "Anyaca");
            dialogue("You don't have to.");
            dialogue("Yes I have to. You've shown yourself worthy.", "Anyaca");
            dialogue("Worthy of what?");
            dialogue("You are in communion with the nature.", "Anyaca");
            dialogue("That's why I show my gratitude in a form of a spell.", "Anyaca");
            parse_window("You receive a spell scroll from Anyaca.");
            dialogue("Study that carefully.", "Anyaca");
            player.var.score += 2;
            player.magic.bestial_speech = true;
            update_all_windows();
         }
      	dialogue("Well I must go now.", "Anyaca");
         player.var.anyaca = false;
         player.var.vision = 5;
         reset_objects();
      }
		if(player.time.talking[6] == 3) // when she is mad
      {
      	dialogue("I don't want to see you ever again.", "Anyaca");
         dialogue("Anyaca, I'm sorry.");
         dialogue("Go away from me!", "Anyaca");
      }
		if(player.time.talking[6] == 2) // trading thing
      {
      	dialogue("So, trading it? What do you offer?");
         dialogue("I could kiss you.", "Anyaca");
         dialogue("I could give you 5 crowns.", "Anyaca");
         dialogue("Or I could teach you a spell.", "Anyaca");
         talk_daemon("I will trade it to your kiss.", 1, false);
         talk_daemon("I will trade it to 5 crowns.", 2, false);
         talk_daemon("I will trade it to a spell.", 3, false);
         switch(talk_daemon("I still want to keep the flute.", 4, true))
         {
         	case 1: dialogue("Really? I'm so shy...well..", "Anyaca");
            		  parse_window("Anyaca blushes.");
                    dialogue("Could you close your eyes?", "Anyaca");
                    parse_window("You close your eyes.");
                    parse_window("You feel Anyaca's lips on your lips.");
                    parse_window("As you open yours eyes, you see no flute, nor Anyaca.");
                    player.var.anyaca = false;
                    player.item.flute = false;
                    player.var.score += 4; // gain spell later
                    player.time.talking[6] = 4;
                    update_all_windows();
                    reset_objects();
                    break;
            case 2: dialogue("So my kiss isn't worth 5 crowns?", "Anyaca");
             		  dialogue("Here is your stupid coins.", "Anyaca");
                    parse_window("Anyaca throws a small purse at you.");
                    dialogue("I'm sorry, I didn't mean to..");
                    parse_window("You can see tears on her face.");
                    parse_window("You give flute to Anyaca.");
                    dialogue("I hate you, I hate you, I hate you..", "Anyaca");
                    parse_window("She runs away from you.");
                    player.var.anyaca = false;
                    player.item.flute = false;
                    player.var.money += 5;
                    player.var.score += 2; // have to get her to LOVE you again
                    player.time.talking[6] = 3;
                    update_all_windows();
                    reset_objects();
                    break;
            case 3: dialogue("I have a spell scroll of bestial speech in here.", "Anyaca");
            		  dialogue("Is this stupid paper more valuable than my kiss?", "Anyaca");
                    dialogue("Umm....err..");
                    dialogue("Don't you think I'm attractive?", "Anyaca");
                    dialogue("Take your stupid scroll.", "Anyaca");
                    parse_window("You can see tears on her face.");
                    parse_window("You give flute to Anyaca.");
                    dialogue("I hate you, I hate you, I hate you..", "Anyaca");
                    parse_window("She runs away from you.");
                    player.var.anyaca = false;
                    player.item.flute = false;
                    player.magic.bestial_speech = true;
                    player.var.score += 4; // have to get her to LOVE you again
                    player.time.talking[6] = 3;
                    update_all_windows();
                    reset_objects();
                    break;
            case 4: dialogue("I...I...I must go.", "Anyaca");
						  parse_window("You can see tears on her eyes.");
                    parse_window("She runs away.");
                    player.time.talking[6] = 4;
                    player.var.anyaca = false;
                    player.var.vision = 3;
                    update_all_windows();
                    reset_objects();
                    break;
         }
      }
		if(player.time.talking[6] == 1)
      {
      	dialogue("So you want your flute back?");
         dialogue("Yes, it is very dear for me.", "Anyaca");
         dialogue("May I have it?", "Anyaca");
         talk_daemon("But I found it, I want to keep it.", 1, false);
         switch(talk_daemon("You can have it, it's yours.", 2, true))
         {
         	case 1: dialogue("I understand, would you trade it?", "Anyaca");
            		  player.time.talking[6] = 2;	
            		  break;
            case 2: dialogue("Thank you, you can't believe how happy I am.", "Anyaca");
            		  dialogue("Well, it is yours after all.");
                    parse_window("You give flute to Anyaca.");
						  parse_window("Anyaca starts playing a song to you.");
						  dialogue("Thank you very much.", "Anyaca");
                    dialogue("I will remember you.", "Anyaca");
                    parse_window("Anyaca kisses you to lips before she leaves.");
                    player.var.score += 4;
                    player.var.anyaca = false;
                    player.item.flute = false;
                    reset_objects();
                    player.time.talking[6] = 4;
                    update_all_windows();
                    break;
         }
      }
   	if(player.time.talking[6] == 0)
      {
      	dialogue("I've been expecting you.", "Anyaca");
         dialogue("Something tells me you have something that belongs to me.", "Anyaca");
			talk_daemon("What do you want then?", 1, false);
         talk_daemon("I don't think so.", 2, false);
         switch(talk_daemon("Do you mean this flute?", 3, true))
         {
         	case 1:
            case 2: dialogue("I want my flute, I know you have it.", "Anyaca"); break;
            case 3: dialogue("Yes, and I want it back.", "Anyaca"); break;
         }
         dialogue("Will you give my flute back?", "Anyaca");
         player.time.talking[6] = 1;
      }
   }
	if(strcmp(args, "Mandal, the bard") == 0)
	{
   	if(player.time.talking[5] == 2)
      {
         dialogue("So, what do you think about your horn?", "Mandal");
         dialogue("It is fine.");
      }
   	if(player.time.talking[5] == 1)
      {
      	talk_daemon("How much does a horn cost?", 1, false);
         switch(talk_daemon("What can I do with a horn?", 2, true))
         {
         	case 1: dialogue("Mere 3 crowns.", "Mandal"); break;
            case 2: dialogue("If you get to a deserted island, you can stop a ship.", "Mandal");
            		  dialogue("Why is that?");
                    dialogue("It has a very high sound.", "Mandal");
                    dialogue("Wiseguy...");
                    break;
         }
      }
   	if(player.time.talking[5] == 0)
      {
	   	talk_daemon("What are the most popular instruments?", 1, false);
			talk_daemon("Could you teach me to play?", 2, false);
   	   switch(talk_daemon("Could you teach me to sing?", 3, true))
	   	{
      		case 1: dialogue("Nowadays it is a banjo. That's why I'm out of those.", "Mandal"); break;
	         case 2: dialogue("Of course I can teach you, but it takes time.", "Mandal");
   	      		  dialogue("How long?");
      	           dialogue("It depends on how talented you are.", "Mandal");
         	        dialogue("I don't have time to train that much.");
            	     dialogue("Bah! Then I suggest you will buy a horn from me.", "Mandal");
               	  dialogue("You don't have to do anything but blow.", "Mandal");
	                 player.time.talking[5]++;
	                 player.var.score += 2;
                    update_all_windows();
                    break;
	         case 3: dialogue("Singing is a talent. You can't learn it.", "Mandal"); break;
	      }
   	}
   }
	if(strcmp(args, "Librarian") == 0)
   {
		if(player.time.talking[4] == 1)
      {
      	talk_daemon("How do you work if you're blind?", 1, false);
         switch(talk_daemon("How can I borrow a book?", 2, true))
         {
         	case 1: dialogue("I have a gift for library.", "Librarian");
            		  dialogue("I know if somebody takes a book out from here.", "Librarian");
                    dialogue("It is not a magic, but it is a psychic talent.", "Librarian");
                    dialogue("I see.");
                    dialogue("Feel free to look around.", "Librarian");
                    break;
            case 2: dialogue("You can look around on your own.", "Librarian");
            		  dialogue("If you find a book you like, you can borrow it.", "Librarian");
                    dialogue("Just like that?");
                    dialogue("Well, you have to write your name to this book.", "Librarian");
                    dialogue("Okay.");
                    dialogue("Then I'll check that the book isn't reserved for anyone.", "Librarian");
                    dialogue("And then I can borrow a book?");
                    dialogue("Yes, then you can borrow a book.", "Librarian");
						  break;
         }
      }
   	if(player.time.talking[4] == 0)
      {
      	talk_daemon("Excuse me, I'm looking for a book.", 1, false);
         switch(talk_daemon("How many books are there in this library?", 2, true))
         {
         	case 1: dialogue("I'm sorry, I didn't notice you.", "Librarian");
            		  dialogue("That's alright.");
                    dialogue("No, I mean...I'm blind.", "Librarian");
                    dialogue("Oh..");
                    player.time.talking[4]++;
                    break;
            case 2: dialogue("Approximately 43593260253 books, or was it 43593260254?", "Librarian");
            		  dialogue("Could you check it, I really NEED the exact number?");
                    parse_window("Librarian ignores you totally.");
             		  break;
         }
      }
   }
	if(strcmp(args, "Tof, Archwizard of the Winter") == 0)
   {
		if(player.time.talking[3] == 3)
      {
			talk_daemon("Tramplers attack if you remove mountains.", 1, false);
         talk_daemon("Viscount is behind this winter!", 2, false);
         switch(talk_daemon("Sorceress Anyaca is behind this winter!", 3, true))
         {
         	case 1: dialogue("Well, we're doomed in any case.", "Tof");
            		  dialogue("We starve or get killed by tramplers.", "Tof");
                    dialogue("Unless, you find a solution to food problem.", "Tof");
                    break;
            case 2:
            case 3: dialogue("What do you mean?", "Tof");
            		  dialogue("Viscount made a deal with a sorceress to summon winter.");
                    dialogue("Why would he do that?", "Tof");
                    dialogue("Viscount wants the mountain range to be removed.");
                    dialogue("Then viscount is enemy.", "Tof");
                    dialogue("He cannot be trusted. What can we do?");
                    dialogue("We have to cancel the winter.", "Tof");
                    dialogue("Can you do it?");
                    dialogue("Spell can only be countered by its caster.", "Tof");
                    dialogue("You will have to find that sorceress!", "Tof");
                    dialogue("But remember, I won't remove the mountains!", "Tof");
                    dialogue("I won't, even if it kills us all!", "Tof");
                    dialogue("Tell it to her too.", "Tof");
                    break;
         }
      }
		if(player.time.talking[3] == 2)
      {
			dialogue("Have you heard the news, my friend?", "Tof");
         dialogue("What news?");
         dialogue("Viscount demanded the mountain range to be removed.", "Tof");
         dialogue("Oh no.");
         dialogue("Corn doesn't grow at winter, so we are in trouble.", "Tof");
         dialogue("Because of winter, people will starve to death otherwise.", "Tof");
			player.time.talking[3] = 3;
      }
   	if(player.time.talking[3] == 1)
      {
      	talk_daemon("Could you teach me a spell?", 1, false);
         talk_daemon("Who is Darol?", 2, false);
         talk_daemon("Could I have keys to magician's guild?", 3, false);
         switch(talk_daemon("Can I have my horn back?", 4, true))
         {
         	case 1: if(player.magic.frosty_way == true)
            		  {
                    		dialogue("I already taught you a spell.", "Tof");
                        break;
                    }
            		  dialogue("I could teach you a lovely winter spell.", "Tof");
            		  dialogue("Nice.");
                    dialogue("This spell is called 'frosty way'", "Tof");
                    dialogue("What does it do?");
                    dialogue("It withdraws all the heat from the environment to you.", "Tof");
                    dialogue("Does that mean that I become hot then?");
                    dialogue("Physically, yes. And the environment becomes cold. Very cold.", "Tof");
                    dialogue("What can it be used?");
                    dialogue("I'm old and tired, but your young brains will find a way.", "Tof");
                    dialogue("Thank you anyway.");
                    parse_window("You learn 'frosty way'.");
                    player.magic.frosty_way = true;
                    player.var.score += 4;
                    update_all_windows();
                    break;
            case 2: dialogue("Darol is a friend of mine.", "Tof");
            		  dialogue("How did you meet?");
                    dialogue("He was entering the tower of wonders.", "Tof");
                    dialogue("I was there too.", "Tof");
                    dialogue("He was stuck in quicksand and I saved him.", "Tof");
                    dialogue("It was you who was stuck in the sand!", "Darol");
                    dialogue("Oh..Then who was the one attacked by bats?", "Tof");
                    dialogue("It was you also.", "Darol");
                    dialogue("Umm..my memory is troubling me again..", "Tof");
                    dialogue("It sure is, my friend. I've never been to tower of wonders.", "Darol");
                    dialogue("Oh...now I remember, neither have I..", "Tof");
                    break;
            case 3: dialogue("Unfortunately I don't have any spare keys.", "Tof");
            		  dialogue("Could I loan yours?");
                    dialogue("I'm sorry, I don't give my keys away.", "Tof");
                    break;
            case 4: dialogue("No.", "Tof");
             		  dialogue("Why not?");
                    dialogue("I ate it.", "Tof");
                    dialogue("Hate I mean.", "Tof");
                    break;
         }
      }
	  	if(player.time.talking[3] == 0)
      {
			talk_daemon("Can you teach me a spell?", 1, false);
         switch(talk_daemon("Sir! I need to talk to you!", 2, true))
			{
				case 1: dialogue("No.", "Tof");
            		  dialogue("What did you say?", "Darol");
                    dialogue("Did I say something?", "Tof");
                    dialogue("Yes, you said 'no'", "Darol");
                    dialogue("Hmm..that's strange.", "Tof");
                    break;
            case 2: dialogue("I feel the wind in my back.", "Tof");
            		  dialogue("Perhaps we should close the windows.", "Darol");
                    break;
         }
      }
   }
	if(strcmp(args, "Darol, the Dauntless") == 0)
   {
		if(player.time.talking[2] == 2)
      {
      	dialogue("We are doomed! Doomed!", "Darol");
         dialogue("Viscount manifested mountains to be removed.", "Darol");
         dialogue("Tof, explain it to him.", "Darol");
      }
		if(player.time.talking[2] == 1)
      {
      	talk_daemon("I need to tell about my visions.", 1, false);
         talk_daemon("Who is Tof?", 2, false);
			switch(talk_daemon("Do you know the viscount?", 3, true))
         {
         	case 1: dialogue("So, you're a seer?", "Darol");
            		  dialogue("Yes, I see visions in my dreams.");
                    dialogue("So what have you seen?", "Darol");
                    dialogue("I have seen visions about ugly creatures attacking us.");
                    dialogue("Those are tramplers.", "Tof");
                    dialogue("They've started attacking, and mountains can't stop them.");
                    dialogue("Tramplers can't cross the mountains.", "Darol");
                    dialogue("They might.", "Tof");
                    dialogue("In my dreams, there were tramplers in Cornland already.");
                    dialogue("Well, this is critical.", "Tof");
                    dialogue("We have to think about this.", "Darol");
                    break;
            case 2: dialogue("Tof is an archwizard of Winter.", "Darol");
            		  dialogue("of Winter?");
                    dialogue("There are archwizards for every season.", "Darol");
                    dialogue("He is the archwizard of the Winter.", "Darol");
                    dialogue("What does it mean to be a seasonal wizard?");
                    dialogue("It means that Tof masters all Winter spells.", "Darol");
                    break;
            case 3: dialogue("I have never met him, but I've heard he is mysterious.", "Darol"); break;
         }
      }
   	if(player.time.talking[2] == 0)
      {
	   	talk_daemon("Excuse me?", 1, false);
   	   talk_daemon("May I have the honour of asking a question?", 2, false);
   		switch(myrand(talk_daemon("Hey you!", 3, true)))
	      {
				case 0: dialogue("What is this whispering sound?", "Darol");
            		  dialogue("I can't hear anything?", "Tof");
                    dialogue("No, I hear it again.", "Darol");
                    dialogue("It must be the wind blowing to your ears.", "Tof");
                    dialogue("It must be it, yes..", "Darol");
                    break;
            case 1: dialogue("Did you hear that?", "Darol");
            		  dialogue("Yes..it sounded like a crack.", "Tof");
                    dialogue("No..nothing like that.", "Darol");
                    dialogue("Perhaps a hummingbird then?", "Tof");
                    dialogue("No..but almost.", "Darol");
                    dialogue("Perhaps a locust?", "Tof");
                    dialogue("Yes...but there are no locusts in here.", "Darol");
                    dialogue("Well...perhaps it was nothing then.", "Tof");
                    dialogue("I guess you're right, my friend.", "Darol");
                    break;
            default:dialogue("What was that?", "Darol");
            		  dialogue("I bet that is that new servant with a funny name.", "Tof");
                    dialogue(player.name, "Darol");
                    dialogue("Yes! Have you ever heard more stupid name than that!", "Tof");
                    dialogue("Hahahaha!", "Darol and Tof");
                    break;
      	}
      }
   }
	if(strcmp(args, "Lion") == 0)
   {
		talk_daemon("Grrrr...Meowth!", 1, false);
		talk_daemon("So, you are the tame lion in the show?", 2, false);
		switch(talk_daemon("Were you in Disney's movie Lion king?", 3, true))
      {
      	case 1: dialogue("I'm sorry but I don't understand your dialect.", "Lion"); break;
         case 2: dialogue("No, I am the talking lion.", "Lion"); break;
         case 3: dialogue("Yes, do you want my autograph?", "Lion");
         		  dialogue("Yes! I would love to!");
                 dialogue("Argh! I'm talking to a lion."); break;
      }
   }
   if(strcmp(args, "Liontamer") == 0)
   {
   	talk_daemon("Hi, is that lion yours?", 1, false);
      talk_daemon("How long have you been working as a liontamer?", 2, false);
      switch(talk_daemon("How come you have only one hand?", 3, true))
      {
      	case 1: dialogue("Yes, but it is stupid as a duck.", "Liontamer"); break;
         case 2: dialogue("I started two years ago.", "Liontamer"); break;
         case 3: dialogue("I had a show where I put my hand inside lion's mouth.", "Liontamer");
         		  dialogue("And the lion ate your hand?");
                 dialogue("Something like that.", "Liontamer"); break;
      }

   }
	if(strcmp(args, "Juggler") == 0)
   {
		if(player.time.talking[1] == 4)
      {
      	dialogue("Thank you for your help.", "Juggler");
         dialogue("No, thank you for the spell.");
         dialogue("Well, bye!");
      }
		if(player.time.talking[1] == 3)
      {
      	talk_daemon("That looks even too easy.", 1, false);
         switch(talk_daemon("What is your secret?", 2, true))
         {
         	case 1: dialogue("I shouldn't tell you this but...", "Juggler"); // notify, no break;
            case 2: dialogue("Well....do you promise not to tell anyone?", "Juggler");
            		  dialogue("I promise.");
                    dialogue("It's...magic.", "Juggler");
                    dialogue("MAGIC?");
                    dialogue("Don't shout.", "Juggler");
                    dialogue("It's a small spell called 'animate'.", "Juggler");
                    dialogue("It causes items to move in air.", "Juggler");
                    dialogue("I know some magic too...");
                    dialogue("You do?", "Juggler");
                    dialogue("Yes..");
                    dialogue("I could teach you the spell.", "Juggler");
                    parse_window("You learn 'animate' spell.");
                    player.time.talking[1] = 4;
                    player.var.score += 3;
                    update_all_windows();
                    break;
         }
      }
		if(player.time.talking[1] == 2)
      {
      	talk_daemon("Would you show me how to juggle?", 1, false);
         switch(talk_daemon("How long have you trained juggling?", 2, true))
         {
         	case 1: dialogue("Alright, I owe you that favour.", "Juggler");
                    player.time.talking[1] = 3;
            		  break;
            case 2: dialogue("A few years, I'm slowly getting the hang of it.", "Juggler");
            		  player.time.talking[1] = 3;
                    break;
         }
      }
		if(player.time.talking[1] == 1)
      {
      	talk_daemon("Not now, I don't have time to listen.", 1, false);
         switch(talk_daemon("Sure, why not.", 2, true))
         {
         	case 1: dialogue("Perhaps some other time then.", "Juggler");
            		  player.time.talking[1]--; break;
            case 2: dialogue("Okay. I used to throw some knives in air but recently", "Juggler");
            		  dialogue("I lost my knives.", "Juggler");
                    dialogue("Is there anything I can do to help?");
                    dialogue("No, unless you bring me something I can juggle with.", "Juggler");
                    break;
         }
         return 0;
      }
   	if(player.time.talking[1] == 0)
      {
      	parse_window("It seems the juggler is having a break since she is not practicing.");
         dialogue("Hi there.", "Juggler");
         dialogue("Hi.");
         talk_daemon("Why aren't practicing when everyone other is?", 1, false);
         talk_daemon("When do you perform again?", 2, false);
         switch(talk_daemon("Who owns this place?", 3, true))
         {
         	case 1: dialogue("It's kind of long story, do you want to hear?", "Juggler");
            		  player.time.talking[1]++; break;
            case 2: dialogue("All the time, but we are on vacation now.", "Juggler"); break;
            case 3: dialogue("My father used to, but he is dead. Now I own the place.", "Juggler"); break;
         }
      }
   }
	if(strcmp(args, "Bailiff") == 0)
   {
		if(player.time.talking[0] == 2)
      {
      	dialogue("What are you doing here now?", "Bailiff");
         talk_daemon("I wonder if I could get some money beforehand, Sir.", 1, false);
         switch(talk_daemon("Could I have an increase on my salary, Sir.", 2, true))
         {
         	case 1: dialogue("I'm not a banker! Go to work. I don't pay for slacking!", "Bailiff"); break;
            case 2: dialogue("Your work is not worth a crown, go away.", "Bailiff"); break;
         }
      }
   	if(player.time.talking[0] == 1)
      {
      	dialogue("What are you doing here now?", "Bailiff");
         talk_daemon("I came to get money from my work.", 1, false);
         switch(talk_daemon("Could you leave money to table in granary if I work?", 2, true))
         {
				case 1: dialogue("I bring them to you to the cornfields, just wait there.", "Bailiff"); break;
            case 2: dialogue("What do you mean?", "Bailiff");
            		  dialogue("If you see me working on the fields, it saves your time.");
                    dialogue("Hmm..?", "Bailiff");
                    dialogue("You didn't have to wait for me to come from the fields.");
                    dialogue("That would save my time though.", "Bailiff");
                    dialogue("But I won't pay if I don't see you working in the fields!", "Bailiff");
                    dialogue("I will leave your salary to the table in the granary then.", "Bailiff");
                    player.var.score += 1;
                    player.time.talking[0] = 2;
                    update_all_windows();
                    break;
         }
      }
		if(player.time.talking[0] == 0)
      {
        	dialogue("What are you doing here! You should be working!", "Bailiff");
			talk_daemon("I left scarecrow there when I left.", 1, false);
	      switch(talk_daemon("I thought I left my cloak here the last time I visited.", 2, true))
   	   {
      	 	case 1: dialogue("It was removed, since it doesn't work! Go!", "Bailiff"); break;
         	case 2: dialogue("This is the first time you come here!", "Bailiff"); break;
	      }
	 		dialogue("Now go if you want to earn your crowns!", "Bailiff");
      }
   }
   return 0;
}

int get_monster_class(char c, char place[20])
{
   strcpy(char_temp, "You see ");
	identify(c, place);
   strcat(char_temp, args);
   strcat(char_temp, ".");
   parse_window(char_temp);
	return 0;
}

int vision(int x, int y, int loop)
{
	bool north = false, west = false, east = false, south = false;
	int line_sight = 0, turn_plr = 0, turn_block = 0;
	bool vision = false;
	line_sight = 5;
   if(line_sight < 5) line_sight = 5;
	if(screen.x[0] > x) east = true;
	if(screen.x[0] < x) west = true;
   if(screen.y[0] > y) south = true;
   if(screen.y[0] < y) north = true;
   do
   {
   	line_sight--;
		x += east;
      x -= west;
      y += south;
      y -= north;
      if(true_x(x) == true_x(screen.x[0]) && true_y(y) == true_y(screen.y[0])) turn_plr = line_sight;
      if(map[true_y(y)][true_x(x)] == '#') turn_block = line_sight;
   } while(line_sight > 0);
   if(turn_plr > turn_block) vision = true;
   else vision = false;
   if(vision == true && screen.draw.seen[loop] == false)
   {
	   screen.draw.seen[loop] = true;
      get_monster_class(screen.draw.sign[loop], player.time.place);
   }
   return vision;
}

int monster_move(bool screen_move) // Currently monster AI
{
	bool north = false, west = false, east = false, south = false;
	for(int loop = 1; loop < screen.max_obj; loop++)
   {
		north = false, west = false, east = false, south = false;
		if(screen.x[0] > screen.x[loop] && screen.draw.alive[loop] == true)
  		{
   		screen.x[loop]++;
	      east = true;
  		}
   	if(screen.x[0] < screen.x[loop] && screen.draw.alive[loop] == true)
   	{
	   	screen.x[loop]--;
  		   west = true;
   	}
   	if(screen.y[0] > screen.y[loop] && screen.draw.alive[loop] == true)
   	{
	   	screen.y[loop]++;
  	   	south = true;
	   }
  		if(screen.y[0] < screen.y[loop] && screen.draw.alive[loop] == true)
   	{
   		screen.y[loop]--;
			north = true;
   	}
		for(int i = 0; i < screen.max_obj; i++)
      {
			if(i != loop && screen.x[i] == screen.x[loop] && screen.y[i] == screen.y[loop] && screen.draw.alive[loop] == true)
		   {
				if(south == true) screen.y[loop]--;
      		if(north == true) screen.y[loop]++;
	      	if(east == true) screen.x[loop]--;
		   	if(west == true) screen.x[loop]++;
         }
      }
		// map_field_boundaries();
		/* updates new object places */
		if(map[true_y(screen.y[loop])][true_x(screen.x[loop])] == '#') // can't go through '#'- sign
	   {
         surter(screen.x[loop], screen.y[loop]);
	      if(north == true) screen.y[loop]--;
	      if(south == true) screen.y[loop]++;
	     	if(east == true) screen.x[loop]--;
	  		if(west == true) screen.x[loop]++;
	   }
      else
      {
		   if(vision(screen.x[loop], screen.y[loop], loop) == 1)
		   {
		 		erase_old_obj(loop, true, screen_move);
           	draw(screen.x[loop], screen.y[loop], screen.draw.sign[loop], screen.draw.color[loop]);
	      }
  	      surter(screen.x[loop], screen.y[loop]);
      }
   }
	return 0;
}


int examine_item(char what[30])
{
	if(strcmp(what, "black orb") == 0 && player.item.black_orb == true)
   {
   	parse_window("This is the black orb. It is somehow very dark");
      parse_window("and it is the product of the stars, Zar and Tarn.");
   }
   if(strcmp(what, "white orb") == 0 && player.item.white_orb == true)
   {
   	parse_window("This is the white orb. It is somehow very bright");
		parse_window("and it is the product of the stars, Vira and Dural.");
   }
   if(strcmp(what, "moonstone") == 0 && player.item.moonstone == true)
   {
   	parse_window("This is the moonstone that was created by you as you");
      parse_window("combined white and black orb. It is sparkling but ");
      parse_window("something tell you that it is not useful right now.");
   }
   if(strcmp(what, "terastone") == 0 && player.item.terastone == true)
	{
   	parse_window("This is the legendary terastone. It is said that ");
      parse_window("if a terastone is given to a person, it will take");
      parse_window("full possession of the receiver. But it is also");
      parse_window("said to work both ways, so that the giver also");
      parse_window("gets possessed by the receiver.");
   }
	if(strcmp(what, "cure for death") == 0 && player.item.cure > 0)
   {
   	parse_window("This is a cure for death, that you invented by");
      parse_window("yourself with your skills of alchemy.");
      parse_window("It cancels all the possible diseases. You might");
      parse_window("win a prize in the alchemy fair with this!");
   }
	if(strcmp(what, "dural stone") == 0 && player.item.dural == true)
   {
   	parse_window("This is one of the pieces of stars. This belongs ");
      parse_window("to Dural star. It is blue glowing stone.");
   }
   if(strcmp(what, "vira stone") == 0 && player.item.vira == true)
   {
   	parse_window("This is the Vira stone that you found from the elves");
      parse_window("dimension in the middle of waterfalls. It is yellow");
      parse_window("and there is a faint glow in it.");
   }
   if(strcmp(what, "tarn stone") == 0 && player.item.tarn == true)
   {
   	parse_window("This is the Tarn stone that you found from the village");
      parse_window("in the south islands. You healed the chief and received");
      parse_window("piece of Tarn star as a reward.");
   }
   if(strcmp(what, "zar stone") == 0 && player.item.zar == true)
   {
   	parse_window("This is the Zar stone that you found from the volcano");
      parse_window("that belonged to the salamanders. You diabolically");
      parse_window("blackmailed this star from them.");
   }
	if(strcmp(what, "jewels") == 0 && player.item.jewels == true)
   {
   	parse_window("These are rubies. These rubies cost you quite a lot");
      parse_window("but they are very beautiful. They sparkle in the ");
      parse_window("light as the rays of the sun hit them.");
   }
	if(strcmp(what, "red roses") == 0 && player.item.roses == true)
   {
   	parse_window("These red roses are very beautiful. Rarely have you ");
      parse_window("seen that red and big roses. It would cost at least ");
      parse_window("two crowns to buy this kind of roses from the");
      parse_window("gardeners.");
   }
	if(strcmp(what, "guild keys") == 0 && player.item.mage_keys == true)
   {
   	parse_window("These are the magical keys that fit to the lock in the");
      parse_window("guild of magicians. The guild is known for its magical");
      parse_window("guidance to the novices of the guild.");
   }
	if(strcmp(what, "elven flute") == 0 && player.item.flute == true)
   {
   	parse_window("This is a very lovely bamboo flute. It looks like it had");
      parse_window("been created very skillfully. You have never seen such ");
      parse_window("craftmanship. There are some inscriptions in it but you");
      parse_window("don't recognize the language.");
   }
	if(strcmp(what, "war horn") == 0 && player.item.horn == true)
   {
   	parse_window("This is a war horn that is used to command large armies to");
      parse_window("attack. It looks worthless but with it you can make high ");
      parse_window("voices. Like Mandal, the bard said, you might actually");
      parse_window("be able to stop a ship with this.");
   }
	if(strcmp(what, "history book") == 0 && player.item.history_book == true)
   {
   	parse_window("This a large book that is labelled as 'Heroes of our Lifetime'.");
      parse_window("This is not fictional book as it contains the small biographies");
      parse_window("of famous people of Cornland. If you are looking for a person");
      parse_window("you should pay attention to reading this epic masterpiece.");
   }
	if(strcmp(what, "poem book") == 0 && player.item.poem_book == true)
   {
   	parse_window("This large book of poems does not have an author nor title.");
      parse_window("It is just a collection of poems written by many authors. Some");
      parse_window("of the poems are named, but most of them are not.");
   }
	if(strcmp(what, "necro book") == 0 && player.item.necro_book == true)
   {
   	parse_window("This is a book that is made of leather. It looks very horrible");
      parse_window("but you guess that belong to the style of necromancy. It is ");
      parse_window("labelled as 'Hauntings from the grave.' This book looks very old");
      parse_window("and you guess that nobody has loaned it for a long time.");
   }
	if(strcmp(what, "return book") == 0 && player.item.incarnate_book == true)
   {
   	parse_window("This is a very big book labelled 'Creations and Incarnations'");
      parse_window("You picked this book from the 'returned books' place. You wonder");
      parse_window("who might have loaned this book. Then again, you realize that it's");
      parse_window("none of your business at all, and think about returning it to its");
      parse_window("place.");
   }
	if(strcmp(what, "money purse") == 0)
   {
   	parse_window("This is a small money pouch made by your mother from leather.");
      parse_window("It is attached to your belt with a string. The only problem is that");
      parse_window("you have to be very careful that cut-purses don't take your money.");
   }
   if(strcmp(what, "corn-cob") == 0 && player.item.corn > 0)
   {
   	parse_window("This is a delicious looking corn-cob you have taken from the ");
      parse_window("cornfields. The viscount doesn't like you stealing these and if");
      parse_window("you get caught, he might make you pay for those.");
   }
   if(strcmp(what, "scythe") == 0 && player.item.scythe == true)
   {
   	parse_window("This scythe is rusty but perhaps it can still be used to collect ");
      parse_window("those corn-cobs. You think you could go to the fields to check how");
      parse_window("it works, but you also remember that collecting corn is not your");
      parse_window("work. You were hired to scare the crows away.");
   }
   if(strcmp(what, "wax apples") == 0 && player.item.wax_apples == true)
   {
   	parse_window("You have six wax apples. Those look very nice, and almost real");
      parse_window("even though there is much more colour in those than in real");
      parse_window("apples.");
   }
   if(strcmp(what, "sleeping bag") == 0 && player.item.sleeping_bag == true)
   {
   	parse_window("This sleeping bag is 'loaned' from Hill Inn. You can use it");
      parse_window("whenever you want to sleep. Sleeping outside isn't safe but");
      parse_window("this sure is useful even if you're sleeping at Hill Inn ");
      parse_window("because it is quite cold during the night.");
   }
   if(strcmp(what, "scarecrow") == 0 && player.item.scarecrow == true)
   {
   	parse_window("You wonder why this scarecrow is here. Why isn't it in the fields.");
      parse_window("You think about taking it to the fields to reduce your work.");
      parse_window("It's a big human-sized doll with some rags worn for it.");
   }
   if(strcmp(what, "animated scarecrow") == 0 && player.item.animated_scarecrow == true)
   {
		parse_window("Your magical spell makes the scarecrow look more alive. It shows ");
      parse_window("signs of animation, but you can't truly know because you're holding");
      parse_window("it. You think you should drop it to see how it works.");
   }
	return 0;
}

int bless_item(char what[30])
{
	if(strcmp(what, "moonstone") == 0 && player.item.moonstone == true)
   {
   	if(player.magic.duration == 0 || player.magic.spell != 'h')
      {
      	parse_window("Nothing special happens.");
         return 0;
      }
		parse_window("You touch the sparkling moonstone with your flaming fist.");
      parse_window("Scintillating colours explode to the sky as you hand");
      parse_window("reaches the moonstone. What a wonder it is. The moonstone");
      parse_window("changes its colour to scintillating terastone.");
      player.item.moonstone = false;
      player.item.terastone = true;
		player.magic.duration = 0;
      player.var.score += 16;
    	player.time.talking[6] = 8;
      update_all_windows();
		return 0;
   }
	if(strcmp(what, "scarecrow") == 0 && player.item.scarecrow == true)
   {
   	if(player.magic.duration == 0 || player.magic.spell != 'c')
      {
			parse_window("Nothing special happens.");
         return 0;
      }
   	parse_window("You touch the scarecrow and it becomes alive!");
      parse_window("You feel like the scarecrow was trying to struggle away");
      parse_window("from you.");
      player.item.animated_scarecrow = true;
		player.magic.duration = 0;
      player.var.score += 1;
      update_all_windows();
      return 0;
   }
	parse_window("Nothing special happens.");
   return 0;
}

int use_items(char what[30])
{
   if(strcmp(what, "corn-cob") == 0 && player.item.corn > 0)
   {
      parse_window("You take a delicious looking corn-cob and eat it.");
      parse_window("It was very satisfying.");
      player.item.corn -= 1;
      player.var.food += 1;
      update_all_windows();
      return 0;
   }
   if(strcmp(what, "elven flute") == 0 && player.item.flute == true)
   {
   	parse_window("You attempt to play the flute when words enthrall your mind.");
      parse_window("'Please don't, it is not yours.' You are frightened and are");
      parse_window("afraid to use the flute.");
      return 0;
   }
   if(strcmp(what, "war horn") == 0 && player.item.horn == true)
   {
   	if(strcmp(player.time.place, "Council") != 0)
      {
      	parse_window("You blow the horn.");
         parse_window("It releases a very high voice but that's really it.");
         return 0;
      }
      /* using in council, waking up elders (Tof and Darol), talking 2 && 3 */
		parse_window("You blow the horn.");
      dialogue("What was that?", "Darol");
      dialogue("What?", "Tof");
      dialogue("Somebody blowed a horn!", "Darol");
      dialogue("Really..?", "Tof");
      dialogue("We'd better hurry to the harbour!", "Darol");
      dialogue("But there's no harbour near Deserras!", "Tof");
      dialogue("What was it then?", "Darol");
		dialogue("Why don't we look?", "Tof");
      parse_window("The elders turn around.");
		dialogue("Some kind of prankster?", "Darol");
      dialogue("Let's hear your explanation, stranger.", "Tof");
      dialogue("And give that damn horn to me.", "Tof");
      parse_window("Tof magically summons horn from your hand.");
      player.item.horn = false;
      player.time.talking[2] = 1;
      player.time.talking[3] = 1;
      player.var.score += 7;
      update_all_windows();
      return 0;
	}
	if(strcmp(what, "return book") == 0 && player.item.incarnate_book == true)
   {
   	parse_window("You start reading 'Incarnations and Creations'");
      parse_window("You read the book and find out that there are some text");
      parse_window("about rituals on how to turn flesh into fur. You don't");
      parse_window("really understand the rest of the book.");
      return 0;
   }
   if(strcmp(what, "history book") == 0 && player.item.history_book == true)
   {
		dialogue("I wonder if they have spelled by name right..");
      if(player.item.horn == false && player.picked.horn == true)
      {
      	talk_daemon("I could search about Darol, the Dauntless.", 1, false);
         switch(talk_daemon("I could search about Tof, the archwizard.", 2, true))
         {
         	case 1: parse_window("You browse the book and open a page telling about Darol.");
            		  parse_window("There is some information told about Darol, the Dauntless.");
                    parse_window("'Darol was a brave warrior. He had his strength and power");
                    parse_window("that were required to smite tramplers. He lost his daughter");
                    parse_window("to a trampler, as he was unable to protect her.'");
                    break;
            case 2: parse_window("You browse the book and open a page telling about Tof.");
            		  parse_window("'Tof is something like 500 years old. He is the Archwizard");
                    parse_window("of Winter. He masters all seasonal spells of winter, and his");
                    parse_window("powers are controlled by the winter spirit, Domaja. It is said");
                    parse_window("that this old wizard has become eccentric during the years.");
                    break;
         }
      }
      else
      {
   	   parse_window("You start reading but that doesn't really help since");
	      parse_window("the book is full of names of heroes whose names ");
      	parse_window("doen't ring a bell at all to you. You only wish that");
   	   parse_window("you knew who you were looking from it.");
	   }
      return 0;
   }
   if(strcmp(what, "poem book") == 0 && player.item.poem_book == true)
   {
		parse_window("You browse a few pages and find an interesting poem.");
      getch();
      rand_poem();
		if(player.stat.Wis < 8)
      {
         parse_window("You feel wiser as you realize the philosophy.");
         player.stat.Wis++;
		   player.var.max_sp = count_max_sp();
         getch();
         update_all_windows();
      }
      return 0;
   }
   if(strcmp(what, "necro book") == 0 && player.item.necro_book == true)
   {
		parse_window("You start reading the 'Hauntings from the grave'.");
      parse_window("It sounds really interesting as it tells about the");
      parse_window("main things about necromancy and actually introduces");
      parse_window("a way to communicate with the dead. You study carefully");
      parse_window("and learn a new spell. The book vanishes into dust.");
      player.item.necro_book = false;
      player.var.score += 5;
      update_all_windows();
      return 0;
   }
	if(strcmp(what, "sleeping bag") == 0 && player.item.sleeping_bag == true)
   {
		if(strcmp(player.time.place, "Hill Inn") != 0)
      {
      	parse_window("You should sleep in Hill Inn. It is dangerous here.");
         return 0;
      }
      if(player.time.sleep < 12)
      {
			parse_window("You are not even sleepy.");
         return 0;
      }
      parse_window("You open your sleeping bag and jump in it.");
      parse_window("You start sleeping like a log.");
      getch();
      show_vision(player.var.vision);
      if(player.time.talking[6] > 0) show_vision(4); // Anyaca at geyser
      clrscr();
      delay_text("ZzzZzzzZzzZZZzzzz...snore........");
      create_map();
      player.time.hours = 7;
      player.time.days++;
      player.time.minutes = myrand(60) + 1;
		player.time.sleep -= 16;
      player.var.sp += player.stat.Mag;
      player.var.hp += player.stat.Con;
      player.var.food -= 1;
      if(player.time.sleep < 0) player.time.sleep = 0;
      if(player.var.sp > player.var.max_sp) player.var.sp = player.var.max_sp;
      if(player.var.hp > player.var.max_hp) player.var.hp = player.var.max_hp;
      parse_window("You wake up refreshed.");
      update_all_windows();
      return 0;
   }
	if(strcmp(what, "scarecrow") == 0 && player.item.scarecrow == true)
   {
   	char c;
      c = map[true_y(screen.y[0])][true_x(screen.x[0])];
      if(c != 'Y')
      {
         parse_window("Why would you like to leave it here?");
         return 0;
      }
      parse_window("You place the scarecrow so that crows can see it.");
      parse_window("First crows stay away from the cornfields but then");
      parse_window("they seem to realize that it isn't a real person.");
      parse_window("It didn't really help, so you take the scarecrow");
      parse_window("with you.");
      return 0;
   }
	if(strcmp(what, "animated scarecrow") == 0 && player.item.animated_scarecrow == true)
   {
   	char c;
      c = map[true_y(screen.y[0])][true_x(screen.x[0])];
      if(c != 'Y')
      {
         parse_window("Why would you like to leave it here?\n");
         return 0;
      }
      parse_window("You place the scarecrow so that crows can see it.");
		parse_window("Suddenly the scarecrow starts moving across the cornfields");
      parse_window("automatically. It seems your animation spell worked.");
      getch();
		dialogue("I'd better not tell about this to bailiff.");
      dialogue("I've got to think of something.");
      player.time.talking[0] = 1; // talking about granary store
      player.var.score += 4;
      player.var.vision = 1;
      player.item.animated_scarecrow = false;
      player.item.scarecrow = false;
      update_all_windows();
      return 0;
   }
	if(strcmp(what, "scythe") == 0 && player.item.scythe == true)
   {
   	char c;
      c = map[true_y(screen.y[0])][true_x(screen.x[0])];
      if(c != 'Y')
      {
      	parse_window("That can be used to collect corn-cobs from cornfields.");
         parse_window("There's no corn in here. But you think you could get ");
         parse_window("some other things that could be used in alchemy.");
         if(!strcmp(player.time.place, "Cornland") == 0) return 0;
         switch(c)
         {
         	case 's': parse_window("You find swamp mush."); player.var.alchemy[1]++; break;
            case 'v': parse_window("You find a raspberry."); player.var.alchemy[2]++; break;
				case 'F':
            case 'f': parse_window("You find a blueberry."); player.var.alchemy[3]++; break;
            case 'd': parse_window("You find a scorpion tail."); player.var.alchemy[4]++; break;
            case 'J':
            case 'j':
            case 'S': parse_window("You find a dead snake."); player.var.alchemy[5]++; break;
            case 'm': parse_window("You find acorn."); player.var.alchemy[6]++; break;
            default: parse_window("You don't find anything useful."); break;
         }
         return 0;
      }
		if(player.time.talking[6] > 5 && player.time.talking[6] < 10) // magical winter
      {
      	parse_window("It's useless. The winter has destroyed the crops.");
         return 0;
      }
      dialogue("I wish the bailiff doesn't catch me for stealing.");
      parse_window("You swing your scythe to collect corn-cobs from the fields.");
      parse_window("You collect some corn from the fields.");
      player.item.corn++;
      update_all_windows();
      return 0;
   }
	switch(myrand(5))
   {
   	case 1: parse_window("No use for it."); break;
      case 2: parse_window("What are you going to do with it?"); break;
      case 3: parse_window("Impossible."); break;
      default: parse_window("That's completely ridiculous."); break;
   }
	return 0;
}

int combine_items(char item1[30], char item2[30])
{
	if(strcmp(item1, "tarn stone") == 0 || strcmp(item2, "tarn stone") == 0)
   {
   	if(strcmp(item1, "zar stone") == 0 || strcmp(item2, "zar stone") == 0)
      {
			if(player.item.tarn == false || player.item.zar == false)
         {
            parse_window("That would produce nothing but mess.");
            return 0;
         }
			parse_window("You take a Tarn Star to your left hand and take the");
         parse_window("Zar Star to your right hand. You slowly combine them");
         parse_window("creating a black orb.");
			player.item.tarn = false;
         player.item.zar = false;
         player.item.black_orb = true;
         player.var.score += 1;
         update_all_windows();
         return 0;
	   }
   }
	if(strcmp(item1, "vira stone") == 0 || strcmp(item2, "vira stone") == 0)
   {
   	if(strcmp(item1, "dural stone") == 0 || strcmp(item2, "dural stone") == 0)
      {
			if(player.item.vira == false || player.item.dural == false)
         {
            parse_window("That would produce nothing but mess.");
            return 0;
         }
			parse_window("You take a Vira Star to your left hand and take the");
         parse_window("Dural Star to your right hand. You slowly combine them");
         parse_window("creating a white orb.");
			player.item.vira = false;
         player.item.dural = false;
         player.item.white_orb = true;
         player.var.score += 1;
         update_all_windows();
         return 0;
	   }
   }
	if(strcmp(item1, "white orb") == 0 || strcmp(item2, "white orb") == 0)
   {
   	if(strcmp(item1, "black orb") == 0 || strcmp(item2, "black orb") == 0)
      {
			if(player.item.white_orb == false || player.item.black_orb == false)
         {
            parse_window("That would produce nothing but mess.");
            return 0;
         }
         parse_window("You take black orb to your right hand, and then take");
         parse_window("white orb to your left hand. You slowly combine them");
         parse_window("into a glowing moonstone.");
         player.item.black_orb = false;
         player.item.white_orb = false;
         player.item.moonstone = true;
         player.var.score += 2;
         update_all_windows();
         return 0;
	   }
   }
   parse_window("That would produce nothing but mess.");
	return 0;
}

int show_inventory(char usage)
{
	int use_item = 0, comb1 = 0, comb2 = 0;
   char item[30], combined1[30], combined2[30], cmd = 0;
   bool exit = false;
	do
   {
		textcolor(TOPIC);
		strcpy(item, "");
      strcpy(combined1, "");
      strcpy(combined2, "");
		exit = false;
		clrscr();
		gotoxy(12, 1); cout <<"*!* INVENTORY *!*\n";
      textcolor(TEXT);
		gotoxy(12, wherey()); cout <<"a) Money purse ("<< player.var.money <<" crowns)\n";
      if(player.item.corn > 0) { gotoxy(12, wherey()); cout << "b) Delicious looking corn-cob (x"<< player.item.corn <<")\n"; }
      if(player.item.scythe == true) { gotoxy(12, wherey()); cout <<"c) Rusty steel scythe\n"; }
      if(player.item.scarecrow == true && player.item.animated_scarecrow == false) { gotoxy(12, wherey()); cout <<"d) Heavy old scarecrow\n"; }
      if(player.item.scarecrow == true && player.item.animated_scarecrow == true) { gotoxy(12, wherey()); cout <<"d) Magically animated scarecrow\n"; }
      if(player.item.wax_apples == true) { gotoxy(12, wherey()); cout <<"e) Six wax apples\n"; }
      if(player.item.sleeping_bag == true) { gotoxy(12, wherey()); cout <<"f) Sleeping bag\n"; }
      if(player.item.history_book == true) { gotoxy(12, wherey()); cout <<"g) Book labelled 'Heroes of our Lifetime'\n"; }
      if(player.item.necro_book == true) { gotoxy(12, wherey()); cout <<"h) Book labelled 'Hauntings from the grave'\n"; }
      if(player.item.poem_book == true) { gotoxy(12, wherey()); cout <<"i) Tome of Poems\n"; }
      if(player.item.incarnate_book == true) { gotoxy(12, wherey()); cout <<"j) Book labelled 'Creations and Incarnations'\n"; }
      if(player.item.horn == true) { gotoxy(12, wherey()); cout <<"k) War horn\n"; }
      if(player.item.flute == true) { gotoxy(12, wherey()); cout <<"l) Cute bamboo flute\n"; }
      if(player.item.mage_keys == true) { gotoxy(12, wherey()); cout <<"m) Keys to magicians' guild\n"; }
      if(player.item.roses == true) { gotoxy(12, wherey()); cout <<"n) Beautiful red roses\n"; }
      if(player.item.jewels == true) { gotoxy(12, wherey()); cout <<"o) Sparkling rubies\n"; }
      if(player.item.dural == true) { gotoxy(12, wherey()); cout <<"p) Piece of Dural star\n"; }
      if(player.item.vira == true) { gotoxy(12, wherey()); cout <<"q) Piece of Vira star\n"; }
      if(player.item.zar == true) { gotoxy(12, wherey()); cout <<"r) Piece of Zar star\n"; }
      if(player.item.tarn == true) { gotoxy(12, wherey()); cout <<"s) Piece of Tarn star\n"; }
      if(player.item.cure > 0) { gotoxy(12, wherey()); cout <<"t) Cure for Death\n"; }
      if(player.item.black_orb == true) { gotoxy(12, wherey()); cout <<"u) Black orb\n"; }
      if(player.item.white_orb == true) { gotoxy(12, wherey()); cout <<"v) White orb\n"; }
      if(player.item.moonstone == true) { gotoxy(12, wherey()); cout <<"w) Sparkling moonstone\n"; }
      if(player.item.terastone == true) { gotoxy(12, wherey()); cout <<"x) Scintillating terastone\n"; }
      gotoxy(12, wherey()); cout <<"(ESC) Exit inventory, (u) Use item, (c) Combine items\n";
		gotoxy(12, wherey()); cout <<"                      (e) Examine,  (g) Give item\n";
      gotoxy(12, wherey()); cout <<"                      (b) Bless item (with magic)\n";
      if(usage == 'i') cmd = getch();
		if(usage == 'u') cmd = 'u';
      if(usage == 'b') cmd = 'b';
		if(usage == 'c') cmd = 'c';
      if(usage == 'e') cmd = 'e';
      if(usage == 'g') cmd = 'g';
		if(cmd == 27) exit = true;
		if(cmd == 'c')
      {
      	textcolor(TEXT);
			strcpy(combined1, "");
         strcpy(combined2, "");
         exit = true;
         gotoxy(12, wherey());
         cout <<"Combine which item: ";
         comb1 = getch();
         cprintf("%c", comb1);
         gotoxy(12, wherey()+1);
         cout <<"With which item: ";
         comb2 = getch();
         cprintf("%c", comb2);
         switch((char)comb1)
         {
         	case 'a': strcpy(combined1, "money purse"); break;
            case 'b': strcpy(combined1, "corn-cob"); break;
            case 'c': strcpy(combined1, "scythe"); break;
            case 'd': strcpy(combined1, "scarecrow"); if(player.item.animated_scarecrow == true) strcpy(combined1, "animated scarecrow"); break;
            case 'e': strcpy(combined1, "wax apples"); break;
            case 'f': strcpy(combined1, "sleeping bag"); break;
            case 'g': strcpy(combined1, "history book"); break;
            case 'h': strcpy(combined1, "necro book"); break;
            case 'i': strcpy(combined1, "poem book"); break;
            case 'j': strcpy(combined1, "return book"); break;
            case 'k': strcpy(combined1, "war horn"); break;
            case 'l': strcpy(combined1, "elven flute"); break;
            case 'm': strcpy(combined1, "guild keys"); break;
            case 'n': strcpy(combined1, "red roses"); break;
            case 'o': strcpy(combined1, "jewels"); break;
            case 'p': strcpy(combined1, "dural stone"); break;
            case 'q': strcpy(combined1, "vira stone"); break;
            case 'r': strcpy(combined1, "zar stone"); break;
            case 's': strcpy(combined1, "tarn stone"); break;
            case 't': strcpy(combined1, "cure for death"); break;
            case 'u': strcpy(combined1, "black orb"); break;
            case 'v': strcpy(combined1, "white orb"); break;
            case 'w': strcpy(combined1, "moonstone"); break;
            case 'x': strcpy(combined1, "terastone"); break;
         }
         switch((char)comb2)
         {
         	case 'a': strcpy(combined2, "money purse"); break;
            case 'b': strcpy(combined2, "corn-cob"); break;
            case 'c': strcpy(combined2, "scythe"); break;
            case 'd': strcpy(combined2, "scarecrow"); if(player.item.animated_scarecrow == true) strcpy(combined2, "animated scarecrow"); break;
            case 'e': strcpy(combined2, "wax apples"); break;
            case 'f': strcpy(combined2, "sleeping bag"); break;
            case 'g': strcpy(combined2, "history book"); break;
            case 'h': strcpy(combined2, "necro book"); break;
            case 'i': strcpy(combined2, "poem book"); break;
            case 'j': strcpy(combined2, "return book"); break;
            case 'k': strcpy(combined2, "war horn"); break;
            case 'l': strcpy(combined2, "elven flute"); break;
            case 'm': strcpy(combined2, "guild keys"); break;
            case 'n': strcpy(combined2, "red roses"); break;
            case 'o': strcpy(combined2, "jewels"); break;
            case 'p': strcpy(combined2, "dural stone"); break;
            case 'q': strcpy(combined2, "vira stone"); break;
            case 'r': strcpy(combined2, "zar stone"); break;
            case 's': strcpy(combined2, "tarn stone"); break;
            case 't': strcpy(combined2, "cure for death"); break;
            case 'u': strcpy(combined2, "black orb"); break;
            case 'v': strcpy(combined2, "white orb"); break;
            case 'w': strcpy(combined2, "moonstone"); break;
            case 'x': strcpy(combined2, "terastone"); break;
         }
      }
		if(cmd == 'u' || cmd == 'e' || cmd == 'g' || cmd == 'b')
      {
			textcolor(TEXT);
			strcpy(item, "");
      	exit = true;
         gotoxy(12, wherey());
         if(cmd == 'u') cout <<"Use which item: ";
         else if(cmd == 'b') cout <<"Bless which item: ";
         else if(cmd == 'e') cout <<"Examine which item: ";
         else cout <<"Give which item: ";
         use_item = getch();
         cprintf("%c", use_item);
         switch((char)use_item)
         {
         	case 'a': strcpy(item, "money purse"); break;
            case 'b': strcpy(item, "corn-cob"); break;
            case 'c': strcpy(item, "scythe"); break;
            case 'd': strcpy(item, "scarecrow"); if(player.item.animated_scarecrow == true) strcpy(item, "animated scarecrow"); break;
            case 'e': strcpy(item, "wax apples"); break;
            case 'f': strcpy(item, "sleeping bag"); break;
            case 'g': strcpy(item, "history book"); break;
            case 'h': strcpy(item, "necro book"); break;
            case 'i': strcpy(item, "poem book"); break;
            case 'j': strcpy(item, "return book"); break;
            case 'k': strcpy(item, "war horn"); break;
            case 'l': strcpy(item, "elven flute"); break;
            case 'm': strcpy(item, "guild keys"); break;
            case 'n': strcpy(item, "red roses"); break;
            case 'o': strcpy(item, "jewels"); break;
            case 'p': strcpy(item, "dural stone"); break;
            case 'q': strcpy(item, "vira stone"); break;
            case 'r': strcpy(item, "zar stone"); break;
            case 's': strcpy(item, "tarn stone"); break;
            case 't': strcpy(item, "cure for death"); break;
            case 'u': strcpy(item, "black orb"); break;
            case 'v': strcpy(item, "white orb"); break;
            case 'w': strcpy(item, "moonstone"); break;
            case 'x': strcpy(item, "terastone"); break;
         }
      }
   } while(exit == false);
   clrscr();
   create_map();
	if(player.time.indoors == true)
   {
		if(screen.x[0] < 12) screen.x[0] = 12;
      if(screen.y[0] < 3) screen.y[0] = 3;
		if(screen.x[0] > (player.time.area_x3 - player.time.area_x1) + 8) screen.x[0] = player.time.area_x3 - player.time.area_x1 + 8;
      if(screen.y[0] > (player.time.area_y2 - player.time.area_y1) - 1) screen.y[0] = player.time.area_y2 - player.time.area_y1 - 1;
		draw_area(player.time.area_x1, player.time.area_y1, player.time.area_y2, player.time.area_x3);
   	draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   }
   update_all_windows();
	if(strlen(item) > 0 && cmd == 'u') use_items(item);
   if(strlen(item) > 0 && cmd == 'e') examine_item(item);
   if(strlen(item) > 0 && cmd == 'g') give_item(item);
   if(strlen(item) > 0 && cmd == 'b') bless_item(item);
   if(strlen(combined1) > 0 && strlen(combined2) > 0) combine_items(combined1, combined2);
	return 0;
}

int alchemy()
{
   bool exit = false;
	char cmd;
	do
   {
		cmd = 0;
		textcolor(TOPIC);
		exit = false;
		clrscr();
		gotoxy(12, 1); cout <<"*!* ALCHEMY *!*\n";
      textcolor(TEXT);
	   for(int_temp = 0; int_temp < 17; int_temp++)
      {
      	if(player.var.alchemy[int_temp] > 0)
         {
         	switch(int_temp)
            {
            	case 1: gotoxy(12, wherey()); cout <<"a) Swamp mush (x"<< player.var.alchemy[int_temp] <<")\n"; break;
					case 2: gotoxy(12, wherey()); cout <<"b) Raspberry (x"<< player.var.alchemy[int_temp] <<")\n"; break;
					case 3: gotoxy(12, wherey()); cout <<"c) Blueberry (x"<< player.var.alchemy[int_temp] <<")\n"; break;
   				case 4: gotoxy(12, wherey()); cout <<"d) Scorpion tail (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 5: gotoxy(12, wherey()); cout <<"e) Dead snake (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 6: gotoxy(12, wherey()); cout <<"f) Acorn (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 7: gotoxy(12, wherey()); cout <<"g) Mandrake root (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 8: gotoxy(12, wherey()); cout <<"h) Spider web (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 9: gotoxy(12, wherey()); cout <<"i) Mistletoe (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 10:gotoxy(12, wherey()); cout <<"j) Muddy goo (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 11:gotoxy(12, wherey()); cout <<"k) Green weed (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 12:gotoxy(12, wherey()); cout <<"l) Bird egg (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 13:gotoxy(12, wherey()); cout <<"m) Amber (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 14:gotoxy(12, wherey()); cout <<"n) Bee wax (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 15:gotoxy(12, wherey()); cout <<"o) Black acid (x"<< player.var.alchemy[int_temp] <<")\n"; break;
               case 16:gotoxy(12, wherey()); cout <<"p) White dust (x"<< player.var.alchemy[int_temp] <<")\n"; break;
            }
			}
      }
      gotoxy(12, wherey()); cout <<"(M)ix item, (ESC) Exit alchemy\n";
      cmd = getch();
      if(cmd == 'm')
      {
         do
         {
         	gotoxy(12, wherey()); cout <<"Mix which item: ";
	         cmd = getch();
            if(cmd == 27) exit = true;
				cmd -= 96;
            cprintf("%c", cmd+96);
         }  while(player.var.alchemy[cmd] < 1 && exit == false);
         if(exit == true) break;
         int_temp = cmd;
         do
         {
         	cout << endl;
   			gotoxy(12, wherey()); cout <<"Another item: ";
            cmd = getch();
            if(cmd == 27) exit = true;
            cmd -= 96;
         } while(player.var.alchemy[cmd] < 1 && exit == false);
         if(exit == true) break;
         player.var.alchemy[int_temp]--;
         int_temp += cmd;
         player.var.alchemy[cmd]--;
         if(player.skill.Alchemy > myrand(15))
         {
         	if(int_temp < 17) player.var.alchemy[int_temp]++;
   	      gotoxy(12, wherey()); cout <<"You mix the components together.\n";
            switch(int_temp)
            {
            	default: gotoxy(12, wherey()); cout <<"You get a new component from those.\n"; break; // 1-15
               case 17: gotoxy(12, wherey()); cout <<"You make some corn crops.\n"; player.item.corn += 3; break;
					case 18: gotoxy(12, wherey()); cout <<"You make a strange solid potion. It was like eating a beaf.\n"; player.var.food += 10; break;
               case 19: gotoxy(12, wherey()); cout <<"It melts into gold crowns!\n"; player.var.money += myrand(5) + 5; break;
               case 20: gotoxy(12, wherey()); cout <<"It explodes in magical power, activates a spell.\n"; player.magic.duration = 250; break;
               case 21:
               case 22: gotoxy(12, wherey()); cout <<"It creates strange incense that heals you.\n"; player.var.hp = player.var.max_hp * 2; break; 
               case 23:
               case 24: gotoxy(12, wherey()); cout <<"It creates strange incense that boosts you.\n"; player.var.sp = player.var.max_sp * 2; break;
               case 25: gotoxy(12, wherey()); cout <<"You feel luckier.\n"; player.stat.Luck++; break;
					case 26: gotoxy(12, wherey()); cout <<"You feel stronger.\n", player.stat.Str++; player.var.max_hp = count_max_hp(); break;
               case 27: gotoxy(12, wherey()); cout <<"You feel robust.\n"; player.stat.Con++; player.var.max_hp = count_max_hp(); break;
               case 28:
               case 29: gotoxy(12, wherey()); cout <<"You feel wiser.\n"; player.stat.Wis++; player.var.max_sp = count_max_sp(); break;
               case 30: gotoxy(12, wherey()); cout <<"You feel more powerful.\n"; player.stat.Mag++; player.var.max_sp = count_max_sp(); break;
               case 31: gotoxy(12, wherey()); cout <<"You invent cure for death disease.\n"; player.item.cure++; if(player.picked.cure == 0) { player.var.score += 23; player.picked.cure = 1; } break;
               case 32: gotoxy(12, wherey()); cout <<"You feel more powerful.\n"; player.stat.Mag++; player.var.max_sp = count_max_sp(); break;
            }
         }
         else if(player.stat.Luck > myrand(25))
         {
         	int_temp -= myrand(3) - 1;
            if(int_temp < 0) int_temp = 0;
         	player.var.alchemy[int_temp]++;
            gotoxy(12, wherey()); cout <<"You fumble but luckily created something.\n";
         }
         else
         {
         	gotoxy(12, wherey()); cout <<"You completely fail to mix properly.\n";
         }
         getch();
      }
      if(cmd == 27) exit = true;
 	} while(exit == false);
   clrscr();
   create_map();
/*	if(player.time.indoors == true)
   {
		if(screen.x[0] < 12) screen.x[0] = 12;
      if(screen.y[0] < 3) screen.y[0] = 3;
		if(screen.x[0] > (player.time.area_x3 - player.time.area_x1) + 8) screen.x[0] = player.time.area_x3 - player.time.area_x1 + 8;
      if(screen.y[0] > (player.time.area_y2 - player.time.area_y1) - 1) screen.y[0] = player.time.area_y2 - player.time.area_y1 - 1;
		draw_area(player.time.area_x1, player.time.area_y1, player.time.area_y2, player.time.area_x3);
   	draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   } */
   update_all_windows();
   return 0;
}
int magic()
{
   bool exit = false;
   char cmd;
	do
   {
		cmd = 0;
		textcolor(TOPIC);
		exit = false;
		clrscr();
		gotoxy(12, 1); cout <<"*!* MAGIC *!*\n";
      textcolor(TEXT);
		gotoxy(12, wherey()); cout <<"a) Light  		     2 spell points\n";
      gotoxy(12, wherey()); cout <<"b) Dim path		     3 spell points\n";
      if(player.time.talking[1] > 3) // Juggler taught animate spell
      {
      	gotoxy(12, wherey()); cout <<"c) Animate		     8 spell points\n";
      }
      if(player.picked.necro_book == true && player.item.necro_book == false) // Learned from book
      {
      	gotoxy(12, wherey()); cout <<"d) Mourning from beyond      7 spell points\n";
      }
      if(player.magic.frosty_way == true)  // from Tof, Archwizard of Winter
      {
      	gotoxy(12, wherey()); cout <<"e) Frosty way		     5 spell points\n";
      }
      if(player.magic.bestial_speech == true) // from Sorceress Anyaca
      {
      	gotoxy(12, wherey()); cout <<"f) Bestial speech	     4 spell points\n";
      }
      if(player.magic.gateway == true)
      {
      	gotoxy(12, wherey()); cout <<"g) Gateway     		     5 spell points\n";
      }
      if(player.magic.reinforce == true)
      {
      	gotoxy(12, wherey()); cout <<"h) Reinforce	 	     7 spell points\n";
      }
      gotoxy(12, wherey()); cout <<"(ESC) Exit magic\n";
		cmd = getch(); // getting spell.
		if(cmd == 27) exit = true; // cancelling spell
      if(cmd == 'a') exit = true;
      if(cmd == 'b') exit = true;
      if(cmd == 'c' && player.time.talking[1] > 3) exit = true;
      if(cmd == 'd' && player.picked.necro_book == true && player.item.necro_book == false) exit = true;
      if(cmd == 'e' && player.magic.frosty_way == true) exit = true;
      if(cmd == 'f' && player.magic.bestial_speech == true) exit = true;
      if(cmd == 'g' && player.magic.gateway == true) exit = true;
      if(cmd == 'h' && player.magic.reinforce == true) exit = true;
   } while(exit == false);
   clrscr();
   create_map();
	if(player.time.indoors == true)
   {
		if(screen.x[0] < 12) screen.x[0] = 12;
      if(screen.y[0] < 3) screen.y[0] = 3;
		if(screen.x[0] > (player.time.area_x3 - player.time.area_x1) + 8) screen.x[0] = player.time.area_x3 - player.time.area_x1 + 8;
      if(screen.y[0] > (player.time.area_y2 - player.time.area_y1) - 1) screen.y[0] = player.time.area_y2 - player.time.area_y1 - 1;
		draw_area(player.time.area_x1, player.time.area_y1, player.time.area_y2, player.time.area_x3);
   	draw(screen.x[0], screen.y[0], screen.draw.sign[0], screen.draw.color[0]);
   }
   update_all_windows();
	if(cmd == 27) return 0;
   if(cmd == 'a')	cast_spell("light");
   if(cmd == 'b') cast_spell("dim path");
   if(cmd == 'c') cast_spell("animate");
   if(cmd == 'd') cast_spell("mourning from beyond");
   if(cmd == 'e') cast_spell("frosty way");
   if(cmd == 'f') cast_spell("bestial speech");
   if(cmd == 'g') cast_spell("gateway");
   if(cmd == 'h') cast_spell("reinforce");
	return 0;
}

