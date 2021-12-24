#include <stdlib.h> 
#include <stdio.h>  
#include <string.h>     //Wird für "string"-Funktionen benötigt.
#include <string>   
#include <time.h>       //Wird für "random"-Funktionen benötigt.
#include <conio.h>      //Wird für Tastatureingaben benötigt.
#include <Windows.h>    //Wird für Sleep-Funktion benötigt.


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
struKarten* ausgabe(struKarten*, struKarten*);                  // Test-Methode für Ausgabe der Karten
struKarten* createlist(struKarten*, struKarten*);               // Funktion für das Kreieren von Listen und Hinzufügen von Karten mit Hilfe der Methode karte
struKarten* removelist(struKarten*, struKarten*);               // Funktion für das Entfernen von einer Karte/n aus einer Liste
struKarten* karte(int, const char*, int, int, int);             // Funktion für das Erstellen und Abfüllen der Karten mit Werten

struKarten* firstlast(struKarten*);                             // Funktion für das Verschieben der 1. und der gewonnenen Karte an den letzten Platz
struKarten* vergleiche(int, struKarten*, struKarten*);          // Funktion für das Vergleichen von Karten aus zwei Listen


int listcount(struKarten*);                                     // Einfache Funktion fürs Zählen von Elementen in einer Liste
int menü();                                                     // Hauptmenü
int einstellungen();                                            // Einstellungen
void farbmatrix(char, char);                                    // Farbmatrix fürs Einstellen der Farben der CMD
int rundestart();                                               // Start einer Runde
void falsche_eingabe();                                         // Einfache Ausgabe bei falscher Eingabe
void end();                                                     // Ausgabe für Spielende wenn man das Spiel verlässt
void logo();                                                    // Ausgabe für Logo des Spiels
int random(int, int);                                           // Zufällige Zahl mit Angabe von Wertebereich


// Globale Variablen
bool admin = false;                                             // Wird für die Einstellungen/Entwicklermodus benötigt.
bool first = true;                                              // Wird für die Einstellungen/Farben benötigt.
char hintergrundfarbe;                                          // Hintergrundfarbe der CMD.
char textfarbe;                                                 // Textfarbe der CMD.

struKarten* ausgabe(struKarten* pListePlayer, struKarten* pListeCPU) {

  char c;
  bool menü = false;
  bool nextkarte_win = false;
  bool nextkarte_lose = false;
  

  for (pListePlayer; pListePlayer != NULL && !menü; pListePlayer = pListePlayer->pNext) {
    nextkarte_win = false;
    nextkarte_lose = false;

    int AnzPlayer;
    AnzPlayer = listcount(pListePlayer);    // Zählt Anzahl Karten im eigenen Stapel.

    int AnzCPU;
    AnzCPU = listcount(pListeCPU);          // Zählt Anzahl Karten im CPU-Stapel.

    while (!nextkarte_win && !nextkarte_lose && !menü) {
      system("cls");

      printf("\n\n");
      printf("\n  ==================================");
      printf("\n");
      printf("\n   _______________________________ ");
      printf("\n  /                               \x5C");
      printf("\n  | CoC Quartett  |  Karte Nr. %-2i |", pListePlayer->Nr);
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |-------------------------------|");
      printf("\n  |---------%-14s--------|", pListePlayer->Bez);
      printf("\n  |-------------------------------|");
      printf("\n  |                               |");
      printf("\n  |                               |");
      printf("\n  |   -----------------------     |");
      printf("\n  |   |Trefferpunkte   | %4i|    |", pListePlayer->Trefferpunkte);
      printf("\n  |   |                |     |    |");
      printf("\n  |   |Geschwindigkeit | %4i|    |", pListePlayer->Geschw);
      printf("\n  |   |                |     |    |");
      printf("\n  |   |Schaden         | %4i|    |", pListePlayer->Schaden);
      printf("\n  |   -----------------------     |");
      printf("\n  |                               |");
      printf("\n  \x5C_______________________________/");
      printf("\n\n");
      printf("\n  =================================");

      char* pNaechste = pListePlayer->pNext->Bez;
      printf("\n\n\n  Ihre N\x84""chste Karte lautet: %-14s ", pNaechste);
      printf("\n  Sie besitzen insgesamt noch %i Karten.", AnzPlayer);
      /* */
      printf("\n\n\n  Trefferpunkte?         (1)");
      printf("\n  Geschwindigkeit?       (2)");
      printf("\n  Schaden?               (3)");
      printf("\n\n  Neu Starten            (4)");
      printf("\n  Zur\x81" "ck zum Hauptmen\x81   (5)");
      printf("\n\n  (1/2/3/4/5): ");

      c = _getch();

      if (c == '1' || c == 't') {
        printf("\n\n  M\x94""chten Sie wirklich Trefferpunkte abfragen?");
        printf("\n  (J/N) ");
        //vergleiche(1, pListePlayer, pListeCPU);
      }

      else if (c == '2' || c == 'g') {
        printf("\n\n  M\x94""chten Sie wirklich Geschwindigkeit abfragen?");
        printf("\n  (J/N) ");
        //vergleiche(2, pListePlayer, pListeCPU);
      }

      else if (c == '3' || c == 's') {
        printf("\n\n  M\x94""chten Sie wirklich Schaden?");
        printf("\n  (J/N) ");
        //vergleiche(3, pListePlayer, pListeCPU);

      }

      else if (c == '4') {
        printf("\n\n  M\x94""chten Sie wirklich das Spiel neustarten?");
        printf("\n  (J/N) ");

        char e = _getch();
        if (e == 'j') bool neustart = true;
      }

      else if (c == '5') {
        printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
        printf("\n  (J/N) ");

        char e = _getch();
        if (e == 'j') menü = true;
      }

      else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5')
      {
        falsche_eingabe();
      }

    }
  }
  return 0;
}

struKarten* firstlast(struKarten* pStart)
{
  struKarten* pTempFirst = pStart;
  struKarten* pTempLast = pStart;
  struKarten* pTempLastMinus = NULL;

  int f; //waren gedacht als index für eine for schleife
  int l; //waren gedacht als index für eine for schleife
  int lm; //waren gedacht als index für eine for schleife

  while (pTempLast->pNext != NULL)
  {

    pTempLastMinus = pTempLast;
    pTempLast = pTempLast->pNext;

    printf("pTempFirst %i\n", f = pTempFirst->Nr);
    printf("pTempLast %i\n", l = pTempLast->Nr);
    printf("pTempLastMinus %i\n\n", lm = pTempLastMinus->Nr);
  }
  printf("==================================\n");


  pTempLast->pNext = pTempFirst;

  pStart = pTempFirst->pNext;
  pTempLast->pNext->pNext = NULL;
  pStart->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext = pTempLast->pNext;

  pTempLast = pStart;

  while (pTempLast->pNext != NULL)
  {

    pTempLastMinus = pTempLast;
    pTempLast = pTempLast->pNext;

    //printf("pTempFirst %i\n", pTempFirst->Nr);
    //printf("pTempLast %i\n", pTempLast->Nr);
    //printf("pTempLastMinus %i\n\n", pTempLastMinus->Nr);

    int z = pTempLast->Nr;
    //Zum Testen
    printf("pTemp Zeigt auf die Karte Nr: %i \n", z);

  }
  printf("==================================\n");

  system("pause");

  return 0;
}

struKarten* vergleiche(int typ, struKarten* pListePlayer, struKarten* pListeCPU) {
  return 0;
}

struKarten* createlist(struKarten* pListe, struKarten* pKarte)
{

  if (pListe == NULL) {   // Als erstes die Referenz zur ersten Karte "pStart", bzw. der Liste, die anfängt mit pStart.
    pListe = pKarte;      // Wenn diese Liste leer ist, dann referenziert pNew mit dem ganzen Inhalt auf die erste Karte "pStart".
    pKarte->pNext = NULL; // Die nächste Karte existiert dann noch nicht. Die Referenz dazu ist vorerst leer.
  }
  else {
    struKarten* pLast = pListe; // Beispiel: "Barbar" wird von pLast referenziert, weil zu Beginn die erste Karte auch die letzte ist.
    while (pLast->pNext != NULL) {
      pLast = pLast->pNext;     // Schleife: Zum finden der letzten Karte. Solange die Referenz auf die nächste Karte jeder Karte nicht NULL, also nicht leer ist,
                                // ist diese die letzte Karte. Wird beim ersten mal gar nicht ausgeführt weil Barbar schon die letzte Karte ist und keinen pNext hat.
    }
    pLast->pNext = pKarte;      // Jeder neue Inhalt, der sich in pNew befindet (Beispiel: Bogenschützin) ist die nächste Karte der temporär "letzten" Karte (Beispiel: Barbar).
  }
  return pListe;                // Die Liste wird samt allen neuen Elementen zurückgegeben.
}

struKarten* removelist(struKarten* pListe, struKarten* pKarte)
{
  if (pListe == pKarte)
  {
    pListe = pListe->pNext;
    pKarte->pNext = NULL;
  }

  else
  {
    struKarten* pTmp = pListe;
    while (pTmp->pNext != pKarte) {
      pTmp = pTmp->pNext;
    }
    pTmp->pNext = pKarte->pNext;
    pKarte->pNext = NULL;
  }


  return pListe;
}

struKarten* karte(int pTruppe, const char* pBez, int Hp, int Spd, int Dmg)
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

int listcount(struKarten* pListe) {
  int anz = 0;
  struKarten* pTmp = pListe;
  for (pTmp; pTmp != NULL; pTmp = pTmp->pNext) {  // Es werden alle Elemente im eigenen Kartenstapel gezählt.
    anz++;
  }
  return anz;
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

  struKarten* pListePlayer = NULL;  //Erstellt Liste von Player
  struKarten* pListeCPU = NULL;     //Erstellt Liste von CPU
  struKarten* pStart = NULL;        //Erstellt Startliste mit der gearbeitet wird

  pStart = createlist(pStart, karte(1, "Barbar", 160, 16, 30));
  pStart = createlist(pStart, karte(2, "Bogenschuetzin", 48, 24, 25));
  pStart = createlist(pStart, karte(3, "Drache", 3100, 16, 240));
  pStart = createlist(pStart, karte(4, "P.E.K.K.A", 5300, 16, 470));
  pStart = createlist(pStart, karte(5, "Hexe", 300, 12, 100));
  pStart = createlist(pStart, karte(6, "Schweinereiter", 270, 24, 60));
  pStart = createlist(pStart, karte(7, "Lakai", 58, 32, 38));
  pStart = createlist(pStart, karte(8, "Tunnelgraeber", 610, 32, 88));
  pStart = createlist(pStart, karte(9, "Riese", 800, 12, 31));
  pStart = createlist(pStart, karte(10, "Ballon", 390, 10, 108));

  int runde = 0;    // Verteilen: Runde 1 bis 5 werden dem Player Karten zugeteilt, der Rest der noch in pStart übrig bleibt gehört dem CPU.
  struKarten* pTmp; // Temporäre Variable fürs Zählen in einer 

  for (runde; runde < 5; runde++)
  {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt.
    //int pEnd = 1;
    
    // int r = random(1, listcount); // Zufällige Zahl, die nicht grösser als die Liste ist, mit der man arbeitet.

    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    int z = 0;
    for (int c = 1; c <= r; c++)
    {
      pKarte = pKarte->pNext;
      z = pKarte->Nr;
    }

    /*
    //Ausgabe zum Testen
    printf("\n  Die zuf\xE4llige Karte ist Karte Nr: %i ", z);
    printf("\n  Diese Karte heisst %c.", pKarte->Bez);
    printf("\n  Diese wird jetzt aus der Startliste entfernt.");
    system("pause");
    */

    pStart = removelist(pStart, pKarte);
    pListePlayer = createlist(pListePlayer, pKarte);
  }

  pListeCPU = pStart;

  //firstlast(pStart);

  ausgabe(pListePlayer, pListeCPU);

  return 0;
}

int main()
{
  srand(time(NULL));                                            // Rand Initialisierung für die Methode "random".
  system("mode con cols=150 lines=45");                         // Setzt die Grösse der CMD

  menü();                                                       // Menü wird Aufgerufen
  end();                                                        // Spiel wird beendet

  return 0;
}

int menü()
{
  bool hauptmenü = true; // Überprüft ob das Menü geschlossen werden soll.

  while (hauptmenü)
  {
    //variablen
    char eingabe; // Variable für Eingabe

    system("cls"); // Leeren des Bildschirms

    logo();

    printf("\n  ==================================");
    printf("\n  W\x84hlen Sie ihren Spielmodus:");
    printf("\n  Spiel starten     (1)");
    printf("\n  Einstellungen     (2)");
    printf("\n  Beenden           (3)");
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
      einstellungen();
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
      falsche_eingabe();
    }
  }
  return 0;
}

int random(int min, int max) {
  // Random-Funktion, wo Zahlen für das zufällige Verteilen der Karten 
  int r = rand() % max + min;

  return(r);
}

int einstellungen()
{
  //variablen
  bool debug;
  bool settings = true;
  bool farben = true;

  char eingabe;
  char neue_hintergrundfarbe;
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

    if (eingabe == '1')
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

          else if (neue_hintergrundfarbe == textfarbe) {
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
      if (admin == true) {
        admin = false;
        printf("\n  Entwicklermodus Deativiert ");
        system("timeout 1 >null");
        system("cls");
      }
      else if (admin == false) {
        admin = true;
        printf("\n  Entwicklermodus Aktiviert ");
        system("timeout 1 >null");
        system("cls");
      }
    }
    else if (eingabe == '4') settings = false;
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4') falsche_eingabe();
  }
  return 0;
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