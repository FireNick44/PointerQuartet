#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Wird für "random" Funktion benötigt.


int random(int, int);
void ausgabe();

int main()
{
  srand(time(NULL));
  int rTmp = random(1, 10);
  
  
  ausgabe();
  printf("Hello: %i\n", rTmp = random(1, 10)); //Test 2
  system("pause");
  return 0;
}


int random(int min, int max) {

  int r = rand() % max + min;

  return(r);
}

void ausgabe() {

  char c;
  printf("\n\n\n");
  printf("==================================\n");
  printf("Was M\x94""chten Sie Vergleichen?\n");
  printf("1 = Variable 1: value X... \n");
  printf("2 = Variable 2:\n");
  printf("3 = Variable 3:\n");
  printf("4 = Variable 4:\n");
  printf("==================================\n");
  printf("5 = Neu Starten\n");
  printf("6 = Beenden\n");

  c = getchar();


}
