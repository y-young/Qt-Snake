#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <queue>
#include "constants.h"

class Snake : public QWidget
{
    Q_OBJECT

public:
    const int id;
    Snake(QWidget *parent = nullptr);
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
    Heading heading;
    QColor color;
    int scale;
    QTimer *timer;
    int undefeatableTime = 0;
    int lives;
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
    void snakeMoved(int id, QPoint &head);
    void gameOver();
    void died(int id, int lives);

public slots:
    void applyEffect(int snakeId, Effect effect);
    void die(int snakeId);
};

#endif // SNAKE_H
