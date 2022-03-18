/**
 * \file acceptdialog.h
 * \brief Plik nagłówkowy modułu acceptdialog
 *
 */
#ifndef ACCEPTDIALOG_H
#define ACCEPTDIALOG_H

#include <QDialog>

namespace Ui {
class acceptDialog;
}

class acceptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit acceptDialog(QWidget *parent = nullptr);
    ~acceptDialog();

private slots:
    void on_pbUsun_clicked();

private:
    Ui::acceptDialog *ui;
};

#endif // ACCEPTDIALOG_H
