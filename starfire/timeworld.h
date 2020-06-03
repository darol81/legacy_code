int reset_time()
{
   /* this creates a totally new (time)world for start */
	player.time.minutes = myrand(60) + 1;
   player.time.hours = myrand(3) + 8;
   player.time.sleep = 0;
   player.time.days = 1;
   player.time.light = 0; // 0 is light, all other positive numbers are night
   return 0;
}

int time_update()
{
	char c;
   int waterdam = 0, swimlevel = 0;
   c = map[true_y(screen.y[0])][true_x(screen.x[0])];
	switch(c)
   {
   	case 'r': swimlevel = 5; waterdam = 4; break;
      case 'R': swimlevel = 9; waterdam = 6; break;
      case 'l': swimlevel = 5; waterdam = 2; break;
      case 'L': swimlevel = 7; waterdam = 2; break;
      case '*': swimlevel = 15; waterdam = 15; break;
      case '~': swimlevel = 8; waterdam = 8; break;
      default:  swimlevel = 0; waterdam = 0; break;
   }
	if(strcmp(player.time.place, "Cornland") == 0 && player.time.talking[6] == 5 && myrand(20) == 1)
   {
		dialogue("What is that white thing falling from the sky?");
		dialogue("A snow flake? And there's another? In the middle of summer?");
      dialogue("How can this be explained?");
      player.time.talking[6] = 6; // Anyaca
      player.time.talking[3] = 2; // Tof
      player.time.talking[2] = 2; // Darol
      player.var.score += 1;
      update_all_windows();
   }
   if(c == 'Y' && player.time.talking[0] == 0 && myrand(10) == 1 && strcmp(player.time.place, "Cornland") == 0)
   {
   	parse_window("You scare some crows off the cornfield.");
   }
   if(c == 'Y' && player.time.hours == 9 && player.time.minutes == 30
   			   || player.time.hours == 12 && player.time.minutes == 30
               || player.time.hours == 16 && player.time.minutes == 30
               && player.time.talking[0] > 1)
   {
   	player.var.salary++;
   }
   if(player.time.hours == 9 && player.time.minutes == 30
   	|| player.time.hours == 12 && player.time.minutes == 30
      || player.time.hours == 16 && player.time.minutes == 30)
   {
   	if(c == 'Y' && player.time.talking[0] < 2 && strcmp(player.time.place, "Cornland") == 0)
      {
	   	parse_window("You see the bailiff coming. You try to look busy.");
   		switch(myrand(6) + 1)
      	{
      		case 1: dialogue("I can't believe my eyes! You're working!", "Bailiff"); break;
	         case 2: dialogue("Didn't notice you coming, Sir!");
   	      		  dialogue("Yeah....right.", "Bailiff"); break;
      	   case 3: dialogue("You're working! Are you feverish!", "Bailiff"); break;
         	case 4: dialogue("Acting as if working, right slacker?", "Bailiff"); break;
	         case 5: dialogue("Crowns for the crows.", "Bailiff"); break;
   	      default:dialogue("You're slacking after I leave, aren't you.", "Bailiff"); break;
      	}
	      parse_window("Bailiff checks the results of your work.");
			if(myrand(10) == 1)
      	{
				dialogue("What do you think of my work, Sir!");
   	      dialogue("You're the worst, but we don't have anyone else.", "Bailiff");
      	}
      	if(player.item.corn > 0)
		   {
	      	dialogue("Is that corn-cob in your pocket, you slacker?", "Bailiff");
   	      dialogue("You're not worth this crown, work harder.", "Bailiff");
      	}
	      else
   	   {
	      	dialogue("Looks good, I can't see crows.", "Bailiff");
   	      dialogue("Keep up the good work boy, here's your crown.", "Bailiff");
	         player.var.money += 1;
   	      update_all_windows();
         }
	      parse_window("The bailiff leaves.");
      }
   }
   if(swimlevel > 0 && player.time.indoors == false)
   {
		if(strcmp(player.time.place, "Cornland") == 0 && player.time.talking[6] > 5 && player.time.talking[6] < 10) // magical winter cast by Anyaca
      {
      	parse_window("The magical winter has frozen the water in Cornland.");
      }
   	else if(player.magic.duration > 0 && player.magic.spell == 'e')
      {
      	parse_window("The water freezes in front of you.");
      }
      else if(myrand(player.skill.Swimming) > myrand(swimlevel))
      {
      	parse_window("You swim.");
      }
      else 
      {
      	parse_window("You feel exhausted and go underwater.");
         hurt(myrand(waterdam) + 1);
      }
   }
   player.time.minutes += myrand(2) + 1;
	if(player.magic.duration > 0)
   {
		player.magic.duration--;
      if(player.magic.duration == 0)
      {
      	switch(player.magic.spell)
         {
         	case 'a': parse_window("Your white light is captured by night."); break;
            case 'b': parse_window("You are left alone by Will O'Wisps."); break;
            case 'c': parse_window("Your animation bless wears off."); break;
            case 'd': parse_window("You have lost your connection with the dead."); break;
            case 'e': parse_window("You feel the warmth leaving your body."); break;
            case 'f': parse_window("Your feel the power of nature leaving your body."); break;
            case 'h': parse_window("Your hands calm down."); break;
         }
      }
   }
   if(player.time.minutes > 60)
   {
   	player.time.minutes = 0;
      player.time.hours++;
      player.time.sleep++;
		if(player.var.food > 0 && myrand(3) == 1)
      {
			player.var.hp++;
         if(player.var.hp > player.var.max_hp)
         	player.var.hp = player.var.max_hp;
         update_all_windows();
      }
      if(player.var.food > 0 && myrand(3) == 1)
      {
      	player.var.sp++;
         if(player.var.sp > player.var.max_sp)
         	player.var.sp = player.var.max_sp;
         update_all_windows();
      }
      if(myrand(3) == 1)
      {
      	player.var.food--;
         update_all_windows();
      }
      if(player.var.food < 0)
      {
      	parse_window("You are very hungry.");
      	if(myrand(3) == 1) hurt((player.var.food / 10) * -1);
         update_all_windows();
      }
	   if(player.time.sleep > 12 && player.time.sleep < 25) // hours
	   {
   		if(myrand(2) == 1) parse_window("You are feeling sleepy.");
	   }
   	if(player.time.sleep > 24)
		{
			if(myrand(2) == 1) parse_window("You feel VERY tired.");
			if(myrand(100) < player.time.sleep) // force sleep
   		{
	      	parse_window("You fall asleep for a short time.");
            parse_window("As you wake up, you notice how time has gone by.");
            parse_window("You feel more hungry.");
   	      player.time.hours += myrand(player.time.sleep) + 3;
            player.var.food -= (player.time.sleep / 3);
            player.var.food--;
      	   if(player.time.hours > 24)
	         {
   	      	player.time.hours = (player.time.hours - 24);
               player.time.days++;
      	   }
	         player.time.sleep -= (6 + myrand(6));
            update_all_windows();
   	   }
	   }
   }
   if(player.time.hours > 24)
   {
   	player.time.hours = 1;
      player.time.days++;
   }
   if(player.time.hours < 7 || player.time.hours > 20)
   {
		if(myrand(10) == 1 && player.time.light < 4)
      {
      	player.time.light++;
         create_map();
      }
		if(player.time.light == 4 && player.time.day == true)
      {
 			parse_window("The sun goes down.");
         player.time.day = false;
      }
   }
   else
   {
   	if(myrand(10) == 1 && player.time.light > 0)
      {
			player.time.light--;
       	create_map();
      }
      if(player.time.light == 0 && player.time.day == false)
      {
         parse_window("The sun gets up.");
         player.time.day = true;
      }
   }
	return 0;
}

int show_time() // this is for the command 'time'
{
	if(player.time.sleep > 24)
   {
   	parse_window("You are too tired to think about time.");
      return 0;
   }
	if(player.time.hours > 23 || player.time.hours < 3)
   	strcpy(args, "It is midnight.");
   if(player.time.hours > 2 && player.time.hours < 5)
   	strcpy(args, "It is not yet dawn.");
   if(player.time.hours > 4 && player.time.hours < 7)
   	strcpy(args, "Day is dawning.");
   if(player.time.hours > 6 && player.time.hours < 10)
   	strcpy(args, "It is morning.");
   if(player.time.hours > 9 && player.time.hours < 12)
   	strcpy(args, "It is mid-morning.");
   if(player.time.hours > 11 && player.time.hours < 14)
   	strcpy(args, "It is midday.");
   if(player.time.hours > 13 && player.time.hours < 17)
   	strcpy(args, "It is afternoon.");
   if(player.time.hours > 16 && player.time.hours < 20)
   	strcpy(args, "Sun is setting down.");
   if(player.time.hours > 19 && player.time.hours < 24)
   	strcpy(args, "Night is still young.");
	parse_window(args);
   itoa(player.time.days, temp, 10);
   strcpy(args, "It is day ");
   strcat(args, temp);
   strcat(args, " in year 32 during the season of Moon.");
   parse_window(args);
	return 0;
}
