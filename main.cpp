/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/


#include <QtGui/QApplication>
#include "mainwindow.h"
#include "alphabet.h"
#include "language.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
