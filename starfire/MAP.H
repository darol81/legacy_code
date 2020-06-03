int calc_ysiz(char *filename)
{
	FILE *calcfile;
	int i = 0;
	char c;
	if((calcfile=fopen(filename,"r")) == NULL)
   {
		cout <<"Error opening calcfile.\n";
		exit(1);
	}
	while(1)
   {
		c=fgetc(calcfile);
      if(c==EOF)
      {
			fclose(calcfile);
			i += 2;
			return i;
      }
      if(c=='\r' || c=='\n') i++;
	}
}

int calc_xsiz(char *filename)
{
	FILE *calcfile;
	int i = 0;
	char c;
	if((calcfile=fopen(filename,"r")) == NULL)
   {
		cout <<"Error opening calcfile.\n";
		exit(1);
	}
	while(1)
   {
   	c=fgetc(calcfile);
   	if(c=='\n' || c=='\r')
      {
			fclose(calcfile);
			i += 2;
			return i;
      }
		i++;
	}
}

/* true_x() and true_y() define correct big_x and big_y rooms */
int true_x(int num)
{
	int ret = 0;
   ret = num;
   ret += screen.draw.big_x * 40;
   return ret;
}

int true_y(int num)
{
	int ret = 0;
   ret = num;
   ret += screen.draw.big_y * 8;
   return ret;
}


char **read_map(char *map_file, int *max_x, int *max_y)
{
	int i = 0;
	int ysiz = 0, xsiz = 0;
	char *in;
	char **kartta;
	FILE *mapfile;
	ysiz = calc_ysiz(map_file);
	xsiz = calc_xsiz(map_file);
	*max_x = xsiz-2;
	*max_y = ysiz-2;
	kartta=(char **)malloc(sizeof(char *)*ysiz);
	in=(char *)malloc((sizeof(char)*xsiz)+5);
	for(i = 0; i < ysiz; i++)
	{
		kartta[i]=(char *)malloc(sizeof(char)*xsiz);
	}
	if((mapfile=fopen(map_file,"r")) == NULL)
   {
		cout <<"Error opening mapfile " << map_file << ".\n";
		exit(1);
	}
	i = 0;
	while(1)
   {
		if(feof(mapfile)) break;
		fgets(in, xsiz, mapfile);
		strncpy(kartta[i], in, xsiz);
		i++;
	}
	fclose(mapfile);
	return kartta;
}


