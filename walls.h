#ifndef WALLS_H
#define WALLS_H

#include <QWidget>
#include <QVector>
#include "constants.h"

class Walls : public QWidget
{
    Q_OBJECT

public:
    explicit Walls(QWidget *parent = nullptr);
    void generateSurroundingWalls();
    void draw(QPainter *painter);
    ~Walls();

private:
    QVector<QPoint> list;

signals:
    void hitWall(int snakeId);

public slots:
    void checkHit(int snakeId, const QPoint& head);
};

#endif // WALLS_H
