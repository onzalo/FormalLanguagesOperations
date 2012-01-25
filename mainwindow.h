/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alphabet.h"
#include "language.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Alphabet alphabet;
    QList<Language> languageList;
private:
    Ui::MainWindow *ui;


    void showAlphabet();
    void showLanguage(int i,int diplay);

private slots:

    //Slots Creacion por teclado
    void showAlphabetCreate();
    void showLanguageCreate();
    void createAlphabet();
    void createLanguage();

    //Slots Archivos
    void openAlphabet();
    void openLanguage();

    void saveAlphabet();
    void saveLanguages();
    void saveCurrentLanguage1();
    void saveResult();

    //Slots Operaciones
    void listLanguages();
    void showLanguageIn1(int i);
    void showLanguageIn2(int i);
    void showArgument(int op);
    void resolve();


signals:
    void statusChanged(QString status);

};


#endif // MAINWINDOW_H
