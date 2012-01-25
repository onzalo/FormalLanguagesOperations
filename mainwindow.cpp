/**********
Sintaxis y Semantica de los Lenguajes
AL1 - Operaciones con Lenguajes
Comision: 2k1
Año:2011

Autor:Lescano, Gonzalo
***********/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->dockWidget_Alphabet->hide();
    ui->dockWidget_Language->hide();


    //Ej
    alphabet.setName("Alfabeto1");
    alphabet.insert("a");
    alphabet.insert("b");
    showAlphabet();

    Language empty("Lenguaje Vacio",&alphabet);
    Language l1("Leng 1",&alphabet);
    l1.insert("aba");
    l1.insert("baa");
    Language l2("Leng 2",&alphabet);
    l2.insert("a");
    l2.insert("b");

    languageList.push_back(empty);
    languageList.push_back(l1);
    languageList.push_back(l2);


    listLanguages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAlphabet(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
            tr("No se pudo abrir el archivo."));
            return;
        }

        this->alphabet.setName(QString(file.readLine()).trimmed());
        this->alphabet.setPath(fileName.trimmed());

        QString simbols = file.readLine();
        simbols.trimmed();

        QStringList simbolsList=simbols.split(',');
        if(simbolsList.count()!=0){
            for(int i=0;i<simbolsList.count();i++)
                 alphabet.insert(simbolsList.at(i));
            showAlphabet();
        }
        else
            QMessageBox::critical(this, tr("Error"),
            tr("El alfabeto debe tener al menos un simbolo."));

        file.close();
    }
}

void MainWindow::openLanguage(){
    if(!alphabet.empty()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("Text Files (*.txt)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"),
                tr("No se pudo abrir el archivo."));
                return;
            }
            if(!file.atEnd()){
                Language language(QString(file.readLine()).trimmed(),&alphabet);
                language.setPath(fileName.trimmed());
                QString words = file.readLine();

                QString _lambda(QChar(955));
                QString first=words.at(0);
                if(first==",")
                    words.prepend(_lambda);


                QStringList wordsList=words.split(',');
                    for(int i=0;i<wordsList.count();i++){
                         language.insert(wordsList.at(i));
                         //qDebug()<<"palabra";
                         //qDebug()<<wordsList.at(i);
                    }

                    this->languageList.push_back(language);
                    //qDebug()<<this->languageList.at(languageList.count()-1);
            }else
                QMessageBox::critical(this, tr("Error"),
                 tr("Archivo Vacio."));
            file.close();
            listLanguages();
            ui->languageList->setCurrentIndex(ui->languageList->count()-1);
        }

    }else
        QMessageBox::critical(this, tr("Error"),
        tr("Debe haber un alfabeto cargado."));

}




void MainWindow::showAlphabet(){
    ui->alphabetDisplay->setText(alphabet.getText());
}
void MainWindow::showLanguage(int i,int display){
    Language l=this->languageList.at(i);
    QString position;
    position.setNum(i+1,10);
    if(display==1)
            ui->languageDisplay->setText("L"+position+":"+l.getText());
    else
    if(display==2)
        ui->languageDisplay_2->setText("L"+position+":"+l.getText());
}

void MainWindow::listLanguages(){
    QString element;
    QString position;

   int n=ui->languageList->count();
   for(int i=n;i>0;i--){
        //qDebug()<<ui->languageList->itemText(i);
        ui->languageList->removeItem(i);
        ui->languageList_2->removeItem(i);
    }

    n=languageList.count();
    for(int i=0;i<n;i++){
        position.setNum(i+1);
        element="L"+position+":"+languageList.at(i).getName();
        ui->languageList->insertItem(i+1,element);
        ui->languageList_2->addItem(element);
    }

}

void MainWindow::showLanguageIn1(int i){
    if(i!=0){
        showLanguage(i-1,1);
    }else{
            ui->languageDisplay->setText("");
    }
}
void MainWindow::showLanguageIn2(int i){
    if(i!=0){
        showLanguage(i-1,2);
    }else{
        ui->languageDisplay_2->setText("");
}
}
void MainWindow::showArgument(int op){
    if(op<4)
        ui->stackedArgument->setCurrentIndex(0);
    else if(op==4)
        ui->stackedArgument->setCurrentIndex(1);
    else if(op<8)
        ui->stackedArgument->setCurrentIndex(2);
    else
        ui->stackedArgument->setCurrentIndex(3);
}


void MainWindow::resolve(){
    emit statusChanged("Calculando");
    QString operatorSimbol;    

    int p1=ui->languageList->currentIndex();
    int p2=ui->languageList_2->currentIndex();
    int operation=ui->operations->currentIndex();
    if(p1!=0){
        Language l1=languageList.at(p1-1);
        if(operation<4&&p2!=0){
            Language l2=languageList.at(p2-1);
            if(operation==0){
                l1.unite(l2);
                operatorSimbol="u";
            }else if(operation==1){
                l1.intersect(l2);
                operatorSimbol="n";
            }else if(operation==2){
                l1.subtract(l2);
                operatorSimbol="-";
            }else if(operation==3){
                l1.concatenate(l2);
                operatorSimbol=".";
            }
            l1.setName("("+l1.getName()+") "+operatorSimbol+" ("+l2.getName()+")");
        }else if(operation==4){
            int n=ui->argumentN->value();
            QString strN;
            strN.setNum(n);
            l1.exponentiate(n);
            l1.setName("("+l1.getName()+")^"+strN);

        }else if(operation<8){
            int k=ui->argumentK->value();
            QString strK;
            strK.setNum(k);
            if(operation==5){
                l1.kleenePlus(k);
                l1.setName("("+l1.getName()+")^+");
            }else if(operation==6){
                l1.kleeneStar(k);
                l1.setName("("+l1.getName()+")^*");
            }else if(operation==7){
                l1.complement(k);
                l1.setName("~("+l1.getName()+")");
            }
        }else if(operation==8){
            l1.invert();
            l1.setName("("+l1.getName()+")^-1");
        }


        if(l1.getName()!=""){
            ui->resultDisplay->setText(l1.getName()+"= {"+l1.getElementsText()+"}");
        }
    }

    emit statusChanged("Listo");
}



//Slots Creacion por teclado
void MainWindow::showAlphabetCreate(){
    ui->simbols->setText("");
    ui->AlphabetName->setText("");
    if(alphabet.isEmpty())
       ui->alphabetAdvice->hide();
    else
        ui->alphabetAdvice->show();
    ui->dockWidget_Alphabet->show();
}
void MainWindow::showLanguageCreate(){
    if(!alphabet.empty()){
        ui->languageName->setText("");
        ui->words->setText("");
        ui->dockWidget_Language->show();
    }else
        QMessageBox::critical(this, tr("Error"),
        tr("Debe haber un alfabeto cargado."));
}

void MainWindow::createAlphabet(){
    QString simbols;
    QStringList simbolsList;

    this->alphabet.setName(ui->AlphabetName->text());

    simbols=ui->simbols->toPlainText();
    simbols.trimmed();
    simbolsList=simbols.split(',');

    for(int i=0;i<simbolsList.count();i++){
        if(!((simbolsList.at(i)>="a"&&simbolsList.at(i)<="z"))){
            simbolsList.removeAt(i);
        }
    }

    if(!simbolsList.isEmpty()){
        alphabet.clear();
        for(int i=0;i<simbolsList.count();i++){
            alphabet.insert(simbolsList.at(i));
        }
        showAlphabet();
        ui->dockWidget_Alphabet->hide();
        //Revalidar palabras para el nuevo alfabeto
        for(int i=0;i<languageList.count();i++){
            Language l=languageList.takeAt(i);
            l.revalidateWords();
            languageList.insert(i,l);
        }
        int index=ui->languageList->currentIndex();
        listLanguages();
        ui->languageList->setCurrentIndex(index);

    }else{
        QMessageBox::critical(this, tr("Error"),
        tr("El alfabeto debe tener al menos un simbolo."));
    }
}
void MainWindow::createLanguage(){
    Language language(ui->languageName->text(),&alphabet);
    QString words = ui->words->toPlainText();
    words.trimmed();

    QStringList wordsList=words.split(',');
    for(int i=0;i<wordsList.count();i++)
        language.insert(wordsList.at(i));
    this->languageList.push_back(language);

    listLanguages();
    ui->languageList->setCurrentIndex(ui->languageList->count()-1);

    ui->dockWidget_Language->hide();
}


void MainWindow::saveAlphabet(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                    tr("Guardar Alfabeto"),
                                    alphabet.getName(),
                                    tr("Archivo de Texto (*.txt)"));

    fileName+=".txt";
    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
         QTextStream out(&data);
         out << alphabet.getName()<<"\n"<<alphabet.getElementsText()<<"\n";
     }

}

void MainWindow::saveCurrentLanguage1(){
    int index=ui->languageList->currentIndex();
    Language l=languageList.at(index-1);

    QString fileName = QFileDialog::getSaveFileName(this,
                                    tr("Guardar Lenguaje"),
                                    l.getName(),
                                    tr("Archivo de Texto (*.txt)"));

    fileName+=".txt";
    QString elements=l.getElementsText();
    elements.replace(QChar(955),"");
    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
         QTextStream out(&data);
         out << l.getName()<<"\n"<<elements;
     }

}

void MainWindow::saveLanguages(){

}

void MainWindow::saveResult(){

}

//fin slot teclado
