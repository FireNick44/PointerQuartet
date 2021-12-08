#include <stdlib.h>
#include <stdio.h>
#include <string.h> //Wird für "string" Funktionen benötigt.
#include <string>
#include <time.h>   //Wird für "random" Funktionen benötigt.
#include <conio.h>   //Wird für Tastatur Eingaben benötigt.
#include <Windows.h>


// Struktur für Karten 

typedef struct Karten 
{
  int Nr;
  char Bez[40];
  int Trefferpunkte;
  int Geschw;
  int Schaden;
  struct Karten* pNext;
}struKarten;


//Prototypen der Methoden
int random(int, int);                                           // Zufällige Zahl mit Angabe von Wertebereich
struKarten* ausgabe(struKarten*);                               // Test Methode
struKarten* karten(struKarten*, struKarten*);                   // Algorithmus für das Mischen und Verteilen der Karten
struKarten* füllkarten(int, const char*, int, int, int);        // Algorithmus für das Abfüllen der Karten mit Werten
struKarten* verteile_User();
struKarten* verteile_PC();
struKarten* vergleiche();
void einstellungen(bool, bool);                                 // Farbeinstellungen
int rundestart();                                               // Start einer Runde
void end();                                                     // Spielende
void logo();


int main()
{


  // Rand Initialisierung für die Methode "random".
  srand(time(NULL));

  system("mode con cols=80 lines=35");

  bool menü = true;
  while (menü == true)
  {
    //variablen
    int spielmodus;
    char eingabe; //Variabel für Eingabe

    system("cls"); // Leeren des Bildschirms

    logo();

    printf("\n  ==================================");
    printf("\n  W\x84hlen Sie ihren Spielmodus:");
    printf("\n  1 Spieler     (1)");
    printf("\n  Einstellungen (2)");
    printf("\n  Beenden       (3)");
    printf("\n  ==================================");
    printf("\n");
    printf("\n  (1/2/3): ");

    eingabe = _getch(); //getch oder getche (getche gibt ein Echo mit aus.)

    //1 Spieler (PC vs Spieler)
    if (eingabe == '1')
    {
      rundestart();
    }

    //Einstellungen
    else if (eingabe == '2')
    {
      bool admin = false;
      bool first = true;
      einstellungen(first, admin);
    }

    //Ende
    else if (eingabe == '3')
    {
      printf("\n\n  M\x94""chten Sie das Spiel wirklich beenden?");
      printf("\n  (J/N) ");
      
      eingabe = _getch();

      if (eingabe == 'J' || eingabe == 'j') menü = false;
    }

    //falsche Eingabe
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3')
    {
      printf("\n  Falsche Eingabe ");
      system("timeout 1 >null");
      system("cls");
    }
  }

  end();
  return 0;
}

int random(int min, int max) {
  // Random-Funktion, wo Zahlen für das zufällige Verteilen der Karten 
  int r = rand() % max + min;

  return(r);
}

void logo()
{
  printf("\n     ___  _             _             __     ___ _");
  printf("\n    / __\x5C| |  __ _  ___| |__     ___ / _|   / __\x5C | __ _ _ __  ___");
  printf("\n   / /   | | / _` / __ | '_ \x5C   / _ \x5C| |_  / /  | |/ _` | '_ \x5C/ __|");
  printf("\n  / /___ | |(  _| \x5C__ \x5C| | | |  |(_) | _| / /___| | (_| | | | \x5C__ \x5C ");
  printf("\n  \x5C____/ |_| \x5C__,_|___/|_| |_|  \x5C___/|_|  \x5C____/|_|\x5C__,_|_| |_|___/");
  printf("\n");
  printf("    .d88888b.                            888            888    888     \n");
  printf("   d88P   Y88b                           888            888    888     \n");
  printf("   888     888                           888            888    888     \n");
  printf("   888     888 888  888  8888b.  888d888 888888 .d88b.  888888 888888  \n");
  printf("   888     888 888  888     '88b 888P'   888   d8P  Y8b 888    888     \n");
  printf("   888 Y8b 888 888  888 .d888888 888     888   88888888 888    888     \n");
  printf("   Y88b.Y8b88P Y88b 888 888  888 888     Y88b. Y8b.     Y88b.  Y88b.   \n");
  printf("    'Y888888'   'Y88888 'Y888888 888      'Y888 'Y8888'  'Y888  'Y888  \n");
  printf("          Y8b                                                          \n\n");
}

struKarten* ausgabe(struKarten* pStart) {

  char c;
  bool menü = false;

  for (struKarten* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
    while (menü == false) {
      system("cls");

      printf("\n\n");
      printf("\n  ==================================");
      printf("\n\n");
      printf("\n   _______________________________ ");
      printf("\n  /                               \x5C");
      printf("\n  |                    Karte Nr. %2i |", pStart->Nr);
      printf("\n  |                               |");
      printf("\n  |         CoC Quartett          |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |      %-14s           |", pStart->Bez);
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |   Trefferpunkte  :   %4i     |", pStart->Trefferpunkte);
      printf("\n  |                               |");
      printf("\n  |   Geschwindigkeit:   %4i     |", pStart->Geschw);
      printf("\n  |                               |");
      printf("\n  |   Schaden        :   %4i     |", pStart->Schaden);
      printf("\n  |                               |");
      printf("\n  \x5C_______________________________/");
      printf("\n  Ihre Naechste Karte: %14s ", pStart->pNext->Bez);
      /* */

      printf("\n\n\n  Trefferpunkte?        (1)");
      printf("\n  Geschwindigkeit?      (2)");
      printf("\n  Schaden?              (3)");
      printf("\n  =================================");
      printf("\n\n  Neu Starten           (4)");
      printf("\n  Zur\x81" "ck zum Hauptmen\x81  (5)");
      printf("\n  (1/2/3/4/5): ");

      c = _getch();

      if (c == '1' || c == 't') {

      }

      else if (c == '2' || c == 'g') {

      }

      else if (c == '3' || c == 's') {

      }

      else if (c == '4') {

      }

      else if (c == '5') {
        printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
        printf("\n  (J/N) ");
        char e = _getch();
        if(e == 'j') menü = true;
      }

      else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5')
      {
        printf("\n  Falsche Eingabe ");
        system("timeout 1 >null");
        system("cls");
        break;
      }

    }

  }



  return 0;
}

struKarten* verteile_User() {
  return 0;
}

struKarten* verteile_PC() {
  return 0;
}

struKarten* vergleiche() {
  return 0;
}


void end()
{
  system("cls");

  printf("\n\n");
  printf("  oooooooooooo                   .o8           \n");
  printf("  `888'     `8                  '888           \n");
  printf("   888         ooo. .oo.    .oooo888   .d88b.  \n");
  printf("   888oooo8    `888P'Y88b  d88' `888  d8P  Y8b \n");
  printf("   888    '     888   888  888   888  88888888 \n");
  printf("   888       o  888   888  888   888  Y8b.     \n");
  printf("  o888ooooood8 o888o o888o `Y8bod88P'  'Y8888' \n\n\n");

  Sleep(900);
}

int rundestart()
{
  system("cls");

  for (int i = 0; i <= 3; i++) {
    system("cls");

    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt.");
    printf("\n\n  Bitte Warten");

    Sleep(500);


    system("cls");

    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt..");
    printf("\n\n  Bitte Warten");

    Sleep(500);

    system("cls");

    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt...");
    printf("\n\n  Bitte Warten");

    Sleep(500);
  }

  struKarten* pStart = NULL;
  pStart = karten(pStart, füllkarten(1, "Barbar", 0, 0, 0));
  pStart = karten(pStart, füllkarten(2, "Bogenschuetzin", 0, 0, 0));
  pStart = karten(pStart, füllkarten(3, "Drache", 0, 0, 0));
  pStart = karten(pStart, füllkarten(4, "P.E.K.K.A", 0, 0, 0));
  pStart = karten(pStart, füllkarten(5, "Hexe", 0, 0, 0));
  pStart = karten(pStart, füllkarten(6, "Schweinereiter", 0, 0, 0));
  pStart = karten(pStart, füllkarten(7, "Lakai", 0, 0, 0));
  pStart = karten(pStart, füllkarten(8, "Tunnelgraeber", 0, 0, 0));
  pStart = karten(pStart, füllkarten(9, "Riese", 0, 0, 0));
  pStart = karten(pStart, füllkarten(10, "Ballon", 0, 0, 0));

  ausgabe(pStart);
  return 0;
}

struKarten* karten(struKarten* pStart, struKarten* pNew)
{
  
  if (pStart == NULL) {
    pStart = pNew;
    pNew->pNext = NULL;
  }
  else {
    struKarten* pLast = pStart;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pNew;
  }
  return pStart;
}

struKarten* füllkarten(int pTruppe, const char* pBez, int Hp, int Spd, int Dmg)
{

  struKarten* pTmp = (struKarten*)malloc(sizeof(struKarten));

  pTmp->Nr = pTruppe;
  strcpy_s(pTmp->Bez, pBez);
  pTmp->Trefferpunkte = Hp;
  pTmp->Geschw = Spd;
  pTmp->Schaden = Dmg;
  pTmp->pNext = NULL;

  return pTmp;
}

void einstellungen(bool first, bool root)
{
  //variablen
  char eingabe;
  bool debug;
  bool settings = true;

  char neue_hintergrundfarbe;
  char hintergrundfarbe;
  char textfarbe;
  char neue_textfarbe;

  //Erste Ausführung
  if (first == true)
  {
    char hintergrundfarbe = '0';
    char textfarbe = '7';
    first = false;
  }

  while (settings == true)
  {
    system("cls");

    logo();

    printf("\n  ==================================");
    printf("\n  Einstellungen:     ");
    printf("\n  Farbe           (1)");
    printf("\n  Version         (2)");
    printf("\n  Entwicklermodus (3)");
    printf("\n  Zur\x81""ck          (4)");
    printf("\n  ==================================");
    printf("\n\n  (1/2/3/4): ");

    eingabe = _getch(); //getch oder getche (getche gibt ein Echo mit aus.)

    if (eingabe      == '1')
    {
      char aktiviert[6]   = {'A','k','t','i','v','\0'};
      char deaktiviert[6] = {' ',' ','-',' ',' ','\0'};
      system("cls");

      printf("\n\n  Farben:");
      printf("\n  ==================================");
      printf("\n  *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
      printf("\n   Nur eine Farbe kann Aktiv sein.");


      //Farben die zur Auswahl stehen (kann noch mehr dazu kommen)
      printf("\n  Hintergrundfarbe      |  Textfarbe                                ");
      printf("\n  ======================|=======================");
      printf("\n  Schwarz = 1  [%s]  |  Schwarz = 1  [%s]", deaktiviert, deaktiviert);
      printf("\n  Grau    = 2  [%s]  |  Grau    = 2  [%s]", deaktiviert, deaktiviert);
      printf("\n  Weiss   = 3  [%s]  |  Weiss   = 3  [%s]", deaktiviert, deaktiviert);
      printf("\n  Grün    = 4  [%s]  |  Grün    = 4  [%s]", deaktiviert, deaktiviert); //Gr\x81n
      printf("\n  Blau    = 5  [%s]  |  Blau    = 5  [%s]", deaktiviert, deaktiviert);
      printf("\n  Rot     = 6  [%s]  |  Rot     = 6  [%s]", deaktiviert, deaktiviert);
      printf("\n  ======================|=======================");

      printf("\n  Hintergrundfarbe (1) ");
      printf("\n  Textfarbe        (2)");
      printf("\n  Zur\x81""ck      (3)");

      printf("\n  (1/2/3) ");
      eingabe = _getch();
      if (eingabe == '1') {
        printf("\n  Hintergrundfarbe: ");
        eingabe = _getch();
      }
      else if (eingabe == '2') {
        printf("\n  Textfarbe: ");
        eingabe = _getch();
      }
      else if (eingabe != '1' && eingabe != '2' && eingabe != '3')
      {
        printf("\n  Falsche Eingabe ");
        system("timeout 1 >null");
        system("cls");
      }
    }
    else if (eingabe == '2')
    {
      system("cls");
      logo();
      printf("\n\n      .@@@@@@@@@@@@@@@@@@.                                        .@@@@@@@@            \n");
      printf("      @                  @.                                    @@@@@@@@@@@@@           \n");
      printf("     @@                  @@.                                  @@@@@@@@@@@@@@@@         \n");
      printf("    @@                    @@                                 ,@@@@@@@@       @@        \n");
      printf("    @@                    &@                                @  @@@@'           @       \n");
      printf("    @ @@@@@@@    .@@@@@@@@ @.                             ,@                    @ ,@.  \n");
      printf("    @@   (o)      (O)     @@@                             @@ @@@@    /@@@@@.    @@  @  \n");
      printf("   .@@        ((           @@         Version 1.1         @@  (O)      (O)     .@@  @  \n");
      printf("   @@@  @@@@@@@@@@@@@@@    @@          x64-Debug          @        /           @@@.(.) \n");
      printf("       @@ ########## @@@                                  @       (@.          @@@     \n");
      printf("      @@@            @@@                                 .@@@@@@@@@@@@@@@@@@   @@,     \n");
      printf("      @@ ##________## @@@                                @@@@ ########## @@@@ .@@*     \n");
      printf("      @@@ '########'  @@@                                '@@@              @@@@@@*     \n");
      printf("      @@@             @@@           Clash Of Clans        @@@@ #########,@@@@@@@       \n");
      printf("       @               @               Quartett!           @@@@@@@@@@@@@@@@@@@         \n");
      printf("       @               @                                     @@@@@@@@@@@@@@@@          \n");
      system("timeout 3 >null");

    }
    else if (eingabe == '3') {
      if (root == true) {
        root = false;
        printf("\n  Entwicklermodus Deativiert ");
        system("timeout 1 >null");
        system("cls");
      }
      else if (root == false) {
        root = true;
        printf("\n  Entwicklermodus Aktiviert ");
        system("timeout 1 >null");
        system("cls");
      }
    }
    else if (eingabe == '4') settings = false;
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4')
    {
      printf("\n  Falsche Eingabe ");
      system("timeout 1 >null");
      system("cls");
    }
  }
  ///vlt return Wert für Entwicklermodus und Farbe?////////////////////////////////////////////////////////////////////////////////////////////////
}

void farbmatrix(char hintergrundfarbe, char textfarbe)
{
  //Alles mit schwarzem Hintergrund
  if (hintergrundfarbe == '0' && textfarbe == '7')      system("color 07");
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
