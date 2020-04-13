
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

typedef unsigned char mask;

void set_mask(int begin, int end, mask *m)
{
	if (begin > end)
	{
		end += begin;
		begin = end - begin;
		end -= begin;
	}

	for (int offset=0, i = begin; i <= end; ++i)
	{
		int offset = i / sizeof(mask);
		m[offset] |= 1 << (i%sizeof(mask));
	}
}

void split(char *s, mask *m)
{
	int begin = -1, end = -1;
	unsigned int tmp = 0;
	for (int i = 0; i <= strlen(s); i++)
	{
		if (47 < s[i] && s[i] < 58)
		{
			tmp *= 10;
			tmp += s[i] - 48;
			continue;
		}

		end = tmp;
		if (begin == -1)
		{
			begin = tmp;
		}

		if (45 != s[i] )
		{
			set_mask(begin, end, m);
			begin = -1;
		}

		tmp = 0;
	}

}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		return 0;
	}

	size_t core_count = get_nprocs_conf();
	size_t mask_length = core_count / sizeof(mask);

	mask core_mask[mask_length];
	for (int i = 0; i < mask_length; ++i)
	{
		core_mask[i] = 0;
	}

	split(argv[1], core_mask);

	for (int offset = 0, i = 0; i < core_count; ++i)
	{
		offset = i / sizeof(mask);
		if (core_mask[offset] & (1 << (i%sizeof(mask))))
		{
			printf("%d\n", i);
		}
	}

	return 0;
}
