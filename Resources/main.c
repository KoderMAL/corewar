#include <stdio.h>
int main(void)
{
	int tab[5] = {10,16,0x6,0x9,0x0};
	FILE *fp;

	int i = 0;
	fp = fopen("dtry.cor", "a");
	while (i < 5)
	{
		fwrite(&tab[i], sizeof(char), 1, fp);
		i++;
	}
	return (0);
}
