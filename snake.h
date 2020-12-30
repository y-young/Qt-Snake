#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <QPainter>
#include <QTimer>
#include <QDeadlineTimer>
#include <queue>
#include "constants.h"

class Snake : public QWidget
{
    Q_OBJECT

    friend QDataStream& operator<<(QDataStream& out, const Snake& snake);
    friend QDataStream& operator>>(QDataStream& in, Snake& snake);
public:
    Snake(QWidget *parent = nullptr);
    void render(QPainter *painter);
    virtual void keyEvent(int key);
    void pause();
    void resume();
    int getId();
    virtual QString name();
    QPoint head();
    int getLives();
    int getScore();
    int undefeatableTime();
    virtual bool isAI();
    bool isDead();
    ~Snake();

protected:
    int id;
    static int _id;
    QColor color;
    QTimer *timer;
    QDeadlineTimer *undefeatable = nullptr;
    QVector<QPoint> body;
    Heading heading;
    int speed = SNAKE_SPEED;
    virtual void move();
    void setHeading(Heading newHeading);

private:
    int lives = 1;
    int score = 0;
    std::queue<Heading> userInputs;
    void constructBody();
    void processTeleport(int &x, int &y);
    void checkHitSelf();
    void reset();
    void initTimers();
    void grow();
    void accelerate();
    void decelerate();
    void keyEvent1(int key);
    void keyEvent2(int key);
    void keyEvent3(int key);
    void handleUserInput();
    void increaseUndefeatable(int secs = FOOD_UNDEFEATABLE);

signals:
    void snakeMoved(int id, QPoint &head);
    void snakeDied(int id);
    void overwritten(const QPoint& p);
    void livesUpdated(int lives);
    void scoreUpdated(int score);

public slots:
    void eatFood(int snakeId, FoodType foodType);
    void die(int snakeId);
    void checkOverwrite(const QPoint& p);
};

#endif // SNAKE_H
