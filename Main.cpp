#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Wird für "random" Funktion benötigt.


int random();
void ausgabe();

int main()
{
  srand(time(NULL));
  random(1,10);
  
  
  ausgabe();
  printf("Hello\n"); //Test 2
  system("pause");
  return 0;
}


int random(int min, int max) {

  int r = rand() % max + min;

  return(r);
}

void ausgabe() {
  printf("Was Möchten Sie Vergleichen?\n");
}
