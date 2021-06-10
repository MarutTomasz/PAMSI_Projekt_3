#include "Plansza.hh"

Plansza::Plansza (int s) { // konstruktor jednoparametryczny planszy
  rozmiar = s; // zapamietaj rozmiar planszy
  pola = new char* [rozmiar]; // stworz tablice wskaznikow
  for (int i = 0; i < rozmiar; i++) { // powtorz dla kazdego wskaznika
    pola[i] = new char [rozmiar];   // stworz tablice char
    for (int j = 0; j < rozmiar; j++) // powtorz dla kazego pola char
      pola[i][j] = ' ';  // wstaw puste pole
   }    
}

Plansza::~Plansza() {   // destruktor 
  for (int i = 0; i < rozmiar; i++) // powtorz dla kazego wskaznika
    delete[] pola[i];  // zwolnik miejsce z tablicy char
  delete[] pola; // zwolnij miejsce z tablicy wskaznikow
}

bool Plansza::PlanszaPelna() const {  // Sprawdzanie czy plansza jest pelna
  for (int i = 0; i < rozmiar; i++) // Przesuwaj sie po wierszach
    for (int j = 0; j < rozmiar; j++) // Przesuwaj sie po kolumnach
      if (pola[i][j] == ' ')  // Czy pole jest wolne
	return false; // Tablica nie pelna
  return true;  // tablica pelna
}

bool Plansza::PoleDostepne(int x, int y) const { // Sprawdzanie czy pole dostepne
  if (x < 0 || y < 0 || x >= rozmiar || y >= rozmiar)  // Jesli wspolrzednie nie mieszcza sie w zakeesie planszy
    return false; // pole nie dostepne  
  if (pola[x][y] == ' ')  // Jesli pole nie ma o ani x
    return true; // pole dostepne
  return false; // jesli jest x lub o to pole niedostepne
}

// Wyświetlanie zawartości elementu
std::ostream & operator << (std::ostream &strm, const Plansza &elem) {
  int wielkosc = elem.GetRozmiar();  // zapamieetywanie roazmiaru tablicy
  
  strm << " --" ;    // tworzenie linii gornej planszy
  for (int k = 0; k < wielkosc; k++)
    strm << "---" ;
  strm << "-- " << endl; 
  
  for (int i = 0; i < wielkosc; i++){ // powtarzaj dla wszystkich wierszy
    strm << " | " ; // postaw pierwsza linie
    for (int j = 0; j < wielkosc; j++){ // powtarzaj dla wszystkich kolumn
      strm << elem.GetPole(i,j) << " | "; // wypisz znak z pola i linie pionowa
    }
    strm << endl; 
  }

  strm << " --" ;  // tworzenie linii dolnej planszy
  for (int k = 0; k < wielkosc; k++)
    strm << "---" ;
  strm << "-- " << endl;
  
  strm << endl;
  return strm; 
}
