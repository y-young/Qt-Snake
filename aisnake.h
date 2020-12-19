#ifndef AISNAKE_H
#define AISNAKE_H

#include <QWidget>
#include "snake.h"
#include "foods.h"

class AISnake : public Snake
{
    Q_OBJECT

public:
    explicit AISnake();
    void setFoods(Foods* f);
    void keyEvent(int key);
    bool isAI() override;
    ~AISnake();

protected:
    QPoint target;
    void move() override;
    void decide();

private:
    QVector<Food>* foods;

public slots:
    void refreshTarget();
};

#endif // AISNAKE_H
