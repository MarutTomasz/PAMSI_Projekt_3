#include "Gracz.hh"
bool Gracz::Wygrana() const { // Metoda sprawdzająca, czy gracz ma ulożoną odpowiednią liczbę symboli w rzędzie
  
  //sprawdzanie pionów
  for (int i = 0; i < plansza->GetRozmiar(); i++){ // powtarzaj po wierszach
    for (int j = 0; j < plansza->GetRozmiar(); j++) { // powtarzaj po kolumnach
      if (plansza->GetPole(i,j) == znak){ // jesli wszystkie pola w wierszu to znak
	if (j == plansza->GetRozmiar()-1) // jak doszlismy do prawego boku planszy
	  return true; // jest wygrana
      }	  
      else // jesli po drodze byl inny znak
	break; // nie ma wygranej w wierszu 
    }
  }  

  //sprawdzanie poziomów
  for (int i = 0; i < plansza->GetRozmiar(); i++) {  // powtarzaj po kolumnach
    for (int j = 0; j < plansza->GetRozmiar(); j++) {  // powtarzaj po wierszach
      if (plansza->GetPole(j,i) == znak){  // jesli wwszystkie pola w kolumnie to znak
	if (j == plansza->GetRozmiar() - 1) // jak doszlismy na dol planszy
	  return true; // jest wygrana
      }
      else // jesli po drodze byl inny znak
	break; // nie ma wygranej w kolumnie
    }
  }

  //sprawdzanie skosów
  for (int i = 0; i < plansza->GetRozmiar(); i++){ // powtarzaj dla rozmiaru planszy
    if (plansza->GetPole(i,i) == znak){ // jesli wszystkie pola na jednej przekatnej to znak
      if (i == plansza->GetRozmiar() - 1) // jak doszlismy to prawego dolnego rogu
	return true; // jest wygrana
    }
    else // jesli po drodze byl inny znak
      break; // nie ma wygranej w tej przekatnej
  }
  
  for (int i = 0; i < plansza->GetRozmiar(); i++){ // powtarzaj dla rozmiaru planszy
    if (plansza->GetPole(i,2-i) == znak){ // jesli wszystkie pola na drugiej przekatnej to znak
      if (i == plansza->GetRozmiar() -1) // jak doszlismy to lewego dolnego rogu
	return true; // jest wygrana
    }
    else // jesli po drodze byl inny znak
      break; // nie ma wygranej w tej przekatnej
  }
  return false; // jak wszystko zawiodlo to nie ma wygranej
}

int Gracz::Punkty(Gracz* czlowiek) const { // Metoda okreslajaca puntkty do algorytmu minmax na podstawie obecnosci zwyciestwa ktoregos gracza
  if (Wygrana()) // jesli wygralo SI
    return ZWYCIESTWO;  
  if (czlowiek->Wygrana()) // jeśli wygrał gracz
    return PRZEGRANA;
  return 0; // jeśli remis
}
 
int* Gracz::MinMax(Gracz* czlowiek, int glebokosc, int alfa, int beta, bool maxGracza) { // algorytm symulujacy sztuczna inteligencje, ktory przewiduje ruchy do przodu
  
  int* minmax = new int[3]; // zmienna na najlepsza opcje i wspolrzedne do jej wykonania
  minmax[0] = minmax[1] = minmax[2] = 0;
  int* wynik = new int[3]; // zmienna pomocnicza do szukania najlepszej opcji. Na dnie rekurencji, przy koncy planszy lub zwyciestwie któregoś z graczy zwraca wartość punktów
  wynik[2] = Punkty(czlowiek); // sprawdzanie czy moze ktos wygral
  
  if(glebokosc == 0){ // jeśli dno rekurencji
    delete minmax; // zwolnij pamiec 
    return wynik; // zwroc punkty wyniku
  }

  if(plansza->PlanszaPelna()){ // jeśli plansza pelna
    delete minmax; // zwolnij pamiec
    return wynik; // zwroc punkty wyniku
  }
  
  if(wynik[2] != 0){ // jeśli ktoś wygrał
    delete minmax; // zwolnij pamiec 
    return wynik; // zwroc punkty wyniku
  }
    
  if (maxGracza){  // przypadek najlepszego wyjscia dla sztucznej inteligencji 
    minmax[2] = -INF;  // niech wartosc startowa bedzie nieskonczenie mala
    for (int i = 0; i < plansza->GetRozmiar();i++){  // powtarzaj dla wszystkich pol
      for (int j = 0; j < plansza->GetRozmiar();j++){
	if(plansza->PoleDostepne(i,j)){ // jeśli można wykonać rucj
	  this->ZrobRuch(i,j);  // wykonaj go
	  wynik = MinMax(czlowiek,glebokosc-1,alfa,beta,false); // wywołaj rekurencyjnie algorytm, tylko dla szukania minimum zysków SI
	  this->CofnijRuch(i,j); // cofnij ruch jakby nigdy nie był wykonany
	  if(wynik[2] > minmax[2]){ // jeśli punktów jest wiecej niż w najlepszym przyapdku - podmień najlepszy 
	    minmax[0] = i;
	    minmax[1] = j;
	    minmax[2] = wynik[2];
	  }
	  alfa = max(alfa,wynik[2]); // zapamiętanie jak największej wartości do alfa
	  if (beta <= alfa){ // jeśli nie oplaca się dalej szukać lepszych wynikow - opusc petle
	    break;
	  }
	}
      }
      if (beta <= alfa)  // opuść też drugą pętlę
	break;
    }
    delete wynik;  // zwolnij pamięc
 
    minmax[2] /= 2; // podziel punkty na 2, zeby dazenie do zwyciestwa znalezionego w glebszej czesci algorytmu bylo mniej oplacalne niz takiego znalezionego wyżej
    return minmax; // zwróc najlepszy wynik punktowy i współrzędne go jego uzyskania
  }
  
  else {   // wprzypadek najgorszego wyjscia dla sztucznej intaligencji (najlepszego dla przeciwnika)
    minmax[2] = INF;  // niech wartosc startowa będzie nieskonczenie duza
    for (int i = 0; i < plansza->GetRozmiar();i++){  // powtarzaj dla wszystkich pol
      for (int j = 0; j < plansza->GetRozmiar();j++){
	if(plansza->PoleDostepne(i,j)){  // jesli można wykonac ruch
	  czlowiek->ZrobRuch(i,j); // niech przeciwnik go wykona
	  wynik = MinMax(czlowiek,glebokosc-1,alfa,beta,true); // wywołaj rekurencyjnie algorytm, tylko dla szukania maximum zysków SI
	  czlowiek->CofnijRuch(i,j); // cofnij ruch 
	  if(wynik[2] < minmax[2]){ // jeśli punktów jest mniej niż w najlepszym przyapdku - podmień najlepszy (dla przeciwnika najlepszy)
	    minmax[0] = i;
	    minmax[1] = j;
	    minmax[2] = wynik[2];
	  } 
	  beta = min(beta,wynik[2]); // zapamietanie jak najmniejszej wartosci do beta
	  if (beta <= alfa){ // jesli nie oplaca sie dalej szukac gorszych wynikow - opusc petle
	    break;
	  }
	}
      }
      if (beta <= alfa) // opusc tez druga petle
	break;
    }
    delete wynik; // zwolnij pamiec

    minmax[2] /= 2; // podziel punkty na 2, zeby dazenie do przegranej znalezionej w glebszej czesci algorytmu bylo mniej oplacalne niz takiej znalezionego wyżej
    return minmax; // zwróc najgorszy wynik punktowy i współrzędne go jego uzyskania
  }
}
