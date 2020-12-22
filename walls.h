#ifndef WALLS_H
#define WALLS_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include "constants.h"

class Walls : public QWidget
{
    Q_OBJECT

    friend class AISnake;
    friend QDataStream& operator<<(QDataStream& out, const Walls& walls);
    friend QDataStream& operator>>(QDataStream& in, Walls& walls);
public:
    explicit Walls(QWidget *parent = nullptr);
    void render(QPainter *painter);
    void add(QPoint pos);
    void remove(QPoint pos);
    void generateSurroundingWalls();
    ~Walls();

private:
    QVector<QPoint> list;

signals:
    void hitWall(int snakeId);
    void overwritten(int index);

public slots:
    void checkHit(int snakeId, const QPoint& head);
    void checkOverwrite(QPoint& p, int index);
};

#endif // WALLS_H
