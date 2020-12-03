#ifndef FOODS_H
#define FOODS_H

#include <QWidget>
#include <QVector>
#include <QTime>
#include <QRandomGenerator>
#include <QtDebug>
#include "constants.h"

struct Food {
    QString type;
    QPoint pos;
    Food(QPoint p) {
        int t = QRandomGenerator::global()->bounded(0, 8);
        type = FoodTypes[t];
        pos = p;
    }
    Food(QPoint p, QString t) {
        type = t;
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
