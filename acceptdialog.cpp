/**
 * \file acceptdialog.cpp
 * \brief Plik źródłowy modułu acceptdialog
 */
#include "acceptdialog.h"
#include "ui_acceptdialog.h"
#include "baza_przesylek.h"

extern lista_paczek * adres_glowy;
extern lista_paczek * adres_ogona;
extern lista_paczek * g_item;

acceptDialog::acceptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acceptDialog)
{
    ui->setupUi(this);
    ui->leInfo->setText("Czy na pewno chcesz usunac paczke o numerze: " + QString::number(g_item->nr_paczki) + " ?");
}

acceptDialog::~acceptDialog()
{
    delete ui;
}

/**
 * Funkcja reaguje na kliknięcie przycisku usuń
 * Po kliknięciu przycisku usuń funkcja wywołuje funkcję usun, która usuwa konkretny element listy.
 *
 * \attention jeżeli funkcja usuń zwróci wartość false,
 *            okno się zamknie.
 */
void acceptDialog::on_pbUsun_clicked()
{
    if (usun(adres_glowy,adres_ogona, g_item) == false)
    {
        this->close();
    }
}
