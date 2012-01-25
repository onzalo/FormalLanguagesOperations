/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#include "language.h"
#include <QStringList>
#include <QList>

Language::Language()
{

}

Language::Language(QString n, Alphabet *a)
{
    name=n;
    alphabet=a;
}

bool Language::insert(t_word w){
    bool r=false;
    //Si pertenece al lenguaje, agrega la palabra (w)
    if(alphabet->wordBelong(w)||w==QChar(955)||w==""){
        //Si la cadena es vacia, ingresa el simbolo lambda
        if(w=="")
            w=QChar(955);
        QSet<QString>::insert(w);
        r=true;
    }

return r;
}

void Language::screenWords(){
    QStringList l(this->toList());

    qSort(l.begin(), l.end(), qLess<t_word>());

    for (int i = 1; i<l.count(); ++i){
        for (int j = 0; j != (l.count())-i; ++j){
            if(l.at(j).length()>l.at(j+1).length())
                l.swap(j,j+1);
         }
    }

//    qDebug() << "Elements of "+name;

   // QStringList::iterator i;
   //  for (i = l.begin(); i != l.end(); ++i)
   // qDebug() << *i;
}

//Operations

Language &Language::invert(){
    Language copy1(*this);
    //Recorremos el lenguaje
    Language::const_iterator i = copy1.constBegin();
    while (i != copy1.constEnd()) {

    t_word w,invertW;
    //copaimos la palabra de la posicion i en w
    w=(*i);
    //asignamos a j la cantidad de caracteres de la palabra
    int j=w.count();
    //Copia de manera invertida la palabra w en invert w
    while(j!=0){
        --j;
        invertW.append(w[j]);
    }
    //Eliminamos la palabra original
    remove(*i);
    //Insertamos la invertida
    insert(invertW);
    i++;
}

    return *this;
}
Language &Language::concatenate(const Language &other){
    QList<t_word> l1=(*this).toList();
    QList<t_word> l2=other.toList();
    QList<t_word> l3;
    t_word w;

    this->clear();
    for(int i=0;i<l1.count();i++){
        for(int j=0;j<l2.count();j++){
            w=l1.at(i)+l2.at(j);
            this->insert(w);
        }
    }
    return *this;
}
Language &Language::exponentiate(int exponent){
    Language copy(*this);
    if(exponent==0){

        this->clear();
        this->insert(QChar(955));
    }else{
        for(int i=1;i<abs(exponent);i++){
            concatenate(copy);
        }
        if(exponent<0){
            invert();
        }
    }
    return *this;
}
Language &Language::kleenePlus(int k){
    Language copy1(*this);
    copy1.alphabet=this->alphabet;
    Language p=Language("p",this->alphabet);
    int i=1;
    while (i<k+1) {
        p=(*this);
        //p.exponentiate(i);
        copy1.unite(p.exponentiate(i));
        i++;
    }
    QList<t_word> l=copy1.toList();
    this->clear();

   for(int i=0;i<l.count();i++){
       if(l.at(i).length()<=k){
         this->insert(l.at(i));
       }
   }
    return *this;
}
Language &Language::kleeneStar(int k){
    Language copy1(*this);
    copy1.alphabet=this->alphabet;

    copy1.kleenePlus(k);
    copy1.insert(QChar(955));
    (*this)=copy1;
    return *this;
}
Language &Language::complement(int k){
    Language copy1(*this);
     copy1.alphabet=this->alphabet;

    copy1.universalLanguage(k);
    copy1.subtract(*this);
    (*this)=copy1;
    return *this;
}

Language &Language::universalLanguage(int k){
   Language universal= Language(this->getName(),alphabet);
    QList<QString> l=this->alphabet->toList();

    for(int i=0;i<l.count();i++)
        universal.insert(l.at(i));
    //qDebug()<<universal.getText();
    universal.kleeneStar(k);


    (*this)=universal;

    return *this;
}

QString Language::getText(){
    return name+" = {"+getElementsText()+"}\n";
}

QString Language::getElementsText(){
    QString text;
    QStringList l(this->toList());
    qSort(l.begin(), l.end(), qLess<t_simbol>());

    for (int i = 1; i<l.count(); ++i){
        for (int j = 0; j != (l.count())-i; ++j){
            if(l.at(j).length()>l.at(j+1).length())
                l.swap(j,j+1);
         }
    }
    QString _lambda=QChar(955);
    if(l.contains(_lambda)){
        l.removeOne(_lambda);
        l.push_front(_lambda);
    }
    QStringList::const_iterator i;
    if(l.count()!=0){
       for(i=l.constBegin();i!=l.constEnd();i++){
          text+=(*i)+",";
        }
        text.chop(1);
    }
    return text;
}

void Language::revalidateWords(){
    this->count();
    QStringList l=this->toList();
    this->clear();
    for(int i=0;i<l.count();i++)
        this->insert(l.at(i));
}
