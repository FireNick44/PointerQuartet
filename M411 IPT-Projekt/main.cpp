#include <stdlib.h> 
#include <stdio.h>  
#include <string.h>     //Wird für "string"-Funktionen benötigt.
#include <string>   
#include <time.h>       //Wird für "random"-Funktionen benötigt.
#include <conio.h>      //Wird für Tastatureingaben benötigt.
#include <Windows.h>    //Wird für Sleep-Funktion benötigt.


// Struktur für Karten
typedef struct Karten
{
  int Nr;
  char Bez[40];
  int Trefferpunkte;
  int Geschw;
  double Schaden;
  struct Karten* pNext;
}struKarten;


// Prototypen der Methoden
void rundestart();                                              // Start einer Runde
void ausgabe(struKarten*, struKarten*);                         // Funktion für Ausgabe der Karten
struKarten* createlist(struKarten*, struKarten*);               // Funktion für das Kreieren von Listen und Hinzufügen von Karten mit Hilfe der Methode "karte"
struKarten* removelist(struKarten*, struKarten*);               // Funktion für das Entfernen von einer Karte/n aus einer Liste
struKarten* karte(int, const char*, int, int, double);          // Funktion für das Erstellen und Abfüllen der Karten mit Werten
struKarten* firstlast_gew(struKarten*, struKarten*);            // Funktion für den Gewinner einer Karte
struKarten* firstlast_verl(struKarten*);                        // Funktion für den Verlierer einer Karte
struKarten* firstlast_unent(struKarten*);                       // Funktion für Unentschieden
int vergleiche(int, struKarten*, struKarten*);                  // Funktion für das Vergleichen von Karten aus zwei Listen
void vergleiche_karten(struKarten*, struKarten*);               // Funktion für die Ausgabe von Karten nebeneinander für das visuelle Vergleichen
void ausgabe_kartenbild(struKarten*);                           // Funktion für die Ausgabe von Kartenbilder 

int listcount(struKarten*);                                     // Einfache Funktion fürs Zählen von Elementen in einer Liste
void menü();                                                    // Hauptmenü
void einstellungen();                                            // Einstellungen
void farbmatrix(char, char);                                    // Farbmatrix fürs Einstellen der Farben auf der CMD
void falsche_eingabe();                                         // Einfache Ausgabe bei falscher Eingabe
void end();                                                     // Ausgabe für Spielende wenn man das Spiel verlässt
void logo();                                                    // Ausgabe für Logo des Spiels
void verloren();                                                // Ausgabe wenn man eine Karte verliert
void gewonnen();                                                // Ausgabe wenn man eine Karte gewinnt
void unentschieden();                                           // Ausgabe wenn unentschieden

// Weitere Beschreibungen findet man in den einzelnen Funktionen.

// Globale Variablen
bool admin = false;                                             // Wird für den Entwicklermodus benötigt. Es gibt Funktionen, die noch zusätzliche Entwicklermodus-Funktionen beinhalten.
bool first = true;                                              // Wird für die Einstellungen/Farben benötigt.
char hintergrundfarbe = '0';                                    // Hintergrundfarbe der CMD.
char textfarbe = 'F';                                           // Textfarbe der CMD.

void main()
{
  srand(time(NULL));
  system("mode con cols=120 lines=60");    // Setzt die Grösse des CMD-Fensters

  menü();
  end();

}

void menü() {
  // Yannic
  // Diese Funktion beinhaltet das Menü, in dem man navigieren kann.

  bool hauptmenü = true; // Überprüft ob das Menü geschlossen werden soll.

  while (hauptmenü)
  {
    char eingabe; // Variable für Eingabe

    system("cls"); // Leeren des Bildschirms
    logo(); // Ausgabe des Logos
    printf("\n  ==================================");
    printf("\n  ------------Hauptmen\x81-------------");
    printf("\n");
    printf("\n  Spiel starten     (1)");
    printf("\n  Einstellungen     (2)");
    printf("\n  Beenden           (3)");
    printf("\n  ==================================");
    printf("\n");
    printf("\n  (1/2/3): ");

    eingabe = _getch(); //getch oder getche (getche gibt ein Echo mit aus.) Es verarbeitet die Eingabe für das Navigieren.

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
      printf("\n");
      printf("\n  (J/N): ");

      eingabe = _getch();

      if (eingabe == 'J' || eingabe == 'j') hauptmenü = false;
    }

    //falsche Eingabe
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3')
    {
      falsche_eingabe();
    }
  }
}

void rundestart() {
  // Mazen
  // In dieser Funktion startet das Erstellen beider Kartenstapel und die Karten werden verteilt.

  system("cls");

  for (int i = 0; i < 2; i++) {
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und neu gemischt .");
    printf("\n\n  Bitte Warten");
    Sleep(500);
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und neu gemischt ..");
    printf("\n\n  Bitte Warten");
    Sleep(500);
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und neu gemischt ...");
    printf("\n\n  Bitte Warten");
    Sleep(500);
  }

  system("cls");

  printf("\n\n  ==================================\n");

  struKarten* pStart = NULL;        // Erstellt Startliste mit der beim Verteilen gearbeitet wird
  struKarten* pListePlayer = NULL;  // Erstellt Liste von Player
  struKarten* pListeCPU = NULL;     // Erstellt Liste von CPU

  // Einfüllen der Startliste mit Karten
  pStart = createlist(pStart, karte(1, "Barbar", 160, 16, 30.3));
  pStart = createlist(pStart, karte(2, "Magier", 48, 24, 25.7));
  pStart = createlist(pStart, karte(3, "Golem", 3100, 16, 240.1));
  pStart = createlist(pStart, karte(4, "P.E.K.K.A", 5300, 16, 470.3));
  pStart = createlist(pStart, karte(5, "Hexe", 300, 12, 100.2));
  pStart = createlist(pStart, karte(6, "Schweinereiter", 270, 24, 60.0));
  pStart = createlist(pStart, karte(7, "Skelett", 58, 32, 38.2));
  pStart = createlist(pStart, karte(8, "Tunnelgr\x84""ber", 610, 32, 88.7));
  pStart = createlist(pStart, karte(9, "Riese", 800, 12, 31.5));
  pStart = createlist(pStart, karte(10, "Ballon", 390, 10, 108.0));

  int runde;    // Verteilen: Runde 1 bis 5 werden dem Player Karten zugeteilt, Runde 5 bis 10 dem CPU.

  for (runde = 1; runde <= 5; runde++)
  {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt.

    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    for (int c = 1; c <= r; c++) pKarte = pKarte->pNext;

    if (admin) {
      //Ausgabe zum Testen

      printf("\n  Die zuf\x84llige Karte heisst: %14s", pKarte->Bez);

    }

    pStart = removelist(pStart, pKarte);              // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListePlayer = createlist(pListePlayer, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }

  if (admin) {
    printf("\n\n  Diese Karten werden jetzt der Spielerliste hinzugef\x81gt.");
    printf("\n\n");
    system("pause");
  }


  for (runde = 5; runde < 10; runde++)
  {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt. 5 wurden schon entfernt.
    //int pEnd = 1;


    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    for (int c = 1; c <= r; c++) pKarte = pKarte->pNext;

    if (admin) {
      //Ausgabe zum Testen
      printf("\n  Die zuf\x84llige Karte heisst: %14s", pKarte->Bez);

    }




    pStart = removelist(pStart, pKarte);        // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListeCPU = createlist(pListeCPU, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }

  if (admin) {
    printf("\n\n  Diese Karten werden jetzt der CPU-Liste hinzugef\x81gt.");
    printf("\n\n");
    system("pause");
  }


  if (admin) {
    system("cls");

    printf("\n  Jetzt wird das Spiel anfangen.");
    printf("\n\n  ==================================\n");
    system("pause");
  }

  ausgabe(pListePlayer, pListeCPU);
}

int listcount(struKarten* pListe) {
  // Yannic
  // Diese Funktion zählt alle Elemente einer Liste.
  // Der Parameter ist die Liste, aus der gezählt werden soll.

  int anz = 0;
  struKarten* pTmp = pListe;
  for (pTmp; pTmp != NULL; pTmp = pTmp->pNext) anz++;  // Es werden alle Elemente in der Liste gezählt und zurück gegeben.
  return anz;
}

struKarten* karte(int pTruppe, const char* pBez, int Hp, int Spd, double Dmg) {
  // Mazen
  // Diese Funktion verarbeitet die Parameterwerte in eine Karte und gibt die ganze Karte als Pointer zurück.
  // Die Parameter sind die einzelnen einzufüllenden Werte für eine Karte mit abgekürzten Namen.

  struKarten* pTmp = (struKarten*)malloc(sizeof(struKarten));

  pTmp->Nr = pTruppe;
  strcpy_s(pTmp->Bez, pBez);
  pTmp->Trefferpunkte = Hp;
  pTmp->Geschw = Spd;
  pTmp->Schaden = Dmg;
  pTmp->pNext = NULL;

  return pTmp;      // Die Karte wird samt allen Werten zurückgegeben.
}

struKarten* createlist(struKarten* pListe, struKarten* pKarte) {
  // Mazen
  // Diese Funktion fügt die pKarte zur mitgegebenen pListe hinzu.
  // Die Parameter sind sowohl die Liste, als auch die Karte selbst, die hinzugefügt werden soll.

  if (pListe == NULL) {
    pListe = pKarte;
    pKarte->pNext = NULL;
  }
  else {
    struKarten* pLast = pListe;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pKarte;

  }
  return pListe;                                        // Die Liste wird verändert zurückgegeben.
}

struKarten* removelist(struKarten* pListe, struKarten* pKarte) {
  // Yannic
  // Diese Funktion dient zum entfernen von Karten aus einer Liste, in dem die Referenzen neu gesetzt werden.
  // Die Parameter sind sowohl die Liste, als auch die Karte selbst, die entfernt werden soll.

  if (pListe == pKarte) {     
    pListe = pListe->pNext;   
    pKarte->pNext = NULL;     
  }
  
  else {
    struKarten* pTmp = pListe;

    while (pTmp->pNext != pKarte) pTmp = pTmp->pNext;

    pTmp->pNext = pKarte->pNext;
    pKarte->pNext = NULL;
  }

  return pListe;                                          // Die Liste wird verändert zurückgegeben.
}

void ausgabe_kartenbild(struKarten* pListe) {
  // Yannic
  // Diese Funktion beinhaltet die Bilder der Karten und deren Ausgabe.
  // Der Parameter enthaltet die Liste bzw. Karte, in der ausgegeben werden soll.

  // Pointer der mitgegebenen Werte
  struKarten* pPlayer = pListe;

  char barbar[15][30]
  {
    "    .@@@@@@@@@@@@@@@@@@.    \0",
    "    @                  @.   \0",
    "   @@                  @@.  \0",
    "  @@                    @@  \0",
    "  @@                    &@  \0",
    "  @ @@@@@@@    .@@@@@@@@ @. \0",
    "  @@   (o)      (O)     @@@ \0",
    " .@@        ((           @@ \0",
    " @@@  @@@@@@@@@@@@@@@    @@ \0",
    "     @@ ########## @@@      \0",
    "    @@@            @@@      \0",
    "    @@ ##________## @@@     \0",
    "    @@@ '########'  @@@     \0",
    "    @@@             @@@     \0",
    "                            \0",
  };
  char schweinereiter[15][30]
  {
    "         @@@@@@@@@@         \0",
    "       @@@@@@@@@@@@@@       \0",
    "    ,@@@@@@@@       @@      \0",
    "   @  @@@@'           @     \0",
    " ,@                    @ ,@.\0",
    " @@ @@@@    /@@@@@.    @@  @\0",
    " @@  (O)      (O)     .@@  @\0",
    " @        /           @@@(.)\0",
    " @       (@.          @@@   \0",
    ".@@@@@@@@@@@@@@@@@@   @@,   \0",
    "@@@@ ########## @@@@ .@@*   \0",
    "'@@@              @@@@@@*   \0",
    " @@@@ #########,@@@@@@@     \0",
    "  @@@@@@@@@@@@@@@@@@@       \0",
    "    @@@@@@@@@@@@@@@@        \0",
  };
  char ballon[15][30]
  {
    "        @@@@@@@@@@@         \0",
    "     @@@@@@@@@@@@@@@@@      \0",
    "   @@@@@@         @@@@@@    \0",
    "  @@@@@@ (O)   (O) @@@@@@   \0",
    "  @@@@@@     @     @@@@@@   \0",
    "  @@@@@@@  , , ,  @@@@@@@   \0",
    "   @@@@@@@ @ @ @ @@@@@@@    \0",
    "    @@@@@@U@U@U@U@@@@@@     \0",
    "       @@@@@@@@@@@@@        \0",
    "        |  |   |  |         \0",
    "        |  |   |  |  `      \0",
    "       (###########)    `   \0",
    "        @@@@@@@@@@@  ` `    \0",
    "         @@@@@@@@@  `  #  ` \0",
    "                      `  `  \0",
  };
  char riese[15][30]
  {
    "    @                 @     \0",
    "  @@                   @@   \0",
    " @                       @  \0",
    "@@@@@@@@@@@@   @@@@@@@@@@@@ \0",
    "@@@@@@@@@@@@@ @@@@@@@@@@@@@@\0",
    "@        @@@   @@@        @ \0",
    "   ( o )     .     ( o )  @@\0",
    "@@          ,@            @@\0",
    "@@@       ,@@  @.        @@@\0",
    "@@@)        @@@         (@@@\0",
    "@@@@                    @@@@\0",
    " @@@@@   ###########  @@@@@@\0",
    " @@@@@@              @@@@@@ \0",
    "   @@@@@@          @@@@@@   \0",
    "     @@@@@@.     .@@@@@     \0",
  };
  char pekka[15][30]
  {
    "                            \0",
    "@                         @ \0",
    "@@                       @@ \0",
    "@@@@  ,-------------,  @@@@ \0",
    " @@@@@@'           '@@@@@@  \0",
    " @@@@                 @@@@  \0",
    "  @@  @(O)@)   (@(O)@  @@   \0",
    "   |  @@@'   M   '@@@  |    \0",
    "   |  '     MMM     '  |    \0",
    "   |        MMM        |    \0",
    "   |        MMM        |    \0",
    " /MMMMMMMMMM/ \x5CMMMMMMMMMM\x5C  \0",
    "/'         /   \x5C         '\x5C \0",
    "          /     \x5C           \0",
    "                            \0",
  };
  char magier[15][30]
  {
    "    ,@@@@@@@@@@@@@@@@@@,    \0",
    "  @@@@@@@@@@@@@@@@@@@@@@@@  \0",
    " @@@@@@@@@@@@@@@@@@@@@@@@@@ \0",
    "@@@@                    @@@@\0",
    "@@@ Xx                xX @@@\0",
    "@@|  'XXXx,      ,xXXX'  |@@\0",
    "@ |   (O)    ,     (O)   | @\0",
    "@ |         ,@           | @\0",
    "@ |        ,@  @.        | @\0",
    "@@|    @@@@@@@@@@@@@@    |@@\0",
    " @,\x5C   @@ ######## @@   /,@ \0",
    "  @@ \x5C '@          @' / @@  \0",
    "   @@  \x5C@@@@@@@@@@@@/  @@   \0",
    "    @    '@@@@@@@@'    @    \0",
    "   @@       '@@'       @@   \0",
  };
  char hexe[15][30]
  {
    "   ,@@@@@@@@@@@@@@@@@@@@,   \0",
    " @@@@@@@@@@@@@@@@@@@@@@@@@@ \0",
    " @@@@@@@@@@@@@@@@@@@@@@@@@@ \0",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\0",
    "@@  '@@@@@@@@@@@@@@@@@@'  @@\0",
    "@@,     @@@@@@@@@@@@     ,@@\0",
    "@@@        @@@@@@        @@@\0",
    " @@    (O)  @@@@  (O)    @@ \0",
    " @@          @@          @@ \0",
    "  @@        ,' .        @@  \0",
    "  @@                    @@  \0",
    " @@.\x5C     ########     /.@@ \0",
    "@@...\x5C     '####'     /...@@\0",
    "@@@....\x5C            /....@@@\0",
    " @@@.....\x5C________/.....@@@ \0",
  };
  char golem[15][30]
  {
    ".x...,@@@@@@@@@@@@@@@@@,....\0",
    "..X @@'               '@@...\0",
    "...@@                   @@..\0",
    "..@' ___             ___ '@.\0",
    "..@  '@@@@@@XxxxX@@@@@@'  @@\0",
    ".@'   @@.O`@     @,O`@@  `@@\0",
    ",@@   `@@@@+     +@@@@:   @@\0",
    "@@@,                    ,@@@\0",
    "@@  @@@@@@@,        ,@@@@@'@\0",
    "'@  .@/   '@@@@@@@@@@     ,@\0",
    ".@@  @        @@'   @`    @@\0",
    "..@.          `@          @@\0",
    "xX `@@`              ,@@@/..\0",
    ".....+@@@@@@@@@@@@@@@@@'x...\0",
    ".....X...................X..\0",
  };
  char skelett[15][30]
  {
    "    ,..xx@@@@@@@@@@xx..,    \0",
    "  @'                   ,'@, \0",
    " @@@'`  `' ` `'  `'@@@'  `@,\0",
    "@@'                   @@  `@\0",
    "@   @@@@        @@@@  '@@  @\0",
    "@  @@@@@@      @@@@@@   @  @\0",
    "@   @@@@        @@@@    @, @\0",
    "@           ,           @  @\0",
    "@          .@@,        @ @  \0",
    " @@       ,@@@@.       @@'` \0",
    "   @@@@            @@@@     \0",
    "      @,###########,@       \0",
    "        ###########         \0",
    "             @   @  @@@@@@  \0",
    "      @@@@@@  @   @         \0",
  };
  char tunnelgräber[15][30]
  {
    "       )                    \0",
    "      (_)                   \0",
    "      |`|MMMMMMMMM          \0",
    "    MM| |MMMMMMMMMMMMM      \0",
    "   MMMMMMMMMMMMMMMMMMMM     \0",
    "  MMMMMMMMMMMMMMMMMMMMMM    \0",
    "MMMMMMMMMMMMMMMMMMMMMMMMMMM \0",
    " @@@ @@@@@     @@@@@  @@@   \0",
    "  @@  (O)       (O)   @@    \0",
    "   @        )         @     \0",
    "   @       (@@       @      \0",
    "    @  ##,     ,###  @      \0",
    "    @  `'#######'`  @       \0",
    "     @@,.       .,@@        \0",
    "        `'@@@@@'`           \0",
  };


  int id = pPlayer->Nr;

  if (id == 1) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", barbar[i]);
      printf("  |\n");
    }
  }
  else if (id == 2) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", magier[i]);
      printf("  |\n");
    }
  }
  else if (id == 3) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", golem[i]);
      printf("  |\n");
    }
  }
  else if (id == 4) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", pekka[i]);
      printf("  |\n");
    }
  }
  else if (id == 5) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", hexe[i]);
      printf("  |\n");
    }
  }
  else if (id == 6) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", schweinereiter[i]);
      printf("  |\n");
    }
  }
  else if (id == 7) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", skelett[i]);
      printf("  |\n");
    }
  }
  else if (id == 8) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", tunnelgräber[i]);
      printf("  |\n");
    }
  }
  else if (id == 9) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", riese[i]);
      printf("  |\n");
    }
  }
  else if (id == 10) {
    for (int i = 0; i < 15; i++)
    {
      printf("  |  ");
      printf("%s", ballon[i]);
      printf("  |\n");
    }
  }

}

void ausgabe(struKarten* pListePlayer, struKarten* pListeCPU) {
  // Mazen
  // Funktion, bei der die Ausgabe der Karten und die eigentliche Runde geschieht.
  // Die Parameter sind die Liste des Players und des CPU-Spielers, weil beide darin verarbeitet werden.

  // übergeordnete Variablen
  char c;                     // Überprüfung der ersten Eingabe benötigt.
  char j;                     // Vergewisserung der ersten Eingabe (Sind Sie sicher? Ja/Nein). Nur im Entwicklermodus verfügbar.
  bool menü = false;          // Das Rückkehren zum Hauptmenü
  bool nextkarte = false;     // Aus der Ausgabe-Schleife raus zu kommen & falls zur nächsten Karte gewechselt werden sollte.
  int kartenänderung;         // Kartenänderung: 0 = leer (keine Änderung), 1 = gewonnen, 2 = verloren, 3 = unentscheiden (siehe unter der Kartenausgabe-Schleife)
  
  while (!menü) {
    nextkarte = false;
    kartenänderung = 0;

    int AnzPlayer = listcount(pListePlayer);
    int AnzCPU = listcount(pListeCPU);

    // Kartenausgabe-Schleife
    while (!nextkarte && !menü && AnzPlayer > 0 && AnzCPU > 0) {  // In dieser While-Schleife wird immer wieder die gleiche Karte ausgegeben, bis man eine gültige Eingabe macht.
      system("cls");

      printf("\n\n\n  =================================");

      printf("\n\n  --------------KARTE---------------");
      if (admin) printf("\n\n         Entwicklermodus EIN");
      printf("\n    ______________________________ ");
      printf("\n   /                              \x5C");
      printf("\n  /                                \x5C");
      printf("\n  |  CoC Quartett | Karte Nr.  %-2i  |", pListePlayer->Nr);
      printf("\n  |                                |");
      printf("\n  |      ---%-14s---      |", pListePlayer->Bez);
      printf("\n  |                                |");
      printf("\n");
      ausgabe_kartenbild(pListePlayer);
      printf("  |                                |");
      printf("\n  |   |Trefferpunkte   | %4i |    |", pListePlayer->Trefferpunkte);
      printf("\n  |   |                |      |    |");
      printf("\n  |   |Geschwindigkeit | %4i |    |", pListePlayer->Geschw);
      printf("\n  |   |                |      |    |");
      printf("\n  |   |Schaden         | %5.1lf|    |", pListePlayer->Schaden);
      printf("\n  \x5C                                /");
      printf("\n   \x5C______________________________/");
      printf("\n\n");

      if (pListePlayer->pNext != NULL && admin) printf("\n  Ihre n\x84""chste Karte lautet: %-14s ", pListePlayer->pNext->Bez);
      else printf("\n");


      if (listcount(pListePlayer) == 1) printf("\n  Sie besitzen nur noch %i Karte.", AnzPlayer);
      else printf("\n  Sie besitzen insgesamt noch %i Karten.", AnzPlayer);

      if (listcount(pListeCPU) == 1) printf("\n\n  Der CPU-Spieler besitzt nur noch %i Karte.", AnzCPU);
      else printf("\n\n  Der CPU-Spieler besitzt insgesamt noch %i Karten.", AnzCPU);
      
      if (admin) {
        printf("\n  Karten des CPU-Spielers:");
        for (struKarten* pTemp = pListeCPU; pTemp != NULL; pTemp = pTemp->pNext) {
          if (pTemp->pNext == NULL) {
            printf(" %s", pTemp->Bez);
          }
          else printf(" %s->", pTemp->Bez);
        }
      }
      

      printf("\n\n\n  =================================");
      printf("\n  Trefferpunkte?         (1)");
      printf("\n  Geschwindigkeit?       (2)");
      printf("\n  Schaden?               (3)");
      printf("\n\n  Neu Starten            (4)");
      printf("\n  Zur\x81" "ck zum Hauptmen\x81   (5)");
      printf("\n  =================================");
      printf("\n\n  (1/2/3/4/5): ");

      c = _getch();

      if (admin) { // Was ausgeführt werden sollte, wenn der Entwicklermodus eingeschaltet ist.
        if (c == '1' || c == 't') {
          printf("\n\n  M\x94""chten Sie wirklich Trefferpunkte abfragen?");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') {
            kartenänderung = vergleiche(1, pListePlayer, pListeCPU);
            nextkarte = true;
          }

          else if (j == 'n');

          else falsche_eingabe();
        }

        else if (c == '2' || c == 'g') {
          printf("\n\n  M\x94""chten Sie wirklich Geschwindigkeit abfragen?");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') {
            kartenänderung = vergleiche(2, pListePlayer, pListeCPU);
            nextkarte = true;
          }

          else if (j == 'n');

          else falsche_eingabe();
        }

        else if (c == '3' || c == 's') {
          printf("\n\n  M\x94""chten Sie wirklich Schaden abfragen?");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') {
            kartenänderung = vergleiche(3, pListePlayer, pListeCPU);
            nextkarte = true;
          }

          else if (j == 'n');

          else falsche_eingabe();
        }

        else if (c == '4') {
          printf("\n\n  M\x94""chten Sie wirklich das Spiel neustarten?");
          printf("\n  Ihre Karten werden somit neu gemischt und Sie verlieren Ihren Spielstand.");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') {
            rundestart();
            menü = true;
          }

          else if (j == 'n');

          else falsche_eingabe();
        }

        else if (c == '5') {
          printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') menü = true;
        }

        else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5')
        {
          falsche_eingabe();
        }
      }

      if (!admin) { // Was ausgeführt werden sollte, wenn der Entwicklermodus ausgeschaltet ist.
        if (c == '1' || c == 't') {
          kartenänderung = vergleiche(1, pListePlayer, pListeCPU);
          nextkarte = true;
        }

        else if (c == '2' || c == 'g') {
            kartenänderung = vergleiche(2, pListePlayer, pListeCPU);
            nextkarte = true;
        }

        else if (c == '3' || c == 's') {
            kartenänderung = vergleiche(3, pListePlayer, pListeCPU);
            nextkarte = true;
        }

        else if (c == '4') {
          printf("\n\n  M\x94""chten Sie wirklich das Spiel neustarten?");
          printf("\n  Ihre Karten werden somit neu gemischt und Sie verlieren Ihren Spielstand.");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') {
            rundestart();
            menü = true;
          }

          else if (j == 'n');

          else falsche_eingabe();
        }

        else if (c == '5') {
          printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
          printf("\n\n  (J/N): ");

          j = _getch();
          if (j == 'j') menü = true;
        }

        else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5')
        {
          falsche_eingabe();
        }
      }

    }

    // Es wird durch den Rückgabewert von "vergleiche" ermittelt, wie sich die beiden Listen und Karten verändern sollen.
    if (kartenänderung == 1) // Bei Gewinn einer Karte sollen diese Änderungen vorgenommen werden.
    {
      vergleiche_karten(pListePlayer, pListeCPU);
      pListePlayer = firstlast_gew(pListePlayer, pListeCPU);
      pListeCPU = firstlast_verl(pListeCPU);
      gewonnen();
    }

    else if (kartenänderung == 2) // Bei Verlust einer Karte sollen diese Änderungen vorgenommen werden.
    {
      vergleiche_karten(pListePlayer, pListeCPU);
      pListeCPU = firstlast_gew(pListeCPU, pListePlayer);
      pListePlayer = firstlast_verl(pListePlayer);
      verloren();
    }

    else if (kartenänderung == 3) // Bei Unentschieden sollen diese Änderungen vorgenommen werden.
    {
      vergleiche_karten(pListePlayer, pListeCPU);
      pListePlayer = firstlast_unent(pListePlayer);
      pListeCPU = firstlast_unent(pListeCPU);
      unentschieden();
    }


    // Spielende: Verloren-Schleife
    while (AnzPlayer <= 0 && AnzCPU >= 10 && !menü)
    {
      system("cls");

      printf("\n\n\n  ==================================");
      printf("\n\n  ----------SPIEL VERLOREN----------");
      printf("\n\n  Sie besitzen keine Karten mehr.");
      printf("\n  Sie haben das Spiel verloren.");
      printf("\n\n  ==================================");
      printf("\n\n\n\n  M\x94""chten Sie das Spiel neustarten?");
      printf("\n  Falls nicht, kehren Sie zum Hauptmen\x81 zur\x81""ck.");
      printf("\n\n  (J/N): ");

      c = _getch();

      if (c == 'j') {
        rundestart();
        menü = true;
      }
      else if (c == 'n') menü = true;
      else falsche_eingabe();
    }

    // Spielende: Gewonnen-Schleife
    while (AnzPlayer >= 10 && AnzCPU <= 0 && !menü)
    {
      system("cls");

      printf("\n\n\n  ==================================");
      printf("\n\n  ----------SPIEL GEWONNEN----------");
      printf("\n\n  Der CPU-Spieler besitzt keine Karten mehr.");
      printf("\n  Sie haben das Spiel gewonnen.");
      printf("\n\n  ==================================");
      printf("\n\n\n\n  M\x94""chten Sie das Spiel neustarten?");
      printf("\n  Falls nicht, kehren Sie zum Hauptmen\x81 zur\x81""ck.");
      printf("\n\n  (J/N): ");

      c = _getch();

      if (c == 'j') {
        rundestart();
        menü = true;
      }
      else if (c == 'n') menü = true;
      else falsche_eingabe();
    }
  }
}

int vergleiche(int Typ, struKarten* pListePlayer, struKarten* pListeCPU) {
  // Mazen
  // Diese Funktion vergleicht zwei Listen und gibt
  // Der Parameter ist der Typ des Vergleichs und die beiden Listen, die verglichen werden.

  int kartenänderung = 0; // Wie bei der Ausgabe bedeutet 1 = gewonnen, 2 = verloren, 3 = unentschieden. 0 = leer und bedeutet, dass nichts geschehen soll.

  if (Typ == 1) {
    if (pListePlayer->Trefferpunkte > pListeCPU->Trefferpunkte)      kartenänderung = 1;
    else if (pListePlayer->Trefferpunkte < pListeCPU->Trefferpunkte) kartenänderung = 2;
    else if (pListePlayer->Trefferpunkte = pListeCPU->Trefferpunkte) kartenänderung = 3;
  }
  else if (Typ == 2) {
    if (pListePlayer->Geschw > pListeCPU->Geschw)      kartenänderung = 1;
    else if (pListePlayer->Geschw < pListeCPU->Geschw) kartenänderung = 2;
    else if (pListePlayer->Geschw = pListeCPU->Geschw) kartenänderung = 3;
  }
  else if (Typ == 3) {
    if (pListePlayer->Schaden > pListeCPU->Schaden)      kartenänderung = 1;
    else if (pListePlayer->Schaden < pListeCPU->Schaden) kartenänderung = 2;
    else if (pListePlayer->Schaden = pListeCPU->Schaden) kartenänderung = 3;
  }
  return kartenänderung;
}

void vergleiche_karten(struKarten* pListePlayer, struKarten* pListeCPU) {
  // Mazen
  // Diese Funktion gibt beide aktuellen Karten nebeneinander, 
  // allerdings ohne Kartenbilder aus, da die Bilder in einer Funktion ausgegeben werden.
  // Die Parameter sind erneut die beiden Listen, da sie beide ausgegeben werden.

  system("cls");

  printf("\n\n\n  =================================");

  printf("\n\n  --------------KARTEN---------------");
  printf("\n\n             Ihre Karte                      Karte des CPU-Spielers");
  printf("\n    ______________________________");
  printf("       ______________________________ ");
  printf("\n   /                              \x5C");
  printf("     /                              \x5C");
  printf("\n  /                                \x5C");
  printf("   /                                \x5C");
  printf("\n  |  CoC Quartett | Karte Nr.  %-2i  |", pListePlayer->Nr);
  printf("   |  CoC Quartett | Karte Nr.  %-2i  |", pListeCPU->Nr);
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |      ---%-14s---      |", pListePlayer->Bez);
  printf("   |      ---%-14s---      |", pListeCPU->Bez);
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |   |Trefferpunkte   | %4i |    |", pListePlayer->Trefferpunkte);
  printf("   |   |Trefferpunkte   | %4i |    |", pListeCPU->Trefferpunkte);
  printf("\n  |   |                |      |    |");
  printf("   |   |                |      |    |");
  printf("\n  |   |Geschwindigkeit | %4i |    |", pListePlayer->Geschw);
  printf("   |   |Geschwindigkeit | %4i |    |", pListeCPU->Geschw);
  printf("\n  |   |                |      |    |");
  printf("   |   |                |      |    |");
  printf("\n  |   |Schaden         | %5.1lf|    |", pListePlayer->Schaden);
  printf("   |   |Schaden         | %5.1lf|    |", pListeCPU->Schaden);
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  |                                |");
  printf("   |                                |");
  printf("\n  \x5C                                /");
  printf("   \x5C                                /");
  printf("\n   \x5C______________________________/");
  printf("     \x5C______________________________/");
  printf("\n\n");

}

struKarten* firstlast_gew(struKarten* pListeGew, struKarten* pListeVerl) { 
  // Mazen & Yannic
  // Diese Funktion verschiebt die erste Karte des Gewinners und des Verlierers an die letzte Stelle der Gewinnerkarte.
  // Die Parameter sind 1. Die Liste des Gewinners und 2. Die Liste des Verlierers.

  struKarten* pLast;
  struKarten* pTemp;

  if (listcount(pListeGew) == 1) {                      // Wenn beim Gewinner nur noch 1 Karte vorhanden ist, wird die gewonnene hinter dieser verschoben.
    pLast = pListeGew;
    struKarten* pKarte = pListeVerl;
    pLast->pNext = pKarte;
  }

  else if (listcount(pListeGew) > 1) {                  // Wenn der Gewinner mehr als 1 Karte besitzt, wird zur letzten gewechselt, also pLast, 
    pTemp = pListeGew;                                  // und deren nächste Karte ist die gewonnene Karte. Ebenfalls wird die eigene erste Karte an den letzten Platz versetzt.
    pListeGew = pListeGew->pNext;
    pTemp->pNext = NULL;
    pLast = pListeGew;

    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pTemp;

    struKarten* pKarte = pListeVerl;
    pTemp->pNext = pKarte;
  }

  return pListeGew;                                   // Die Liste wird verändert zurückgegeben.
}

struKarten* firstlast_verl(struKarten* pListeVerl) {
  // Mazen & Yannic
  // Diese Funktion löscht die Referenz der entfernten Karte aus der Verlierer-Liste.
  // Der Parameter ist nur die Liste des Verlierers.

  if (listcount(pListeVerl) == 1) {
    pListeVerl = NULL;
  }

  else {
    struKarten* pTemp = pListeVerl;
    pListeVerl = pListeVerl->pNext;
    pTemp->pNext = NULL;
  }



  return pListeVerl;                                  // Die Liste wird verändert zurückgegeben.
}

struKarten* firstlast_unent(struKarten* pListe) {
  // Mazen & Yannic
  // Diese Funktion versetzt die erste Karte ganz hinten wenn ein Unentschieden geschieht.
  // Der Parameter ist irgendeine Liste, da diese Funktion neutral ist.

  struKarten* pTemp = pListe;
  struKarten* pLast;

  if (listcount(pListe) == 1)
  {
    pListe = pTemp;
  }

  else {
    struKarten* pLast = pListe;

    while (pLast->pNext != NULL) pLast = pLast->pNext;

    pLast->pNext = pTemp;
    pListe = pListe->pNext;
    pTemp->pNext = NULL;
  }



  return pListe;                                      // Die Liste wird verändert zurückgegeben.
}





void einstellungen() {
  // Yannic
  // Diese Funktion beinhaltet optionale Einstellungen wie Farbe, Entwicklermodus und Version.

  //Variablen
  bool settings = true;
  bool farben = true;

  char neue_hintergrundfarbe = ' ';
  char neue_textfarbe = ' ';
  char eingabe = ' ';

  while (settings)
  {
    system("cls");

    logo();

    printf("\n  ==================================");
    printf("\n  -----------Einstellungen----------");
    printf("\n\n  Farbe           (1)");
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
        printf("\n\n  Hintergrundfarbe      |  Textfarbe                                ");
        printf("\n  ======================|=======================");
        printf("\n  Schwarz = 1  [%s]  |  Schwarz = 1  [%s]", s_h, s_t);
        printf("\n  Grau    = 2  [%s]  |  Grau    = 2  [%s]", g_h, g_t);
        printf("\n  Weiss   = 3  [%s]  |  Weiss   = 3  [%s]", w_h, w_t);
        printf("\n  Gr\x81n    = 4  [%s]  |  Gr\x81n    = 4  [%s]", gr_h, gr_t);
        printf("\n  Blau    = 5  [%s]  |  Blau    = 5  [%s]", b_h, b_t);
        printf("\n  Rot     = 6  [%s]  |  Rot     = 6  [%s]", r_h, r_t);
        printf("\n  ======================|=======================");

        printf("\n\n  Hintergrundfarbe (1) ");
        printf("\n  Textfarbe        (2)");
        printf("\n  Zur\x81""ck           (3)");

        printf("\n  (1/2/3): ");
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
      printf("\n\n\n");
      printf("      .@@@@@@@@@@@@@@@@@@.               Team:                    @@@@@@@@@@           \n");
      printf("      @                  @.          Mazen & Yannic             @@@@@@@@@@@@@@         \n");
      printf("     @@                  @@.                                 ,@@@@@@@@       @@        \n");
      printf("    @@                    @@                                @  @@@@'           @       \n");
      printf("    @@                    &@                              ,@                    @ ,@.  \n");
      printf("    @ @@@@@@@    .@@@@@@@@ @.                             @@ @@@@    /@@@@@.    @@  @  \n");
      printf("    @@   (o)      (O)     @@@         Version 1.2         @@  (O)      (O)     .@@  @  \n");
      printf("   .@@        ((           @@          x64-Debug          @        /           @@@.(.) \n");
      printf("   @@@  @@@@@@@@@@@@@@@    @@                             @       (@.          @@@     \n");
      printf("       @@ ########## @@@                                 .@@@@@@@@@@@@@@@@@@   @@,     \n");
      printf("      @@@            @@@                                 @@@@ ########## @@@@ .@@*     \n");
      printf("      @@ ##________## @@@                                '@@@              @@@@@@*     \n");
      printf("      @@@ '########'  @@@           Clash Of Clans        @@@@ #########,@@@@@@@       \n");
      printf("      @@@             @@@              Quartett!           @@@@@@@@@@@@@@@@@@@         \n");
      printf("       @               @                                     @@@@@@@@@@@@@@@@          \n");
      
      system("timeout 5 >null");
      printf("\n\n");
    }
    else if (eingabe == '3') {
      if (admin == true) {
        admin = false;
        printf("\n  Entwicklermodus Deativiert ");
        Sleep(700);
        system("cls");
      }
      else if (admin == false) {
        admin = true;
        printf("\n  Entwicklermodus Aktiviert ");
        Sleep(700);
        system("cls");
      }
    }
    else if (eingabe == '4') settings = false;
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4') falsche_eingabe();
  }
}

void farbmatrix(char hintergrundfarbe, char textfarbe) {
  // Yannic
  // Diese Funktion verarbeitet die Einstellungen für die Farben des Debugging-Fensters.
  // Die Parameter sind die Hintergrundfarbe und die Textfarbe.

  char SysPrint[20];
  sprintf_s(SysPrint, "color %c%c", hintergrundfarbe, textfarbe);
  system(SysPrint);
}

void falsche_eingabe() {
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

  printf("\n  Falsche Eingabe ");
  system("timeout 1 >null");
  system("cls");
}

void verloren()
{
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

  printf("\n\n\n\n  =================================");
  printf("\n\n  ------------VERLOREN------------");
  printf("\n\n  Sie verlieren diese Karte leider.");
  printf("\n  Der Gegner gewinnt Ihre aktuelle Karte.");
  printf("\n\n  ==================================");
  printf("\n\n\n");
  printf("  Zum Fortfahren eine Taste dr\x81""cken.");
  system("pause >nul");
}

void gewonnen()
{
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

  printf("\n\n\n\n  =================================");
  printf("\n\n  ------------GEWONNEN------------");
  printf("\n\n  Sie gewinnen die Karte des Gegners.");
  printf("\n  Der Gegner verliert sie.");
  printf("\n\n  ==================================");
  printf("\n\n\n");
  printf("  Zum Fortfahren eine Taste dr\x81""cken.");
  system("pause >nul");
}

void unentschieden()
{
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

  printf("\n\n\n\n  =================================");
  printf("\n\n  ---------UNENTSCHIEDEN----------");
  printf("\n\n  Niemand gewinnt dieses Mal.");
  printf("\n  Die obersten Karten werden nach hinten versetzt.");
  printf("\n\n  ==================================");
  printf("\n\n\n");
  printf("  Zum Fortfahren eine Taste dr\x81""cken.");
  system("pause >nul");
}

void logo()
{
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

   printf("\n\n     ________           __             ____   ________                ");
   printf("\n    / ____/ /___ ______/ /_     ____  / __/  / ____/ /___ _____  _____");
   printf("\n   / /   / / __ `/ ___/ __ \x5C   / __ \x5C/ /_   / /   / / __ `/ __ \x5C/ ___/");
   printf("\n  / /___/ / /_/ (__  ) / / /  / /_/ / __/  / /___/ / /_/ / / / (__  ) ");
   printf("\n  \x5C____/_/\x5C__,_/____/_/ /_/ __\x5C____/_/_  __\x5C____/_/\x5C__,_/_/ /_/____/  ");
   printf("\n    / __ \x5C__  ______ ______/ /____  / /_/ /_                          ");
   printf("\n   / / / / / / / __ `/ ___/ __/ _ \x5C/ __/ __/                          ");
   printf("\n  / /_/ / /_/ / /_/ / /  / /_/  __/ /_/ /_                            ");
   printf("\n  \x5C___\x5C_\x5C__,_/\x5C__,_/_/   \x5C__/\x5C___/\x5C__/\x5C__/                            ");
   printf("\n\n                                                                      ");

}

void end()
{
  // Mazen & Yannic
  // Diese Funktion beinhaltet eine einfache Ausgabe.

  system("cls");

  printf("\n\n      ______          __   ");
  printf("\n     / ____/___  ____/ /__ ");
  printf("\n    / __/ / __ \x5C/ __  / _ \x5C");
  printf("\n   / /___/ / / / /_/ /  __/");
  printf("\n  /_____/_/ /_/\x5C__,_/\x5C___/ ");
  printf("\n\n\n                           \n");

  Sleep(800);
}

//Letzte Zeile