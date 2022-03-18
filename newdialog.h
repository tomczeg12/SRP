/**
 * \file newdialog.h
 * \brief Plik nagłówkowy modułu newdialog
 */
#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

namespace Ui {
class newdialog;
}

class newdialog : public QDialog
{
    Q_OBJECT

public:
    explicit newdialog(QWidget *parent = nullptr);
    ~newdialog();

private slots:
    void on_pbZapisz_clicked(); // dodaje element do listy paczek

private:
    Ui::newdialog *ui;
};

#endif // NEWDIALOG_H
