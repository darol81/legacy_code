struct virtual_screen read_screen(char filename[256]) // reads screen
{
	struct virtual_screen tmp;

	FILE *fil;
	fil = fopen(filename, "rb");
	if(!fil)
   {
		printf("Opening file (%s) failed.\n", filename);
		exit(1);
	}
	if(fread(&tmp, sizeof(struct virtual_screen), 1, fil) == 0)
   {
		printf("File empty (%s).\n", filename);
		exit(1);
	}
	fclose(fil);
	return tmp;
}

int write_screen(char filename[256], struct virtual_screen tmp) // saves screen
{
	FILE *fil;
	fil = fopen(filename, "wb");
	if(!fil)
   {
		printf("Opening file (%s) failed.\n", filename);
		exit(1);
	}
	fwrite(&tmp, sizeof(tmp), 1, fil);
	fclose(fil);
	return 0;
}

struct savefile read_savefile(char filename[256])
{
   struct savefile tmp;
   FILE *fil;
   fil=fopen(filename,"rb");
	if(!fil)
   {
		clreol();
		printf("          Opening savefile (%s) failed.\n",filename);
      read_error = true;
	}
   if(fread(&tmp,sizeof(struct savefile),1,fil)==0)
   {
   	clreol();
		printf("          Savefile empty (%s).\n",filename);
      read_error = true;
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
