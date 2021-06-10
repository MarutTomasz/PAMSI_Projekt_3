#ifndef PLANSZA
#define PLANSZA

#include <iostream>
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::cin;

enum Symbol {o = 'o',x = 'x'};  // Typ wyliczeniowy na znaki dostepne w grze

class Plansza { // Klasa reprezentująca kwadratowa planszę do gry
private:
  int rozmiar; // zmienna przechowująca ilość pol w linii
  char** pola; // wskaznik na tablice dwuwymairowa z polami 
public:
  Plansza(int s);  // Konstruktor klasy z parametrem okreslajacym rozmiar 
  ~Plansza();  // destruktor zwalniajacy pamiec przydzielana dynamicznie
  
  // Metody pobierające wartości przechowywane przez clasę
  int GetRozmiar() const {return rozmiar;}
  char GetPole(int x, int y) const {return pola[x][y];}
  
  // Metody ustanawiające nowe wartości, które ma przechowywać struktura 
  void SetRozmiar(int nowyRozmiar) {rozmiar = nowyRozmiar;}
  void SetPole(int x, int y, Symbol znak) {pola[x][y] = znak;}
  void ResetPole(int x, int y) {pola[x][y] = ' ';}

  // Pomocnicze metody informujace o stanie zapelnienia planszy
  bool PlanszaPelna() const;
  bool PoleDostepne(int x, int y) const;
};

//Funkcja wyświetlająca plansze
std::ostream & operator << (std::ostream &strm, const Plansza &Skl);


#endif
