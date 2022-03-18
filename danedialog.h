/**
 * \file danedialog.h
 * \brief Plik nagłówkowy modułu danedialog
 */
#ifndef DANEDIALOG_H
#define DANEDIALOG_H

#include <QDialog>

namespace Ui {
class daneDialog;
}

class daneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit daneDialog(QWidget *parent = nullptr);
    ~daneDialog();

private slots:
    void on_pbZapisz_clicked();

private:
    Ui::daneDialog *ui;
};

#endif // DANEDIALOG_H
