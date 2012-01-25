/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "alphabet.h"
#include <QSet>
#include <QDebug>
typedef QString t_simbol;
typedef QString t_word;


class Language : public QSet<t_word> //Lenguaje hereda de QSet
{
private:
    QString name;
    Alphabet *alphabet;
    QString path;
public:
    Language();
    Language(QString n, Alphabet *a);

    /*Inserta palabra si
        Hay alfabeto cargado
        Si la palabra pertenece al alfabeto
      */
    bool insert(t_word w);

    inline QString getName()const{return name;}
    inline void setName(QString n){name=n;}
    void screenWords();
    inline void setPath(QString path){this->path=path;}
    inline QString getPath()const{return path;}
    QString getText();
    QString getElementsText();
    void revalidateWords();

    ///Operations

    //Invierte cada palabra del lenguaje
    Language &invert();
    //Concatena las cada palabra del lenguaje con cada palabra del otro lenguaje
    Language &concatenate(const Language &other);
    /*Devuelve un lenguaje formado por la concatenacion
    de cada palabra consigo misma "exponent" veces*/
    Language &exponentiate(int exponent);
    //Union de todas las potencias del lenguaje desde 1 hasta k
    Language &kleenePlus(int k);
    //Unimos lambda con kleeneplus
    Language &kleeneStar(int k);
    /*Creamos un lenguaje formado por los simbolos del alfabeto
      le aplicamos estrella de kleene
     */
    Language &universalLanguage(int k);
    //Al lenguaje universal  se le resta las palabras del lenguaje.
    Language &complement(int k);

    ///Operators
    inline Language operator|(const Language &other) const
        { Language result = *this; result |= other; return result; }
    inline Language operator&(const Language &other) const
        { Language result = *this; result &= other; return result; }
    inline Language operator+(const Language &other) const
        { Language result = *this; result += other; return result; }
    inline Language operator-(const Language &other) const
        { Language result = *this; result -= other; return result; }

};

#endif // LANGUAGE_H

