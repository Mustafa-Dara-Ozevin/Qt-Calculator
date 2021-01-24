#include "calculator.h"
#include "ui_calculator.h"
double calcVal = 0.0;
double memVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i=0; i<10;i++)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Substract,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(released()),this,
            SLOT(EqualButton()));
    connect(ui->ChangeSign,SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear,SIGNAL(released()),this,
            SLOT(ClearPressed()));
    connect(ui->MemAdd,SIGNAL(released()),this,
            SLOT(MemAddPressed()));
    connect(ui->MemGet,SIGNAL(released()),this,
            SLOT(MemGetPressed()));
    connect(ui->Dot,SIGNAL(released()),this,
            SLOT(DotPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton* button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if (displayVal.toDouble() == 0 or displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblnewval = newVal.toDouble();
        ui->Display->setText(QString::number(dblnewval,'g',10));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/",Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }else if (QString::compare(butVal, "*",Qt::CaseInsensitive) == 0){
        mulTrigger = true;
    }else if (QString::compare(butVal, "+",Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else{
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButton(){
    double solution = 0.0;
    double dblDisplayVal = ui->Display->text().toDouble();
    if (divTrigger or mulTrigger or addTrigger or subTrigger){
        if(divTrigger){
            solution = calcVal / dblDisplayVal;
        }else if(mulTrigger){
            solution = calcVal * dblDisplayVal;
        }else if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else {
            solution = calcVal - dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution,'g',10));
}

void Calculator::ChangeNumberSign(){
     double dblDisplayVal = ui->Display->text().toDouble();
     dblDisplayVal *= -1;
     ui->Display->setText(QString::number(dblDisplayVal,'g',10));
}

void Calculator::ClearPressed(){
    calcVal = 0.0;
    ui->Display->setText(QString::number(0));
    memVal = 0.0;
}
void Calculator::MemAddPressed(){
    memVal = ui->Display->text().toDouble();
    ui->Display->setText(QString::number(0));
}

void Calculator::MemGetPressed(){
    ui->Display->setText(QString::number(memVal,'g',10));
}
void Calculator::DotPressed(){
    QString displayVal = ui->Display->text();
    displayVal += QString(".");
    ui->Display->setText(displayVal);
}

