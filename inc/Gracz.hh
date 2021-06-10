#ifndef GRACZ
#define GRACZ

#include "Plansza.hh"

#define INF 1000000 // Zmienna na bardzo duza liczbe
#define ZWYCIESTWO 4096 // Punkty za zwyciestwo
#define PRZEGRANA -4096 // Punkty za przegrana


class Gracz { // Klasa reprezentujaca gracza 
private:
  Symbol znak;  // Pole na symbol przypisany do gracza
  Plansza* plansza; // Wskaznik na plansze na ktorej ma grac
public:
  Gracz(Symbol s, Plansza* p) {znak = s; plansza = p;} //konstuktor gracza
  
  // Metody pobierające wartości przechowywane przez clasę
  Symbol GetZnak() const {return znak;}
  Plansza* GetPlansza() const {return plansza;}
  
  // Metody ustanawiające nowe wartości, które ma przechowywać struktura 
  void SetZnak(Symbol nowyZnak) {znak = nowyZnak;}
  void SetPlansza(Plansza* nowaPlansza) {plansza= nowaPlansza;}

  // Metody dokonujące ruchów na planszy
  void ZrobRuch(int x, int y) {plansza->SetPole(x,y,znak);}
  void CofnijRuch(int x, int y) {plansza->ResetPole(x,y);}

  // Metoda sprawdzająca czy gracz wygral
  bool Wygrana() const;

  // Metody wykorzystywane w sztucznej intaligencji
  int* MinMax(Gracz* czlowiek, int glebokosc, int alfa, int beta, bool maxGracza);
  int Punkty(Gracz* czlowiek) const;



  
};



#endif
