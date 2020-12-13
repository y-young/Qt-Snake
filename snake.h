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
    const int id;
    Snake(QWidget *parent = nullptr, Foods* f = nullptr);
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
    static int _id;
    QVector<QPoint> body;
    Foods* foods;
    Heading heading;
    QColor color;
    int scale;
    QTimer *timer;
    int undefeatableTime = 0;
    int speed = SNAKE_SPEED;
    bool processing = false;
    void checkHitSelf();
    void checkEat();
    void increaseUndefeatable();
    void decreaseUndefeatable();

signals:
    void hitSelf();
};

#endif // SNAKE_H
