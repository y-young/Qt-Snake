#ifndef WALLS_H
#define WALLS_H

#include <QWidget>
#include <QVector>
#include "snake.h"
#include "constants.h"

class Walls : public QWidget
{
    Q_OBJECT

public:
    explicit Walls(QWidget *parent = nullptr);
    void draw(QPainter *painter);
    void checkHit(Snake* snake);
    ~Walls();

private:
    QVector<QPoint> list;
    void generateSurroundingWalls();

signals:
    void hitWall();
};

#endif // WALLS_H
