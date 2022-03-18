/**
 * \file logdialog.h
 * \brief Plik nagłówkowy modułu logdialog
 */
#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <string>

using namespace std;

/** \brief Element listy administratorów
 * Definicja elementu listy jednokierunkowej dynamicznej listy paczek
 */
struct lista_admin
{
    /// login użytkownika
    string login;
    /// hasło użytkownika
    string haslo;
    /// wskaźnik na kolejny element listy administratorów
    lista_admin * nast;
};

/** \brief Element listy klientów
 * Definicja elementu listy jednokierunkowej dynamicznej listy paczek
 */
struct lista_klient
{
    /// login użytkownika
    string login;
    /// hasło użytkownika
    string haslo;
    /// imie użytkownika
    string imie;
    /// nazwisko użytkownika
    string nazwisko;
    /// miejscowość zamieszkania użytkownika
    string miejscowosc;
    /// kod pocztowy miejsca zamieszkania użytkownika
    string kodpocztowy;
    /// ulica zamieszkania użytkownika
    string ulica;
    /// numer budynku użytkownika
    int nrbudynku;
    /// numer mieszkania/lokalu użytkownika
    int nrlokalu;
    /// nnumer telefonu użytkownika
    int nrtel;
    /// wskaźnik na kolejny element listy klientów
    lista_klient * nast;
};

void zapisz_rejestr_klient(lista_klient * glowa);
void usun_liste_admin(lista_admin *& glowa);
void usun_liste_klient(lista_klient *& glowa);

namespace Ui {
class logDialog;
}


class logDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logDialog(QWidget *parent = nullptr);
    ~logDialog();


private slots:
    void on_pbZaloguj_clicked();

    void on_leHaslo_returnPressed();

    void on_pbZarejestruj_clicked();

private:
    Ui::logDialog *ui;

    int logowanie(string login, string haslo);
    void wczytaj_rejestr_klient();
    void wczytaj_rejestr_admin(lista_admin *& ogon);


};

#endif // LOGDIALOG_H
