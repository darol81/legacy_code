/* Pawn = sotilas, rook = torni, knight = ratsu, bishop = lähetti, queen, king */

#ifdef __TINY__
#error Chess cannot be compiled in TINY model!
#endif

#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#define COORD_X 				150		/* Starting coordinate for X 			*/
#define COORD_Y 				75			/* Starting coordinate for Y 			*/
#define SQUARE_SIZE 			30			/* Square size in pixels, 30 * 30 	*/
#define SQUARES 				8			/* Squares on board, 8 * 8 = 64		*/
#define PIC_SIZE				20			/* Size of SAVED pics				 	*/
#define WHITE_PLAYER			1
#define BLACK_PLAYER			0
#define WHITE_PAWN 			1
#define WHITE_ROOK			2
#define WHITE_KNIGHT			3
#define WHITE_BISHOP			4
#define WHITE_KING	  		5
#define WHITE_QUEEN			6
#define BLACK_PAWN 			7
#define BLACK_ROOK			8
#define BLACK_KNIGHT			9
#define BLACK_BISHOP			10
#define BLACK_KING 			11
#define BLACK_QUEEN			12

class Obj
{
	private:
		int pixel[PIC_SIZE][PIC_SIZE];
		int ulx, uly, lrx, lry, size;
      void *Image;
   public:
		void ReadObject();
		void SavePixels(char *file);
		void Convert(bool ob_color, int square_color);
		void Show(int count_x, int count_y);
      void Destroy() { free(Image); }
};

struct savefile
{
	int pixel[PIC_SIZE][PIC_SIZE];
} pic;

struct chessboard
{
	int slot[SQUARES][SQUARES];
   int start[2], end[2];
} board;

struct chessboard read_board(char filename[30])
{
	struct chessboard tmp;
	FILE *fil;
   fil = fopen(filename, "rb");
   if(!fil)
   {
   	closegraph();
   	printf("Cannot open %s to read.\n", filename);
      exit(1);
   }
   if(fread(&tmp, sizeof(struct chessboard), 1, fil) == 0)
   {
   	closegraph();
   	printf("File %s empty or invalid!\n", filename);
      exit(1);
   }
   fclose(fil);
   return tmp;
}

int write_board(char filename[80], struct chessboard tmp)
{
	FILE *fil;
   fil = fopen(filename, "wb");
   if(!fil)
   {
   	closegraph();
      printf("Cannot open %s to write.\n", filename);
      exit(1);
   }
   fwrite(&tmp, sizeof(tmp), 1, fil);
   fclose(fil);
   return 0;
}

void InitGraphics()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();

   if(errorcode != grOk)    /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      exit(1);
   }
}

struct savefile read_savefile(char filename[30])
{
	struct savefile tmp;
	FILE *fil;
   fil = fopen(filename, "rb");
   if(!fil)
   {
   	printf("Cannot open %s to read.\n", filename);
      exit(1);
   }
   if(fread(&tmp, sizeof(struct savefile), 1, fil) == 0)
   {
   	printf("File %s empty or invalid!\n", filename);
      exit(1);
   }
   fclose(fil);
   return tmp;
}

void Clear()
{
	setfillstyle(SOLID_FILL, 0);
	bar(COORD_X + SQUARES * SQUARE_SIZE + 90, COORD_Y, COORD_X + SQUARES * SQUARE_SIZE + 280, COORD_Y + 20);
	bar(COORD_X + SQUARES * SQUARE_SIZE + 40, COORD_Y + 30, COORD_X + SQUARES * SQUARE_SIZE + 280, COORD_Y + 50);
}

void Promote(int x, int y, bool color)
{
	char c = 0;
	setcolor(15);
	if(color == WHITE_PLAYER)
   {
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 40, "Promote to?");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 70, "1 - Knight");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 90, "2 - Bishop");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 110, "3 - Rook");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 130, "4 - Queen");
      while(c < 49 || c > 52)
      {
			c = getch();
      }
      switch(c)
      {
      	case '1': board.slot[x][y] = WHITE_KNIGHT; break;
         case '2': board.slot[x][y] = WHITE_BISHOP; break;
         case '3': board.slot[x][y] = WHITE_ROOK; break;
         default : board.slot[x][y] = WHITE_QUEEN; break;
      }
   }
	if(color == BLACK_PLAYER)
   {
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 40, "Promote to?");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 70, "1 - Knight");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 90, "2 - Bishop");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 110, "3 - Rook");
		outtextxy(COORD_X, COORD_Y + (SQUARE_SIZE * SQUARES) + 130, "4 - Queen");
      while(c < 49 || c > 52)
      {
			c = getch();
      }
      switch(c)
      {
      	case '1': board.slot[x][y] = BLACK_KNIGHT; break;
         case '2': board.slot[x][y] = BLACK_BISHOP; break;
         case '3': board.slot[x][y] = BLACK_ROOK; break;
         default : board.slot[x][y] = BLACK_QUEEN; break;
      }
   }
   setfillstyle(SOLID_FILL, 0);
   bar(COORD_X - 10, COORD_Y - 20, COORD_X + 150, COORD_Y + (SQUARE_SIZE * SQUARES) + 150); 
}

void StatusScreen(bool turn, bool white_check, bool black_check)
{
	setfillstyle(SOLID_FILL, 0);
	bar(COORD_X - 150, COORD_Y, COORD_X - 30, COORD_Y + 70);
	setcolor(15);
   if(turn == WHITE_PLAYER)
	   outtextxy(COORD_X - 140, COORD_Y + 20, "Turn: White");
   else
	   outtextxy(COORD_X - 140, COORD_Y + 20, "Turn: Black");
   if(white_check == true)
   {
   	outtextxy(COORD_X - 140, COORD_Y + 40, "White: CHECK!");
   }
   if(black_check == true)
   {
   	outtextxy(COORD_X - 140, COORD_Y + 40, "Black: CHECK!");
   }
}

void DrawChessBoard()
{
	int counter = 0, color = 0, y = 0;
   char temp[2] = "";
	/* Creating chessboard */
   for(counter = 0; counter <= SQUARES; counter++)
   {
		/* vertical lines */
   	moveto(COORD_X + counter * SQUARE_SIZE, COORD_Y);
      lineto(COORD_X + counter * SQUARE_SIZE, COORD_Y + SQUARES * SQUARE_SIZE);
		/* horizontal lines */
   	moveto(COORD_X, COORD_Y + counter * SQUARE_SIZE);
      lineto(COORD_X + SQUARES * SQUARE_SIZE, COORD_Y + counter * SQUARE_SIZE);
   }
	/* Printing letters to show which square is equal to each letter */
	for(counter = 1; counter <= SQUARES; counter++)
   {
		strcpy(temp, "");
   	temp[0] = (char)counter + 64; // 65 is ascii value for 'A'
      outtextxy(COORD_X - (SQUARE_SIZE / 2) + counter * SQUARE_SIZE, COORD_Y - (SQUARE_SIZE / 2), temp);
		outtextxy(COORD_X - (SQUARE_SIZE / 2) + counter * SQUARE_SIZE, COORD_Y + (SQUARE_SIZE / 2) + SQUARES * SQUARE_SIZE, temp);  
   }
	/* Printing equivalent numbers */
   for(counter = 1; counter <= SQUARES; counter++)
   {
   	itoa((SQUARES + 1 - counter), temp, 10); // reverse order
	   outtextxy(COORD_X - (SQUARE_SIZE / 2), COORD_Y - (SQUARE_SIZE / 2) + (counter * SQUARE_SIZE), temp);
      outtextxy(COORD_X + (SQUARE_SIZE / 2) + SQUARE_SIZE * SQUARES, COORD_Y - (SQUARE_SIZE / 2) + (counter * SQUARE_SIZE), temp);
   }
   /* Coloring grid by floodfilling by yellow/blue */
	color = 14;
   y = COORD_Y + SQUARE_SIZE / 2;
	do
   {
		for(counter = COORD_X + SQUARE_SIZE / 2; counter < (COORD_X + SQUARES * SQUARE_SIZE); counter += SQUARE_SIZE)
   	{
	   	setcolor(color);
		   setfillstyle(SOLID_FILL, color);
			floodfill(counter, y, 15);
         if(color == 14)
         	color = 1;    // blue
         else
         	color = 14;   // yellow
	   }
      /* This must also be in here, otherwise the color won't change when
      	moving in Y sector */
      if(color == 14)
       	color = 1;    // blue
      else
        	color = 14;   // yellow
      y += SQUARE_SIZE;
   } while(y < (COORD_Y + SQUARES * SQUARE_SIZE));
}

void Obj::ReadObject()
{
	int _x = 0, _y = 0;
	ulx = 0;
   uly = 0;
	lrx = PIC_SIZE - 1;
   lry = PIC_SIZE - 1;
	do
   {
		for(_x = 0; _x < PIC_SIZE; _x++)
   	{
         putpixel(_x, _y, pixel[_x][_y]);
	   }
      _y++;
   } while(_y < PIC_SIZE);
   size = imagesize(ulx, uly, lrx, lry);
   Image = malloc(size);
   getimage(ulx, uly, lrx, lry, Image);
   putimage(ulx, uly, Image, XOR_PUT);
}

void Obj::Convert(bool ob_color, int square_color)
{
	int _x = 0, _y = 0;
	do
   {
		for(_x = 0; _x < PIC_SIZE; _x++)
   	{
         if(pixel[_x][_y] == 10) /* the default color of drawn object */
         {
         	if(ob_color == WHITE_PLAYER)
            	pixel[_x][_y] = 13;
            else
            	pixel[_x][_y] = 0;
         }
         if(pixel[_x][_y] == 4) /* default background color of drawn object */
         {
         	pixel[_x][_y] = square_color;
         }
	   }
      _y++;
   } while(_y < PIC_SIZE);
}

void Obj::SavePixels(char *file)
{
	int _x = 0, _y = 0;
	pic = read_savefile(file);
	do
   {
		for(_x = 0; _x < PIC_SIZE; _x++)
   	{
			pixel[_x][_y] = pic.pixel[_x][_y];
	   }
      _y++;
   } while(_y < PIC_SIZE);
}

void Obj::Show(int count_x, int count_y)
{
	int var_x = 0, var_y = 0;
   var_x = COORD_X + (count_x * SQUARE_SIZE) + SQUARE_SIZE / 6;
   var_y = COORD_Y + (count_y * SQUARE_SIZE) + SQUARE_SIZE / 6;
   setfillstyle(SOLID_FILL, 0);
   bar(var_x, var_y, var_x + PIC_SIZE - 1, var_y + PIC_SIZE - 1);
	putimage(var_x, var_y, Image, XOR_PUT);
}

void UpdateBoard() // updates all objects to the chessboard
{
	Obj Chess_OB;
	int _x = 0, _y = 0, square_color = 0;
	do
	{
		for(_x = 0; _x < SQUARES; _x++)
   	{
			if(board.slot[_x][_y] == WHITE_PAWN)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("pawn.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == WHITE_ROOK)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("rook.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == WHITE_KNIGHT)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("knight.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == WHITE_BISHOP)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("bishop.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == WHITE_KING)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("king.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == WHITE_QUEEN)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("queen.ch");
            Chess_OB.Convert(WHITE_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_PAWN)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("pawn.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_ROOK)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("rook.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_KNIGHT)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("knight.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_BISHOP)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("bishop.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_KING)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("king.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
			if(board.slot[_x][_y] == BLACK_QUEEN)
         {
         	square_color = (_x % 2) == (_y % 2) ? 14 : 1;
            Chess_OB.SavePixels("queen.ch");
            Chess_OB.Convert(BLACK_PLAYER, square_color);
            Chess_OB.ReadObject();
            Chess_OB.Show(_x, _y);
            Chess_OB.Destroy();
      	}
	   }
      _y++;
   } while(_y < SQUARES);
}

void ResetObjects()
{
	int i = 0, y = 0;
	/* Complete resetting of objects */
	while(y < 8)
   {
		for(i = 0; i < 8; i++)
      {
      	board.slot[i][y] = 0;
      }
      y++;
   }
   /* Setting pawns */
   for(i = 0; i < 8; i++)
   {
   	board.slot[i][6] = WHITE_PAWN; // white pawns
	   board.slot[i][1] = BLACK_PAWN; // black pawns
   }
	/* white objects */
	board.slot[0][7] = WHITE_ROOK;
   board.slot[1][7] = WHITE_KNIGHT;
   board.slot[2][7] = WHITE_BISHOP;
   board.slot[3][7] = WHITE_QUEEN;
   board.slot[4][7] = WHITE_KING;
   board.slot[5][7] = WHITE_BISHOP;
   board.slot[6][7] = WHITE_KNIGHT;
   board.slot[7][7] = WHITE_ROOK;
   /* black objects */
	board.slot[0][0] = BLACK_ROOK;
   board.slot[1][0] = BLACK_KNIGHT;
   board.slot[2][0] = BLACK_BISHOP;
   board.slot[3][0] = BLACK_QUEEN;
   board.slot[4][0] = BLACK_KING;
   board.slot[5][0] = BLACK_BISHOP;
   board.slot[6][0] = BLACK_KNIGHT;
   board.slot[7][0] = BLACK_ROOK; 
}

int Move()
{
	char from[20], to[20], temp[20];
   char c;
	int counter = 0, start[2], end[2];
   bool valid = true; // checking if given coordinates are valid
	setcolor(15);
	/* Setting: FROM */
	outtextxy(COORD_X + SQUARES * SQUARE_SIZE + 50, COORD_Y, "From: ");
   do
   {
      c = getch();
      if(c == 27)
      {
      	closegraph();
      	exit(0);
      }
      if((counter < 2 && c == 13) || (c == 8)) // backspace
      {
      	if(c != 8) Clear();
         strcpy(from, "            ");
         strcpy(temp, "       ");
         counter = 0;
         setfillstyle(SOLID_FILL, 0);
         bar(COORD_X + SQUARES * SQUARE_SIZE + 90, COORD_Y, COORD_X + SQUARES * SQUARE_SIZE + 280, COORD_Y + 20);
      }
      if(c != 13 && c != 8) // no enter nor backslash -> setting var -> from
      {
         temp[counter] = c;
         counter++;
         strcpy(from, "            ");
         from[1] = c;
         outtextxy(COORD_X + SQUARES * SQUARE_SIZE + 80 + counter * 8, COORD_Y, from);
      }
   } while(c != 13 || counter < 2);
   if(counter > 2) counter = 2; // only two letters when giving coordinates
   strncpy(from, temp, counter);
	/* Setting: TO */
   strcpy(temp, "");
   counter = 0;
	outtextxy(COORD_X + SQUARES * SQUARE_SIZE + 50, COORD_Y + 30, "To: ");
   do
   {
      c = getch();
      if(c == 27)
      {
      	closegraph();
      	exit(0);
      }
      if((counter < 2 && c == 13) || (c == 8)) // backspace
      {
      	if(c != 8) Clear();
         strcpy(to, "            ");
         strcpy(temp, "       ");
         counter = 0;
         setfillstyle(SOLID_FILL, 0);
         bar(COORD_X + SQUARES * SQUARE_SIZE + 90, COORD_Y + 30, COORD_X + SQUARES * SQUARE_SIZE + 280, COORD_Y + 50);
      }
      if(c != 13 && c != 8) // no enter nor backslash -> setting var -> to
      {
         temp[counter] = c;
         counter++;
         strcpy(to, "            ");
         to[1] = c;
         outtextxy(COORD_X + SQUARES * SQUARE_SIZE + 80 + counter * 8, COORD_Y + 30, to);
      }
   } while(c != 13 || counter < 2);
   if(counter > 2) counter = 2; // only two letters when giving coordinates
   strncpy(to, temp, counter);
   from[0] = toupper(from[0]); // capitalized
   to[0] = toupper(to[0]);
   strcpy(temp, "   ");
	/* Checking if coordinates are valid, should be in form: (char) & (int) */
	if(from[0] < 'A' || from[0] > 'H') valid = false;
	if(to[0] < 'A' || to[0] > 'H') valid = false;
   temp[0] = from[1]; // using temp 'coz cant atoi singular char
   if(atoi(temp) < 1 || atoi(temp) > 8) valid = false;
   strcpy(temp, "   ");
	temp[0] = to[1];
   if(atoi(temp) < 1 || atoi(temp) > 8) valid = false;

   if(valid == false) { Clear(); return valid; } // If not valid values, return!

	/* continueing with good values */
   start[0] = (int)from[0] - 65; // 65 is ascii value for 'A'
	temp[0] = from[1];
	start[1] = atoi(temp);
   end[0] = (int)to[0] - 65;
   temp[0] = to[1];
   end[1] = atoi(temp);
   /* Now we have start[2] and end[2] that we can use to check if the moves
   	are valid, putting them to struct */
   board.start[0] = start[0]; // coordinates for first location
   board.start[1] = 8 - start[1];
   board.end[0] = end[0]; 		// destination of move
   board.end[1] = 8 - end[1];
   return true;
}

bool WHITE_OBJECT()
{
	if(board.slot[board.end[0]][board.end[1]] != 0 && board.slot[board.end[0]][board.end[1]] < 7)
   	return true;
   else
   	return false;
}

bool BLACK_OBJECT()
{
	if(board.slot[board.end[0]][board.end[1]] > 6 && board.slot[board.end[0]][board.end[1]] < 13)
   	return true;
   else
   	return false;
}

int QueryCheck(int x, int y, bool color) // using king's coordinates in here
{
	int i = 0, ob = 0; // first object found from direction
	bool stop_loop = false;
	if(color == WHITE_PLAYER) // white king used
	{
		/* king exceptions listed, 8 choices */
		/* != 0 and != 7 checks are used to keep kings on borders */
		if(x != 0 && y != 0 && board.slot[x - 1][y - 1] == BLACK_KING) return 1;
  	   if(y != 0 && board.slot[x][y - 1] == BLACK_KING) return 1;
		if(x != 7 && y != 0 && board.slot[x + 1][y - 1] == BLACK_KING) return 1;

		if(x != 0 && board.slot[x - 1][y] == BLACK_KING) return 1;
		if(x != 7 && board.slot[x + 1][y] == BLACK_KING) return 1;

		if(x != 0 && y != 7 && board.slot[x - 1][y + 1] == BLACK_KING) return 1; // possible located bug!
      if(y != 7 && board.slot[x][y + 1] == BLACK_KING) return 1;
		if(x != 7 && y != 7 && board.slot[x + 1][y + 1] == BLACK_KING) return 1;

		/* pawn exceptions listed, 2 choices */
		if(x != 0 && board.slot[x - 1][y - 1] == BLACK_PAWN) return 1;
		if(x != 0 && board.slot[x + 1][y - 1] == BLACK_PAWN) return 1;

      /* knight exceptions listed, 8 choices */
		if(x > 1 && y != 0 && board.slot[x - 2][y - 1] == BLACK_KNIGHT) return 1;
      if(x > 1 && y != 7 && board.slot[x - 2][y + 1] == BLACK_KNIGHT) return 1;
      if(x < 6 && y != 0 && board.slot[x + 2][y - 1] == BLACK_KNIGHT) return 1;
      if(x < 6 && y != 7 && board.slot[x + 2][y + 1] == BLACK_KNIGHT) return 1;
		if(x != 0 && y > 1 && board.slot[x - 1][y - 2] == BLACK_KNIGHT) return 1;
      if(x != 0 && y < 6 && board.slot[x - 1][y + 2] == BLACK_KNIGHT) return 1;
      if(x != 7 && y > 1 && board.slot[x + 1][y - 2] == BLACK_KNIGHT) return 1;
      if(x != 7 && y < 6 && board.slot[x + 1][y + 2] == BLACK_KNIGHT) return 1;

      /* OWN PARSE CODE FOR BISHOPS, ROOKS, AND QUEENS (BELOW) */

   	/* checking up/left direction for check */
      ob = 0; i = 0;
      stop_loop = false;  
		do
      {
      	i++;
         ob = board.slot[x - i][y - i];
         if(ob != 0 && ob != BLACK_BISHOP && ob != BLACK_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_BISHOP || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking up/right direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y - i];
         if(ob != 0 && ob != BLACK_BISHOP && ob != BLACK_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_BISHOP || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down/right direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y + i];
         if(ob != 0 && ob != BLACK_BISHOP && ob != BLACK_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_BISHOP || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down/left direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x - i][y + i];
         if(ob != 0 && ob != BLACK_BISHOP && ob != BLACK_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_BISHOP || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking up direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x][y - i];
         if(ob != 0 && ob != BLACK_ROOK && ob != BLACK_QUEEN) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_ROOK || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x][y + i];
         if(ob != 0 && ob != BLACK_ROOK && ob != BLACK_QUEEN) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_ROOK || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking west direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x - i][y];
         if(ob != 0 && ob != BLACK_ROOK && ob != BLACK_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_ROOK || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking east direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y];
         if(ob != 0 && ob != BLACK_ROOK && ob != BLACK_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == BLACK_ROOK || ob == BLACK_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   }
	if(color == BLACK_PLAYER) // black king used
	{
		/* king exceptions listed, 8 choices */
		/* != 0 and != 7 checks are used to keep kings on borders */
		if(x != 0 && y != 0 && board.slot[x - 1][y - 1] == WHITE_KING) return 1;
  	   if(y != 0 && board.slot[x][y - 1] == WHITE_KING) return 1;
		if(x != 7 && y != 0 && board.slot[x + 1][y - 1] == WHITE_KING) return 1;

		if(x != 0 && board.slot[x - 1][y] == WHITE_KING) return 1;
		if(x != 7 && board.slot[x + 1][y] == WHITE_KING) return 1;

		if(x != 0 && y != 7 && board.slot[x - 1][y + 1] == WHITE_KING) return 1; // possibly located bug
      if(y != 7 && board.slot[x][y + 1] == WHITE_KING) return 1;
		if(x != 7 && y != 7 && board.slot[x + 1][y + 1] == WHITE_KING) return 1;

		/* pawn exceptions listed, 2 choices */
		if(x != 0 && board.slot[x - 1][y + 1] == WHITE_PAWN) return 1;
		if(x != 0 && board.slot[x + 1][y + 1] == WHITE_PAWN) return 1;

      /* knight exceptions listed, 8 choices */
		if(x > 1 && y != 0 && board.slot[x - 2][y - 1] == WHITE_KNIGHT) return 1;
      if(x > 1 && y != 7 && board.slot[x - 2][y + 1] == WHITE_KNIGHT) return 1;
      if(x < 6 && y != 0 && board.slot[x + 2][y - 1] == WHITE_KNIGHT) return 1;
      if(x < 6 && y != 7 && board.slot[x + 2][y + 1] == WHITE_KNIGHT) return 1;
		if(x != 0 && y > 1 && board.slot[x - 1][y - 2] == WHITE_KNIGHT) return 1;
      if(x != 0 && y < 6 && board.slot[x - 1][y + 2] == WHITE_KNIGHT) return 1;
      if(x != 7 && y > 1 && board.slot[x + 1][y - 2] == WHITE_KNIGHT) return 1;
      if(x != 7 && y < 6 && board.slot[x + 1][y + 2] == WHITE_KNIGHT) return 1;

      /* OWN PARSE CODE FOR BISHOPS, ROOKS, AND QUEENS (BELOW) */

   	/* checking up/left direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x - i][y - i];
         if(ob != 0 && ob != WHITE_BISHOP && ob != WHITE_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_BISHOP || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking up/right direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y - i];
         if(ob != 0 && ob != WHITE_BISHOP && ob != WHITE_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_BISHOP || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down/right direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y + i];
         if(ob != 0 && ob != WHITE_BISHOP && ob != WHITE_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_BISHOP || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down/left direction for check */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x - i][y + i];
         if(ob != 0 && ob != WHITE_BISHOP && ob != WHITE_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_BISHOP || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking up direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x][y - i];
         if(ob != 0 && ob != WHITE_ROOK && ob != WHITE_QUEEN) stop_loop = true;
         if((y - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_ROOK || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking down direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x][y + i];
         if(ob != 0 && ob != WHITE_ROOK && ob != WHITE_QUEEN) stop_loop = true;
         if((y + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_ROOK || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking west direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x - i][y];
         if(ob != 0 && ob != WHITE_ROOK && ob != WHITE_QUEEN) stop_loop = true;
         if((x - i) < 0) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_ROOK || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   	/* checking east direction */
      ob = 0; i = 0;
      stop_loop = false;
		do
      {
      	i++;
         ob = board.slot[x + i][y];
         if(ob != 0 && ob != WHITE_ROOK && ob != WHITE_QUEEN) stop_loop = true;
         if((x + i) > 7) stop_loop = true;
         if(stop_loop != true && (ob == WHITE_ROOK || ob == WHITE_QUEEN)) return 1; // check!
      } while(stop_loop == false);
   }
	return 0; // return 0 if not check! (else check)
}

int QueryCheckMate(int x, int y, bool color) // using king's coordinates in here
{
	int check_count = 0;
	/* Checking king coordinates and its surroundings */
	if(QueryCheck(x - 1, y - 1, color) == 1) check_count++;
	if(QueryCheck(x - 1, y + 1, color) == 1) check_count++;
	if(QueryCheck(x - 1, y, color) == 1) check_count++;
	if(QueryCheck(x, y - 1, color) == 1) check_count++;
	if(QueryCheck(x, y + 1, color) == 1) check_count++;
	if(QueryCheck(x, y, color) == 1) check_count++;
	if(QueryCheck(x + 1, y - 1, color) == 1) check_count++;
	if(QueryCheck(x + 1, y + 1, color) == 1) check_count++;
	if(QueryCheck(x + 1, y, color) == 1) check_count++;
   if(check_count < 9) return 0; // under 9 isn't qualified as checkmate
}

int CheckValidity(bool turn)
{
	/* Checking that starting slot and after-move slot isn't same! */
	if(board.start[0] == board.end[0] && board.start[1] == board.end[1]) return 1;

	/* Finding out what kind of objects exists in slot */

	if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_KING)
   {
   	int x_dif = 0, y_dif = 0, dif = 0, i = 0;
      int x = 0, y = 0, val = 0;
      if(WHITE_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);
		/* Castle (tower/king swap)*/
		//   board.slot[4][7] = WHITE_KING;
      if(board.start[0] == 4 && board.start[1] == 7)
      {
      	if(board.end[0] == 6 && board.end[1] == 7) // castle right
         {
         	/* Checking if right tower exits */
				if(board.slot[7][7] != WHITE_ROOK) return 1;
            if(board.slot[6][7] > 0) return 1;
            if(board.slot[5][7] > 0) return 1;
            if(QueryCheck(4, 7, WHITE_PLAYER) == true) return 1; // Check!
            if(QueryCheck(5, 7, WHITE_PLAYER) == true) return 1; // Check!
            if(QueryCheck(6, 7, WHITE_PLAYER) == true) return 1; // Check!
				board.slot[board.start[0]][board.start[1]] = 0;
				board.slot[board.end[0]][board.end[1]] = WHITE_KING;
            board.slot[7][7] = 0;
            board.slot[5][7] = WHITE_ROOK;
				return 0;
			}
         else if(board.end[0] == 2 && board.end[1] == 7) // castle left
         {
         	/* Checking if left tower exits */
				if(board.slot[0][7] != WHITE_ROOK) return 1;
            if(board.slot[1][7] > 0) return 1;
            if(board.slot[2][7] > 0) return 1;
            if(board.slot[3][7] > 0) return 1;
            if(QueryCheck(4, 7, WHITE_PLAYER) == true) return 1; // Check!
            if(QueryCheck(3, 7, WHITE_PLAYER) == true) return 1; // Check! 
            if(QueryCheck(2, 7, WHITE_PLAYER) == true) return 1; // Check!
				board.slot[board.start[0]][board.start[1]] = 0;
				board.slot[board.end[0]][board.end[1]] = WHITE_KING;
            board.slot[0][7] = 0;
            board.slot[3][7] = WHITE_ROOK;
				return 0;
         }
         else
         {
         	return 1;
         }
      }
		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;
		if(x_dif > 1 || y_dif > 1) return 1; // too many moves
      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_KING;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_KING;
         return 0;
      }
		else
      {
      	if(x_dif != y_dif) return 1;
	      for(i = 1; i < x_dif; i++)
   	   {
				if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
	//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
	      }
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_KING;
	      return 0;
	   }
   }
	if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_KING)
   {
   	int x_dif = 0, y_dif = 0, dif = 0, i = 0;
      int x = 0, y = 0, val = 0;
      if(BLACK_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);

		/* Castle (tower/king swap)*/
      if(board.start[0] == 4 && board.start[1] == 0)
      {
      	if(board.end[0] == 6 && board.end[1] == 0) // castle right
         {
         	/* Checking if right tower exits */
				if(board.slot[7][0] != BLACK_ROOK) return 1;
            if(board.slot[6][0] > 0) return 1;
            if(board.slot[5][0] > 0) return 1;
            if(QueryCheck(4, 0, BLACK_PLAYER) == true) return 1; // Check!
            if(QueryCheck(5, 0, BLACK_PLAYER) == true) return 1; // Check!
            if(QueryCheck(6, 0, BLACK_PLAYER) == true) return 1; // Check!
				board.slot[board.start[0]][board.start[1]] = 0;
				board.slot[board.end[0]][board.end[1]] = BLACK_KING;
            board.slot[7][0] = 0;
            board.slot[5][0] = BLACK_ROOK;
				return 0;
			}
         else if(board.end[0] == 2 && board.end[1] == 0) // castle left
         {
         	/* Checking if left tower exits */
				if(board.slot[0][0] != BLACK_ROOK) return 1;
            if(board.slot[1][0] > 0) return 1;
            if(board.slot[2][0] > 0) return 1;
            if(board.slot[3][0] > 0) return 1;
            if(QueryCheck(4, 0, BLACK_PLAYER) == true) return 1; // Check!
            if(QueryCheck(3, 0, BLACK_PLAYER) == true) return 1; // Check!
            if(QueryCheck(2, 0, BLACK_PLAYER) == true) return 1; // Check!
				board.slot[board.start[0]][board.start[1]] = 0;
				board.slot[board.end[0]][board.end[1]] = BLACK_KING;
            board.slot[0][0] = 0;
            board.slot[3][0] = BLACK_ROOK;
				return 0;
         }
         else
         {
         	return 1;
         }
      }
		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;
		if(x_dif > 1 || y_dif > 1) return 1; // too many moves 
      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_KING;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_KING;
         return 0;
      }
		else
      {
      	if(x_dif != y_dif) return 1;
	      for(i = 1; i < x_dif; i++)
   	   {
				if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
	//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
	      }
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_KING;
	      return 0;
	   }
   }
	if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_QUEEN)
   {
   	int x_dif = 0, y_dif = 0, dif = 0, i = 0;
      int x = 0, y = 0, val = 0;
      if(WHITE_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);

		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;

      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_QUEEN;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_QUEEN;
         return 0;
      }
		else
      {
      	if(x_dif != y_dif) return 1;
	      for(i = 1; i < x_dif; i++)
   	   {
				if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
	//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
	      }
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_QUEEN;
	      return 0;
	   }
   }
	if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_QUEEN)
   {
   	int x_dif = 0, y_dif = 0, dif = 0, i = 0;
      int x = 0, y = 0, val = 0;
      if(BLACK_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);

		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;

      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_QUEEN;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_QUEEN;
         return 0;
      }
		else
      {
      	if(x_dif != y_dif) return 1;
	      for(i = 1; i < x_dif; i++)
   	   {
				if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
	//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
	      }
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_QUEEN;
	      return 0;
	   }
   }
	if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_ROOK)
   {
   	int dif = 0, val = 0, i = 0;
   	if(WHITE_OBJECT() == true) return 1;
      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_ROOK;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_ROOK;
         return 0;
      }
      else
      {
      	return 1; /* not valid move for rook */
      }
   }
	if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_ROOK)
   {
   	int dif = 0, val = 0, i = 0;
   	if(BLACK_OBJECT() == true) return 1;
      if(board.start[0] == board.end[0]) /* moving in up/down sector */
      {
      	dif = (board.start[1] - board.end[1]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0]][board.start[1] + (val*i)] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_ROOK;
         return 0;
      }
      else if(board.start[1] == board.end[1]) /* moving in left/right sector */
      {
      	dif = (board.start[0] - board.end[0]);
			if(dif < 1) val = 1;
   	   if(dif > 1) val = -1;
         if(dif < 1) dif *= -1;
	      for(i = 1; i < dif; i++)
   	   {
				if(board.slot[board.start[0] + (val*i)][board.start[1]] > 0) return 1;
// 	        printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
			}
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_ROOK;
         return 0;
      }
      else
      {
      	return 1; /* not valid move for rook */
      }
   }
	if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_BISHOP)
   {
   	int x_dif = 0, y_dif = 0, i = 0;
      int x = 0, y = 0;
      if(WHITE_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);

		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;
      for(i = 1; i < x_dif; i++)
      {
			if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
      }
      if(x_dif != y_dif) return 1;
      if(x_dif == 0 || y_dif == 0) return 1;

		board.slot[board.start[0]][board.start[1]] = 0;
		board.slot[board.end[0]][board.end[1]] = WHITE_BISHOP;
      return 0;
   }
	if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_BISHOP)
   {
   	int x_dif = 0, y_dif = 0, i = 0;
      int x = 0, y = 0;
      if(BLACK_OBJECT() == true) return 1;
     	x_dif = (board.start[0] - board.end[0]);
     	y_dif = (board.start[1] - board.end[1]);

		if(x_dif < 1) x = 1;
      if(x_dif > 1) x = -1;
      if(y_dif < 1) y = 1;
      if(y_dif > 1) y = -1;
      if(x_dif < 0) x_dif *= -1;
      if(y_dif < 0) y_dif *= -1;
      for(i = 1; i < x_dif; i++)
      {
			if(board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)] > 0) return 1;
//         printf("(%d, %d) -> %d\n", board.start[0] + (x*i), board.start[1] + (y*i), board.slot[board.start[0] + (x*i)][board.start[1] + (y*i)]);
      }
      if(x_dif != y_dif) return 1;
      if(x_dif == 0 || y_dif == 0) return 1;

		board.slot[board.start[0]][board.start[1]] = 0;
		board.slot[board.end[0]][board.end[1]] = BLACK_BISHOP;
      return 0;
   }
	if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_KNIGHT)
   {
   	/* There is a white object in the slot */
   	if(WHITE_OBJECT() == true) return 1;
		if((board.end[0] + 1) == board.start[0] || (board.end[0] - 1) == board.start[0])
      {
      	/* 1 slot moved on X sector, now 2 to Y sector */
       	if((board.end[1] + 2) != board.start[1] && (board.end[1] - 2) != board.start[1]) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_KNIGHT;
         return 0;
      }
      else if((board.end[0] + 2) == board.start[0] || (board.end[0] - 2) == board.start[0])
		{
      	/* 2 slot moved on X sector, now 1 to Y sector */
       	if((board.end[1] + 1) != board.start[1] && (board.end[1] - 1) != board.start[1]) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_KNIGHT;
         return 0;
      }
      else
      {
   		/* Not valid move for Knight */
      	return 1;
      }
	}
	if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_KNIGHT)
   {
   	/* There is a black object in the slot */
   	if(BLACK_OBJECT() == true) return 1;
		if((board.end[0] + 1) == board.start[0] || (board.end[0] - 1) == board.start[0])
      {
      	/* 1 slot moved on X sector, now 2 to Y sector */
       	if((board.end[1] + 2) != board.start[1] && (board.end[1] - 2) != board.start[1]) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_KNIGHT;
         return 0;
      }
      else if((board.end[0] + 2) == board.start[0] || (board.end[0] - 2) == board.start[0])
		{
      	/* 2 slot moved on X sector, now 1 to Y sector */
       	if((board.end[1] + 1) != board.start[1] && (board.end[1] - 1) != board.start[1]) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_KNIGHT;
         return 0;
      }
      else
      {
   		/* Not valid move for Knight */
      	return 1;
      }
	}
   if(turn == WHITE_PLAYER && board.slot[board.start[0]][board.start[1]] == WHITE_PAWN)
   {
		/* Pawn must go straight (one exception) */
      if(board.start[0] != board.end[0])
      {
			if(board.end[1] != (board.start[1] - 1)) return 1;
         if(board.end[0] != (board.start[0] + 1) &&
         	board.end[0] != (board.start[0] - 1)) return 1;
         if(board.slot[board.end[0]][board.end[1]] < 7) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = WHITE_PAWN;
         if(board.end[1] == 0) Promote(board.end[0], board.end[1], WHITE_PLAYER);
         return 0;
      }
   	if(board.start[0] != board.end[0]) return 1;
		if(board.start[1] == 6) // pawn not moved once!
      {
			if(board.start[1] != (board.end[1] + 1) &&
         	board.start[1] != (board.end[1] + 2)) return 1;
      }
      else // pawn moved!
      {
      	if(board.start[1] != (board.end[1] + 1)) return 1;
      }
      /* Pawns can't go through objects */
      if(board.slot[board.end[0]][board.end[1]] != 0) return 1;
		/* valid, moving pawn */
		board.slot[board.start[0]][board.start[1]] = 0;
		board.slot[board.end[0]][board.end[1]] = WHITE_PAWN;
      if(board.end[1] == 0) Promote(board.end[0], board.end[1], WHITE_PLAYER);
      return 0;
   }
   if(turn == BLACK_PLAYER && board.slot[board.start[0]][board.start[1]] == BLACK_PAWN)
   {
		/* Pawn must go straight (one exception) */
      if(board.start[0] != board.end[0])
      {
			if(board.end[1] != (board.start[1] + 1)) return 1;
         if(board.end[0] != (board.start[0] + 1) &&
         	board.end[0] != (board.start[0] - 1)) return 1;
         if(board.slot[board.end[0]][board.end[1]] == 0 ||
         	board.slot[board.end[0]][board.end[1]] > 6) return 1;
			board.slot[board.start[0]][board.start[1]] = 0;
			board.slot[board.end[0]][board.end[1]] = BLACK_PAWN;
         if(board.end[1] == 7) Promote(board.end[0], board.end[1], BLACK_PLAYER);
         return 0;
      }
		if(board.start[1] == 1) // pawn not moved once!
      {
			if(board.start[1] != (board.end[1] - 1) &&
         	board.start[1] != (board.end[1] - 2)) return 1;
      }
      else // pawn moved!
      {
      	if(board.start[1] != (board.end[1] - 1)) return 1;
      }
      /* Pawns can't go through objects */
      if(board.slot[board.end[0]][board.end[1]] != 0) return 1;
		/* valid, moving */
		board.slot[board.start[0]][board.start[1]] = 0;
		board.slot[board.end[0]][board.end[1]] = BLACK_PAWN;
      if(board.end[1] == 7) Promote(board.end[0], board.end[1], BLACK_PLAYER);
      return 0;
   }
   /* didn't find any objects from this place */
   return 1;
}


int FindKingX(bool color)
{
	int x = 0, y = 0;
   do
   {
   	for(x = 0; x < 8; x++)
      {
      	if(color == WHITE_PLAYER)
         {
         	if(board.slot[x][y] == WHITE_KING) return x;
         }
         else
         {
         	if(board.slot[x][y] == BLACK_KING) return x;
         }
      }
   	y++;
   } while(y < 8);
	closegraph();
   printf("No king on the board!!!\n");
   exit(1);
   return 1;
}

int FindKingY(bool color)
{
	int x = 0, y = 0;
   do
   {
   	for(x = 0; x < 8; x++)
      {
      	if(color == WHITE_PLAYER)
         {
         	if(board.slot[x][y] == WHITE_KING) return y;
         }
         else
         {
         	if(board.slot[x][y] == BLACK_KING) return y;
         }
      }
   	y++;
   } while(y < 8);
	closegraph();
   printf("No king on the board!!!\n");
   exit(1);
   return 1;
}

void main()
{
	bool valid_coord = true, valid_move = true, turn = WHITE_PLAYER;
   bool white_check = false, black_check = false;
	int errorcode = 0;

   errorcode = registerbgidriver(EGAVGA_driver);

   /* report any registration errors */
   if (errorcode < 0)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      exit(1);
   }

	InitGraphics();
   ResetObjects();
   write_board("chess.dat", board);
	for(;;)
   {
   	white_check = false;
      black_check = false;
		white_check = QueryCheck(FindKingX(WHITE_PLAYER), FindKingY(WHITE_PLAYER), WHITE_PLAYER);
      black_check = QueryCheck(FindKingX(BLACK_PLAYER), FindKingY(BLACK_PLAYER), BLACK_PLAYER);
		Clear();
	   DrawChessBoard();
   	UpdateBoard();
      StatusScreen(turn, white_check, black_check);
      do
      {
      	/* Checking that coordinates are correct and also the input is valid */
      	valid_coord = Move();
      } while(valid_coord == false);
      do
  	   {
      	/* Checking that the move is valid, and moving the right objects */
			valid_move = CheckValidity(turn);
			white_check = QueryCheck(FindKingX(WHITE_PLAYER), FindKingY(WHITE_PLAYER), WHITE_PLAYER);
	      black_check = QueryCheck(FindKingX(BLACK_PLAYER), FindKingY(BLACK_PLAYER), BLACK_PLAYER);
         if(white_check == true && turn == WHITE_PLAYER)
         {
	         valid_move = 1; // Check! Not allowed
            board = read_board("chess.dat");
         }
         if(black_check == true && turn == BLACK_PLAYER)
         {
         	valid_move = 1; // Check! Not allowed
            board = read_board("chess.dat");
         }
         if(valid_move == 0)
         {
         	write_board("chess.dat", board);
         	if(turn == BLACK_PLAYER)
            	turn = WHITE_PLAYER;
            else
            	turn = BLACK_PLAYER;
         }
         if(!valid_move) valid_coord = false; // seems like useless
     	} while(valid_move == false);
	}
}
