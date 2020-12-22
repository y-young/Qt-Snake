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
    int lives = 1;
    int score = 0;
    QDeadlineTimer *undefeatable = nullptr;
    Snake(QWidget *parent = nullptr);
    void draw(QPainter *painter);
    void grow();
    void keyEvent(int key);
    void slowDown();
    void speedUp();
    QPoint head();
    void pause();
    void resume();
    virtual QString name();
    bool isDead();
    ~Snake();
    virtual bool isAI();

protected:
    static int _id;
    QColor color;
    QTimer *timer;
    QVector<QPoint> body;
    Heading heading;
    int speed = SNAKE_SPEED;
    virtual void move();
    void setHeading(Heading newHeading);
    void checkHitSelf();

private:
    std::queue<Heading> userInputs;
    void constructBody();
    void reset();
    void initTimers();
    void keyEvent1(int key);
    void keyEvent2(int key);
    void keyEvent3(int key);
    void handleUserInput();
    void increaseUndefeatable(int secs = 5);

signals:
    void snakeMoved(int id, QPoint &head);
    void snakeDied(int id);
    void overwritten(int index);
    void livesUpdated(int lives);
    void scoreUpdated(int score);

public slots:
    void eatFood(int snakeId, FoodType foodType);
    void die(int snakeId);
    void checkOverwrite(QPoint& p, int index);
};

#endif // SNAKE_H
