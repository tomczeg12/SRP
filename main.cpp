/**
 * \mainpage
 * \par System Rejestracji Przesyłek
 * Przykładowy program do zarządzania bazą przesyłek z poziomu administratora i klienta.
 * \author Michał Kosmala
 * \date 02.04.2021
 * \version 1.0
 * \par
 * \a
*/
#include "logdialog.h"
#include "baza_przesylek.h"
#include <QApplication>
#include <QTableWidgetItem>

/// zmienna globalna wskaźnikowa adres_glowy
lista_paczek * adres_glowy = NULL;
/// zmienna globalna wskaźnikowa adres_ogona
lista_paczek * adres_ogona = NULL;
/// zmienna globalna nazwa_pliku
/// przechowuje ona nazwe pliku z którego ma być wczytana lista paczek
string nazwa_pliku("zap_dane.txt");
/// zmienna globalna wskaźnikowa g_item
/// przechowuje wskaźnik do elementu listy którego dane są wyświetlane w obecnie klikniętym elemencie tabelki
lista_paczek * g_item = NULL;
/// zmienna globalna wskaźnikowa now_item
/// przechowuje wskaźnik do elementu tabelki które obecnie jest kliknięty
QTableWidgetItem * now_item = NULL; // obecnie kliknięty element
/// zmienna globalna wskaźnikowa glowa
extern lista_admin * glowa;
/// zmienna globalna wskaźnikowa glowa1
extern lista_klient * glowa1;
/// zmienna globalna wskaźnikowa ogon1
extern lista_klient * ogon1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    logDialog oknolog; // otwieram okno logowania
    oknolog.show();
    usun_liste(adres_glowy);
    usun_liste_admin(glowa);
    usun_liste_klient(glowa1);
    delete adres_glowy;
    delete adres_ogona;
    delete glowa;
    delete glowa1;
    delete ogon1;
    return a.exec();
}
