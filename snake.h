#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <QDeadlineTimer>
#include <queue>
#include "constants.h"

class Snake : public QWidget
{
    Q_OBJECT

    friend QDataStream& operator<<(QDataStream& out, const Snake& snake);
    friend QDataStream& operator>>(QDataStream& in, Snake& snake);
public:
    int id;
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
    ~Snake();
protected:

private:
    static int _id;
    QVector<QPoint> body;
    Heading heading;
    QColor color;
    int scale;
    QTimer *timer;
    QDeadlineTimer *undefeatable = nullptr;
    int lives;
    int speed = SNAKE_SPEED;
    std::queue<Heading> userInputs;
    void constructBody();
    void initTimers();
    void keyEvent1(int key);
    void keyEvent2(int key);
    void keyEvent3(int key);
    void setHeading(Heading newHeading);
    void handleUserInput();
    void move();
    void checkHitSelf();
    void checkEat();
    void increaseUndefeatable(int secs = 5);

signals:
    void snakeMoved(int id, QPoint &head);
    void gameOver();
    void died(int id, int lives);
    void overwritten(int index);

public slots:
    void applyEffect(int snakeId, Effect effect);
    void die(int snakeId);
    void checkOverwrite(QPoint& p, int index);
};

#endif // SNAKE_H
