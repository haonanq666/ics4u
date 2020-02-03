#include "helpwindow.h"
#include "ui_helpwindow.h"

helpwindow::helpwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpwindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(242,236,222)");
    this->setWindowTitle("长安十二时辰|Help");
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //remove top taskbar
    ui->textEdit->setReadOnly(true);

}

helpwindow::~helpwindow()
{
    delete ui;
}

void helpwindow::on_pushButton_clicked()
{
    emit okaypressed();
}
