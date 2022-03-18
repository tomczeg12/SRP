/**
 * \file logdialog.cpp
 * \brief Plik źródłowy modułu logdialog
 */
#include "logdialog.h"
#include "ui_logdialog.h"
#include "admainwindow.h"
#include "klmainwindow.h"
#include "danedialog.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/// zmienna globalna login
string login = "";
/// zmienna globalna b
/// zmienna globalna do zapamiętywania ile razy użytkownik próbuje się zalogować
int b(0);
/// zmienna globalna user
/// zmienna globalna do zapamiętywania jaki użytkownik się zalogował
int user(0);
/// zmienna globalna ile_a
/// zmienna globalna przechowująca ilosc użytkowników o statusie klient w bazie danych
int ile_a(0);
/// zmienna globalna ile_kl
/// zmienna globalna przechowująca ilosc użytkowników o statusie administrator w bazie danych
int ile_kl(0);
/// zmienna globalna wskaźnikowa admin_log
/// adres elementu z listy administratorów w którym znajdują się dane zalogogwanego administratora
lista_admin * admin_log = NULL;
/// zmienna globalna wskaźnikowa klient_log
/// adres elementu z listy klientów w którym znajdują się dane zalogogwanego klienta
lista_klient * klient_log = NULL;
/// zmienna globalna wskaźnikowa glowa
lista_admin * glowa = NULL;
/// zmienna globalna wskaźnikowa glowa1
lista_klient * glowa1 = NULL;
/// zmienna globalna wskaźnikowa ogon1
lista_klient * ogon1 = NULL;

logDialog::logDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logDialog)
{
    ui->setupUi(this);  
}

logDialog::~logDialog()
{
    delete ui;
}
/**
 * Funkcja zapisuje rejestr klientów do pliku.
 * Pobiera adres pierwszego elementu listy i nic nie zwraca.
 *
 * \param glowa adres pierwszego elementu listy klientów.
 * \attention jeżeli plik okaże się uszkodzony, bądź go nie będzie,
 *            funkcja zatrzyma swoje działanie. Następnie dopóki istnieje element listy fukcja zapisuje go do pliku
 */
void zapisz_rejestr_klient(lista_klient * glowa)
{
    ofstream plik;
    plik.open("dane_klient.txt", ios::out | ios::trunc); // czyszcze plik przed zapisem
    if(plik.good()==false)
        return;
    while (glowa != NULL)
    {
        plik << glowa->login << " " << glowa->haslo << " " << glowa->imie << " " << glowa->nazwisko  << " " << glowa->miejscowosc << " " << glowa->kodpocztowy << " " << glowa->ulica << " " << glowa->nrbudynku << " " << glowa->nrlokalu << " " << glowa->nrtel;
        if(glowa->nast!=NULL)
           plik << endl;
        glowa=glowa->nast;
    }

    plik.close();
}

/**
 * Funkcja usuwa liste administratorów
 * Pobiera adres pierwszego elementu listy i nic nie zwraca.
 *
 * \param g adres pierwszego elementu listy administratorów.
 * \attention Dopóki istnieje element listy fukcja go usuwa
 */
void usun_liste_admin(lista_admin *& g)  // usuwa liste administratoróW z pamięci
{
    while(g)
    {
        lista_admin * p = g;
        g = g->nast;
        delete p;
    }
}

/**
* Funkcja usuwa liste klientów
* Pobiera adres pierwszego elementu listy i nic nie zwraca.
*
* \param g1 adres pierwszego elementu listy klientów.
* \attention Dopóki istnieje element listy fukcja go usuwa
*/
void usun_liste_klient(lista_klient *& g1) // usuwa liste klientów z pamięci
{
    while(g1)
    {
        lista_klient * p = g1;
        g1 = g1->nast;
        delete p;
    }
}

/**
 * Funkcja reaguje na przyciśnięcie przycisku zaloguj
 * Funkcja w zależności od podanych danych otwiera okno klienta, albo administratora.
 *
 * \attention Maksymalnie można próbować się zalogować 3 razy, po 3 krotnym podaniu złych danych program się wyłącza.
 *            Funkcja wywołuje funkcje logowanie i zapisuje ją do zmiennej user
 *            W zależności od tego co zwróci funkcja logowanie zostają otwarte albo okno administratora albo klienta.
 */
void logDialog::on_pbZaloguj_clicked() // reaguje na kliknięcie przycisku zaloguj
{
    b++;
    if(b==3) delete ui;

    login = ui->leLogin->text().toStdString();
    string haslo = ui->leHaslo->text().toStdString();

    usun_liste_admin(glowa);
    usun_liste_klient(glowa1);

    user = logowanie(login, haslo);
    switch(user)
    {
    case 1:
    {
        adMainWindow *ad = new adMainWindow();
        ad->show();
        b=0;
    }
        break;

    case 2:
    {
        klMainWindow *kl = new klMainWindow();
        kl->show();
        b=0;
    }
        break;
    }
    ui->leLogin->clear();
    ui->leHaslo->clear();
}

/**
 * Funkcja reaguje na przyciśnięcie przycisku enter
 * Funkcja w zależności od podanych danych otwiera okno klienta, albo administratora.
 *
 * \attention Maksymalnie można próbować się zalogować 3 razy, po 3 krotnym podaniu złych danych program się wyłącza.
 *            Funkcja wywołuje funkcje logowanie i zapisuje ją do zmiennej user
 *            W zależności od tego co zwróci funkcja logowanie zostają otwarte albo okno administratora albo klienta.
 */
void logDialog::on_leHaslo_returnPressed() // reaguje na kliknięcie przycisku enter w okienku hasło
{
    b++;
    if(b==3) delete ui; // maksymalnie można próbować się zalogować 3 razy, po 3 krotnym podaniu złych danych program się wyłącza

    login = ui->leLogin->text().toStdString();
    string haslo = ui->leHaslo->text().toStdString();

    usun_liste_admin(glowa);
    usun_liste_klient(glowa1);

    user = logowanie(login, haslo);
    switch(user)
    {
    case 1:// jeżeli zalogował się użytkowanik na prawach administratora
    {
        adMainWindow *ad = new adMainWindow();  // nowe okno administratora
        ad->show();
        b=0;
    }
        break;

    case 2:// jeżeli zalogował się klient *chwilowo niedostępna opcja*
    {
        klMainWindow *kl = new klMainWindow();  // nowe okno klienta
        kl->show();
        b=0;
    }
        break;
    }
    ui->leLogin->clear();
    ui->leHaslo->clear();
}

/**
 * Funkcja wczytuje rejestr administratorów z pliku.
 * Pobiera adres ostatniego elementu listy oraz nazwę przesyłki i nic nie zwraca.
 *
 * \param ogon adres ostatniego elementu listy paczek.
 * \attention jeżeli plik okaże sięuszkodzony, bądź go nie będzie,
 *            funkcja zatrzyma swoje działanie.
 */
void logDialog::wczytaj_rejestr_admin(lista_admin *& ogon) // wczytuje rejestr administratorów z pliku
{
    ifstream plik;
    plik.open("dane_admin.txt", ios::in);
    string slowo;

    ile_a=0;

    glowa=NULL;
    ogon=NULL;

    if(plik.good()==false)
        return;
    while (!plik.eof()) // dopóki plik nie pusty wczytuje elementy
    {
        lista_admin *nowy = new lista_admin;
        plik>>slowo;
        nowy->login=slowo;
        plik >> slowo;
        nowy->haslo=slowo;
        nowy->nast=NULL;

        if(glowa == NULL)
            glowa = nowy;
        else
            ogon->nast=nowy;
        ogon = nowy;
        ile_a++;
    }
    plik.close();
}

/**
 * Funkcja wczytuje rejestr administratorów z pliku.
 *
 * \attention jeżeli plik okaże sięuszkodzony, bądź go nie będzie,
 *            funkcja zatrzyma swoje działanie.
 */
void logDialog::wczytaj_rejestr_klient() // wczytuje rejestr klientów z pliku
{
    ifstream plik;
    plik.open("dane_klient.txt", ios::in);
    string slowo;
    int liczba;

    ile_kl=0;

    glowa1=NULL;
    ogon1=NULL;

    if(plik.good()==false)
        return;
    while (!plik.eof()) // dopóki plik nie pusty wczytuje elementy
    {
        lista_klient *nowy = new lista_klient;
        plik>>slowo;
        nowy->login=slowo;
        plik >> slowo;
        nowy->haslo=slowo;
        plik>>slowo;
        nowy->imie=slowo;
        plik >> slowo;
        nowy->nazwisko=slowo;
        plik >> slowo;
        nowy->miejscowosc=slowo;
        plik >> slowo;
        nowy->kodpocztowy=slowo;
        plik >> slowo;
        nowy->ulica=slowo;
        plik >> liczba;
        nowy->nrbudynku=liczba;
        plik >> liczba;
        nowy->nrlokalu=liczba;
        plik >> liczba;
        nowy->nrtel=liczba;
        nowy->nast=NULL;

        if(glowa1 == NULL)
            glowa1 = nowy;
        else
            ogon1->nast=nowy;
        ogon1 = nowy;
        ile_kl++;
    }
    plik.close();
}

/**
 * Funkcja sprawdza jkai użytkownik się zalogował
 * Pobiera login oraz hasło i zwraca numer zalogowanego użytkownika, odpowiednio 1-administrator, 2-klient
 *
 * \param login tekst wpisany w pole login
 * \param haslo tekst wpisany w pole hasło
 * \attention Funkcja w pierwszej kolejności wczytuje rejestr administratoróW oraz klientów,
 *            a nastepnie sprawdza czy podany login i haslo należą do jednego obiektu z listy administratorów
 *            lub do odpowiedniego obiektu listy klientów
 */
int logDialog::logowanie(string login, string haslo)
{  
    lista_admin * ogon =NULL;
    wczytaj_rejestr_admin(ogon);
    lista_admin * g = glowa;

    wczytaj_rejestr_klient();
    lista_klient * g1 = glowa1;

    for (int i=0;i<ile_a;i++)
    {
        if (login == g->login) // funkcja sprawdza czy dany login jest wśród zapisanych użytkowników kategorii: administrator
        {
            if (haslo == g->haslo) // funkcja sprawdza czy dane hasło odpowiada danemu loginowi
            {
                admin_log=g;
                return 1;
            }
            else
                return 0;
        }
        g=g->nast;
        if (g==NULL) // jeżeli nie ma kolejnego elementu listy to okńczy działanie pętli  *zabezpieczenie*
            i=ile_a;
    }
    for (int i=0;i<ile_kl;i++)
    {
        if (login == g1->login) // funkcja sprawdza czy dany login jest wśród zapisanych użytkowników kategorii: klient
        {
            if (haslo == g1->haslo) // funkcja sprawdza czy dane hasło odpowiada danemu loginowi
            {

                klient_log=g1;
                return 2;
            }
            else
                return 0;
        }
        g1=g1->nast;
        if (g1==NULL)  // jeżeli nie ma kolejnego elementu listy to okńczy działanie pętli  *zabezpieczenie*
            i=ile_kl;
    }
    return 0;
}

/**
 * Funkcja reaguje na przyciśnięcie przycisku zarejestruj
 * Funkcja otwiera okno daneDialog.
 */
void logDialog::on_pbZarejestruj_clicked()
{
    wczytaj_rejestr_klient();
    daneDialog oknoadd;
    oknoadd.exec();
}
