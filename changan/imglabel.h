#ifndef IMGLABEL_H
#define IMGLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QTime>
#include "startscreen.h"

//widget for the clock
class imglabel : public QWidget
{
    Q_OBJECT
public:
    explicit imglabel(QWidget *parent = nullptr);
    //predefined destructor already exists no need for another
    void addstartscreen(StartScreen* st);
protected:
    void paintEvent(QPaintEvent *) override;
    //called every loop to update the clock and repaint it

public slots:
    void updatetime();

};

#endif // IMGLABEL_H
