#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int flipCoin()
{
  if (rand() %2 == 0) return 0;
  else return 1;
}

int scansione(int a, int b)
{
    int c;
    do{
        scanf("%d", &c);
        if(c<a || c>b)
        printf ("scegliere un valore valido\n");
	} while (c<a || c>b);

    return c;
}
