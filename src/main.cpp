#include "Plansza.hh"
#include "Gracz.hh"

bool CzyKoniec(Gracz* czlowiek, Gracz* komputer) { // Funkcja sprawdzajaca czy jest koniec meczu
  if (czlowiek->Wygrana()) { // Jesli wygral gracz
    cout << "Wygrales mecz" << endl;
    return true;  // koniec
  }
  if (komputer->Wygrana()) { // jesli wygral komputer
    cout << "Przegrales mecz" << endl;
    return true; // koniec
  }
  if (czlowiek->GetPlansza()->PlanszaPelna()) { // jesli plansza pelna i nie ma zwyciestwa
    cout << "Mecz zakonczyl sie remisem" << endl;
    return true; // koniec
  }
  return false; // gramy dalej
}

bool PodajParametry(int* parametry){ // Prośba o parametry inicjalizujace gre
  bool flaga = true; // flaga pomocnicza przy petlach
  int pomocnicza; // zmienna pomocnicza konwertowana pozniej na bool
  while(flaga){ // jesli flaga podniesiona
    cout << endl << "Podaj rozmiar planszy do gry (nie mniej niz 3)" << endl; 
    cin >> parametry[0];
    if (parametry[0] < 3) // jesli problem
      cout << "Rozmiar planszy nie może być mniejszy niż 3x3" << endl;
    else // jak podano dobrze
      flaga = false; // opuszc flage
  }

  flaga = true; // podnies flage

  while(flaga){ // jesli flaga podniesiona
    cout << endl << "Podaj glebokosc przewidywan komputera (nie mniej niz 1)" << endl;
    cin >> parametry[1];
    if (parametry[1] < 1) // jesli problem
      cout << "Glebokosc nie może być mniejsza niż 1" << endl;
    else // jesli podano dobrze
      flaga = false; // opusc flage
  }
  
  flaga = true; // podnies flage 

  while(flaga){ // jesli flaga podniesiona
    cout << endl << "Podaj kto ma zaczynać partię" << endl;
    cout << "0. Gracz" << endl;
    cout << "1. Komputer" << endl;
    cin >> pomocnicza;
    if (pomocnicza < 0 || pomocnicza > 1) // jesli problem
      cout << "Wybierz poprawnego gracza" << endl;
    else // jesli podano dobrze
      flaga = false; // opusc flage
  }

  cout << endl << endl << endl; // zrob kilka linii wolengo
  return pomocnicza; // konwersja z int do bool. Jedyne możliwe wartości zmiennej to 0 i 1;
}

//-------------------------------------------------------------------------------------------------------------

int main() {
  int i, j; // zmienne na wspolrzedne podawane przez gracza
  int parametry[2]; // zmienne na parametry gry
  bool tura = PodajParametry(parametry); // podawanie parametrow
  Plansza* plansza = new Plansza(parametry[0]); // Tworzenie planszy
  Gracz czlowiek(o, plansza); // tworzenia gracza
  Gracz komputer(x, plansza); // tworzenie gracza ze sztuczna intelligencja 
  
  cout << *plansza << endl; // drukowanie planszy
  while (!CzyKoniec(&czlowiek, &komputer)) { // pętla do konca meczu
    if(!tura) {// jesli tura czlowieka
      do  {
	cout << endl << endl << "Twoj ruch" << endl; // prosba o wspolrzedne
	cout << "Podaj x: ";
	cin >> i;
	cout << "Podaj y: ";
	cin >> j;
	cout << endl;
	
	if (!plansza->PoleDostepne(i,j)){  // sprawdzanie poprawnosci wspolrzednych
	  cout << "Chcesz wybrac pole zajete lub poza plansza" << endl << endl;
	}     
      }     
      while (!plansza->PoleDostepne(i,j)); // wyjdz jak podano poprawne 
      
      czlowiek.ZrobRuch(i, j); // zrob ruch
      cout << *plansza << endl; // wydrukuj plansze
      tura = true; // zmien na ture komputera
    }
    else if (tura) { // jesli tura komputera
      cout << endl << endl << "Ruch przeciwnika" << endl; // Ładnie poinformuj
      int* ruch = komputer.MinMax(&czlowiek,parametry[1],-INF,INF,true);  // wyszukaj najlepszy ruch i wzroc wspolrzedne
      komputer.ZrobRuch(ruch[0],ruch[1]); // wykonaj ten najlepszy ruch
      cout << *plansza << endl;  // drukuj plansze
      tura = false; // zmien na ture czlowieka
    }
  }
  return 0;
}
