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
int rundestart();                                               // Start einer Runde
int rundeneustart();                                            // Neustart einer Runde
int ausgabe(struKarten*, struKarten*);                          // Funktion für Ausgabe der Karten
struKarten* createlist(struKarten*, struKarten*);               // Funktion für das Kreieren von Listen und Hinzufügen von Karten mit Hilfe der Methode "karte"
struKarten* removelist(struKarten*, struKarten*);               // Funktion für das Entfernen von einer Karte/n aus einer Liste
struKarten* karte(int, const char*, int, int, double);          // Funktion für das Erstellen und Abfüllen der Karten mit Werten
struKarten* firstlast_gew(struKarten*, struKarten*);            // Funktion für den Gewinner einer Karte
struKarten* firstlast_verl(struKarten*);                        // Funktion für den Verlierer einer Karte
struKarten* firstlast_unent(struKarten*);                       // Funktion für Unentschieden
int vergleiche(int, struKarten*, struKarten*);                  // Funktion für das Vergleichen von Karten aus zwei Listen

int listcount(struKarten*);                                     // Einfache Funktion fürs Zählen von Elementen in einer Liste
int menü();                                                     // Hauptmenü
int einstellungen();                                            // Einstellungen
void farbmatrix(char, char);                                    // Farbmatrix fürs Einstellen der Farben auf der CMD
void falsche_eingabe();                                         // Einfache Ausgabe bei falscher Eingabe
void end();                                                     // Ausgabe für Spielende wenn man das Spiel verlässt
void logo();                                                    // Ausgabe für Logo des Spiels
void verloren();                                                // Ausgabe wenn man eine Karte verliert
void gewonnen();                                                // Ausgabe wenn man eine Karte gewinnt
void unentschieden();                                           // Ausgabe wenn unentschieden

// Weitere Beschreibungen findet man in den einzelnen Funktionen.


// Globale Variablen
bool admin = false;                                             // Wird für die Einstellungen/Entwicklermodus benötigt.
bool first = true;                                              // Wird für die Einstellungen/Farben benötigt.
char hintergrundfarbe;                                          // Hintergrundfarbe der CMD.
char textfarbe;                                                 // Textfarbe der CMD.


int ausgabe(struKarten* pListePlayer, struKarten* pListeCPU) {

  // Funktion, bei der die Ausgabe der Karten und die eigentliche Runde geschieht.

  // Variablen
  char c;                     // Wird zur Überprüfung der ersten Eingabe benötigt.
  char j;                     // Wird zur Vergewisserung der ersten Eingabe benötigt (Sind Sie sicher? Ja/Nein).
  bool menü = false;          // Wird für das Rückkehren zum Hauptmenü benötigt.
  bool nextkarte = false;     // Wird benötigt, um aus der Ausgabe-Schleife raus zu kommen und, falls zur nächsten Karte gewechselt werden sollte.
  int kartenänderung;         // Wird benötigt, um zu identifizieren, welche änderung an den beiden Listen vorgenommen werden sollte.
                              // Kartenänderung: 0 = leer (keine Änderung), 1 = gewonnen, 2 = verloren, 3 = unentscheiden (siehe unter der Kartenausgabe-Schleife)

  while (!menü) {
    nextkarte = false;

    kartenänderung = 0;                         // Fängt immer mit dem leeren Zustand an. Es geschieht nichts mit den Listen, bis eine gültige Eingabe gemacht wird.

    int AnzPlayer = listcount(pListePlayer);    // Zählt Anzahl Karten im eigenen Stapel.

    int AnzCPU = listcount(pListeCPU);          // Zählt Anzahl Karten im CPU-Stapel.


    // Kartenausgabe-Schleife
    while (!nextkarte && !menü && AnzPlayer > 0 && AnzCPU > 0) {  // In dieser While-Schleife wird immer wieder die gleiche Karte ausgegeben, bis man eine gültige Eingabe macht.
      system("cls");

      printf("\n\n");
      printf("\n  ==================================");
      printf("\n\n               KARTE               ");
      printf("\n\n    ______________________________ ");
      printf("\n   /                              \x5C");
      printf("\n  /  CoC Quartett | Karte Nr.  %-2i  \x5C", pListePlayer->Nr);
      printf("\n  |                                |");
      printf("\n  |      --------------------      |");
      printf("\n  |      ---%-14s---      |", pListePlayer->Bez);
      printf("\n  |      --------------------      |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |                                |");
      printf("\n  |    -----------------------     |");
      printf("\n  |   |Trefferpunkte   | %4i |    |", pListePlayer->Trefferpunkte);
      printf("\n  |   |                |      |    |");
      printf("\n  |   |Geschwindigkeit | %4i |    |", pListePlayer->Geschw);
      printf("\n  |   |                |      |    |");
      printf("\n  |   |Schaden         | %5.1lf|    |", pListePlayer->Schaden);
      printf("\n  |    -----------------------     |");
      printf("\n  \x5C                                /");
      printf("\n   \x5C______________________________/");
      printf("\n\n");

      printf("\n  Ihre n\x84""chste Karte lautet: %-14s ", pListePlayer->pNext->Bez);
      printf("\n  Sie besitzen insgesamt noch %i Karten.", AnzPlayer);
      

      printf("\n\n\n  =================================");
      printf("\n  Trefferpunkte?         (1)");
      printf("\n  Geschwindigkeit?       (2)");
      printf("\n  Schaden?               (3)");
      printf("\n\n  Neu Starten            (4)");
      printf("\n  Zur\x81" "ck zum Hauptmen\x81   (5)");
      printf("\n  =================================");
      printf("\n\n  (1/2/3/4/5): ");

      c = _getch();

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
          rundeneustart();
          menü = true;
        }

        else if (j == 'n');

        else falsche_eingabe();
      }

      else if (c == '5') {
        printf("\n\n  M\x94""chten Sie wirklich zum Hauptmen\x81 zur\x81""ck?");
        printf("\n  (J/N): ");

        j = _getch();
        if (j == 'j') menü = true;
      }

      else if (c != '1' && c != '2' && c != '3' && c != '4' && c != '5')
      {
        falsche_eingabe();
      }

    }

    if (kartenänderung == 1) // Bei Gewinn einer Karte
    {
      pListePlayer = firstlast_gew(pListePlayer, pListeCPU);
      pListeCPU = firstlast_verl(pListeCPU);
      gewonnen();
    }

    else if (kartenänderung == 2) // Bei Verlust einer Karte
    {
      pListeCPU = firstlast_gew(pListeCPU, pListePlayer);
      pListePlayer = firstlast_verl(pListePlayer);
      verloren();
    }

    else if (kartenänderung == 3) // Bei Unentschieden
    {
      pListePlayer = firstlast_unent(pListePlayer);
      pListeCPU = firstlast_unent(pListeCPU);
      unentschieden();
    }


    // Spielende: Verloren-Schleife
    while (AnzPlayer <= 0 && AnzCPU >= 10 && !menü) // Spielende: Wenn man das Spiel verliert.
    {
      system("cls");

      printf("\n  ==================================");
      printf("\n\n  Sie besitzen keine Karten mehr. Sie haben das Spiel verloren.");
      printf("\n\n  ==================================");
      printf("\n\n\n\n  M\x94""chten Sie zum Hauptmen\x81 zur\x81""ck?");


      c = _getch();
      if (c == 'j') menü = true;

      else if (j == 'n');

      else falsche_eingabe();
    }

    // Spielende: Gewonnen-Schleife
    while (AnzPlayer >= 10 && AnzCPU <= 0 && !menü) // Spielende: Wenn man das Spiel gewinnt.
    {
      system("cls");

      printf("\n  ==================================");
      printf("\n\n  Der CPU-Spieler besitzt keine Karten mehr. Sie haben das Spiel gewonnen.");
      printf("\n\n  ==================================");
      printf("\n\n\n\n  M\x94""chten Sie zum Hauptmen\x81 zur\x81""ck?");

      c = _getch();
      if (c == 'j') menü = true;

      else if (j == 'n');

      else falsche_eingabe();
    }

  }
  return 0;
}

struKarten* firstlast(struKarten* pListeGewinner, struKarten* pListeVerlierer)
{
  // In dieser Funktion wird aus der Liste des Verl. die erste Karte und aus der Liste des Gew. die erste Karte
  // an die letzte Stelle des Gew. versetzt


  struKarten* pTempFirst = pListeGewinner;
  struKarten* pTempLast = pListeGewinner;
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

  pListeGewinner = pTempFirst->pNext; //pListeGewinner zeigt direkt auf die 2. Karte
  pTempLast->pNext->pNext = NULL; //Bei der Karte 1 wird pNext auf 0 gesetzt
  pListeGewinner->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext = pTempLast->pNext; //Bei Orginal-Liste wird pNext auf Karte 11 bzw 1 gesetzt.

  pTempLast = pListeGewinner;

  while (pTempLast->pNext != NULL)
  {

    pTempLastMinus = pTempLast;
    pTempLast = pTempLast->pNext;

    //printf("pTempFirst %i\n", pTempFirst->Nr);
    //printf("pTempLast %i\n", pTempLast->Nr);
    //printf("pTempLastMinus %i\n\n", pTempLastMinus->Nr);

    int z = pTempLast->Nr;
    //Zum Testen
    printf("\n  pTemp Zeigt auf die Karte Nr: %i", z);

  }
  printf("\n  ==================================");



  system("pause");

  return 0;
}

struKarten* firstlast_gew(struKarten* pListeGew, struKarten* pListeVerl)
{

  if (pListeGew) {}
  struKarten* pTemp = pListeGew;
  pListeGew = pListeGew->pNext;
  pTemp->pNext = NULL;

  struKarten* pLast = pListeGew;

  while (pLast->pNext != NULL) {
    pLast = pLast->pNext;
  }

  pLast->pNext = pTemp;


  struKarten* pKarte = pListeVerl;
  pTemp->pNext = pKarte;

  return pListeGew;
}

struKarten* firstlast_verl(struKarten* pListeVerl)
{
  struKarten* pTemp = pListeVerl;
  pListeVerl = pListeVerl->pNext;
  pTemp->pNext = NULL;

  return pListeVerl;
}

struKarten* firstlast_unent(struKarten* pListe)
{
  struKarten* pTemp = pListe;
  pListe = pListe->pNext;
  pTemp->pNext = NULL;

  struKarten* pLast = pListe;

  while (pLast->pNext != NULL) {
    pLast = pLast->pNext;
  }

  pLast->pNext = pTemp;

  return pListe;
}

int vergleiche(int Typ, struKarten* pListePlayer, struKarten* pListeCPU) {
  
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
    if (pListePlayer->Schaden > pListeCPU->Geschw)      kartenänderung = 1;
    else if (pListePlayer->Schaden < pListeCPU->Geschw) kartenänderung = 2;
    else if (pListePlayer->Schaden = pListeCPU->Geschw) kartenänderung = 3;
  }
  return kartenänderung;
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

struKarten* karte(int pTruppe, const char* pBez, int Hp, int Spd, double Dmg)
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

int rundestart()
{
  system("cls");

  
  for (int i = 0; i < 3; i++) {
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt .");
    printf("\n\n  Bitte Warten");
    Sleep(500);
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt ..");
    printf("\n\n  Bitte Warten");
    Sleep(500);
    system("cls");
    printf("\n\n");
    printf("\n  ==================================");
    printf("\n\n  Karten werden erstellt und gemischt ...");
    printf("\n\n  Bitte Warten");
    Sleep(500);
  }

  struKarten* pStart = NULL;        //Erstellt Startliste mit der beim Verteilen gearbeitet wird

  struKarten* pListePlayer = NULL;  //Erstellt Liste von Player
  struKarten* pListeCPU = NULL;     //Erstellt Liste von CPU

  pStart = createlist(pStart, karte(1, "Barbar", 160, 16, 30.3));
  pStart = createlist(pStart, karte(2, "Bogensch\x81tzin", 48, 24, 25.7));
  pStart = createlist(pStart, karte(3, "Drache", 3100, 16, 240.1));
  pStart = createlist(pStart, karte(4, "P.E.K.K.A", 5300, 16, 470.3));
  pStart = createlist(pStart, karte(5, "Hexe", 300, 12, 100.2));
  pStart = createlist(pStart, karte(6, "Schweinereiter", 270, 24, 60.0));
  pStart = createlist(pStart, karte(7, "Lakai", 58, 32, 38.2));
  pStart = createlist(pStart, karte(8, "Tunnelgr\x84""ber", 610, 32, 88.7));
  pStart = createlist(pStart, karte(9, "Riese", 800, 12, 31.5));
  pStart = createlist(pStart, karte(10, "Ballon", 390, 10, 108.0));



  int runde;    // Verteilen: Runde 1 bis 5 werden dem Player Karten zugeteilt, Runde 5 bis 10 dem CPU

  for (runde = 1; runde <= 5; runde++)
  {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt.
    //int pEnd = 1;
    
    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;  // pKarte ist eine Variable, in der man eine zufällige Karte aus einer Liste (pStart) hineinspeichert.

    for (int c = 1; c <= r; c++)
    {
      pKarte = pKarte->pNext;
    }

    /*
    //Ausgabe zum Testen
    printf("\n  Die zuf\xE4llige Karte ist Karte Nr: %i ", z);
    printf("\n  Diese Karte heisst %c.", pKarte->Bez);
    printf("\n  Diese wird jetzt aus der Startliste entfernt.");
    system("pause");
    */

    pStart = removelist(pStart, pKarte);              // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListePlayer = createlist(pListePlayer, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }

  for (runde = 5; runde < 10; runde++)
  {
    int anz = listcount(pStart);            // Es werden alle Elemente der Liste pStart gezählt. 5 wurden schon entfernt.
    //int pEnd = 1;


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
    printf("\n  Diese wird jetzt aus der Startliste entfernt und der Playerliste hinzugefügt.");
    system("pause");
    */

    pStart = removelist(pStart, pKarte);        // Parameter: Die Liste, aus der entfernt wird und welche Karte.
    pListeCPU = createlist(pListeCPU, pKarte);  // Parameter: Die Liste, zu der hinzugefügt wird und welche Karte.
  }



  ausgabe(pListePlayer, pListeCPU);

  return 0;
}

int rundeneustart()
{
  // Genau gleiche Funktion wie rundestart, wird aber nur ausgeführt wenn man das Spiel neustarten möchte.

  system("cls");


  printf("\n\n");
  printf("\n  ==================================");
  printf("\n\n  Karten werden wieder neu gemischt .");
  printf("\n\n  Bitte Warten");
  Sleep(500);
  system("cls");
  printf("\n\n");
  printf("\n  ==================================");
  printf("\n\n  Karten werden wieder neu gemischt ..");
  printf("\n\n  Bitte Warten");
  Sleep(500);
  system("cls");
  printf("\n\n");
  printf("\n  ==================================");
  printf("\n\n  Karten werden wieder neu gemischt ...");
  printf("\n\n  Bitte Warten");
  Sleep(500);

  struKarten* pStart = NULL;

  struKarten* pListePlayer = NULL;
  struKarten* pListeCPU = NULL;

  pStart = createlist(pStart, karte(1, "Barbar", 160, 16, 30.3));
  pStart = createlist(pStart, karte(2, "Bogensch\x81tzin", 48, 24, 25.7));
  pStart = createlist(pStart, karte(3, "Drache", 3100, 16, 240.1));
  pStart = createlist(pStart, karte(4, "P.E.K.K.A", 5300, 16, 470.3));
  pStart = createlist(pStart, karte(5, "Hexe", 300, 12, 100.2));
  pStart = createlist(pStart, karte(6, "Schweinereiter", 270, 24, 60.0));
  pStart = createlist(pStart, karte(7, "Lakai", 58, 32, 38.2));
  pStart = createlist(pStart, karte(8, "Tunnelgr\x84""ber", 610, 32, 88.7));
  pStart = createlist(pStart, karte(9, "Riese", 800, 12, 31.5));
  pStart = createlist(pStart, karte(10, "Ballon", 390, 10, 108.0));

  int runde;    

  for (runde = 1; runde < 5; runde++)
  {
    int anz = listcount(pStart);


    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;

    int z = 0;
    for (int c = 1; c <= r; c++)
    {
      pKarte = pKarte->pNext;
      z = pKarte->Nr;
    }

    /*
    // Ausgabe zum Testen
    printf("\n  Die zuf\xE4llige Karte ist Karte Nr: %i ", z);
    printf("\n  Diese Karte heisst %c.", pKarte->Bez);
    printf("\n  Diese wird jetzt aus der Startliste entfernt und der Playerliste hinzugefügt.");
    system("pause");
    */

    pStart = removelist(pStart, pKarte);
    pListePlayer = createlist(pListePlayer, pKarte);
  }

  for (runde = 5; runde < 10; runde++)
  {
    int anz = listcount(pStart);


    srand(time(NULL));
    int r = rand() % anz;

    struKarten* pKarte = pStart;

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
    printf("\n  Diese wird jetzt aus der Startliste entfernt und der Playerliste hinzugefügt.");
    system("pause");
    */

    pStart = removelist(pStart, pKarte);        
    pListeCPU = createlist(pListeCPU, pKarte);  
  }

  ausgabe(pListePlayer, pListeCPU);

  return 0;
}

int listcount(struKarten* pListe) 
{
  int anz = 0;
  struKarten* pTmp = pListe;
  for (pTmp; pTmp != NULL; pTmp = pTmp->pNext) {  // Es werden alle Elemente in einer Liste gezählt.
    anz++;
  }
  return anz;
}

int main()
{

  srand(time(NULL));                                            // Rand Initialisierung für die Methode "random".
  system("mode con cols=150 lines=70");                         // Setzt die Grösse der CMD

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
    printf("\n              Hauptmen\x81             ");
    printf("\n");
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

int einstellungen()
{
  //Variablen
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
      printf("\n\n");
      printf("      .@@@@@@@@@@@@@@@@@@.                                                             \n");
      printf("      @                  @.                                       @@@@@@@@@@           \n");
      printf("     @@                  @@.                                    @@@@@@@@@@@@@@         \n");
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
      

      printf("01234567890123456789012345678\n");
      printf("1    .@@@@@@@@@@@@@@@@@@.    \n");
      printf("2    @                  @.   \n");
      printf("3   @@                  @@.  \n");
      printf("4  @@                    @@  \n");
      printf("5  @@                    &@  \n");
      printf("6  @ @@@@@@@    .@@@@@@@@ @. \n");
      printf("7  @@   (o)      (O)     @@@ \n");
      printf("8 .@@        ((           @@ \n");
      printf("9 @@@  @@@@@@@@@@@@@@@    @@ \n");
      printf("0     @@ ########## @@@      \n");
      printf("1    @@@            @@@      \n");
      printf("2    @@ ##________## @@@     \n");
      printf("3    @@@ '########'  @@@     \n");
      printf("4    @@@             @@@     \n");
      printf("5                            \n");

      printf("01234567890123456789012345678\n");
      printf("1         @@@@@@@@@@         \n");
      printf("2       @@@@@@@@@@@@@@       \n");
      printf("3    ,@@@@@@@@       @@      \n");
      printf("4   @  @@@@'           @     \n");
      printf("5 ,@                    @ ,@.\n");
      printf("6 @@ @@@@    /@@@@@.    @@  @\n");
      printf("7 @@  (O)      (O)     .@@  @\n");
      printf("8 @        /           @@@(.)\n");
      printf("9 @       (@.          @@@   \n");
      printf("0.@@@@@@@@@@@@@@@@@@   @@,   \n");
      printf("1@@@@ ########## @@@@ .@@*   \n");
      printf("2'@@@              @@@@@@*   \n");
      printf("3 @@@@ #########,@@@@@@@     \n");
      printf("4  @@@@@@@@@@@@@@@@@@@       \n");
      printf("5    @@@@@@@@@@@@@@@@        \n");

      printf("01234567890123456789012345678\n");
      printf("1        @@@@@@@@@@@         \n");
      printf("2     @@@@@@@@@@@@@@@@@      \n");
      printf("3   @@@@@@         @@@@@@    \n");
      printf("4  @@@@@@ (O)   (O) @@@@@@   \n");
      printf("5  @@@@@@     @     @@@@@@   \n");
      printf("6  @@@@@@@  , , ,  @@@@@@@   \n");
      printf("7   @@@@@@@ @ @ @ @@@@@@@    \n");
      printf("8    @@@@@@U@U@U@U@@@@@@     \n");
      printf("9       @@@@@@@@@@@@@        \n");
      printf("0        |  |   |  |         \n");
      printf("1        |  |   |  |  `      \n");
      printf("2       (###########)    `   \n");
      printf("3        @@@@@@@@@@@  ` `    \n");
      printf("4         @@@@@@@@@  `  #  ` \n");
      printf("5                      `  `  \n");

      printf("01234567890123456789012345678\n");
      printf("1    @                 @     \n");
      printf("2  @@                   @@   \n");
      printf("3 @                       @  \n");
      printf("4@@@@@@@@@@@@   @@@@@@@@@@@@ \n");
      printf("5@@@@@@@@@@@@@ @@@@@@@@@@@@@@\n");
      printf("6@        @@@   @@@        @ \n");
      printf("7   ( o )     .     ( o )  @@\n");
      printf("8@@          ,@            @@\n");
      printf("9@@@       ,@@  @.        @@@\n");
      printf("0@@@)        @@@         (@@@\n");
      printf("1@@@@                    @@@@\n");
      printf("2 @@@@@   ###########  @@@@@@\n");
      printf("3 @@@@@@              @@@@@@ \n");
      printf("4   @@@@@@          @@@@@@   \n");
      printf("5     @@@@@@.     .@@@@@     \n");

      printf("01234567890123456789012345678\n");
      printf("1                            \n");
      printf("2@                         @ \n");
      printf("3@@                       @@ \n");
      printf("4@@@@  ,-------------,  @@@@ \n");
      printf("5 @@@@@@'           '@@@@@@  \n");
      printf("6 @@@@                 @@@@  \n");
      printf("7  @@  @(O)@)   (@(O)@  @@   \n");
      printf("8   |  @@@'   M   '@@@  |    \n");
      printf("9   |  '     MMM     '  |    \n");
      printf("0   |        MMM        |    \n");
      printf("1   |        MMM        |    \n");
      printf("2 /MMMMMMMMMM/ \MMMMMMMMMM\  \n");
      printf("3/'         /   \         '\ \n");
      printf("4          /     \           \n");
      printf("5                            \n");

      printf("01234567890123456789012345678\n");
      printf("1                            \n");
      printf("2@                         @ \n");
      printf("3@@                       @@ \n");
      printf("4@@@@  ,-------------,  @@@@ \n");
      printf("5 @@@@@@'           '@@@@@@  \n");
      printf("6 @@@@                 @@@@  \n");
      printf("7  @@  @(O)@)   (@(O)@  @@   \n");
      printf("8   |  @@@'   M   '@@@  |    \n");
      printf("9   |  '     MMM     '  |    \n");
      printf("0   |        MMM        |    \n");
      printf("1   |        MMM        |    \n");
      printf("2 /MMMMMMMMMM/ \x5CMMMMMMMMMM\x5C  \n");
      printf("3/'         /   \x5C         '\x5C \n");
      printf("4          /     \x5C           \n");
      printf("5                            \n");

      printf("01234567890123456789012345678\n");
      printf("1    ,@@@@@@@@@@@@@@@@@@,    \n");
      printf("2  @@@@@@@@@@@@@@@@@@@@@@@@  \n");
      printf("3 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("4@@@@                    @@@@\n");
      printf("5@@@ Xx                xX @@@\n");
      printf("6@@|  'XXXx,      ,xXXX'  |@@\n");
      printf("7@ |   (O)    ,     (O)   | @\n");
      printf("8@ |         ,@           | @\n");
      printf("9@ |        ,@  @.        | @\n");
      printf("0@@|    @@@@@@@@@@@@@@    |@@\n");
      printf("1 @,\   @@ ######## @@   /,@ \n");
      printf("2  @@ \ '@          @' / @@  \n");
      printf("3   @@  \@@@@@@@@@@@@/  @@   \n");
      printf("4    @    '@@@@@@@@'    @    \n");
      printf("5   @@       '@@'       @@   \n");

      printf("01234567890123456789012345678\n");
      printf("1    ,@@@@@@@@@@@@@@@@@@,    \n");
      printf("2  @@@@@@@@@@@@@@@@@@@@@@@@  \n");
      printf("3 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("4@@@@                    @@@@\n");
      printf("5@@@ Xx                xX @@@\n");
      printf("6@@|  'XXXx,      ,xXXX'  |@@\n");
      printf("7@ |   (O)    ,     (O)   | @\n");
      printf("8@ |         ,@           | @\n");
      printf("9@ |        ,@  @.        | @\n");
      printf("0@@|    @@@@@@@@@@@@@@    |@@\n");
      printf("1 @,\x5C   @@ ######## @@   /,@ \n");
      printf("2  @@ \x5C '@          @' / @@  \n");
      printf("3   @@  \x5C@@@@@@@@@@@@/  @@   \n");
      printf("4    @    '@@@@@@@@'    @    \n");
      printf("5   @@       '@@'       @@   \n");

      printf("01234567890123456789012345678\n");
      printf("1   ,@@@@@@@@@@@@@@@@@@@@,   \n");
      printf("2 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("3 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("4@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
      printf("5@@  '@@@@@@@@@@@@@@@@@@'  @@\n");
      printf("6@@,     @@@@@@@@@@@@     ,@@\n");
      printf("7@@@        @@@@@@        @@@\n");
      printf("8 @@    (O)  @@@@  (O)    @@ \n");
      printf("9 @@          @@          @@ \n");
      printf("0  @@        ,' .        @@  \n");
      printf("1  @@                    @@  \n");
      printf("2 @@.\     ########     /.@@ \n");
      printf("3@@...\     '####'     /...@@\n");
      printf("4@@@....\            /....@@@\n");
      printf("5 @@@......\_______/......@@@\n");

      printf("01234567890123456789012345678\n");
      printf("1   ,@@@@@@@@@@@@@@@@@@@@,   \n");
      printf("2 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("3 @@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
      printf("4@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
      printf("5@@  '@@@@@@@@@@@@@@@@@@'  @@\n");
      printf("6@@,     @@@@@@@@@@@@     ,@@\n");
      printf("7@@@        @@@@@@        @@@\n");
      printf("8 @@    (O)  @@@@  (O)    @@ \n");
      printf("9 @@          @@          @@ \n");
      printf("0  @@        ,' .        @@  \n");
      printf("1  @@                    @@  \n");
      printf("2 @@.\x5C     ########     /.@@ \n");
      printf("3@@...\x5C     '####'     /...@@\n");
      printf("4@@@....\x5C            /....@@@\n");
      printf("5 @@@......\x5C_______/......@@@\n");
      printf("01234567890123456789012345678\n");

      printf("1.x...,@@@@@@@@@@@@@@@@@,....\n");
      printf("2..X @@'               '@@...\n");
      printf("3...@@                   @@..\n");
      printf("4..@' ___             ___ '@.\n");
      printf("5..@  '@@@@@@XxxxX@@@@@@'  @@\n");
      printf("6.@'   @@.O`@     @,O`@@  `@@\n");
      printf("7,@@   `@@@@+     +@@@@:   @@\n");
      printf("8@@@,                    ,@@@\n");
      printf("9@@  @@@@@@@,        ,@@@@@'@\n");
      printf("0'@  .@/   '@@@@@@@@@@     ,@\n");
      printf("1.@@  @        @@'   @`    @@\n");
      printf("2..@.          `@          @@\n");
      printf("3xX `@@`              ,@@@/..\n");
      printf("4.....+@@@@@@@@@@@@@@@@@'x...\n");
      printf("5.....X...................X..\n");

      printf("01234567890123456789012345678\n");
      printf("1    ,..xx@@@@@@@@@@xx..,    \n");
      printf("2  @'                   ,'@, \n");
      printf("3 @@@'`  `' ` `'  `'@@@'  `@,\n");
      printf("4@@'                   @@  `@\n");
      printf("5@   @@@@        @@@@  '@@  @\n");
      printf("6@  @@@@@@      @@@@@@   @  @\n");
      printf("7@   @@@@        @@@@    @, @\n");
      printf("8@           ,           @  @\n");
      printf("9@          .@@,        @ @  \n");
      printf("0 @@       ,@@@@.       @@'` \n");
      printf("1   @@@@            @@@@     \n");
      printf("2      @,###########,@       \n");
      printf("3        ###########         \n");
      printf("4             @   @  @@@@@@  \n");
      printf("5      @@@@@@  @   @         \n");

      printf("01234567890123456789012345678\n");
      printf("1       )                    \n");
      printf("2      (_)                   \n");
      printf("3      |`|MMMMMMMMM          \n");
      printf("4    MM| |MMMMMMMMMMMMM      \n");
      printf("5   MMMMMMMMMMMMMMMMMMMM     \n");
      printf("6  MMMMMMMMMMMMMMMMMMMMMM    \n");
      printf("7MMMMMMMMMMMMMMMMMMMMMMMMMMM \n");
      printf("8 @@@ @@@@@     @@@@@  @@@   \n");
      printf("9  @@  (O)       (O)   @@    \n");
      printf("0   @        )         @     \n");
      printf("1   @       (@@       @      \n");
      printf("2    @  ##,     ,###  @      \n");
      printf("3    @  `'#######'`  @       \n");
      printf("4     @@,.       .,@@        \n");
      printf("5        `'@@@@@'`           \n");

      system("timeout 3 >null");
      printf("\n\n");
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

void verloren()
{
  system("cls");

  printf("\n  ==================================");
  printf("\n\n  ------------VERLOREN------------");
  printf("\n  Sie verlieren diese Karte leider.");
  printf("\n  Der Gegner erhält Ihre Karte.");
  printf("\n\n  ==================================");
  Sleep(1500);
}

void gewonnen()
{
  system("cls");

  printf("\n  ==================================");
  printf("\n\n  ------------GEWONNEN------------");
  printf("\n  Sie gewinnen die Karte des Gegners.");
  printf("\n  Der Gegner verliert sie.");
  printf("\n\n  ==================================");
  Sleep(1500);
}

void unentschieden()
{
  system("cls");

  printf("\n  ==================================");
  printf("\n\n  ---------UNENTSCHIEDEN----------");
  printf("\n  Niemand gewinnt dieses Mal.");
  printf("\n  Die obersten Karten werden nach hinten versetzt.");
  printf("\n\n  ==================================");
  Sleep(1500);
}


void logo()
{

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
  system("cls");

  printf("\n      ______          __   ");
  printf("\n     / ____/___  ____/ /__ ");
  printf("\n    / __/ / __ \x5C/ __  / _ \x5C");
  printf("\n   / /___/ / / / /_/ /  __/");
  printf("\n  /_____/_/ /_/\x5C__,_/\x5C___/ ");
  printf("\n\n                           ");

  Sleep(700);
}

//Letzte Zeile 1249