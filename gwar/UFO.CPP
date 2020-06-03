/* Galaxy War by Topi Mansikkaviita */

#ifdef __TINY__
#error UFO will not run in the tiny model.
#endif

#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <graphics.h>
#include <time.h>
#define ESC     0x1b                    /* Define the escape key        */
#define CTRL(X)       ((X) & 0x1F)      /* CTRL characters              */
#define bool int
#define TRUE 1
#define FALSE 0
#include "class.h"
int UFO_DELAY = 0, LASER_DELAY = 0, WARP_DELAY = 0;
int    GraphDriver;             /* The Graphics device driver           */
int    GraphMode;               /* The Graphics mode value              */
double AspectRatio;             /* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;              /* The maximum resolution of the screen */
int    MaxColors;               /* The maximum # of colors available    */
int    ErrorCode;               /* Reports any graphics errors          */
bool	 Format; 					  /* Objects formatted for use (?)		   */
struct palettetype palette;             /* Used to read palette info    */
Ufo Blue, Red, Laser1, Laser2;

int myrand(int lim)
{
  static int seed = 0;
  int result = 0;
  if(lim == 0) return 0;
  if(!seed)
  {
    seed = (int)time(0);
    srand(seed);
  }
  result = rand() % lim;
  return result;
}

/* Initializes system to graphics mode */

void Initialize(void)
{
   int xasp, yasp;                       /* Used to read the aspect ratio*/

   GraphDriver = DETECT;                 /* Request auto-detection       */
   initgraph(&GraphDriver, &GraphMode,"");
   ErrorCode = graphresult();            /* Read result of initialization*/
   if(ErrorCode != grOk)                 /* Error occured during init    */
   {
     printf("Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
     exit(1);
   }
	getpalette(&palette);                 /* Read the palette from board  */
   MaxColors = getmaxcolor() + 1;        /* Read maximum number of colors*/

   MaxX = getmaxx();
   MaxY = getmaxy();                     /* Read size of screen          */

   getaspectratio(&xasp, &yasp);         /* read the hardware aspect     */
   AspectRatio = (double)xasp / (double)yasp; /* Get correction factor   */
}

int Game()
{
	int cmd = 0, ext = 0;
   /* random salaa */
   if(Format == false)
   {
   	Red.SavePixels("red.pic");
	   Red.ReadObject();
   	Red.SetX(100);
	   Red.SetY(MaxY/2);
      Red.SetDir(6);
      Red.SetWait(UFO_DELAY);
   	Red.Erase();
		Blue.SavePixels("blue.pic");
	   Blue.ReadObject();
   	Blue.SetX(MaxX - 100);
	   Blue.SetY(MaxY/2);
      Blue.SetDir(4);
      Blue.SetWait(UFO_DELAY);
      Blue.Erase();
	   for(int i=0; i < 1000; ++i)
	   putpixel(myrand(MaxX), myrand(MaxY), myrand(MaxColors-1)+ 1);
	}
   Format = true;
	cmd = getch();
   if(!cmd) ext = getch();
	if(!ext && cmd == 13) // enter, shoot
   {
		for(int i = 0; i < 10; i++)
      {
			sound(300+(i*20));
   	   delay(LASER_DELAY);
         nosound();
      }
		switch(Blue.QueryDir())
      {
      	case 1:
         case 9: Laser1.SavePixels("laser4.pic"); break;
         case 3:
         case 7: Laser1.SavePixels("laser3.pic"); break;
         case 4:
         case 6: Laser1.SavePixels("laser1.pic"); break;
         case 2:
         case 8: Laser1.SavePixels("laser2.pic"); break;
      }
	   Laser1.ReadObject();
   	Laser1.SetX(Blue.QueryX());
	   Laser1.SetY(Blue.QueryY());
      Laser1.SetDir(Blue.QueryDir());
      Laser1.SetWait(LASER_DELAY);
 	 	Laser1.Erase();
      Blue.SetDir(5);
   }
	if(!ext && cmd == 9) // tabulator, shoot
   {
		for(int i = 0; i < 10; i++)
      {
			sound(300+(i*20));
   	   delay(LASER_DELAY);
         nosound();
      }
		switch(Red.QueryDir())
      {
      	case 1:
         case 9: Laser2.SavePixels("laser4.pic"); break;
         case 3:
         case 7: Laser2.SavePixels("laser3.pic"); break;
         case 4:
         case 6: Laser2.SavePixels("laser1.pic"); break;
         case 2:
         case 8: Laser2.SavePixels("laser2.pic"); break;
      }
	   Laser2.ReadObject();
   	Laser2.SetX(Red.QueryX());
	   Laser2.SetY(Red.QueryY());
      Laser2.SetDir(Red.QueryDir());
      Laser1.SetWait(LASER_DELAY);
 	 	Laser2.Erase();
      Red.SetDir(5);
   }
   if(!ext && cmd == 245) // § - key, warp mario 2 :)
   {
		if(Red.QueryPortal() > 0)
      {
      	for(int i = 0; i < 20; i++)
         {
         	sound(500);
            delay(10);
            nosound();
         }
      }
      else
      {
	      Red.UsePortal();
			Red.Erase();
     		for(int i = 30; i > 0; i--) /* warping */
	      {
				setcolor(myrand(15) + 1);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
   	      sound(i+300);
				delay(WARP_DELAY);
	         nosound();
   	   }
			for(int i = 0; i <= 30; i++)
   	   {
      	 	setcolor(0);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
   	      sound(i+300);
				delay(WARP_DELAY);
	         nosound();
   	   }
	      Red.SetX(myrand(MaxX) + 1);
   	   Red.SetY(myrand(MaxY) + 1);
	      for(int i = 0; i < 10; i++)
   	   {
				putpixel(10 + myrand(30) + Red.QueryX(), 10 + myrand(30) + Red.QueryY(), myrand(MaxColors-1)+1);
   	   }
	      Red.SetX(myrand(MaxX) + 1);
      	Red.SetY(myrand(MaxY) + 1);
	     	for(int i = 30; i > 0; i--) /* warping */
   	   {
				setcolor(myrand(15) + 1);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
   	      sound(i+300);
				delay(WARP_DELAY);
	         nosound();
   	   }
			for(int i = 0; i <= 30; i++)
   	   {
      	 	setcolor(0);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
   	      sound(i+300);
				delay(WARP_DELAY);
	         nosound();
   	   }
	      for(int i = 0; i < 10; i++)
   	   {
				putpixel(10 + myrand(30) + Red.QueryX(), 10 + myrand(30) + Red.QueryY(), myrand(MaxColors-1)+1);
	      }
   	   Red.Erase();
	   }
   }
   if(!ext && cmd == 8) // backspace, warp mario :)
   {
		if(Blue.QueryPortal() > 0)
      {
      	for(int i = 0; i < 20; i++)
         {
         	sound(500);
            delay(10);
            nosound();
         }
      }
      else
      {
	      Blue.UsePortal();
			Blue.Erase();
     		for(int i = 30; i > 0; i--) /* warping */
	      {
				setcolor(myrand(15) + 1);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
      	   nosound();
	      }
			for(int i = 0; i <= 30; i++)
      	{
	       	setcolor(0);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
      	   sound(i+300);
				delay(WARP_DELAY);
   	      nosound();
	      }
   	   for(int i = 0; i < 10; i++)
      	{
				putpixel(10 + myrand(30) + Blue.QueryX(), 10 + myrand(30) + Blue.QueryY(), myrand(MaxColors-1)+1);
		   }
      	Blue.SetX(myrand(MaxX) + 1);
	      Blue.SetY(myrand(MaxY) + 1);
   	  	for(int i = 30; i > 0; i--) /* warping */
      	{
				setcolor(myrand(15) + 1);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
      	   sound(i+300);
				delay(WARP_DELAY);
   	      nosound();
      	}
			for(int i = 0; i <= 30; i++)
   	   {
      	 	setcolor(0);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
	         nosound();
   	   }
	      Blue.Erase();
   	}
   }
	if(!cmd && ext == 75 || !ext && cmd == 52) // left arrow
   {
		Blue.SetDir(4);
	}
   if(!cmd && ext == 77 || !ext && cmd == 54) // right arrow
   {
		Blue.SetDir(6);
   }
   if(!cmd && ext == 72 || !ext && cmd == 56) // up arrow
   {
		Blue.SetDir(8);
   }
   if(!cmd && ext == 80 || !ext && cmd == 50) // down arrow
   {
		Blue.SetDir(2);
   }
   if(!cmd && ext == 71 || !ext && cmd == 55) // numpad 7
   {
   	Blue.SetDir(7);
   }
   if(!cmd && ext == 73 || !ext && cmd == 57) // numpad 9
   {
   	Blue.SetDir(9);
   }
   if(!cmd && ext == 79 || !ext && cmd == 49) // numpad 1
   {
   	Blue.SetDir(1);
   }
   if(!cmd && ext == 81 || !ext && cmd == 51) // numpad 3
   {
   	Blue.SetDir(3);
   }
	if(!cmd && ext == 76 || !ext && cmd == 53) // numpad 5, stop moving
   {
   	Blue.SetDir(5);
   }
	if(!ext && cmd == 97 || !ext && cmd == 65) // lower_case a
   {
		Red.SetDir(4);
   }
   if(!ext && cmd == 100 || !ext && cmd == 68) // lower_case d
   {
      Red.SetDir(6);
   }
   if(!ext && cmd == 119 || !ext && cmd == 87) // lower_case w
   {
   	Red.SetDir(8);
   }
   if(!ext && cmd == 115 || !ext && cmd == 83) // lower_case s
   {
   	Red.SetDir(5);
   }
   if(!ext && cmd == 113 || !ext && cmd == 81) // lower_case q
   {
   	Red.SetDir(7);
   }
   if(!ext && cmd == 101 || !ext && cmd == 69) // lower case e
   {
   	Red.SetDir(9);
   }
   if(!ext && cmd == 122 || !ext && cmd == 90) // lower_case z
   {
   	Red.SetDir(1);
   }
   if(!ext && cmd == 120 || !ext && cmd == 88) // lower_case x
   {
   	Red.SetDir(2);
   }
   if(!ext && cmd == 99  || !ext && cmd == 67) // lower_case c
   {
   	Red.SetDir(3);
   }
   if(!ext && cmd == 27) // esc key
   {
   	closegraph();
		textcolor(10);
      cprintf("\rNo winner.\n\r");
		cprintf("\rThank you for playing Galaxy War by Topi Mansikkaviita.\n\r");
      Blue.Destroy(); // freeing memory from objects
      Red.Destroy();
      Laser1.Destroy();
      Laser2.Destroy();
      exit(0);
   }
   while(!kbhit())
   {
		/* setting some objects borderies */
		Red.DecPortal();
      Blue.DecPortal();
		int chk_x = 0, chk_y = 0;
		chk_x = Blue.QueryX() - Red.QueryX();
      chk_y = Blue.QueryY() - Red.QueryY();
      if(chk_x < 0) chk_x *= -1;
      if(chk_y < 0) chk_y *= -1;
      if(chk_x < 20 && chk_y < 20)
      {
			Blue.Erase();
         Red.Erase();
      	for(int i = 30; i > 0; i--) /* warping paradox */
         {
				setcolor(myrand(15) + 1);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
				setcolor(myrand(15) + 1);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
            nosound();
         }
			for(int i = 0; i <= 30; i++)
         {
         	setcolor(0);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
            nosound();
	      }
	      for(int i = 0; i < 5; i++)
   	   {
				putpixel(10 + myrand(30) + Blue.QueryX(), 10 + myrand(30) + Blue.QueryY(), myrand(MaxColors-1)+1);
				putpixel(10 + myrand(30) + Red.QueryX(), 10 + myrand(30) + Red.QueryY(), myrand(MaxColors-1)+1);
	      }
         Blue.SetX(myrand(MaxX) + 1);
         Blue.SetY(myrand(MaxY) + 1);
         Red.SetX(myrand(MaxX) + 1);
         Red.SetY(myrand(MaxY) + 1);
      	for(int i = 30; i > 0; i--) /* warping paradox */
         {
				setcolor(myrand(15) + 1);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
				setcolor(myrand(15) + 1);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
            nosound();
         }
			for(int i = 0; i <= 30; i++)
         {
         	setcolor(0);
				circle(Blue.QueryX()+20, Blue.QueryY()+20, i);
				circle(Red.QueryX()+20, Red.QueryY()+20, i);
	         sound(i+300);
				delay(WARP_DELAY);
            nosound();
         }
         Blue.Erase();
         Red.Erase();
      }
      /* checking lasers */
      chk_x = Red.QueryX() - Laser1.QueryX();
      chk_y = Red.QueryY() - Laser1.QueryY();
      if(chk_x < 0) chk_x *= -1;
      if(chk_y < 0) chk_y *= -1;
      if(chk_x < 15 && chk_y < 15)
      {
			for(int i = 0; i < 20; i++)
   	   {
				sound(500 + (i * 100));
	   	   delay(LASER_DELAY);
   	      nosound();
      	}
			closegraph();
         textcolor(10);
         cprintf("\rBlue player wins.\n\r");
			cprintf("\rThank you for playing Galaxy War by Topi Mansikkaviita.\n\r");
         Blue.Destroy(); // freeing memory from objects
         Red.Destroy();
         Laser1.Destroy();
         Laser2.Destroy();
         exit(0);
      }
      chk_x = Blue.QueryX() - Laser2.QueryX();
		chk_y = Blue.QueryY() - Laser2.QueryY();
      if(chk_x < 0) chk_x *= -1;
      if(chk_y < 0) chk_y *= -1;
      if(chk_x < 15 && chk_y < 15)
      {
			for(int i = 0; i < 20; i++)
   	   {
				sound(500 + (i * 100));
	   	   delay(LASER_DELAY);
   	      nosound();
      	}
			closegraph();
         textcolor(10);
         cprintf("\rRed player wins.\n\r");
			cprintf("\rThank you for playing Galaxy War by Topi Mansikkaviita.\n\r");
         Blue.Destroy(); // freeing memory from objects
         Red.Destroy();
         Laser1.Destroy();
         Laser2.Destroy();
         exit(0);
      }
   	Blue.Erase();
		switch(Blue.QueryDir())
      {
      	case 1: Blue.Move(-10, 10); break;
         case 2: Blue.Move(0, 10); break;
         case 3: Blue.Move(10, 10); break;
         case 4: Blue.Move(-10, 0); break;
         case 5: Blue.Move(0, 0); break;
         case 6: Blue.Move(10, 0); break;
         case 7: Blue.Move(-10, -10); break;
         case 8: Blue.Move(0, -10); break;
         case 9: Blue.Move(10, -10); break;
      }
      Red.Erase();
		switch(Red.QueryDir())
      {
      	case 1: Red.Move(-10, 10); break;
         case 2: Red.Move(0, 10); break;
         case 3: Red.Move(10, 10); break;
         case 4: Red.Move(-10, 0); break;
         case 5: Red.Move(0, 0); break;
         case 6: Red.Move(10, 0); break;
         case 7: Red.Move(-10, -10); break;
         case 8: Red.Move(0, -10); break;
         case 9: Red.Move(10, -10); break;
      }
      switch(Laser1.QueryDir())
      {
      	case 1: Laser1.Move(-35, 35); break;
         case 2: Laser1.Move(0, 35); break;
         case 3: Laser1.Move(35, 35); break;
         case 4: Laser1.Move(-35, 0); break;
         case 6: Laser1.Move(35, 0); break;
         case 7: Laser1.Move(-35, -35); break;
         case 8: Laser1.Move(0, -35); break;
         case 9: Laser1.Move(35, -35); break;
      }
      switch(Laser2.QueryDir())
      {
      	case 1: Laser2.Move(-35, 35); break;
         case 2: Laser2.Move(0, 35); break;
         case 3: Laser2.Move(35, 35); break;
         case 4: Laser2.Move(-35, 0); break;
         case 6: Laser2.Move(35, 0); break;
         case 7: Laser2.Move(-35, -35); break;
         case 8: Laser2.Move(0, -35); break;
         case 9: Laser2.Move(35, -35); break;
      }
   }
   return 0;
}

int main(int argc, char *argv[])
{
	int errorcode = 0;
   errorcode = registerbgidriver(EGAVGA_driver);

   /* report any registration errors */
   if (errorcode < 0)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      exit(1);
   }
   if(argc < 2)
   {
		UFO_DELAY = 30;
      LASER_DELAY = UFO_DELAY / 2;
      WARP_DELAY = LASER_DELAY;
   }
   if(argv[1])
   {
   	UFO_DELAY = 100 - atoi(argv[1]);
      LASER_DELAY = UFO_DELAY / 2;
      WARP_DELAY = LASER_DELAY;
   }
   if(UFO_DELAY < 0 || UFO_DELAY > 100)
   {
   	printf("Speed must be between 0-100.\n");
      return 0;
   }
	Initialize();
   struct viewporttype vp;
   getviewsettings(&vp);
	Format = false; // checking if objects are formatted
	for(;;) Game();
}
