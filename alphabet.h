/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#ifndef ALPHABET_H
#define ALPHABET_H

#include <QSet>
typedef QString t_simbol;
typedef QString t_word;


class Alphabet : public QSet<t_simbol> //Alphabet hereda de QSet (Clase de conjuntos)
                                        //Mecanismo de insersion de elementos(No se agregan elementos repetidos)
                                        //Hereda operaciones: union, interseccion, diferencia
{
public:
    //Contructores
    Alphabet();
    Alphabet(QString name);

    //Metodo insertar sobrecargado para que valide simbolos del alfabeto ingles
    bool insert(t_simbol s);
    //Metodo para validar si una palabra w pertenece al alfabeto
    bool wordBelong(t_word w);

    //Getters y setters
    QString getText();
    QString getElementsText();

    inline void setName(QString n){name=n;}
    inline QString getName()const{return name;}
    inline void setPath(QString path){this->path=path;}
    inline QString getPath()const{return path;}

private:
    QString name;
    QString path;



};

#endif // ALPHABET_H
