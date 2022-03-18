/**
 * \file klmainwindow.h
 * \brief Plik nagłówkowy modułu klmainwindow
 */
#ifndef KLMAINWINDOW_H
#define KLMAINWINDOW_H
#include <QMainWindow>
#include "baza_przesylek.h"
#include <QTableWidgetItem>

namespace Ui {
class klMainWindow;
}

class klMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit klMainWindow(QWidget *parent = nullptr);
    ~klMainWindow();

private slots:

    void on_tbTabelka_itemClicked(QTableWidgetItem *item);

    void on_pbWyslij_clicked();

    void on_pbKonto_clicked();

    void on_leNumer_returnPressed();

private:
    Ui::klMainWindow *ui;
    void wypelnijTabelke(lista_paczek *g); // funkcja wyświetlający w tabelce element o konkretnym adresie
    void wyswietlnanowo(); // funkcja wyświetlająca liste paczek od nowa
};

#endif // KLMAINWINDOW_H
