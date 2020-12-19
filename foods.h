#ifndef FOODS_H
#define FOODS_H

#include <QWidget>
#include <QVector>
#include <QTime>
#include <QRandomGenerator>
#include <QtDebug>
#include "constants.h"

class Food
{
    friend QDataStream& operator<<(QDataStream& out, const Food& food);
    friend QDataStream& operator>>(QDataStream& in, Food& food);
public:
    int typeIndex;
    QPoint position;
    FoodType type;
    Food() {}
    Food(QPoint p, int t) {
        typeIndex = t;
        position = p;
        type = FoodTypes[t];
    }
};

class Foods : public QWidget
{
    Q_OBJECT

    friend class AISnake;
    friend QDataStream& operator<<(QDataStream& out, const Foods& foods);
    friend QDataStream& operator>>(QDataStream& in, Foods& foods);
public:
    explicit Foods(QWidget *parent = nullptr);
    void draw(QPainter *painter);
    void generate(int num = 1);
    Effect check(const QPoint& p);
    void resize(int s);
    ~Foods();

private:
    QVector<Food> list;
    int scale;
    int rockets, snails;
    bool exists(QPoint p);
    Food newFood();
    int randomFood();

signals:
    void foodEaten(int snakeId, FoodType type);
    void foodGenerated(QPoint& p, int index);

public slots:
    void checkEat(int id, const QPoint& head);
    void regenerate(int index);
};

#endif // FOODS_H
