/**
 * \file danedialog.cpp
 * \brief Plik źródłowy modułu danedialog
 */

#include "danedialog.h"
#include "ui_danedialog.h"
#include "logdialog.h"


extern lista_klient * klient_log; // adres elementu z listy klientów w którym znajdują się dane zalogogwanego klienta
extern lista_klient * glowa1;
extern lista_klient * ogon1;
extern int ile_kl;

daneDialog::daneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::daneDialog)
{
        ui->setupUi(this);
        if (klient_log!=NULL)
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
}

daneDialog::~daneDialog()
{
    delete ui;
}

/**
 * Funkcja reaguje na kliknięcie przycisku zapisz
 * Pobiera dane z pól i w zależności czy jest to rejestracja czy zmiana danych użytkownika tworzy nowe konto albo zmienia istniejące dane.
 * \attention Jeżeli żaden klient jeszcze się nie zalogował, funkcja sprawdza czy podane hasłą się zgadzają i jeżeli tak dodaje nowe konto
 *            Jeżeli klient już się zalogował, funkcja zapisze zmiany jeżeli użytkownik nic nie wpisał w polu hasło,
 *            jeśli już coś wpisał to sprawdza czy hasło jest zgodne z hasłem przypisanym do jego konta, a następnie czy podane nowe hasłą są takie same,
 *            a jeżeli hasło nie nie jest takie samo jak przypisane do jego konta to zostanie wypisana informacja że użytkownik podał złe hasło.
 */
void daneDialog::on_pbZapisz_clicked()
{
    if(klient_log==NULL)
    {
        if (ui->lenowehaslo->text()==ui->lenowehaslo1->text())
        {
            lista_klient * nowy = new lista_klient;

            nowy->haslo=ui->lenowehaslo->text().toStdString();
            nowy->imie=ui->leimie_n->text().toStdString();
            nowy->nazwisko=ui->lenazwisko_n->text().toStdString();
            nowy->login=ui->leemail_n->text().toStdString();
            nowy->nrtel=ui->letel_n->text().toInt();
            nowy->ulica=ui->leulica_n->text().toStdString();
            nowy->nrbudynku=ui->lenrdom_n->text().toInt();
            nowy->nrlokalu=ui->lenrlok_n->text().toInt();
            nowy->miejscowosc=ui->lemiasto_n->text().toStdString();
            nowy->kodpocztowy=ui->lekodpoczt_n->text().toStdString();
            nowy->nast=NULL;

            if(glowa1 == NULL)
                glowa1 = nowy;
            else
                ogon1->nast=nowy;
            ogon1 = nowy;
            ile_kl ++;
            zapisz_rejestr_klient(glowa1);
            usun_liste_klient(glowa1);
            this->close();
        }
        else
        {
            ui->lenowehaslo1->clear();
            ui->leinfo->setText("Hasla niezgodne");
        }
    }
    else
    {
        klient_log->imie=ui->leimie_n->text().toStdString();
        klient_log->nazwisko=ui->lenazwisko_n->text().toStdString();
        klient_log->login=ui->leemail_n->text().toStdString();
        klient_log->nrtel=ui->letel_n->text().toInt();
        klient_log->ulica=ui->leulica_n->text().toStdString();
        klient_log->nrbudynku=ui->lenrdom_n->text().toInt();
        klient_log->nrlokalu=ui->lenrlok_n->text().toInt();
        klient_log->miejscowosc=ui->lemiasto_n->text().toStdString();
        klient_log->kodpocztowy=ui->lekodpoczt_n->text().toStdString();
        if (ui->lehaslo==NULL)
        {
            zapisz_rejestr_klient(glowa1);
            this->close();
        }
        else if (ui->lehaslo->text().toStdString()==klient_log->haslo)
        {
            if (ui->lenowehaslo->text()==ui->lenowehaslo1->text())
            {
                klient_log->haslo=ui->lenowehaslo->text().toStdString();
                zapisz_rejestr_klient(glowa1);
                this->close();
            }
            else
            {
                ui->lenowehaslo1->clear();
                ui->leinfo->setText("Hasla niezgodne");
            }
        }
        else
        {
            ui->leinfo->setText("Podales zle haslo");
            ui->lenowehaslo->clear();
            ui->lenowehaslo1->clear();
            ui->lehaslo->clear();
        }
    }
}
