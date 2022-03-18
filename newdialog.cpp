/**
 * \file newdialog.cpp
 * \brief Plik źródłowy modułu newdialog
 */
#include "newdialog.h"
#include "ui_newdialog.h"
#include "baza_przesylek.h"
#include "logdialog.h"
#include <windows.h>
#include <winbase.h>

extern lista_paczek * adres_glowy;
extern lista_paczek * adres_ogona;
extern int user; // zmienna przechowująca kto się zalogował
extern int ile; // zmienna przechowująca ilosc paczek
extern string nazwa_pliku;
extern lista_klient * klient_log; // adres elementu z listy klientów w którym znajdują się dane zalogogwanego klienta
extern bool zmiendane; // zmienna pobrana od administratora mówiąca czy otworzył to okno w celu zmiany danych
extern lista_paczek * g_item; // zmienna przechowująca adres klikniętego elementu

newdialog::newdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newdialog)
{
    ui->setupUi(this);
    if(user==2) // jeżeli zalogował się klient to wypełniam ogno dodawanmia paczki jego danymi
    {
        ui->leimie_n->setText(QString::fromStdString(klient_log->imie));
        ui->lenazwisko_n->setText(QString::fromStdString(klient_log->nazwisko));
        ui->leemail_n->setText(QString::fromStdString(klient_log->login));
        ui->letel_n->setText(QString::number(klient_log->nrtel));
        ui->leulica_n->setText(QString::fromStdString(klient_log->ulica));
        ui->lenrdom_n->setText(QString::number(klient_log->nrbudynku));
        ui->lenrlok_n->setText(QString::number(klient_log->nrlokalu));
        ui->lemiasto_n->setText(QString::fromStdString(klient_log->miejscowosc));
        ui->lekodpoczt_n->setText(QString::fromStdString(klient_log->kodpocztowy));
    }
    else if (zmiendane==true)
    {
        ui->leimie_n->setText(QString::fromStdString(g_item->imie_n));
        ui->lenazwisko_n->setText(QString::fromStdString(g_item->nazwisko_n));
        ui->leemail_n->setText(QString::fromStdString(g_item->email_n));
        ui->letel_n->setText(QString::number(g_item->nrtel_n));
        ui->leulica_n->setText(QString::fromStdString(g_item->ulica_n));
        ui->lenrdom_n->setText(QString::number(g_item->nrbudynku_n));
        ui->lenrlok_n->setText(QString::number(g_item->nrlokalu_n));
        ui->lemiasto_n->setText(QString::fromStdString(g_item->miejscowosc_n));
        ui->lekodpoczt_n->setText(QString::fromStdString(g_item->kodpocztowy_n));

        ui->leimie_o->setText(QString::fromStdString(g_item->imie_o));
        ui->lenazwisko_o->setText(QString::fromStdString(g_item->nazwisko_o));
        ui->leemail_o->setText(QString::fromStdString(g_item->email_o));
        ui->letel_o->setText(QString::number(g_item->nrtel_o));
        ui->leulica_o->setText(QString::fromStdString(g_item->ulica_o));
        ui->lenrdom_o->setText(QString::number(g_item->nrbudynku_o));
        ui->lenrlok_o->setText(QString::number(g_item->nrlokalu_o));
        ui->lemiasto_o->setText(QString::fromStdString(g_item->miejscowosc_o));
        ui->lekodpoczt_o->setText(QString::fromStdString(g_item->kodpocztowy_o));

        ui->leWaga->setText(QString::number(g_item->waga_przesylki));
        ui->leWymiar1->setText(QString::number(g_item->wymiary_przesylki[0]));
        ui->leWymiar2->setText(QString::number(g_item->wymiary_przesylki[1]));
        ui->leWymiar3->setText(QString::number(g_item->wymiary_przesylki[2]));
    }
}

newdialog::~newdialog()
{
    delete ui;
}

/**
 * Funkcja reaguje na kliknięcie przycisku zapisz
 * Funkcja zmienia dane bądź dodaje kolejny element do listy przesyłek.
 */
void newdialog::on_pbZapisz_clicked()
{
    lista_paczek *nowy = new lista_paczek;
    string slowo;
    SYSTEMTIME st;
    GetSystemTime(&st);

    if (zmiendane==true) // jeżeli chce tylko zmienic dane istniejącej paczki
    {
        g_item->imie_n=ui->leimie_n->text().toStdString();
        g_item->nazwisko_n=ui->lenazwisko_n->text().toStdString();;
        g_item->email_n=ui->leemail_n->text().toStdString();;
        g_item->nrtel_n=ui->letel_n->text().toInt();
        g_item->ulica_n=ui->leulica_n->text().toStdString();;
        g_item->nrbudynku_n=ui->lenrdom_n->text().toInt();
        g_item->nrlokalu_n=ui->lenrlok_n->text().toInt();
        g_item->miejscowosc_n=ui->lemiasto_n->text().toStdString();;
        g_item->kodpocztowy_n=ui->lekodpoczt_n->text().toStdString();;

        g_item->imie_o=ui->leimie_o->text().toStdString();;
        g_item->nazwisko_o=ui->lenazwisko_o->text().toStdString();;
        g_item->email_o=ui->leemail_o->text().toStdString();;
        g_item->nrtel_o=ui->letel_o->text().toInt();
        g_item->ulica_o=ui->leulica_o->text().toStdString();;
        g_item->nrbudynku_o=ui->lenrdom_o->text().toInt();
        g_item->nrlokalu_o=ui->lenrlok_o->text().toInt();
        g_item->miejscowosc_o=ui->lemiasto_o->text().toStdString();;
        g_item->kodpocztowy_o=ui->lekodpoczt_o->text().toStdString();;

        g_item->waga_przesylki=ui->leWaga->text().toInt();
        g_item->wymiary_przesylki[0]=ui->leWymiar1->text().toInt();
        g_item->wymiary_przesylki[1]=ui->leWymiar2->text().toInt();
        g_item->wymiary_przesylki[2]=ui->leWymiar3->text().toInt();
    }
    else
    {
        nowy->nr_paczki=ile;
    //pobieram dane poczki kolejno z pól tekstowych
        nowy->imie_n = ui->leimie_n->text().toStdString();
        nowy->nazwisko_n = ui->lenazwisko_n->text().toStdString();;
        nowy->miejscowosc_n = ui->lemiasto_n->text().toStdString();
        nowy->kodpocztowy_n = ui->lekodpoczt_n->text().toStdString();
        nowy->ulica_n = ui->leulica_n->text().toStdString();
        nowy->nrbudynku_n = ui->lenrdom_n->text().toInt();
        nowy->nrlokalu_n =ui->lenrlok_n->text().toInt();
        nowy->email_n = ui->leemail_n->text().toStdString();
        nowy->nrtel_n = ui->letel_n->text().toInt();

        nowy->imie_o = ui->leimie_o->text().toStdString();
        nowy->nazwisko_o = ui->lenazwisko_o->text().toStdString();;
        nowy->miejscowosc_o = ui->lemiasto_o->text().toStdString();
        nowy->kodpocztowy_o = ui->lekodpoczt_o->text().toStdString();
        nowy->ulica_o = ui->leulica_o->text().toStdString();
        nowy->nrbudynku_o = ui->lenrdom_o->text().toInt();
        nowy->nrlokalu_o =ui->lenrlok_o->text().toInt();
        nowy->email_o = ui->leemail_o->text().toStdString();
        nowy->nrtel_o = ui->letel_o->text().toInt();


        nowy->wymiary_przesylki[0] = ui->leWymiar1->text().toInt();
        nowy->wymiary_przesylki[1] = ui->leWymiar2->text().toInt();
        nowy->wymiary_przesylki[2] = ui->leWymiar3->text().toInt();
        nowy->waga_przesylki = ui->leWaga->text().toInt();

        nowy->nr_kuriera_n=0;
        nowy->nr_kuriera_o=0;
        nowy->status=0;
        nowy->data_0[0] = st.wDay;
        nowy->data_0[1] = st.wMonth;
        nowy->data_0[2] = st.wYear;
        for (int j=0;j<3;j++)
        {
            nowy->data_1[j]=0;
            nowy->data_2[j]=0;
            nowy->data_3[j]=0;
            nowy->data_4[j]=0;
        }

        nowy->nast=NULL;

        if(adres_glowy == NULL)
            adres_glowy = nowy;
        else
            adres_ogona->nast=nowy;

        adres_ogona = nowy;

        ile++;
    }

    zapisz_rejestr_paczek(adres_glowy, nazwa_pliku);
    this->close(); // zamykam okno dialogowe
}
