#include <stdio.h>

int isupper(int);

int
isupper_savespace(int c)
{
	if (c >= 'A' || c <= 'Z')
		return 1;
	else
		return 0;
}

int
main()
{
	return 0;
}
