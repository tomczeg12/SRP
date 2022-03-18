/**
 * \file klmainwindow.cpp
 * \brief Plik źródłowy modułu klmainwindow
 */
#include "klmainwindow.h"
#include "ui_klmainwindow.h"
#include "baza_przesylek.h"
#include "newdialog.h"
#include "danedialog.h"
#include "logdialog.h"

#include <QTableWidgetItem>

extern lista_paczek * adres_glowy;
extern lista_paczek * adres_ogona;
extern lista_paczek * g_item;
extern QTableWidgetItem * now_item;
extern string nazwa_pliku;
extern lista_klient * klient_log;

klMainWindow::klMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::klMainWindow)
{
    ui->setupUi(this);
    wczytaj_rejestr_paczek(adres_glowy, adres_ogona, nazwa_pliku); // wczytuje baze danych przesyłek z pliku
    lista_paczek *g = adres_glowy;
    while(g!=NULL)
    {
        wypelnijTabelke(g);
        g=g->nast;
    }
}

klMainWindow::~klMainWindow()
{
    delete ui;
}

/**
 * Funkcja wstawia element do tabelki
 * Po wywołaniu funkcji dodawany jest kolejny element tabelki i uzupełniany o dane elementu listy do którego pobiera wskaźnik
 */
void klMainWindow::wypelnijTabelke(lista_paczek *g)
{
    if(g->email_n==klient_log->login)
    {
        int i(0);
        ui->tbTabelka->insertRow(ui->tbTabelka->rowCount()); //dodaje nowy pusty wiersz
        i=ui->tbTabelka->rowCount()-1; // jest to numer nowo dodanego wiersza
        ui->tbTabelka->setItem(i,0, new QTableWidgetItem(QString::number(g->nr_paczki))); // w pierwszym polu wiersza wstawiam numer paczki
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(g->email_o))); // w drugim polu wiersza wstawiam email nadawcy lub odbiorcy
    }
    else if(g->email_o==klient_log->login)
    {
        int i(0);
        ui->tbTabelka->insertRow(ui->tbTabelka->rowCount());
        i=ui->tbTabelka->rowCount()-1;
        ui->tbTabelka->setItem(i,0, new QTableWidgetItem(QString::number(g->nr_paczki)));
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(g->email_n)));
    }
}

/**
 * Funkcja czyści a następnie uzupełnia tabelke o wszystkie elementy listy przesyłek
 * Po wywołaniu funkcji usuwa ona wszystkie istniejące wiersze a następnie dopóki istnieje kolejny elemnt listy wywołuje funkcję wypelnijTabelke
 */
void klMainWindow::wyswietlnanowo()
{
    int a(0);
    a=ui->tbTabelka->rowCount(); // zapisuje liczbe wierszy tabelki
    for(int i=0;i<a;i++)
        ui->tbTabelka->removeRow(a-i-1); // usuwam wszystkie wiersze z wyjątkiem pierwszego w którym podane są nazwy kolumn
    lista_paczek *g = adres_glowy;
    while(g!=0)
    {
        wypelnijTabelke(g); // wypełniam tableke kolejno elementami
        g=g->nast;
    }
}

/**
 * Funkcja reaguje na kliknięcie w dowolny element w tabelce
 * Funkcja pobiera wskaźnik do klikniętego itemu z tabelki, a nastepnie wypełnia okienko ze statusem danymi z tego samego elementu listy
 */
void klMainWindow::on_tbTabelka_itemClicked(QTableWidgetItem *item)
{
    now_item = item;
    lista_paczek * g = adres_glowy;
    int a = item->row();
    QTableWidgetItem * item1 = ui->tbTabelka->item(a,0); // pobieram element tabelki który zawiera numer przesyłki a który jest w tym samym wierszu
    int nr = item1->text().toInt(); // numer przesylki z wybranego wiersza

    while(g!=NULL && g->nr_paczki!=nr) g=g->nast;

    g_item = g; // zapisuje adres obecnie klikniętego elementu tabelki

    ui->leNumer->clear();
    ui->ledata0_2->clear();
    ui->ledata1_2->clear();
    ui->ledata2_2->clear();
    ui->ledata3_2->clear();
    ui->ledata4_2->clear();

    // wypełniam wszytkie pola danych danej przesyłki
    ui->leNumer->setText(QString::number(g->nr_paczki));
    switch(g->status)
    {
    //w zależności od statusu zmieniam stan konkretnych przycisków
    case 0:
        ui->rb0_2->setChecked(true);
        ui->ledata0_2->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1_2->setChecked(false);
        ui->rb2_2->setChecked(false);
        ui->rb3_2->setChecked(false);
        ui->rb4_2->setChecked(false);
        break;
    case 1:
        ui->rb0_2->setChecked(false);
        ui->ledata0_2->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1_2->setChecked(true);
        ui->ledata1_2->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2_2->setChecked(false);
        ui->rb3_2->setChecked(false);
        ui->rb4_2->setChecked(false);
        break;
    case 2:
        ui->rb0_2->setChecked(false);
        ui->ledata0_2->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1_2->setChecked(false);
        ui->ledata1_2->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2_2->setChecked(true);
        ui->ledata2_2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3_2->setChecked(false);
        ui->rb4_2->setChecked(false);
        break;
    case 3:
        ui->rb0_2->setChecked(false);
        ui->ledata0_2->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1_2->setChecked(false);
        ui->ledata1_2->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2_2->setChecked(false);
        ui->ledata2_2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3_2->setChecked(true);
        ui->ledata3_2->setText(QString::number(g->data_3[0]) + "-" + QString::number(g->data_3[1]) + "-" + QString::number(g->data_3[2]));
        ui->rb4_2->setChecked(false);
        break;
    case 4:
        ui->rb0_2->setChecked(false);
        ui->ledata0_2->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1_2->setChecked(false);
        ui->ledata1_2->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2_2->setChecked(false);
        ui->ledata2_2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3_2->setChecked(false);
        ui->ledata3_2->setText(QString::number(g->data_3[0]) + "-" + QString::number(g->data_3[1]) + "-" + QString::number(g->data_3[2]));
        ui->rb4_2->setChecked(true);
        ui->ledata4_2->setText(QString::number(g->data_4[0]) + "-" + QString::number(g->data_4[1]) + "-" + QString::number(g->data_4[2]));
        break;
    }
}

/**
 * Funkcja reaguje na klknięcie przycisku Wyślij
 * Funkcja otwiera nowe okno dialogowe newdialog
 */
void klMainWindow::on_pbWyslij_clicked()
{
    //newdialog oknoadd;
    //oknoadd.exec();
    //wyswietlnanowo();
}

/**
 * Funkcja reaguje na klknięcie przycisku Konto
 * Funkcja otwiera nowe okno dialogowe daneDialog
 */
void klMainWindow::on_pbKonto_clicked()
{
    daneDialog oknoadd;
    oknoadd.exec();
    wyswietlnanowo();
}

/**
 * Funkcja reagująca na przyciśnięcie przycisku enter w polu wyszukiwania paczki  Funkcja czyści tabelki tak aby był wyświetlony tylko dany element
 * Funkcja usuwa wszystkie elemnty z tabelki poza tym którego szukamy
 */
void klMainWindow::on_leNumer_returnPressed()
{
    int nr = ui->leNumer->text().toInt();

    ui->leNumer->clear();


    lista_paczek * g = adres_glowy;

    if (nr==0)
    {
        wyswietlnanowo();
        return;
    }
    while(g!=NULL)
    {
        if (nr==g->nr_paczki) // jeżeli numer paczki to numer wpisany w polu wyszukiwania
        {
            int a(0);
            a=ui->tbTabelka->rowCount(); // zapisuje liczbe wierszy tabelki
            for(int i=0;i<a;i++)
                ui->tbTabelka->removeRow(a-i-1); // usuwam wszystkie wiersze z wyjątkiem pierwszego w którym podane są nazwy kolumn
            wypelnijTabelke(g);
            return;
        }
        g=g->nast;
    }
}
