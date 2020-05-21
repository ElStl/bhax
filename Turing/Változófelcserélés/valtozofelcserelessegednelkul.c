#include <stdio.h>

int main()
{
	int x = 20;
	int y = 10;
	printf("Az x értéke felcserélés előtt:%d\n",x);
	printf("Az y értéke felcserélés előtt:%d\n",y);
	y=y-x;
	x=x+y;
	y=x-y;
	printf("Az x értéke felcserélés után:%d\n",x);
	printf("Az y értéke felcserélés után:%d\n",y);
}
