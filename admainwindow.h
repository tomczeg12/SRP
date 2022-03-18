/**
 * \file admainwindow.h
 * \brief Plik nagłówkowy modułu admainwindow
 */
#ifndef ADMAINWINDOW_H
#define ADMAINWINDOW_H
#include <QMainWindow>
#include "baza_przesylek.h"
#include <QTableWidgetItem>

namespace Ui {
class adMainWindow;
}

class adMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adMainWindow(QWidget *parent = nullptr);
    ~adMainWindow();

private slots:

    void on_actionZapisz_triggered();

    void on_tbTabelka_itemClicked(QTableWidgetItem *item);

    void on_leNumer_returnPressed();

    void on_actionDodaj_paczke_triggered();

    void on_pbSaveStatus_clicked();

    void on_actionUsun_paczke_triggered();

    void on_actionZmien_dane_paczki_triggered();

private:
    Ui::adMainWindow *ui;

    void wypelnijTabelke(lista_paczek *g);
    void wyswietlnanowo();
};

#endif // ADMAINWINDOW_H
