#ifndef FOODS_H
#define FOODS_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QTime>
#include <QRandomGenerator>
#include <QtDebug>
#define FOOD_SIZE 4

const QString FoodColors[] = {
    "orange", "blue", "green", "purple"
};

struct Food {
    QColor color;
    QPoint pos;
    Food() {
        int c = QRandomGenerator::global()->bounded(0, 4);
        int x = QRandomGenerator::global()->bounded(-36, 37);
        int y = QRandomGenerator::global()->bounded(-20, 21);
        color = QColor(FoodColors[c]);
        pos = QPoint(x*FOOD_SIZE,y*FOOD_SIZE);
//        qDebug() << pos<<color;
    }
    Food(QColor c, QPoint p) {
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
    ~Foods();

private:
    QVector<Food> list;
    bool contains(QPoint p);
};

#endif // FOODS_H
