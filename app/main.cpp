// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "rectangle.hh"
#include "../inc/lacze_do_gnuplota.hh"

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

#define DL_KROTKI_BOK 100
#define DL_DLUGI_BOK 150

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool PrzykladZapisuWspolrzednychDoPliku(const char *sNazwaPliku,
                                        Rectangle Pr)
{
       std::ofstream StrmPlikowy;

       StrmPlikowy.open(sNazwaPliku);
       if (!StrmPlikowy.is_open())
       {
              std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
                        << ":(  nie powiodla sie." << std::endl;
              return false;
       }

       StrmPlikowy << Pr;
       StrmPlikowy << Pr[0];
       StrmPlikowy.close();
       return !StrmPlikowy.fail();
}

int main()
{
       Rectangle Pr;
       std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
                 << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
                 << "."
                 << PROJECT_VERSION_MINOR /* istotne zmiany */
                 << "."
                 << PROJECT_VERSION_PATCH /* naprawianie bugów */
                 << "."
                 << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
                 << std::endl;
       // std::system("cat ../LICENSE");
       // do zadania Rotacja 2D

       PzG::LaczeDoGNUPlota Lacze; // Ta zmienna jest potrzebna do wizualizacji
                                   // rysunku prostokata

       //-------------------------------------------------------
       //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
       //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
       //  na dwa sposoby:
       //   1. Rysowane jako linia ciagl o grubosci 2 piksele
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Ciagly, 2);
       //
       //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
       //      których połowa długości boku wynosi 2.
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Punktowy, 2);
       //
       //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
       //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
       //  jako wspolrzedne punktow podajemy tylko x,y.
       //
       Lacze.ZmienTrybRys(PzG::TR_2D);

       char opcja;

       int ile; //ile razy ma sie powturzyc obrut
       double kat;
  
       std::cout << "o" << std::endl;
       std::cout << "p" << std::endl;
       std::cout << "w" << std::endl;
       std::cout << "m" << std::endl;
       std::cout << "k" << std::endl;

       while (opcja != 'k')
       {

              if (!PrzykladZapisuWspolrzednychDoPliku("../datasets/prostokat.dat", Pr))
                     return 1;
              Lacze.Rysuj();
              std::cin >> opcja;
              switch (opcja)
              {
              case 'o':
              {
                     Vector wek;
                     std::cin >> kat;
                     std::cin >> ile;
                     for (int i = 0; i < ile; i++)
                     {
                            Pr.translacja(kat, wek);
                     }
              }
              break;
              case 'p':
              {
                     Vector wek;
                     std::cin >> wek;
                     Pr.translacja(0, wek);
              }
              break;
              case 'w':
              {
                     std::cout << Pr;
              }
              break;
              case 'm':
              {
                     std::cout << "o" << std::endl;
                     std::cout << "p" << std::endl;
                     std::cout << "w" << std::endl;
                     std::cout << "m" << std::endl;
                     std::cout << "k" << std::endl;
              }
              break;
              }
       }
       Dummy d = Dummy();
       return d.doSomething() ? 0 : -1;
}
