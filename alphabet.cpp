/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#include "alphabet.h"
#include <QStringList>
#include <QDebug>
Alphabet::Alphabet()
{

}

Alphabet::Alphabet(QString name)
{
    this->name=name;
}

bool Alphabet::insert(t_simbol s){
    bool r=false;
    s=s.left(1);
    //Validacion del alfabeto ingles
    if((s>="a"&&s<="z")){
        QSet<QString>::insert(s);
        r=true;
    }
    return r;
}

bool Alphabet::wordBelong(t_word w){
    QString _lambda=QChar(955);

    int i=0;
    bool b=true;
    //Verifica que cada caracter de la palabra pertenezca al alfabeto
    while(i<w.count()&&b){
        if(!((this->contains(w.at(i)))||w==""||w==_lambda)){
            b=false;
        }
        i++;
    }
    return b;
}


QString Alphabet::getText(){
    QString _sigma=QChar(931);
    QString text=name+":\n"+_sigma+"={"+getElementsText()+"}";
    return text;
}
//Devuelve una cadena del alfabeto.
QString Alphabet::getElementsText(){
    QString text;
    QStringList l(this->toList());

    //Ordena alfabeticamente
    qSort(l.begin(), l.end(), qLess<t_simbol>());

    //Ordena por longitud
    for (int i = 1; i<l.count(); ++i){
        for (int j = 0; j != (l.count())-i; ++j){
            if(l.at(j).length()>l.at(j+1).length())
                l.swap(j,j+1);
         }
    }
    //Devuelve una cadena con los simbolos separados por comas
   QStringList::const_iterator i;
   if(l.count()!=0){
       for(i=l.constBegin();i!=l.constEnd();i++){
          text+=(*i)+",";
        }
        text.chop(1);
   }
   return text;
}
