#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <conio.h>
#include <Windows.h>

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
void ausgabe_kartenbild(struKarten*);                           // Funktion für die Ausgabe von Kartenbilder 

int listcount(struKarten*);                                     // Einfache Funktion fürs Zählen von Elementen in einer Liste
void menü();                                                    // Hauptmenü
void einstellungen();                                           // Einstellungen
void farbmatrix(char, char);                                    // Farbmatrix fürs Einstellen der Farben auf der CMD
int admin_wiederholung();
void falsche_eingabe();                                         // Einfache Ausgabe bei falscher Eingabe
void end();                                                     // Ausgabe für Spielende wenn man das Spiel verlässt
void logo();                                                    // Ausgabe für Logo des Spiels
void line();
void verloren();                                                // Ausgabe wenn man eine Karte verliert
void gewonnen();                                                // Ausgabe wenn man eine Karte gewinnt
void unentschieden();                                           // Ausgabe wenn unentschieden

// Globale Variablen
bool admin = false;                                             // Wird für den optionalen Entwicklermodus benötigt. Es gibt Unterprogramme, die Entwicklermodus-Funktionen beinhalten.
bool first = true;                                              // Wird für die Einstellungen/Farben benötigt.
char hintergrundfarbe = '0';
char textfarbe = 'F';

#define MaxAnzBildRow 15
#define MaxAnzBildCol 30

void main()
{
  srand(time(NULL));
  system("mode con cols=85 lines=45");

  menü();
  end();
}

void menü() {
  bool hauptmenü = true;
  while (hauptmenü)
  {
    char eingabe;

    system("cls");
    logo();
    line();
    printf("\n   Hauptmen\x81");
    line();
    printf("\n");
    printf("\n   Spiel starten     (1)");
    printf("\n   Einstellungen     (2)");
    printf("\n   Beenden           (3)\n\n");
    line();
    printf("\n   (1/2/3): ");
    eingabe = _getch();

    if (eingabe == '1') rundestart();
    else if (eingabe == '2') einstellungen();
    else if (eingabe == '3')
    {
      printf("M\x94""chten Sie das Spiel wirklich beenden?");
      printf("\n   (J/N): ");
      eingabe = _getch();

      if (eingabe == 'J' || eingabe == 'j') hauptmenü = false;
    }
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3') falsche_eingabe();
  }
}

void rundestart() {
  system("cls");
  logo();
  line();
  printf("\n\n                     Karten werden erstellt und neu gemischt ");
  for (int i = 0; i < 3; i++) {
    Sleep(400);
    printf(".");
  }

  struKarten* pStart = NULL; // base list
  struKarten* pListePlayer = NULL; //player list
  struKarten* pListeCPU = NULL; //cpu list

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
  
  if (admin) {
    printf("\n");
    line();
    printf("\n\n   Die zuf\x84llige Karten sind:\n   ");
  }
  for (runde = 1; runde <= 5; runde++) {
    int anz = listcount(pStart);
    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    for (int c = 1; c <= r; c++) pKarte = pKarte->pNext;
    if (admin) printf("%s ", pKarte->Bez);

    pStart = removelist(pStart, pKarte);              // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListePlayer = createlist(pListePlayer, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }
  if (admin) printf("\n   Diese Karten werden jetzt der Spielerliste hinzugef\x81gt.\n\n   Die zuf\x84llige Karten sind:\n   ");
  for (runde = 5; runde < 10; runde++) {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt. 5 wurden schon entfernt.
    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    for (int c = 1; c <= r; c++) pKarte = pKarte->pNext;
    if (admin) printf("%s ", pKarte->Bez);

    pStart = removelist(pStart, pKarte);        // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListeCPU = createlist(pListeCPU, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }
  if (admin) {
    printf("\n   Diese Karten werden jetzt der CPU-Liste hinzugef\x81gt.\n");
    line();
    printf("     ");
    system("pause");
    system("cls");
  }
  ausgabe(pListePlayer, pListeCPU);
}

int listcount(struKarten* pListe) {
  int anz = 0;
  struKarten* pTmp = pListe;
  
  for (pTmp; pTmp != NULL; pTmp = pTmp->pNext) anz++;
  return anz;
}

struKarten* karte(int pTruppe, const char* pBez, int Hp, int Spd, double Dmg) {
  // Diese Funktion verarbeitet die Parameterwerte in eine Karte und gibt die ganze Karte als Pointer zurück.
  struKarten* pTmp = (struKarten*)malloc(sizeof(struKarten));

  pTmp->Nr = pTruppe;
  strcpy_s(pTmp->Bez, pBez);
  pTmp->Trefferpunkte = Hp;
  pTmp->Geschw = Spd;
  pTmp->Schaden = Dmg;
  pTmp->pNext = NULL;

  return pTmp;
}

struKarten* createlist(struKarten* pListe, struKarten* pKarte) {
  // Diese Funktion fügt die pKarte zur mitgegebenen pListe hinzu.
  if (pListe == NULL) {
    pListe = pKarte;
    pKarte->pNext = NULL;
  }
  else {
    struKarten* pLast = pListe;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pKarte;
  }
  return pListe;
}

struKarten* removelist(struKarten* pListe, struKarten* pKarte) {
  // Diese Funktion dient zum entfernen von Karten aus einer Liste, in dem die Referenzen neu gesetzt werden.
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
  return pListe;
}

void GotoXY(const int x, const int y)
{
  COORD Pos = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void OutputBild(const int x, const int y, char* pBild)
{
  int Row = 0;
  int Col = 0;

  for (int Row = 0; Row < MaxAnzBildRow; Row++) {
    GotoXY(x, y + Row);
    int iPos = Row * MaxAnzBildCol;
    printf(pBild + iPos);
  }
}

void ausgabe_kartenbild(struKarten* pListePlayer, struKarten* pListeCPU) {
  // Diese Funktion beinhaltet die Bilder der Karten und deren Ausgabe.
  struKarten* pPlayer = pListePlayer;
  struKarten* pCPU = pListeCPU;

  int X = 28;
  int Y = 6;

  char barbar[MaxAnzBildRow][MaxAnzBildCol] {
    "    .@@@@@@@@@@@@@@@@@@.    ",
    "    @                  @.   ",
    "   @@                  @@.  ",
    "  @@                    @@  ",
    "  @@                    &@  ",
    "  @ @@@@@@@    .@@@@@@@@ @. ",
    "  @@   (o)      (O)     @@@ ",
    " .@@        ((           @@ ",
    " @@@  @@@@@@@@@@@@@@@    @@ ",
    "     @@ ########## @@@      ",
    "    @@@            @@@      ",
    "    @@ ##________## @@@     ",
    "    @@@ '########'  @@@     ",
    "    @@@             @@@     ",
    "                            ",
  };
  char schweinereiter[MaxAnzBildRow][MaxAnzBildCol] {
    "         @@@@@@@@@@         ",
    "       @@@@@@@@@@@@@@       ",
    "    ,@@@@@@@@       @@      ",
    "   @  @@@@'           @     ",
    " ,@                    @ ,@.",
    " @@ @@@@    /@@@@@.    @@  @",
    " @@  (O)      (O)     .@@  @",
    " @        /           @@@(.)",
    " @       (@.          @@@   ",
    ".@@@@@@@@@@@@@@@@@@   @@,   ",
    "@@@@ ########## @@@@ .@@*   ",
    "'@@@              @@@@@@*   ",
    " @@@@ #########,@@@@@@@     ",
    "  @@@@@@@@@@@@@@@@@@@       ",
    "    @@@@@@@@@@@@@@@@        ",
  };
  char ballon[MaxAnzBildRow][MaxAnzBildCol] {
    "        @@@@@@@@@@@         ",
    "     @@@@@@@@@@@@@@@@@      ",
    "   @@@@@@         @@@@@@    ",
    "  @@@@@@ (O)   (O) @@@@@@   ",
    "  @@@@@@     @     @@@@@@   ",
    "  @@@@@@@  , , ,  @@@@@@@   ",
    "   @@@@@@@ @ @ @ @@@@@@@    ",
    "    @@@@@@U@U@U@U@@@@@@     ",
    "       @@@@@@@@@@@@@        ",
    "        |  |   |  |         ",
    "        |  |   |  |  `      ",
    "       (###########)    `   ",
    "        @@@@@@@@@@@  ` `    ",
    "         @@@@@@@@@  `  #  ` ",
    "                      `  `  ",
  };
  char riese[MaxAnzBildRow][MaxAnzBildCol] {
    "    @                 @     ",
    "  @@                   @@   ",
    " @                       @  ",
    "@@@@@@@@@@@@   @@@@@@@@@@@@ ",
    "@@@@@@@@@@@@@ @@@@@@@@@@@@@@",
    "@        @@@   @@@        @ ",
    "   ( o )     .     ( o )  @@",
    "@@          ,@            @@",
    "@@@       ,@@  @.        @@@",
    "@@@)        @@@         (@@@",
    "@@@@                    @@@@",
    " @@@@@   ###########  @@@@@@",
    " @@@@@@              @@@@@@ ",
    "   @@@@@@          @@@@@@   ",
    "     @@@@@@.     .@@@@@     ",
  };
  char pekka[MaxAnzBildRow][MaxAnzBildCol] {
    "                            ",
    "@                         @ ",
    "@@                       @@ ",
    "@@@@  ,-------------,  @@@@ ",
    " @@@@@@'           '@@@@@@  ",
    " @@@@                 @@@@  ",
    "  @@  @(O)@)   (@(O)@  @@   ",
    "   |  @@@'   M   '@@@  |    ",
    "   |  '     MMM     '  |    ",
    "   |        MMM        |    ",
    "   |        MMM        |    ",
    " /MMMMMMMMMM/ \x5CMMMMMMMMMM\x5C  ",
    "/'         /   \x5C         '\x5C ",
    "          /     \x5C           ",
    "                            ",
  };
  char magier[MaxAnzBildRow][MaxAnzBildCol] {
    "    ,@@@@@@@@@@@@@@@@@@,    ",
    "  @@@@@@@@@@@@@@@@@@@@@@@@  ",
    " @@@@@@@@@@@@@@@@@@@@@@@@@@ ",
    "@@@@                    @@@@",
    "@@@ Xx                xX @@@",
    "@@|  'XXXx,      ,xXXX'  |@@",
    "@ |   (O)    ,     (O)   | @",
    "@ |         ,@           | @",
    "@ |        ,@  @.        | @",
    "@@|    @@@@@@@@@@@@@@    |@@",
    " @,\x5C   @@ ######## @@   /,@ ",
    "  @@ \x5C '@          @' / @@  ",
    "   @@  \x5C@@@@@@@@@@@@/  @@   ",
    "    @    '@@@@@@@@'    @    ",
    "   @@       '@@'       @@   ",
  };
  char hexe[MaxAnzBildRow][MaxAnzBildCol] {
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
  char golem[MaxAnzBildRow][MaxAnzBildCol] {
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
  char skelett[MaxAnzBildRow][MaxAnzBildCol] {
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
  char tunnelgräber[MaxAnzBildRow][MaxAnzBildCol] {
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

  system("cls");
  if (admin) printf("Entwicklermodus");

  if (pListeCPU == NULL) {
    printf("\n                                     Ihre Karte");
    printf("\n                         \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF");
    printf("\n                         \xB3  Nr.  %-2i  \xB3  %-14s    \xB3", pListePlayer->Nr, pListePlayer->Bez);
    printf("\n                         \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3     Trefferpunkte     %4i     \xB3", pListePlayer->Trefferpunkte);
    if (!admin) printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3     Geschwindigkeit   %4i     \xB3", pListePlayer->Geschw);
    if (!admin) printf("\n                         \xB3                                \xB3");
    printf("\n                         \xB3     Schaden          %5.1lf     \xB3", pListePlayer->Schaden);
    printf("\n                         \xB3                                \xB3");
    printf("\n                         \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9");
  }
  else if (pListeCPU != NULL)
  {
    printf("\n                 Ihre Karte                              Karte des CPUs");
    printf("\n     \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF        \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF");
    printf("\n     \xB3  Nr.  %-2i  \xB3  %-14s    \xB3        \xB3  Nr.  %-2i  \xB3  %-14s    \xB3", pListePlayer->Nr, pListePlayer->Bez, pListeCPU->Nr, pListeCPU->Bez);
    printf("\n     \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4        \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4        \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3     Trefferpunkte     %4i     \xB3        \xB3     Trefferpunkte     %4i     \xB3", pListePlayer->Trefferpunkte, pListeCPU->Trefferpunkte);
    if (!admin) printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3     Geschwindigkeit   %4i     \xB3        \xB3     Geschwindigkeit   %4i     \xB3", pListePlayer->Geschw, pListeCPU->Geschw);
    if (!admin) printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xB3     Schaden          %5.1lf     \xB3        \xB3     Schaden          %5.1lf     \xB3", pListePlayer->Schaden, pListeCPU->Schaden);
    printf("\n     \xB3                                \xB3        \xB3                                \xB3");
    printf("\n     \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9        \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9");
  }

  if (pListeCPU != NULL) X = 8;
  if (pPlayer->Nr == 1) OutputBild(X, Y, &barbar[0][0]);
  else if (pPlayer->Nr == 2) OutputBild(X, Y, &magier[0][0]);
  else if (pPlayer->Nr == 3) OutputBild(X, Y, &golem[0][0]);
  else if (pPlayer->Nr == 4) OutputBild(X, Y, &pekka[0][0]);
  else if (pPlayer->Nr == 5) OutputBild(X, Y, &hexe[0][0]);
  else if (pPlayer->Nr == 6) OutputBild(X, Y, &schweinereiter[0][0]);
  else if (pPlayer->Nr == 7) OutputBild(X, Y, &skelett[0][0]);
  else if (pPlayer->Nr == 8) OutputBild(X, Y, &tunnelgräber[0][0]);
  else if (pPlayer->Nr == 9) OutputBild(X, Y, &riese[0][0]);
  else if (pPlayer->Nr == 10) OutputBild(X, Y, &ballon[0][0]);

  if (pListeCPU != NULL) {
    X = 50;
    if (pCPU->Nr == 1) OutputBild(X, Y, &barbar[0][0]);
    else if (pCPU->Nr == 2) OutputBild(X, Y, &magier[0][0]);
    else if (pCPU->Nr == 3) OutputBild(X, Y, &golem[0][0]);
    else if (pCPU->Nr == 4) OutputBild(X, Y, &pekka[0][0]);
    else if (pCPU->Nr == 5) OutputBild(X, Y, &hexe[0][0]);
    else if (pCPU->Nr == 6) OutputBild(X, Y, &schweinereiter[0][0]);
    else if (pCPU->Nr == 7) OutputBild(X, Y, &skelett[0][0]);
    else if (pCPU->Nr == 8) OutputBild(X, Y, &tunnelgräber[0][0]);
    else if (pCPU->Nr == 9) OutputBild(X, Y, &riese[0][0]);
    else if (pCPU->Nr == 10) OutputBild(X, Y, &ballon[0][0]);
  }
  COORD Pos = { 80, 30 };
  if (admin) Pos = { 80, 28 };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void ausgabe(struKarten* pListePlayer, struKarten* pListeCPU) {
  // Funktion, bei der die Ausgabe der Karten und die eigentliche Runde geschieht.
  char c;                     // Überprüfung der ersten Eingabe benötigt.
  char j;
  bool menü = false;          // Das Rückkehren zum Hauptmenü
  bool nextkarte = false;     // Aus der Ausgabe-Schleife raus zu kommen & falls zur nächsten Karte gewechselt werden sollte.
  int kartenänderung;         // Kartenänderung: 0 = leer (keine Änderung), 1 = gewonnen, 2 = verloren, 3 = unentscheiden (siehe unter der Kartenausgabe-Schleife)
  
  while (!menü) {
    nextkarte = false;
    kartenänderung = 0;

    int AnzPlayer = listcount(pListePlayer);
    int AnzCPU = listcount(pListeCPU);

    while (!nextkarte && !menü && AnzPlayer > 0 && AnzCPU > 0) {  
      // In dieser While-Schleife wird immer wieder die gleiche Karte ausgegeben, bis man eine gültige Eingabe macht.

      ausgabe_kartenbild(pListePlayer, NULL);
      line();

      if (listcount(pListePlayer) == 1) printf("\n   Sie besitzen nur noch eine Karte ");
      else printf("\n   Sie besitzen %i Karten ", AnzPlayer);
      
      if (listcount(pListeCPU) == 1) printf("und der CPU-Spieler besitzt nur noch eine Karte.");
      else printf("und der CPU-Spieler besitzt %i Karten.", AnzCPU);
      if (admin) {
        if (pListePlayer->pNext != NULL) printf("\n   Ihre n\x84""chste Karte lautet: %-14s ", pListePlayer->pNext->Bez);
        else printf("\n");
        printf("\n   Karten der CPU:");
        for (struKarten* pTemp = pListeCPU; pTemp != NULL; pTemp = pTemp->pNext) {
          if (pTemp->pNext == NULL) printf(" %s", pTemp->Bez);
          else printf(" %s->", pTemp->Bez);
        }
      }
      
      line();
      printf("\n   Trefferpunkte?         (1)");
      printf("\n   Geschwindigkeit?       (2)");
      printf("\n   Schaden?               (3)");
      printf("\n\n   Neu Starten            (4)");
      printf("\n   Zur\x81" "ck zum Hauptmen\x81   (5)");
      line();
      printf("\n   (1/2/3/4/5): ");
      c = _getch();

      bool admin_frage = true;
      if (c == '1' || c == 't') {
        if (admin) admin_frage = admin_wiederholung();
        if (admin_frage) {
          kartenänderung = vergleiche(1, pListePlayer, pListeCPU);
          nextkarte = true;
        }
      }
      else if (c == '2' || c == 'g') {
        if (admin) admin_frage = admin_wiederholung();
        if (admin_frage) {
          kartenänderung = vergleiche(2, pListePlayer, pListeCPU);
          nextkarte = true;
        }
      }
      else if (c == '3' || c == 's') {
        if (admin) admin_frage = admin_wiederholung();
        if (admin_frage) {
          kartenänderung = vergleiche(3, pListePlayer, pListeCPU);
          nextkarte = true;
        }
      }
      else if (c == '4') {
        printf("M\x94""chten Sie wirklich das Spiel neustarten?");
        printf("\n   (J/N): ");
        c = _getch();

        if (c == 'j') {
          menü = true;
          rundestart();
        }
        else if (c == 'n');
        else falsche_eingabe();
      }
      else if (c == '5') {
        printf("M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
        printf("\n   (J/N): ");
        j = _getch();
        
        if (j == 'j') menü = true;
        else if (j == 'n');
        else falsche_eingabe();
      }
      else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5') falsche_eingabe();
    }

    // Es wird durch den Rückgabewert von "vergleiche" ermittelt, wie sich die beiden Listen und Karten verändern sollen.
    if (kartenänderung == 1) // Bei Gewinn einer Karte sollen diese Änderungen vorgenommen werden.
    {
      ausgabe_kartenbild(pListePlayer, pListeCPU);
      pListePlayer = firstlast_gew(pListePlayer, pListeCPU);
      pListeCPU = firstlast_verl(pListeCPU);
      gewonnen();
    }
    else if (kartenänderung == 2) // Bei Verlust einer Karte sollen diese Änderungen vorgenommen werden.
    {
      ausgabe_kartenbild(pListePlayer, pListeCPU);
      pListeCPU = firstlast_gew(pListeCPU, pListePlayer);
      pListePlayer = firstlast_verl(pListePlayer);
      verloren();
    }
    else if (kartenänderung == 3) // Bei Unentschieden sollen diese Änderungen vorgenommen werden.
    {
      ausgabe_kartenbild(pListePlayer, pListeCPU);
      pListePlayer = firstlast_unent(pListePlayer);
      pListeCPU = firstlast_unent(pListeCPU);
      unentschieden();
    }

    // Spielende: Verloren
    while (AnzPlayer <= 0 && AnzCPU >= 10 && !menü)
    {
      system("cls");
      logo();
      line();
      printf("\n   SPIEL VERLOREN");
      line();
      printf("\n\n   Sie besitzen keine Karten mehr.");
      printf("\n   Sie haben das Spiel verloren.\n");
      line();
      printf("\n\n   M\x94""chten Sie das Spiel neustarten?");
      printf("\n   Falls nicht, kehren Sie zum Hauptmen\x81 zur\x81""ck.\n");
      line();
      printf("\n   (J/N): ");
      c = _getch();

      if (c == 'j') rundestart();
      else if (c == 'n') menü = true;
      else falsche_eingabe();
    }

    // Spielende: Gewonnen
    while (AnzPlayer >= 10 && AnzCPU <= 0 && !menü)
    {
      system("cls");
      logo();
      line();
      printf("\n   SPIEL GEWONNEN");
      line();
      printf("\n\n   Der CPU-Spieler besitzt keine Karten mehr.");
      printf("\n   Sie haben das Spiel gewonnen.\n");
      line();
      printf("\n\n   M\x94""chten Sie das Spiel neustarten?");
      printf("\n   Falls nicht, kehren Sie zum Hauptmen\x81 zur\x81""ck.\n");
      line();
      printf("\n   (J/N): ");
      c = _getch();

      if (c == 'j') rundestart();
      else if (c == 'n') menü = true;
      else falsche_eingabe();
    }
  }
}

int admin_wiederholung() {
  char j;
  bool admin_true = false;

  printf("M\x94""chten Sie wirklich Trefferpunkte abfragen?");
  printf("\n   (J/N): ");
  j = _getch();

  if (j == 'j') admin_true = true;
  else if (j == 'n') admin_true = false;
  else falsche_eingabe();

  return admin_true;
}

int vergleiche(int Typ, struKarten* pListePlayer, struKarten* pListeCPU) {
  int kartenänderung = 0; // Wie bei der Ausgabe bedeutet 1 = gewonnen, 2 = verloren, 3 = unentschieden. 0 = leer
  // Der Parameter ist der Typ des Vergleichs und die beiden Listen, die verglichen werden.
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

struKarten* firstlast_gew(struKarten* pListeGew, struKarten* pListeVerl) { 
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
  return pListeGew;
}

struKarten* firstlast_verl(struKarten* pListeVerl) {
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
  return pListeVerl;
}

struKarten* firstlast_unent(struKarten* pListe) {
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
  return pListe;
}



void einstellungen() {
  // Diese Funktion beinhaltet optionale Einstellungen wie Farbe, Entwicklermodus und Version.
  bool settings = true;
  bool farben = true;

  char neue_hintergrundfarbe = ' ';
  char neue_textfarbe = ' ';
  char eingabe = ' ';

  while (settings)
  {
    system("cls");
    logo();
    line();
    printf("\n   Einstellungen");
    line();
    printf("\n\n   Farbe             (1)");
    printf("\n   Version           (2)");
    printf("\n   Entwicklermodus   (3)");
    printf("\n   Zur\x81""ck            (4)\n");
    line();
    printf("\n   (1/2/3/4): ");
    eingabe = _getch();

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
        logo();
        line();
        printf("\n   Farben");
        line();
        printf("\n\n   Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
        printf("\n   Nur eine Farbe kann Aktiv sein.\n");
        printf("\n  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
        printf("\n                                          \xBA");
        printf("\n           Hintergrundfarbe               \xBA           Textfarbe");
        printf("\n                                          \xBA");
        printf("\n  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
        printf("\n                                          \xBA");
        printf("\n           Schwarz = 1  [%s]           \xBA           Schwarz = 1  [%s]", s_h, s_t);
        printf("\n           Grau    = 2  [%s]           \xBA           Grau    = 2  [%s]", g_h, g_t);
        printf("\n           Weiss   = 3  [%s]           \xBA           Weiss   = 3  [%s]", w_h, w_t);
        printf("\n           Gr\x81n    = 4  [%s]           \xBA           Gr\x81n    = 4  [%s]", gr_h, gr_t);
        printf("\n           Blau    = 5  [%s]           \xBA           Blau    = 5  [%s]", b_h, b_t);
        printf("\n           Rot     = 6  [%s]           \xBA           Rot     = 6  [%s]", r_h, r_t);
        printf("\n                                          \xBA");
        printf("\n  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n");
        printf("\n   Hintergrundfarbe (1) ");
        printf("\n   Textfarbe        (2)");
        printf("\n   Zur\x81""ck           (3)\n");
        line();

        printf("\n   (1/2/3): ");
        eingabe = _getch();
        if (eingabe == '1')
        {
          printf("Hintergrundfarbe: ");
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
            printf("\n   *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
            system("timeout 1 >null");
            system("cls");
          }
        }
        else if (eingabe == '2') {
          printf("Textfarbe: ");
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
            printf("\n   *Die Hintergrundfarbe und die Textfarbe k\x94nnen nicht gleich sein.");
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
      line();
      printf("\n   Version");
      line();
      printf("\n\n         .@@@@@@@@@@@@@@@@@@.           Team:                @@@@@@@@@@          \n");
      printf("         @                  @.      Mazen & Yannic         @@@@@@@@@@@@@@        \n");
      printf("        @@                  @@.                         ,@@@@@@@@       @@       \n");
      printf("       @@                    @@                        @  @@@@'           @      \n");
      printf("       @@                    &@                      ,@                    @ ,@. \n");
      printf("       @ @@@@@@@    .@@@@@@@@ @.        Final        @@ @@@@    /@@@@@.    @@  @ \n");
      printf("       @@   (o)      (O)     @@@     Version 1.5     @@  (O)      (O)     .@@  @ \n");
      printf("      .@@        ((           @@      x64-Debug      @        /           @@@.(.)\n");
      printf("      @@@  @@@@@@@@@@@@@@@    @@                     @       (@.          @@@    \n");
      printf("          @@ ########## @@@                         .@@@@@@@@@@@@@@@@@@   @@,    \n");
      printf("         @@@            @@@                         @@@@ ########## @@@@ .@@*    \n");
      printf("         @@ ##________## @@@                        '@@@              @@@@@@*    \n");
      printf("         @@@ '########'  @@@       Clash Of Clans    @@@@ #########,@@@@@@@      \n");
      printf("         @@@             @@@          Quartett!       @@@@@@@@@@@@@@@@@@@        \n");
      printf("          @               @                             @@@@@@@@@@@@@@@@         \n");
      line();
      printf("\n   Zum Fortfahren eine Taste dr\x81""cken ");
      system("pause >nul");
    }
    else if (eingabe == '3') {
      if (admin == true) {
        admin = false;
        printf("Entwicklermodus Deativiert ");
        Sleep(700);
        system("cls");
      }
      else if (admin == false) {
        admin = true;
        printf("Entwicklermodus Aktiviert ");
        Sleep(700);
        system("cls");
      }
    }
    else if (eingabe == '4') settings = false;
    else if (eingabe != '1' && eingabe != '2' && eingabe != '3' && eingabe != '4') falsche_eingabe();
  }
}

void farbmatrix(char hintergrundfarbe, char textfarbe) {
  // Diese Funktion verarbeitet die Einstellungen für die Farben des Debugging-Fensters.
  char SysPrint[20];
  sprintf_s(SysPrint, "color %c%c", hintergrundfarbe, textfarbe);
  system(SysPrint);
}

void falsche_eingabe() {
  printf("\n   Falsche Eingabe ");
  system("timeout 1 >null");
  system("cls");
}

void line() {
  printf("\n  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
}

void verloren()
{
  line();
  printf("\n   VERLOREN");
  line();
  printf("\n\n   Sie verlieren diese Karte leider.");
  printf("\n   Der Gegner gewinnt Ihre aktuelle Karte.\n");
  line();
  printf("\n   Zum Fortfahren eine Taste dr\x81""cken ");
  system("pause >nul");
}

void gewonnen()
{
  line();
  printf("\n   GEWONNEN");
  line();
  printf("\n\n   Sie gewinnen die Karte des Gegners.");
  printf("\n   Der Gegner verliert sie.\n");
  line();
  printf("\n   Zum Fortfahren eine Taste dr\x81""cken ");
  system("pause >nul");
}

void unentschieden()
{
  line();
  printf("\n   UNENTSCHIEDEN");
  line();
  printf("\n\n   Niemand gewinnt dieses Mal.");
  printf("\n   Die obersten Karten werden nach hinten versetzt.\n");
  line();
  printf("\n   Zum Fortfahren eine Taste dr\x81""cken ");
  system("pause >nul");
}

void logo()
{
  printf("\n");
  printf("    _____ __    _____ _____ _____    _____ _____    _____ __    _____ _____ _____ \n");
  printf("   |     |  |  |  _  |   __|  |  |  |     |   __|  |     |  |  |  _  |   | |   __|\n");
  printf("   |   --|  |__|     |__   |     |  |  |  |   __|  |   --|  |__|     | | | |__   |\n");
  printf("   |_____|_____|__|__|_____|__|__|  |_____|__|     |_____|_____|__|__|_|___|_____|\n\n");
  printf("                   _____ _____ _____ _____ _____ _____ _____ _____                \n");
  printf("                  |     |  |  |  _  | __  |_   _|   __|_   _|_   _| \n");
  printf("                  |  |  |  |  |     |    -| | | |   __| | |   | |   \n");
  printf("                  |__  _|_____|__|__|__|__| |_| |_____| |_|   |_|   \n");
  printf("                     |__|                                           \n\n");
}

void end()
{
  system("cls");

  printf("\n\n");
  printf("   _____ _____ ____  _____ \n");
  printf("  |   __|   | |    \x5C|   __|\n");
  printf("  |   __| | | |  |  |   __|\n");
  printf("  |_____|_|___|____/|_____|\n");
  printf("\n\n\n                           \n");
  Sleep(800);
}

//last 1266 before rework, now 1044 | wasted hours in this project: 30h+