#include <stdlib.h>
#include <stdio.h>
#include <string.h> //Wird für "string" Funktionen benötigt.
#include <time.h>   //Wird für "random" Funktionen benötigt.

int random(int, int);
void ausgabe();
void end();
void menü();

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
void menü() {

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

void end()
{
  printf("oooooooooooo                   .o8  \n");
  printf("`888'     `8                  '888  \n");
  printf(" 888         ooo. .oo.    .oooo888  \n");
  printf(" 888oooo8    `888P'Y88b  d88' `888  \n");
  printf(" 888    '     888   888  888   888  \n");
  printf(" 888       o  888   888  888   888  \n");
  printf("o888ooooood8 o888o o888o `Y8bod88P' \n\n\n");
}

void farbmatrix(char hintergrundfarbe, char textfarbe)
{

  //Alles mit schwarzem Hintergrund
  if (hintergrundfarbe == '0' && textfarbe == 'F') system("color 0F");
  else if (hintergrundfarbe == '0' && textfarbe == '8') system("color 08");
  else if (hintergrundfarbe == '0' && textfarbe == '2') system("color 02");
  else if (hintergrundfarbe == '0' && textfarbe == '4') system("color 04");
  else if (hintergrundfarbe == '0' && textfarbe == '1') system("color 01");

  //Alles mit grauem Hintergrund
  else if (hintergrundfarbe == '8' && textfarbe == '0') system("color 80");
  else if (hintergrundfarbe == '8' && textfarbe == 'F') system("color 8F");
  else if (hintergrundfarbe == '8' && textfarbe == '2') system("color 82");
  else if (hintergrundfarbe == '8' && textfarbe == '1') system("color 81");
  else if (hintergrundfarbe == '8' && textfarbe == '4') system("color 84");

  //Alles mit weissem Hintergrund
  else if (hintergrundfarbe == 'F' && textfarbe == '0') system("color F0");
  else if (hintergrundfarbe == 'F' && textfarbe == '8') system("color F8");
  else if (hintergrundfarbe == 'F' && textfarbe == '2') system("color F2");
  else if (hintergrundfarbe == 'F' && textfarbe == '1') system("color F1");
  else if (hintergrundfarbe == 'F' && textfarbe == '4') system("color F4");

  //Alles mit Grünem Hintergrund
  else if (hintergrundfarbe == '2' && textfarbe == '0') system("color 20");
  else if (hintergrundfarbe == '2' && textfarbe == '8') system("color 28");
  else if (hintergrundfarbe == '2' && textfarbe == 'F') system("color 2F");
  else if (hintergrundfarbe == '2' && textfarbe == '1') system("color 21");
  else if (hintergrundfarbe == '2' && textfarbe == '4') system("color 24");

  //Alles mit Blauem Hintergrund
  else if (hintergrundfarbe == '1' && textfarbe == '0') system("color 10");
  else if (hintergrundfarbe == '1' && textfarbe == '8') system("color 18");
  else if (hintergrundfarbe == '1' && textfarbe == 'F') system("color 1F");
  else if (hintergrundfarbe == '1' && textfarbe == '2') system("color 12");
  else if (hintergrundfarbe == '1' && textfarbe == '4') system("color 14");

  //Alles mit Rotem Hintergrund
  else if (hintergrundfarbe == '4' && textfarbe == '0') system("color 40");
  else if (hintergrundfarbe == '4' && textfarbe == '8') system("color 48");
  else if (hintergrundfarbe == '4' && textfarbe == 'F') system("color 4F");
  else if (hintergrundfarbe == '4' && textfarbe == '2') system("color 42");
  else if (hintergrundfarbe == '4' && textfarbe == '1') system("color 41");

  //Fertig vlt weitere Farben...
}