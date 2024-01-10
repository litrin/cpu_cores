#include <stdio.h>
#include <malloc.h>

#define MAX_CORE_COUNT 1024

typedef unsigned int core;
typedef struct{
	char map[MAX_CORE_COUNT];
	core last;

} coreset;


int core_exits(coreset *c, core n)
{
	return c->map[n] != 0 ;
}

void set_cores(coreset *c, core b, core e, char stat)
{
	if (b>e)
	{
		core t = b;
		b=e;
		e = b;
	}
	c->last = c->last > e ? c->last : e;
	do 
	{
		c->map[b] = stat;
		b ++;
	}while(b <= e );

}

void show(coreset *c)
{
	for (int i=0; i<= c->last; i++) 
	{
		if (core_exits(c, i))
			printf("%d\n", i);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		return EXIT_SUCCESS;

	coreset *c = {malloc(MAX_CORE_COUNT), 0};
	
	core cur=0;
	int tmp = -1;
	for (int i=0; argv[1][i] != '\0'; ++i)
	{
		if (argv[1][i] == ',')
		{
			tmp = tmp < 0 ? cur : tmp ;
			set_cores(c, tmp, cur, 1);
			
			tmp = -1;
			cur = 0;
			continue;
		}

		if (argv[1][i] == '-')
		{
			tmp = cur;
			cur = 0;
			continue;
		}
		
		cur = cur * 10 + (int)argv[1][i] - 48;



	}

	tmp = tmp < 0 ? cur : tmp ;
	set_cores(c, tmp, cur, 1) ; 
	
	show(c);

	return EXIT_SUCCESS;
}
