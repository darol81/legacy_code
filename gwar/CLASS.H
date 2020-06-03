struct savefile
{
	int pixel[40][40];
} pic;

class Ufo
{
	private:
		int pixel[45][45]; // for some odd reason, array must be 45 :)
		int ulx, uly, lrx, lry, size;
      int x, y, dir, wait, portal;
      void *Saucer;
   public:
   	int QueryDir() { return dir; }
      int QueryPortal() { return portal; }
   	int QueryX() { return x; }
      int QueryY() { return y; }
		void UsePortal() { portal = 150; }
      void DecPortal();
		void SetWait(int value) { wait = value; }
      void SetDir(int value) { dir = value; }
		void SetX(int value) { x = value; }
      void SetY(int value) { y = value; }
      void Move(int var_x, int var_y); // change of coordinates (how much moves)
      void SavePixels(char *file);
      void Erase();
      void Destroy() { free(Saucer); }
		void ReadObject();
};

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

void Ufo::SavePixels(char *file)
{
	int _x = 0, _y = 0;
	pic = read_savefile(file);
	do
   {
		for(_x = 0; _x < 40; _x++)
   	{
			pixel[_x][_y] = pic.pixel[_x][_y];
	   }
      _y++;
   } while(_y < 40);
}

void Ufo::DecPortal()
{
	portal--;
   if(portal == 1) /* giving sign to a player that portal can be used again */
   {
   	sound(500);
      delay(30);
      nosound();
   }
   if(portal < 0) portal = 0;
}

void Ufo::Erase()
{
	putimage(x, y, Saucer, XOR_PUT);
}

void Ufo::Move(int var_x, int var_y)
{
	x += var_x; // negative value -> left, positive -> right
   y += var_y; // negative value -> up, positive -> down
	/* setting some screen borders */
   if(x < 0) x = 0;
  	if(x > getmaxx()-40) x = getmaxx()-40;
   if(y < 0) y = 0;
   if(y > getmaxy()-40) y = getmaxy()-40;
  	putimage(x, y, Saucer, XOR_PUT);                 /*  draw image  */
   delay(wait);
}

void Ufo::ReadObject()
{
	int _x = 0, _y = 0;
	ulx = 0;
   uly = 0;
	lrx = 39;
   lry = 39;
	do
   {
		for(_x = 0; _x < 40; _x++)
   	{
         putpixel(_x, _y, pixel[_x][_y]);
	   }
      _y++;
   } while(_y < 40);
   size = imagesize(ulx, uly, lrx, lry);
   Saucer = malloc(size);
   getimage(ulx, uly, lrx, lry, Saucer);
   putimage(ulx, uly, Saucer, XOR_PUT);
}

