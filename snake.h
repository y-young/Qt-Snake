#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <queue>
#include "foods.h"
#include "constants.h"

class Snake : public QWidget
{
    Q_OBJECT

public:
    const int id;
    Snake(QWidget *parent = nullptr, Foods* f = nullptr);
    void draw(QPainter *painter);
    void grow();
    void keyEvent(int key);
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
    std::queue<Heading> userInputs;
    void keyEvent1(int key);
    void keyEvent2(int key);
    void keyEvent3(int key);
    void setHeading(Heading newHeading);
    void handleUserInput();
    void move();
    void checkHitSelf();
    void checkEat();
    void increaseUndefeatable();
    void decreaseUndefeatable();

signals:
    void hitSelf();
};

#endif // SNAKE_H
