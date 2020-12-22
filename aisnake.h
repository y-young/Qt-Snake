#ifndef AISNAKE_H
#define AISNAKE_H

#include <QWidget>
#include "snake.h"
#include "foods.h"
#include "walls.h"

class AISnake : public Snake
{
    Q_OBJECT

public:
    explicit AISnake();
    void setFoods(Foods* f);
    void setWalls(Walls* w);
    void keyEvent(int key);
    bool isAI() override;
    QString name() override;
    ~AISnake();

protected:
    QPoint target;
    void move() override;
    void decide();

private:
    QVector<Food>* foods;
    QVector<QPoint>* walls;

public slots:
    void refreshTarget();
};

#endif // AISNAKE_H
