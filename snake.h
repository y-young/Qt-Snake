#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include "foods.h"
#include "constants.h"

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr, Foods* f = nullptr, Heading h=RIGHT, QString c="red");
    void move();
    void draw(QPainter *painter);
    void setHeading(Heading newHeading);
    void grow();
    void keyEvent1(int key);
    void keyEvent2(int key);
    void resize(int s);
    void slowDown();
    void speedUp();
    QPoint head();
    void pause();
    void resume();
protected:

private:
    QVector<QPoint> body;
    Foods* foods;
    Heading heading;
    QColor color;
    int scale;
    QTimer *timer;
    int speed = SNAKE_SPEED;
    bool processing = false;
    void checkHitSelf();
    void checkEat();

signals:
    void hitSelf();
};

#endif // SNAKE_H
