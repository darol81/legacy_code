#ifdef __TINY__
#error PICDRAW will not run in the tiny model.
#endif

#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <graphics.h>

#define ESC     0x1b                    /* Define the escape key        */
#define CTRL(X)       ((X) & 0x1F)      /* CTRL characters              */
#define bool int
#define TRUE 1
#define FALSE 0
#define PIC_SIZE 40

int    GraphDriver;             /* The Graphics device driver           */
int    GraphMode;               /* The Graphics mode value              */
double AspectRatio;             /* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;              /* The maximum resolution of the screen */
int    MaxColors;               /* The maximum # of colors available    */
int    ErrorCode;               /* Reports any graphics errors          */

const int HORIZONTAL = 200;
const int VERTICAL = 100;

struct palettetype palette;             /* Used to read palette info    */

struct global_variables
{
 int x, y, color;
 bool line, quit; /* line/dot mode */
} glob;

struct savefile
{
  int pixel[PIC_SIZE][PIC_SIZE];
} pic;

struct savefile read_savefile(char filename[256])
{
   struct savefile tmp;
   FILE *fil;
   fil=fopen(filename,"rb");
   if(!fil)
   {
     printf("Opening savefile (%s) failed.\n",filename);
     exit(1);
   }
   if(fread(&tmp,sizeof(struct savefile),1,fil)==0)
   {
     printf("Savefile empty (%s).\n",filename);
     exit(1);
   }
   fclose(fil);
   return tmp;
}

int write_savefile(char filename[256],struct savefile tmp)
{
  FILE *fil;
  fil=fopen(filename,"wb");
  if(!fil)
  {
    printf("Opening savefile (%s) failed.\n",filename);
    exit(1);
  }
  fwrite(&tmp, sizeof(tmp),1,fil);
  fclose(fil);
  return 0;
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

void Border(void)
{
  struct viewporttype vp;

  setcolor(15);            /* Set current color to white   */
  getviewsettings(&vp);
  rectangle(200, 100, 200+PIC_SIZE, 100+PIC_SIZE);
}


void ColorUsed(int col)
{
  setfillstyle(SOLID_FILL, 0); 
  bar(100, 200, 600, 215);
  setcolor(14);
  setfillstyle(SOLID_FILL, 14); 
  circle(110+(col*30), 210, 5);
  if(glob.line == TRUE) fillellipse(110+(col*30), 210, 5, 5);
}

void ColorBar(void)
{
  int next = 0, i = 0;
  do
  {
    setfillstyle(SOLID_FILL, i);  /* Set to solid fill in color   */
    if(i == 0)
    {
      setcolor(15);
      rectangle(100+next, 220, 120+next, 240);
    }
    else
    {
      bar(100+next, 220, 120+next, 240);
    }
    next += 30;
    i++;
  } while(i <= 15);
}

int ShowPixels(void)
{
  int x = 1, y = 1;
  do
  {
    for(x = 1; x < PIC_SIZE; x++)
    {
      putpixel(x+HORIZONTAL, y+VERTICAL, pic.pixel[x][y]);     
    }
    y++;
  } while(y < PIC_SIZE);
  return 0;
}

int Draw(void)
{
  /* Border control */
  if(glob.x > 199 + PIC_SIZE) glob.x = 199 + PIC_SIZE;
  if(glob.x < 201) glob.x = 201;
  if(glob.y > 99 + PIC_SIZE) glob.y = 99 + PIC_SIZE;
  if(glob.y < 101) glob.y = 101;
  return 0;
}

void ToolBar(void)
{
  char cmd, extended;
  cmd = 0; extended = 0;
  setcolor(15);
  outtextxy(300, 30,  "Commands");
  outtextxy(300, 50,  "F1       - Change color");
  outtextxy(300, 70,  "F2       - Clear previous");
  outtextxy(300, 90,  "F3       - Save pic");
  outtextxy(300, 110, "F4       - Load pic");
  outtextxy(300, 130, "F5       - Drawing mode (dot/line)");
  outtextxy(300, 150, "F6       - Select as background color");
  outtextxy(300, 170, "CTRL+Q   - Quit program");
  ColorBar();
  ColorUsed(glob.color);
  cmd = getch();
  if(!cmd)
    extended = getch();
  putpixel(glob.x, glob.y, 0);
  ShowPixels();
  if(!cmd && extended == ';')
  {
    glob.color++;
    if(glob.color > 15) glob.color = 0;
  }
  if(!cmd && extended == '<') // F2
  {
    pic = read_savefile("clear.pic");
    ShowPixels();
    Border();
  }
  if(!cmd && extended == '=') // F3
  {
    write_savefile("image.pic", pic);
  }
  if(!cmd && extended == '>') // F4
  {
    pic = read_savefile("image.pic");
    ShowPixels();
    Border();
  }
  if(!cmd && extended == '?') // F5
  {
    if(glob.line == FALSE)
      glob.line = TRUE;
    else
      glob.line = FALSE;
  }
  if(!cmd && extended == '@') // F6
  {
   
    int y = 0, x = 0;
    do
    {
      for(x = 0; x < PIC_SIZE; x++)
      {
        pic.pixel[x][y] = glob.color;
      }
      y++;
    } while(y < PIC_SIZE);
    setfillstyle(SOLID_FILL, glob.color);
    floodfill(glob.x, glob.y, 15);
  }
  if(!cmd && extended == 'K') // left arrow
  {
    glob.x--;
    Draw();
  }
  if(!cmd && extended == 'H') // up arrow
  {
    glob.y--;
    Draw();
  }
  if(!cmd && extended == 'M') // right arrow
  {
    glob.x++;
    Draw();
  }
  if(!cmd && extended == 'P') // down arrow
  {
    glob.y++;
    Draw();
  }
  if(!cmd && extended == 'G') // numpad 7
  {
    glob.x--;
    glob.y--;
    Draw();
  }
  if(!cmd && extended == 'I') // numpad 9
  {
    glob.x++;
    glob.y--;
    Draw();
  }
  if(!cmd && extended == 'O') // numpad 1
  {
    glob.x--;
    glob.y++;
    Draw();
  }
  if(!cmd && extended == 'Q') // numpad 3
  {
    glob.x++;
    glob.y++;
    Draw();
  }
  if(cmd == 13) // enter
  {
    pic.pixel[(glob.x-HORIZONTAL)][(glob.y-VERTICAL)] = glob.color;
  }
  if(cmd == CTRL('Q'))
  {
    glob.quit = TRUE;
  }

  /* If drawing lines, then setting pixel to every place */
  
  if(glob.line == TRUE)
  {
    pic.pixel[(glob.x-HORIZONTAL)][(glob.y-VERTICAL)] = glob.color;
  }

  if(glob.color == 0)
  {
    putpixel(glob.x, glob.y, 15);
  }
  else
  {
    putpixel(glob.x, glob.y, glob.color);
  }
  return;
}

int main()
{
  glob.color = 15;
  glob.x = 220;
  glob.y = 120;
  glob.x = 200 + PIC_SIZE / 2;
  glob.y = 100 + PIC_SIZE / 2;
  Initialize();                 /* Set system into Graphics mode        */
  Border();
  do
  {
    ToolBar();
  } while(glob.quit == FALSE);
  closegraph();                 /* Return the system to text mode       */
  return(0);
}

