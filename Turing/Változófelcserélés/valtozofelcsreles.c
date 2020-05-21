#include <stdio.h>


int main()
{
        int x = 1;
        int y = 2;
        printf("Az x alapértéke: %d\n",x);
        printf("Az y alapértéke: %d\n",y);
        int c = x;
        x = y;
        y = c;
        printf("Az x felcserélés utáni értéke: %d\n",x);
        printf("Az y felcserélés utáni értéke: %d\n",y);
}