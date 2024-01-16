// MIT License

// Copyright (c) 2020 Litrin Jiang

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>

#define MAX_CORE_COUNT 1024

typedef unsigned int core;
typedef struct{
	_Bool map[MAX_CORE_COUNT];
	core last;

} coreset;

int core_exits(coreset *c, core n);
inline int core_exits(coreset *c, core n)
{
	return c->map[n] != 0 ;
}

void set_cores(coreset *c, core b, core e, char stat);
inline void set_cores(coreset *c, core b, core e, char stat)
{
	if (b>e)
	{
		core t = b;
		b = e;
		e = t;
	}
	c->last = c->last > e ? c->last : e;
	do 
	{
		c->map[b] = stat;
		b ++;
	}while(b <= e );

}

int coreset_from_char(coreset *c, char *s)
{
	core cur = 0;
	int tmp = -1;

	for (int i=0; s[i] != '\0'; ++i)
	{
		if (s[i] == ',')
		{
			tmp = tmp < 0 ? cur : tmp ;
			set_cores(c, tmp, cur, 1);
			
			tmp = -1;
			cur = 0;
			continue;
		}

		if (s[i] == '-')
		{
			tmp = cur;
			cur = 0;
			continue;
		}
		cur = cur * 10 + (int)s[i] - 48;

		if (cur > MAX_CORE_COUNT - 1)
			return 1;
	}

	tmp = tmp < 0 ? cur : tmp;
	set_cores(c, tmp, cur, 1);
	
	return 0;

}



void show(coreset *c)
{
	for (int i=0; i<= c->last; i++) 
	{
		if (core_exits(c, i))
			printf("%d\n", i);
	}
}

void print(coreset *c)
{
	int b = -1, e = -1;

	for (int i=0; i<= c->last; i++) 
	{
		if (!core_exits(c, i))
			continue;
		
		if (i - 1 == e )
		{
			b = b == -1 ? e : b;
		} 
		else
		{
			if ( b != -1 && e != -1 )
				printf("%d-%d,", b, e);
			else if ( e != -1 )
				printf("%d,",e);
			b = -1;
		}

		e = i;

	}
	if ( b != -1 && e != -1 )
		printf("%d-%d", b, e);
	else if( e != -1 )
		printf("%d",e);
	printf("\n");

}

void show_mask(coreset *c)
{
	printf("0x");
	int mask = 0;
	for(int i = c->last; i >= 0 ; --i)
	{
		if (core_exits(c,i))
			mask |= 1<<(i % 4);

		if (0 == i % 4)
		{
			printf("%X", mask);
			mask = 0;
		}

	}

	printf("\n");
}
