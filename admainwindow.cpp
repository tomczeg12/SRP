/**
 * \file admainwindow.cpp
 * \brief Plik źródłowy modułu admainwindow
 */
#include "admainwindow.h"
#include "ui_admainwindow.h"
#include "baza_przesylek.h"
#include "newdialog.h"
#include "acceptdialog.h"
#include <QTableWidgetItem>
#include <windows.h>
#include <winbase.h>

extern lista_paczek * adres_glowy;
extern lista_paczek * adres_ogona;
extern lista_paczek * g_item; // adres obeecnie klikniętego elementu
extern QTableWidgetItem * now_item; // obecnie kliknięty element
extern string nazwa_pliku;
/// Zmienna globalna zmiendane
/// zmienna przechowująca czy prawdą jest że użytkownik kliknął opcje zminay danych danej paczki ( wykorzystywana w funkcji void on_actionZmien_dane_paczki_triggered())
bool zmiendane(false); // zmienna przechowująca czy prawdą jest że użytkownik kliknął opcje zminay danych danej paczki ( wykorzystywana w funkcji void on_actionZmien_dane_paczki_triggered())

adMainWindow::adMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adMainWindow)
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

adMainWindow::~adMainWindow()
{
    delete ui;
}

/**
 * Funkcja wstawia element do tabelki
 * Po wywołaniu funkcji dodawany jest kolejny element tabelki i uzupełniany o dane elementu listy do którego pobiera wskaźnik
 */
void adMainWindow::wypelnijTabelke(lista_paczek *g)
{
    int i(0);
    ui->tbTabelka->insertRow(ui->tbTabelka->rowCount()); //dodaje nowy pusty wiersz
    i=ui->tbTabelka->rowCount()-1; // jest to numer nowo dodanego wiersza
    ui->tbTabelka->setItem(i,0, new QTableWidgetItem(QString::number(g->nr_paczki))); // w pierwszym polu wiersza wstawiam numer paczki
    switch(g->status) // w zależności od statusu w drugim polu wiersza wstawiam nazwe danego statusu paczki
    {
    case 0:
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem("gotowa do odebrania"));
        break;

    case 1:
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem("odebrana od nadawcy"));
        break;

    case 2:
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem("przyjeta w oddziale"));
        break;

    case 3:
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem("przekazana do doreczenia"));
        break;

    case 4:
        ui->tbTabelka->setItem(i, 1, new QTableWidgetItem("dostarczona"));
        break;
    }
    ui->tbTabelka->setItem(i,2, new QTableWidgetItem(QString::fromStdString(g->nazwisko_o))); // w pierwszym polu wiersza wstawiam numer paczki
    ui->tbTabelka->setItem(i,3, new QTableWidgetItem(QString::fromStdString(g->imie_o))); // w pierwszym polu wiersza wstawiam numer paczki
    ui->tbTabelka->setItem(i,4, new QTableWidgetItem(QString::number(g->waga_przesylki))); // w pierwszym polu wiersza wstawiam numer paczki

}

/**
 * Funkcja czyści a następnie uzupełnia tabelke o wszystkie elementy listy przesyłek
 * Po wywołaniu funkcji usuwa ona wszystkie istniejące wiersze a następnie dopóki istnieje kolejny elemnt listy wywołuje funkcję wypelnijTabelke
 */
void adMainWindow::wyswietlnanowo()
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
 * Funkcja pobiera wskaźnik do klikniętego itemu z tabelki, a nastepnie wypełnia pozostałe widgety danymi z tego samego elementu listy co kliknięty
 */
void adMainWindow::on_tbTabelka_itemClicked(QTableWidgetItem *item)
{
    now_item = item;
    lista_paczek * g = adres_glowy;
    int a = item->row();
    QTableWidgetItem * item1 = ui->tbTabelka->item(a,0); // pobieram element tabelki który zawiera numer przesyłki a który jest w tym samym wierszu
    int nr = item1->text().toInt(); // numer przesylki z wybranego wiersza

    while(g!=NULL && g->nr_paczki!=nr) g=g->nast;

    g_item = g; // zapisuje adres obecnie klikniętego elementu tabelki

    ui->txNadawca->clear();
    ui->txOdbiorca->clear();
    ui->txPaczka->clear();
    ui->leNumer->clear();
    ui->ledata0->clear();
    ui->ledata1->clear();
    ui->ledata2->clear();
    ui->ledata3->clear();
    ui->ledata4->clear();

    // wypełniam wszytkie pola danych danej przesyłki
    ui->txNadawca->setText(QString::fromStdString(g->imie_n) + " " + QString::fromStdString(g->nazwisko_n) + '\n' + QString::fromStdString(g->email_n) + '\n'
            + QString::number(g->nrtel_n) + '\n' + "ul. " + QString::fromStdString(g->ulica_n) + " " + QString::number(g->nrbudynku_n) + " " + QString::number(g->nrlokalu_n)
            + '\n' + QString::fromStdString(g->kodpocztowy_n) + " " + QString::fromStdString(g->miejscowosc_n));

    ui->txOdbiorca->setText(QString::fromStdString(g->imie_o) + " " + QString::fromStdString(g->nazwisko_o) + '\n' + QString::fromStdString(g->email_o) + '\n'
            + QString::number(g->nrtel_o) + '\n' + "ul. " + QString::fromStdString(g->ulica_o) + " " + QString::number(g->nrbudynku_o) + " " + QString::number(g->nrlokalu_o)
            + '\n' + QString::fromStdString(g->kodpocztowy_o) + " " + QString::fromStdString(g->miejscowosc_o));

    ui->txPaczka->setText("wymiary: " +  QString::number(g->wymiary_przesylki[0]) + "x" + QString::number(g->wymiary_przesylki[1]) + "x"
            + QString::number(g->wymiary_przesylki[2]) + " cm \nwaga: " + QString::number(g->waga_przesylki) + " g");
    ui->leNumer->setText(QString::number(g->nr_paczki));
    switch(g->status)
    {
    //w zależności od statusu zmieniam stan konkretnych przycisków
    case 0:
        ui->rb0->setChecked(true);
        ui->ledata0->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1->setChecked(false);
        ui->rb2->setChecked(false);
        ui->rb3->setChecked(false);
        ui->rb4->setChecked(false);
        break;
    case 1:
        ui->rb0->setChecked(false);
        ui->ledata0->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1->setChecked(true);
        ui->ledata1->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2->setChecked(false);
        ui->rb3->setChecked(false);
        ui->rb4->setChecked(false);
        break;
    case 2:
        ui->rb0->setChecked(false);
        ui->ledata0->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1->setChecked(false);
        ui->ledata1->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2->setChecked(true);
        ui->ledata2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3->setChecked(false);
        ui->rb4->setChecked(false);
        break;
    case 3:
        ui->rb0->setChecked(false);
        ui->ledata0->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1->setChecked(false);
        ui->ledata1->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2->setChecked(false);
        ui->ledata2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3->setChecked(true);
        ui->ledata3->setText(QString::number(g->data_3[0]) + "-" + QString::number(g->data_3[1]) + "-" + QString::number(g->data_3[2]));
        ui->rb4->setChecked(false);
        break;
    case 4:
        ui->rb0->setChecked(false);
        ui->ledata0->setText(QString::number(g->data_0[0]) + "-" + QString::number(g->data_0[1]) + "-" + QString::number(g->data_0[2]));
        ui->rb1->setChecked(false);
        ui->ledata1->setText(QString::number(g->data_1[0]) + "-" + QString::number(g->data_1[1]) + "-" + QString::number(g->data_1[2]));
        ui->rb2->setChecked(false);
        ui->ledata2->setText(QString::number(g->data_2[0]) + "-" + QString::number(g->data_2[1]) + "-" + QString::number(g->data_2[2]));
        ui->rb3->setChecked(false);
        ui->ledata3->setText(QString::number(g->data_3[0]) + "-" + QString::number(g->data_3[1]) + "-" + QString::number(g->data_3[2]));
        ui->rb4->setChecked(true);
        ui->ledata4->setText(QString::number(g->data_4[0]) + "-" + QString::number(g->data_4[1]) + "-" + QString::number(g->data_4[2]));
        break;
    }
}

/**
 * Funkcja reagująca na przyciśnięcie przycisku enter w polu wyszukiwania paczki  Funkcja czyści tabelki tak aby był wyświetlony tylko dany element
 * Funkcja usuwa wszystkie elemnty z tabelki poza tym którego szukamy
 */
void adMainWindow::on_leNumer_returnPressed()
{
    int nr = ui->leNumer->text().toInt();

    ui->txNadawca->clear();
    ui->txOdbiorca->clear();
    ui->txPaczka->clear();
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

/**
 * Funkcja reaguje na klknięcie przycisku dodaj paczke
 * Funkcja otwiera nowe okno dialogowe newdialog
 */
void adMainWindow::on_actionDodaj_paczke_triggered()
{
    newdialog oknoadd;
    oknoadd.exec(); // otwieram nowe okno dodania paczki
    wyswietlnanowo();
}

/**
 * Funkcja reagująca na przyciśnięcie przycisku zapisz
 * Funkcja wywołuje funkcję zapisz_rejestr_paczek
 */
void adMainWindow::on_actionZapisz_triggered()
{
    zapisz_rejestr_paczek(adres_glowy, nazwa_pliku);
}

/**
 * Funkcja reaguje na klknięcie przycisku dalej
 * Funkcja zmienia status paczki na kolejny oraz dodaje date z danej chwili jako datę zmiany statusu, a następnie wyświetla tabelke na nowo, z dokonanymi zmianami
 */
void adMainWindow::on_pbSaveStatus_clicked()
{
    int a = g_item->status; // sprawdzam który przycisk jest wciśnięty

    SYSTEMTIME st;
    GetSystemTime(&st);

    switch(a)
    {
    case 0:
        g_item->status++;
        g_item->data_1[0] = st.wDay;
        g_item->data_1[1] = st.wMonth;
        g_item->data_1[2] = st.wYear;
        break;

    case 1:
        g_item->status++;
        g_item->data_2[0] = st.wDay;
        g_item->data_2[1] = st.wMonth;
        g_item->data_2[2] = st.wYear;
        break;

    case 2:
        g_item->status++;
        g_item->data_3[0] = st.wDay;
        g_item->data_3[1] = st.wMonth;
        g_item->data_3[2] = st.wYear;
        break;

    case 3:
        g_item->status++;
        g_item->data_4[0] = st.wDay;
        g_item->data_4[1] = st.wMonth;
        g_item->data_4[2] = st.wYear;
        break;
    }
    ui->tbTabelka->itemClicked(now_item);
    wyswietlnanowo();

    return;
}


/**
 * Funkcja reaguje na klknięcie przycisku usuń paczke
 * Funkcja otwiera nowe okno dialogowe acceptDialog
 * \attention Funkcja otworzy okno acceptDialog tylko jeżeli jakikolwiek element został kliknięty
 */
void adMainWindow::on_actionUsun_paczke_triggered()
{
    if(g_item!=NULL)
    {
        acceptDialog okno1;
        okno1.exec();
        wyswietlnanowo();
    }
}

/**
 * Funkcja reaguje na klknięcie przycisku zmien dane paczki
 * Funkcja otwiera nowe okno dialogowe newdialog
 * \attention Funkcja otworzy okno newdialog tylko jeżeli jakikolwiek element został kliknięty,
 *            przypisuje ona zmiennej zmiendane wartość true w celu oznajmienia, że chcemy tylko zmienić dane paczki.
 *            Po zamknięciu okna funkcja wypełni tabelke na nowo i przypisze zmiennej zmiendane z powrotem wartośc false.
 */
void adMainWindow::on_actionZmien_dane_paczki_triggered()
{
    if(g_item!=NULL)
    {
        zmiendane = true;
        newdialog okno2;
        okno2.exec();
        wyswietlnanowo();
        zmiendane = false;
    }
}
