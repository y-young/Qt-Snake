#ifndef FOODS_H
#define FOODS_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QImage>
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
    void init();
    void render(QPainter *painter);
    void generate(int num = 1);
    void add(QPoint pos, int foodIndex);
    bool remove(QPoint pos);
    ~Foods();

private:
    QVector<Food> list;
    int rockets, snails;
    bool exists(QPoint p);
    Food newFood();
    int randomFoodType();

signals:
    void foodEaten(int snakeId, FoodType type);
    void foodGenerated(const QPoint& p);
    void overwritten(const QPoint& p);

public slots:
    void checkEat(int id, const QPoint& head);
    void checkOverwrite(const QPoint& p);
    void regenerate(const QPoint& p);
};

#endif // FOODS_H
