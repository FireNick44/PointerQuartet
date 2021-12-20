#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> //Wird für "string" Funktionen benötigt.
#include <string>   
#include <time.h>   //Wird für "random" Funktionen benötigt.
#include <conio.h>   //Wird für Tastatur Eingaben benötigt.
#include <Windows.h>


typedef struct Karten // Struktur für Karten 
{
  int Nr;
  char Bez[40];
  int Trefferpunkte;
  int Geschw;
  int Schaden;
  struct Karten* pNext;
}struKarten;


//Prototypen der Methoden

struKarten* ausgabe(struKarten*);                               // Test Methode
struKarten* karten(struKarten*, struKarten*);                   // Funktion für das Mischen und Verteilen der Karten
struKarten* originlist(int, const char*, int, int, int);        // Funktion für das Abfüllen der Karten mit Werten
struKarten* playerlist(int, const char*, int, int, int);        // Funktion für das Abfüllen der Karten des Users mit Werten
struKarten* cpulist(int, const char*, int, int, int);           // Funktion für das Abfüllen der Karten des CPU-Spielers mit Werten
struKarten* remove(struKarten*);                                // Funktion für das Entfernen von Karten aus einer Liste
struKarten* add(struKarten*);                                   // Funktion für das Entfernen von Karten aus einer Liste
struKarten* vergleiche(struKarten*);                            // Funktion für das Entfernen von Karten aus einer Liste

int menü();
int einstellungen(bool, bool);                                  // Einstellungen
void farbmatrix(char, char);                                    // Farbmatrix fürs Einstellen der Farben
int rundestart();                                               // Start einer Runde
void falsche_eingabe();                                         // Einfache Ausgabe bei falscher Eingabe
void end();                                                     // Ausgabe für Spielende
void logo();                                                    // Ausgabe für Logo des Spiels
int random(int, int);                                           // Zufällige Zahl mit Angabe von Wertebereich



int main()
{
  // Rand Initialisierung für die Methode "random".
  srand(time(NULL));

  system("mode con cols=75 lines=35");

  menü();
  end();


  return 0;
}

int menü()
{
  bool admin = false;
  bool first = true;

  bool hauptmenü = true;
  while (hauptmenü)
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
      einstellungen(first, admin);
    }

    //Ende
    else if (eingabe == '3')
    {
      printf("\n\n  M\x94""chten Sie das Spiel wirklich beenden?");
      printf("\n  (J/N) ");

      eingabe = _getch();

      if (eingabe == 'J' || eingabe == 'j') hauptmenü = false;
    }

    //falsche Eingabe
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3')
    {
      printf("\n  Falsche Eingabe ");
      system("timeout 1 >null");
      system("cls");
    }
  }
  return 0;
  //menü hier
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
  bool nextkarte_win = false;
  bool nextkarte_lose = false;

  for (struKarten* pOut = pStart; pOut != NULL && !menü && !nextkarte_lose && !nextkarte_win; pOut = pOut->pNext) {
    nextkarte_win = false;
    nextkarte_lose = false;

    while (!nextkarte_win && !nextkarte_lose && !menü) {
      system("cls");

      printf("\n\n");
      printf("\n  ==================================");
      printf("\n\n");
      printf("\n   _______________________________ ");
      printf("\n  /                               \x5C");
      printf("\n  | CoC Quartett  |  Karte Nr. %-2i |", pStart->Nr);
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |%*31s|", pStart->Bez);
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |   Trefferpunkte  :%4i        |", pStart->Trefferpunkte);
      printf("\n  |                               |");
      printf("\n  |   Geschwindigkeit:%4i        |", pStart->Geschw);
      printf("\n  |                               |");
      printf("\n  |   Schaden        :%4i        |", pStart->Schaden);
      printf("\n  |                               |");
      printf("\n  \x5C_______________________________/");
      printf("\n  Ihre Naechste Karte: %14s ", pStart->pNext->Bez);
      /* */

      printf("\n\n\n  Trefferpunkte?         (1)");
      printf("\n  Geschwindigkeit?       (2)");
      printf("\n  Schaden?               (3)");
      printf("\n  =================================");
      printf("\n\n  Neu Starten            (4)");
      printf("\n\n  Aufgeben und zur nächsten Karte (5)");
      printf("\n  Zur\x81" "ck zum Hauptmen\x81   (6)");
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
        printf("\n\n  M\x94""chten Sie wirklich diese Karte aufgeben und zur n\x84""chsten?");
        printf("\n  (J/N) ");
        char e = _getch();
        if(e == 'j') nextkarte_lose = true;
      }

      else if (c == '6') {
        printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
        printf("\n  (J/N) ");
        char e = _getch();
        if (e == 'j') menü = true;
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


  while (true)
  {

  }
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

  Sleep(400);
}

int rundestart()
{
  system("cls");

  /*for (int i = 0; i < 3; i++) {
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
  }*/

  struKarten* pStart = NULL;
  pStart = karten(pStart, originlist(1, "Barbar", 0, 0, 0));
  pStart = karten(pStart, originlist(2, "Bogenschuetzin", 0, 0, 0));
  pStart = karten(pStart, originlist(3, "Drache", 0, 0, 0));
  pStart = karten(pStart, originlist(4, "P.E.K.K.A", 0, 0, 0));
  pStart = karten(pStart, originlist(5, "Hexe", 0, 0, 0));
  pStart = karten(pStart, originlist(6, "Schweinereiter", 0, 0, 0));
  pStart = karten(pStart, originlist(7, "Lakai", 0, 0, 0));
  pStart = karten(pStart, originlist(8, "Tunnelgraeber", 0, 0, 0));
  pStart = karten(pStart, originlist(9, "Riese", 0, 0, 0));
  pStart = karten(pStart, originlist(10, "Ballon", 0, 0, 0));

  struKarten* pStartPlayer = NULL;
  struKarten* pStartCPU = NULL;

  //int runde = 0; //Runde 1 bis 5 = Player / Runde 6 bis 10 = CPU
  //while (runde >= 10) {
  //  if(pStartPlayer == NULL) //Wenn in Player noch keine Karte ist
  //  {
  //    pStartCPU = Temp;
  //  }
  //  else if (pStartCPU == NULL) //Wenn in CPU noch keine Karte ist
  //  {
  //    pStartPlayer = Temp;
  //  }
  //  else if(pStartPlayer != NULL) //Wenn in Player eine Karte ist
  //  {
  //    pStartPlayer->pNext = pTemp;
  //  }
  //  else if(pStartCPU != NULL) //Wenn in CPU eine Karte ist
  //  {
  //    pStartPlayer->pNext = pTemp;
  //  }
  //}
 




  struKarten* pTemp = pStart;
  int listcount = 1;
  //int pEnd = 1;

  while (pTemp->pNext != NULL) {
    pTemp = pTemp->pNext;
    listcount++;
  }


  int r = random(1, listcount);

  for (int c = 0; c != r; c++)
  {
    pTemp = pTemp->pNext;
  }
    pStartPlayer = pTemp;



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
    struKarten* pLast = pStart; // Beispiel: "Barbar" wird in pLast hineingeschrieben.
    while (pLast->pNext != NULL) pLast = pLast->pNext; // Solange Barbars nächste Karte nicht NULL ist, ist diese die letzte Karte
    pLast->pNext = pNew; // 
  }
  return pStart;
}

struKarten* originlist(int pTruppe, const char* pBez, int Hp, int Spd, int Dmg)
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

struKarten* playerlist(int pTruppe, const char* pBez, int Hp, int Spd, int Dmg)
{

  struKarten* pTmp = (struKarten*)malloc(sizeof(struKarten));



  return pTmp;
}

struKarten* cpulist(int pTruppe, const char* pBez, int Hp, int Spd, int Dmg)
{

  struKarten* pTmp = (struKarten*)malloc(sizeof(struKarten));

  return pTmp;
}

int einstellungen(bool first, bool root)
{
  //variablen
  bool debug;
  bool settings = true;
  bool farben = true;

  char eingabe;
  char neue_hintergrundfarbe;
  char hintergrundfarbe;
  char textfarbe;
  char neue_textfarbe;

  //Erste Ausführung


  while (settings)
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
      farben = true;
      while (farben)
      {
        char on[6] = { 'A','k','t','i','v','\0' };
        char off[6] = { ' ',' ','-',' ',' ','\0' };

        char s_h[6] = { ' ',' ','-',' ',' ','\0' };
        char g_h[6] = { ' ',' ','-',' ',' ','\0' };
        char w_h[6] = { ' ',' ','-',' ',' ','\0' };
        char gr_h[6] = { ' ',' ','-',' ',' ','\0' };
        char b_h[6] = { ' ',' ','-',' ',' ','\0' };
        char r_h[6] = { ' ',' ','-',' ',' ','\0' };

        char s_t[6] = { ' ',' ','-',' ',' ','\0' };
        char g_t[6] = { ' ',' ','-',' ',' ','\0' };
        char w_t[6] = { ' ',' ','-',' ',' ','\0' };
        char gr_t[6] = { ' ',' ','-',' ',' ','\0' };
        char b_t[6] = { ' ',' ','-',' ',' ','\0' };
        char r_t[6] = { ' ',' ','-',' ',' ','\0' };

        if (first) {
          hintergrundfarbe = '0';
          textfarbe = 'F';
          strcpy_s(s_h, on);
          strcpy_s(w_t, on);
          first = false;
        }

        if (hintergrundfarbe == '0')      strcpy_s(s_h, on);
        else if (hintergrundfarbe == '8') strcpy_s(g_h, on);
        else if (hintergrundfarbe == 'F') strcpy_s(w_h, on);
        else if (hintergrundfarbe == '2') strcpy_s(gr_h, on);
        else if (hintergrundfarbe == '1') strcpy_s(b_h, on);
        else if (hintergrundfarbe == '4') strcpy_s(r_h, on);
        
        if (textfarbe == '0')      strcpy_s(s_t, on);
        else if (textfarbe == '8') strcpy_s(g_t, on);
        else if (textfarbe == 'F') strcpy_s(w_t, on);
        else if (textfarbe == '2') strcpy_s(gr_t, on);
        else if (textfarbe == '1') strcpy_s(b_t, on);
        else if (textfarbe == '4') strcpy_s(r_t, on);


        system("cls");

        printf("\n\n  Farben:");
        printf("\n  ==============================================");
        printf("\n  *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
        printf("\n   Nur eine Farbe kann Aktiv sein.");

        //Farben die zur Auswahl stehen (kann noch mehr dazu kommen)
        printf("\n  Hintergrundfarbe      |  Textfarbe                                ");
        printf("\n  ======================|=======================");
        printf("\n  Schwarz = 1  [%s]  |  Schwarz = 1  [%s]", s_h, s_t);
        printf("\n  Grau    = 2  [%s]  |  Grau    = 2  [%s]", g_h, g_t);
        printf("\n  Weiss   = 3  [%s]  |  Weiss   = 3  [%s]", w_h, w_t);
        printf("\n  Gr\x81n    = 4  [%s]  |  Gr\x81n    = 4  [%s]", gr_h, gr_t);
        printf("\n  Blau    = 5  [%s]  |  Blau    = 5  [%s]", b_h, b_t);
        printf("\n  Rot     = 6  [%s]  |  Rot     = 6  [%s]", r_h, r_t);
        printf("\n  ======================|=======================");

        printf("\n  Hintergrundfarbe (1) ");
        printf("\n  Textfarbe        (2)");
        printf("\n  Zur\x81""ck           (3)");

        printf("\n  (1/2/3) ");
        eingabe = _getch();
        if (eingabe == '1')
        {
          printf("\n  ==============================================");
          printf("\n\n  Hintergrundfarbe: ");
          eingabe = _getch();

          if (eingabe == '1') neue_hintergrundfarbe = '0';
          else if (eingabe == '2') neue_hintergrundfarbe = '8';
          else if (eingabe == '3') neue_hintergrundfarbe = 'F';
          else if (eingabe == '4') neue_hintergrundfarbe = '2';
          else if (eingabe == '5') neue_hintergrundfarbe = '1';
          else if (eingabe == '6') neue_hintergrundfarbe = '4';
          else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4' && eingabe != '5' && eingabe != '6') falsche_eingabe();

          if (neue_hintergrundfarbe != textfarbe) {
            hintergrundfarbe = neue_hintergrundfarbe;
            farbmatrix(hintergrundfarbe, textfarbe);
          }

          else if (neue_hintergrundfarbe == textfarbe){
            printf("\n  *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
            system("timeout 1 >null");
            system("cls");
          }

        }
        else if (eingabe == '2') {
          printf("\n  ==============================================");
          printf("\n\n  Textfarbe: ");
          eingabe = _getch();

          if (eingabe == '1') neue_textfarbe = '0';
          else if (eingabe == '2') neue_textfarbe = '8';
          else if (eingabe == '3') neue_textfarbe = 'F';
          else if (eingabe == '4') neue_textfarbe = '2';
          else if (eingabe == '5') neue_textfarbe = '1';
          else if (eingabe == '6') neue_textfarbe = '4';
          else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4' && eingabe != '5' && eingabe != '6') falsche_eingabe();

          if (neue_textfarbe != hintergrundfarbe) {
            textfarbe = neue_textfarbe;
            farbmatrix(hintergrundfarbe, textfarbe);
          }
          else if (neue_textfarbe == hintergrundfarbe) {
            printf("\n  *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
            system("timeout 1 >null");
            system("cls");
          }

        }
        else if (eingabe == '3') farben = false;
        else if (eingabe != '1' && eingabe != '2' && eingabe != '3') falsche_eingabe();
      }
    }
    else if (eingabe == '2')
    {
      system("cls");
      logo();
      printf("\n\n");
      printf("      .@@@@@@@@@@@@@@@@@@.                                        .@@@@@@@@            \n");
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
      printf("                                       Quartett!           @@@@@@@@@@@@@@@@@@@         \n");
      printf("                                                             @@@@@@@@@@@@@@@@          \n");
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
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4') falsche_eingabe();
  }
  return(root);
}

void farbmatrix(char hintergrundfarbe, char textfarbe)
{
  char SysPrint[20];

  sprintf_s(SysPrint, "color %c%c", hintergrundfarbe, textfarbe);
  system(SysPrint);
}

void falsche_eingabe()
{
  printf("\n  Falsche Eingabe ");
  system("timeout 1 >null");
  system("cls");
}