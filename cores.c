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
#include <malloc.h>
#include <unistd.h>
#include "coreset.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void usage()
{
	printf("Usage:\n");
	printf("coreset -c <string> [-s|-m|-r] \n");
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		usage();
		return EXIT_SUCCESS;
	}

	int option;
	coreset *c = malloc(sizeof(coreset));
	while ((option = getopt(argc, argv, "c:s::m::r::")) != -1)
	{
		switch (option)
		{
			case 'c':
				if (coreset_from_char(c, optarg) != 0)
					return EXIT_FAILURE;
				break;
			case 's':
				print(c);
				free(c);
				return EXIT_SUCCESS;

			case 'm':
				show_mask(c);
				free(c);
				return EXIT_SUCCESS;

			case '?':
				usage();
				return EXIT_SUCCESS;
				
		}
	}

	show(c);
	free(c);

	return EXIT_SUCCESS;
	
}
