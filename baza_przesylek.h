/**
 * \file baza_przesylek.h
 * \brief Plik nagłówkowy modułu baza_przesyłek
 */
#ifndef BAZA_PRZESYLEK_H
#define BAZA_PRZESYLEK_H
#include <string>

using namespace std;

/** \brief Element listy paczek
 * Definicja elementu listy jednokierunkowej dynamicznej listy paczek
 */
struct lista_paczek
{
    /// Numer przesyłki
    int nr_paczki;
    /// Imie nadawcy
    string imie_n;
    /// Nazwisko nadawcy
    string nazwisko_n;
    /// Miejscowość zamieszkania nadawcy
    string miejscowosc_n;
    /// Kod pocztowy miejsca zamieszkania nadawcy
    string kodpocztowy_n;
    /// Ulica zamieszkania nadawcy
    string ulica_n;
    /// Numer budynku miejsca zamieszkania nadawcy
    int nrbudynku_n;
    /// Numer mieszkania lub lokalu miejsca zamieszkania nadawcy
    int nrlokalu_n;
    /// Numer email nadawcy
    string email_n;
    /// Numer telefonu nadawcy
    int nrtel_n;
    /// Imie odbiorcy
    string imie_o;
    /// Nazwisko odbiorcy
    string nazwisko_o;
    /// Miejscowość zamieszkania odbiorcy
    string miejscowosc_o;
    /// Kod pocztowy miejsca zamieszkania odbiorcy
    string kodpocztowy_o;
    /// Ulica zamieszkania odbiorcy
    string ulica_o;
    /// Numer budynku miejsca zamieszkania odbiorcy
    int nrbudynku_o;
    /// Numer mieszkania lub lokalu miejsca zamieszkania odbiorcy
    int nrlokalu_o;
    /// Numer email odbiorcy
    string email_o;
    /// Numer telefonu odbiorcy
    int nrtel_o;
    /// Masa całkowita przesyłki
    int waga_przesylki;
    /// Wymiary całkowite przesyłki
    int wymiary_przesylki[3];
    /// Numer kuriera odbierającego od nadawcy
    int nr_kuriera_n;
    /// Numer kuriera dostarczającego do odbiorcy
    int nr_kuriera_o;
    /// Staus przsyłki, odpowiednio: 0 - do odebrania, 1 - odebrana od nadawcy, 2 - przyjeta w oddziale, 3 - przekazana do doręczenia, 4 - dostarczona
    int status;
    /// Data nadania przesyłki
    int data_0[3];
    /// Data odbioru przesyłki od nadawcy
    int data_1[3];
    /// Data przyjęcia przesyłki w oddziale
    int data_2[3];
    /// Data przekazania przesyłki do doręczenia
    int data_3[3];
    /// Data dostarczenia przesyłki do odbiorcy
    int data_4[3];
    /// Wskaźnik na adres kolejnego elementu listy paczek
    lista_paczek * nast;
};


void wczytaj_rejestr_paczek(lista_paczek *& glowa, lista_paczek *& ogon, string nazwa);
void zapisz_rejestr_paczek(lista_paczek * glowa, string nazwa);
bool usun(lista_paczek *& glowa, lista_paczek *& ogon, lista_paczek * item);
void usun_liste(lista_paczek *& glowa);


#endif // BAZA_PRZESYLEK_H
