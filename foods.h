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
    int type;
    QString name;
    QPoint pos;
    Effect effect;
    Food() {}
    Food(QPoint p, int t) {
        type = t;
        name = FoodTypes[t];
        effect = FoodEffects[t];
        pos = p;
    }
};

class Foods : public QWidget
{
    Q_OBJECT

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
    bool contains(QPoint p);
    Food newFood();
    int randomFood();

signals:
    void foodEaten(int snakeId, Effect effect);

public slots:
    void checkEat(int id, const QPoint& head);
};

#endif // FOODS_H
