#include <stdlib.h>
#include <stdio.h>
#include <string.h> //Wird für "string" Funktionen benötigt.
#include <time.h>   //Wird für "random" Funktionen benötigt.
#include <conio.h>   //Wird für Tastatur Eingaben benötigt.


int random(int, int); // Zufällige Zahl mit Angabe von Wertebereich
void ausgabe(); // Test Methode
void end(); // Spielende
void menü(); // Hauptmenü
void karten(); // Algorithmus für das Mischen und Verteilen der Karten
void füllkarten(); // Algorithmus für das Abfüllen der Karten mit Werten
void einstellungen(); // Farbeinstellungen
void rundestart(); // Start einer Runde



typedef struct Karten // Struktur für Karten 
{
  int Nr;
  char Marke[20];
  char Modell[20];
  int Leistung;
  int Gewicht;
  double Höchsttempo;
  struct Karten* pNext;
}struKarten;

int main()
{
  // Rand Initialisierung für die Methode "random".
  srand(time(NULL));
  menü(); // Aufruf des Hauptmenüs

  //
  system("pause");
  return 0;
}


int random(int min, int max) {
  // Random-Funktion, wo Zahlen für das zufällige Verteilen der Karten 
  int r = rand() % max + min;

  return(r);
}

void menü()
{
  //variablen
  char spielmodus;
  system("cls"); // Leeren des Bildschirms

  printf("    .d88888b.                            888            888    888     \n");
  printf("   d88P   Y88b                           888            888    888     \n");
  printf("   888     888                           888            888    888     \n");
  printf("   888     888 888  888  8888b.  888d888 888888 .d88b.  888888 888888  \n");
  printf("   888     888 888  888     '88b 888P'   888   d8P  Y8b 888    888     \n");
  printf("   888 Y8b 888 888  888 .d888888 888     888   88888888 888    888     \n");
  printf("   Y88b.Y8b88P Y88b 888 888  888 888     Y88b. Y8b.     Y88b.  Y88b.   \n");
  printf("    'Y888888'   'Y88888 'Y888888 888      'Y888 'Y8888'  'Y888  'Y888  \n");
  printf("          Y8b                                                          \n");

  printf("\n  W\x84hlen Sie ihren Spielmodus:\n");
  printf("  1 Spieler     (1)\n");
  printf("  2 Spieler     (2)\n\n");
  printf("  Beenden       (3)\n");
  printf("  Einstellungen (4)\n");

  printf("\n  (1/2/3/4): ");
  scanf_s(" %c", &spielmodus,1);

  //1 Spieler (PC vs Spieler)
  if (spielmodus == '1')
  {
    spielmodus = '1';
    
  }
  //Einstellungen
  else if (spielmodus == 'B' || spielmodus == 'b' || spielmodus == '3')
  {
    spielmodus = '3';
    end;
  }

  //Ende
  else if (spielmodus == 'E' || spielmodus == 'e' || spielmodus == '4')
  {
    spielmodus = '4';
    einstellungen;
  }

  //falsche Eingabe
  else if (spielmodus != '1' && spielmodus != '2' && spielmodus != '3' && spielmodus != '4' && spielmodus != 'b' && spielmodus != 'B' && spielmodus == 'e' && spielmodus == 'E')
  {
    printf("  Falsche Eingabe\n");
    system("timeout 1 >null");
    system("cls");
    spielmodus = 0;
  }


}

void rundestart()
{

}

void karten()
{
  füllkarten();
  
}

void füllkarten()
{
  struKarten

}

void ausgabe() {

  char c;
  printf("\n\n");
  printf("\n  ==================================");
  printf("\n  Was M\x94""chten Sie Vergleichen?");
  printf("\n  1 = Variable 1: value X... ");
  printf("\n  2 = Variable 2:");
  printf("\n  3 = Variable 3:");
  printf("\n  4 = Variable 4:");
  printf("\n  ==================================");
  printf("\n  5 = Neu Starten");
  printf("\n  6 = Beenden");
  printf("\n  (1/2/3/4/5/6): ");
}

void end()
{
  char e;
  // Nachfrage zum Beenden
  system("cls");
  printf("\n  M\x94""chten Sie das Spiel wirklich beenden?\n");
  printf("  (J/N) ");
  scanf_s(" %c", &e,1);
  system("cls");
  if (e == 'J' || e == 'j')
  {
  printf("  oooooooooooo                   .o8          \n");
  printf("  `888'     `8                  '888          \n");
  printf("   888         ooo. .oo.    .oooo888   .d88b. \n");
  printf("   888oooo8    `888P'Y88b  d88' `888  d8P  Y8b\n");
  printf("   888    '     888   888  888   888  88888888\n");
  printf("   888       o  888   888  888   888  Y8b.    \n");
  printf("  o888ooooood8 o888o o888o `Y8bod88P'  'Y8888'\n\n\n");
  }


  printf("    .d88888b.                            888            888    888     \n");
  printf("   d88P" "Y88b                           888            888    888     \n");
  printf("   888     888                           888            888    888     \n");
  printf("   888     888 888  888  8888b.  888d888 888888 .d88b.  888888 888888  \n");
  printf("   888     888 888  888     '88b 888P'   888   d8P  Y8b 888    888     \n");
  printf("   888 Y8b 888 888  888 .d888888 888     888   88888888 888    888     \n");
  printf("   Y88b.Y8b88P Y88b 888 888  888 888     Y88b. Y8b.     Y88b.  Y88b.   \n");
  printf("    'Y888888'   'Y88888 'Y888888 888      'Y888 'Y8888'  'Y888  'Y888  \n");
  printf("          Y8b                                                          \n");
}

void einstellungen()
{

}

void farbmatrix(char hintergrundfarbe, char textfarbe)
{
  //Alles mit schwarzem Hintergrund
  if (hintergrundfarbe == '0' && textfarbe == 'F')      system("color 0F");
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

}
