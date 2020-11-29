#ifndef FOODS_H
#define FOODS_H

#include <QWidget>
#include <QVector>
#include <QTime>
#include <QRandomGenerator>
#include <QtDebug>
#include "constants.h"

struct Food {
    QColor color;
    QPoint pos;
    Food(QPoint p) {
        int c = QRandomGenerator::global()->bounded(0, 4);
        color = QColor(FoodColors[c]);
        pos = p;
    }
    Food(QPoint p, QColor c) {
        color = c;
        pos = p;
    }
};

class Foods : public QWidget
{
    Q_OBJECT

public:
    explicit Foods(QWidget *parent = nullptr);
    void draw(QPainter *painter);
    void generate(int num = 1);
    bool check(const QPoint& p);
    void resize(int s);
    ~Foods();

private:
    QVector<Food> list;
    int scale;
    bool contains(QPoint p);
    Food newFood();
};

#endif // FOODS_H
