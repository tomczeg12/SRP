/**
 * \file baza_przesylek.cpp
 * \brief Plik źródłowy modułu baza_przesyłek
 */
#include "baza_przesylek.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/// Zmienna globalna ile
int ile(1);
/// Zmienna globalna nr
int nr;

/**
 * Funkcja wczytuje rejestr paczek z pliku.
 * Pobiera adres pierwszego i ostatniego elementu listy oraz nazwę przesyłki i nic nie zwraca.
 *
 * \param glowa adres pierwszego elementu listy paczek.
 * \param ogon adres ostatniego elementu listy paczek.
 * \param nazwa długość trzeciego odcinka.
 * \attention jeżeli plik okaże sięuszkodzony, bądź go nie będzie,
 *            funkcja zatrzyma swoje działanie.
 */
void wczytaj_rejestr_paczek(lista_paczek *& glowa, lista_paczek *& ogon, string nazwa)
{
    ifstream plik;
    plik.open(nazwa.c_str(), ios::in);
    string slowo;
    int liczba;

    glowa=NULL;
    ogon=NULL;

    ile=1;

    if(plik.good()==false)
        return;
    while (!plik.eof()) // dopóki plik nie pusty wczytuje elementy
    {
        lista_paczek *nowy = new lista_paczek; // nowy element listy paczek
        plik>>liczba;
        nowy->nr_paczki=liczba;
        plik>>slowo;
        nowy->imie_n=slowo;
        plik >> slowo;
        nowy->nazwisko_n=slowo;
        plik >> slowo;
        nowy->miejscowosc_n=slowo;
        plik >> slowo;
        nowy->kodpocztowy_n=slowo;
        plik >> slowo;
        nowy->ulica_n=slowo;
        plik >> liczba;
        nowy->nrbudynku_n=liczba;
        plik >> liczba;
        nowy->nrlokalu_n=liczba;
        plik >> slowo;
        nowy->email_n=slowo;
        plik >> liczba;
        nowy->nrtel_n=liczba;

        plik >> slowo;
        nowy->imie_o=slowo;
        plik >> slowo;
        nowy->nazwisko_o=slowo;
        plik >> slowo;
        nowy->miejscowosc_o=slowo;
        plik >> slowo;
        nowy->kodpocztowy_o=slowo;
        plik >> slowo;
        nowy->ulica_o=slowo;
        plik >> liczba;
        nowy->nrbudynku_o=liczba;
        plik >> liczba;
        nowy->nrlokalu_o=liczba;
        plik >> slowo;
        nowy->email_o=slowo;
        plik >> liczba;
        nowy->nrtel_o=liczba;

        for (int i=0;i<3;i++) // pobieram kolejno 3 liczby i wpisuje je do zmiennej tablicowej wymiar
        {
            plik >> liczba;
            nowy->wymiary_przesylki[i] = liczba;
        }
        plik >> liczba;
        nowy->waga_przesylki=liczba;

        plik >> liczba;
        nowy->nr_kuriera_n=liczba;
        plik >> liczba;
        nowy->nr_kuriera_o=liczba;
        plik >> liczba;
        nowy->status=liczba;

        for (int i=0;i<3;i++) // pobieram kolejno 3 liczby i wpisuje je do zmiennej tablicowej data
        {
            plik >> liczba;
            nowy->data_0[i] = liczba;
        }
        for (int i=0;i<3;i++)
        {
            plik >> liczba;
            nowy->data_1[i] = liczba;
        }
        for (int i=0;i<3;i++)
        {
            plik >> liczba;
            nowy->data_2[i] = liczba;
        }
        for (int i=0;i<3;i++)
        {
            plik >> liczba;
            nowy->data_3[i] = liczba;
        }
        for (int i=0;i<3;i++)
        {
            plik >> liczba;
            nowy->data_4[i] = liczba;
        }

        nowy->nast=NULL;

        if(glowa == NULL)
            glowa = nowy;
        else
            ogon->nast=nowy;
        ogon = nowy;

        ile++;
    }
    plik.close();
}

/**
 * Funkcja zapisuje rejestr paczek do pliku.
 * Pobiera adres pierwszego elementu listy oraz nazwę przesyłki i nic nie zwraca.
 *
 * \param glowa adres pierwszego elementu listy paczek.
 * \param nazwa długość trzeciego odcinka.
 * \attention jeżeli plik okaże sięuszkodzony, bądź go nie będzie,
 *            funkcja zatrzyma swoje działanie.
 */
void zapisz_rejestr_paczek(lista_paczek * glowa, string nazwa)
{
    ofstream plik;
    plik.open(nazwa.c_str(), ios::out | ios::trunc); // czyszcze plik przed zapisem
    while (glowa != NULL)
    {

        plik << glowa->nr_paczki << " ";
        plik << glowa->imie_n << " " << glowa->nazwisko_n  << " " << glowa->miejscowosc_n << " " << glowa->kodpocztowy_n << " " << glowa->ulica_n << " " << glowa->nrbudynku_n << " " << glowa->nrlokalu_n << " " << glowa->email_n << " " << glowa->nrtel_n << " ";
        plik << glowa->imie_o << " " << glowa->nazwisko_o  << " " << glowa->miejscowosc_o << " " << glowa->kodpocztowy_o << " " << glowa->ulica_o << " " << glowa->nrbudynku_o << " " << glowa->nrlokalu_o << " " << glowa->email_o << " " << glowa->nrtel_o << " ";
        for (int i=0;i<3;i++)
            plik << glowa->wymiary_przesylki[i] << " ";
        plik << glowa->waga_przesylki << " ";
        plik << glowa->nr_kuriera_n << " "<< glowa->nr_kuriera_o << " " << glowa->status;
        for (int i=0;i<3;i++) // pobieram kolejno 3 liczby i wpisuje je do zmiennej tablicowej data
        {
            plik << " " << glowa->data_0[i];
        }
        for (int i=0;i<3;i++)
        {
            plik << " " << glowa->data_1[i];
        }
        for (int i=0;i<3;i++)
        {
            plik << " " << glowa->data_2[i];
        }
        for (int i=0;i<3;i++)
        {
            plik << " " << glowa->data_3[i];
        }
        for (int i=0;i<3;i++)
        {
            plik << " " << glowa->data_4[i];
        }
        if(glowa->nast!=NULL)
           plik << endl;
        glowa=glowa->nast;
    }

    plik.close();
}

/**
 * Funkcja usuwa dany element listy.
 * Pobiera adres pierwszego i ostatniego elementu listy oraz adres elementu do usunięcia i zwraca informację czy udało się usunąć.
 *
 * \param glowa adres pierwszego elementu listy paczek.
 * \param ogon adres ostatniego elementu listy paczek.
 * \param item długość trzeciego odcinka.
 * \return true jeżeli pomyślnie usunięto, false jeżeli nie udało się usunąć.
 * \attention jeżeli nie istanieje pierwszy element listy, funkcja od razu zwróci wartość false.
 */
bool usun(lista_paczek *& glowa, lista_paczek *& ogon, lista_paczek * item)
{
    lista_paczek *w = glowa;

    if(glowa!=NULL)
    {
        if (glowa == item)
        {
            glowa = glowa->nast;
            delete item;
            ile--;
            return true;
        }
        if (glowa->nast == item)
        {
            glowa->nast = glowa->nast->nast;
            delete item;
            ile--;
            return true;
        }

        w=w->nast;
        while(w->nast!=NULL)
        {
            if (w->nast == item)
            {
                if (w->nast->nast == ogon)
                {
                    w->nast = w->nast->nast;
                    ogon = w->nast;
                    delete item;
                    ile--;
                    return true;
                }
                else
                {
                    w->nast = w->nast->nast;
                    delete item;
                    ile--;
                    return true;
                }

            }
            w=w->nast;
        }

    }
    return false;
}

/**
 * Funkcja usuwa lista paczek z pamięci.
 * Pobiera adres pierwszego elementu listy i nic nie zwraca.
 *
 * \param glowa adres pierwszego elementu listy paczek.
 */
void usun_liste(lista_paczek *& glowa)
{
    while(glowa)
    {
        lista_paczek * p = glowa;
        glowa = glowa->nast;
        delete p;
    }
}
