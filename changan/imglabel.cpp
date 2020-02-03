#include "imglabel.h"
#include <cmath>
#include <QDebug>
#define cout qDebug()

const double pi = 3.141592654;

imglabel::imglabel(QWidget *parent) : QWidget(parent)
{
//no init neccessary
}

void imglabel::addstartscreen(StartScreen* st){
    connect(st, SIGNAL(clock()),this, SLOT(updatetime()));
}
void imglabel::updatetime(){
    this->update();
}

//called every second to update clock hand
void imglabel::paintEvent(QPaintEvent *){
    QTime time = QTime::currentTime();
    QPoint center;
    center.setX(280);
    center.setY(280);
    QPoint out;
    //this is the other point that, together with center, makes the clock hand
    QPainter painter(this);
    painter.setRenderHint(painter.Antialiasing);
    //this makes diagonal look better
    int seconds = (time.hour()*60*60+time.minute()*60+time.second());
    int radius = 250;
    double fract = seconds/(24.0*60.0*60.0);
    double angle = (pi/2) - (fract*2*pi);

    double x = (280 + radius*cos(angle));
    double y = (280 + radius*sin(-angle));
    out.setX(static_cast<int>(x));
    out.setY(static_cast<int>(y));

    painter.drawLine(center, out);
    painter.end();
}
