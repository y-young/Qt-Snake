#include "walls.h"

#include <QPainter>
#include <QDebug>

Walls::Walls(QWidget *parent) :
    QWidget(parent)
{
}
void Walls::draw(QPainter *painter)
{
    painter->setBrush(QColor(WALL_COLOR));
    for(int i = 0; i < list.size(); ++i) {
        QPoint p = list[i];
        painter->drawRect(p.rx(), p.ry(), GRID_SIZE, GRID_SIZE);
    }
}
void Walls::generateSurroundingWalls() {
    int minX = -MAP_WIDTH / 2, maxX = -minX;
    int minY = -MAP_HEIGHT / 2, maxY = -minY;
    //up
    for(int x = minX; x < maxX; x += GRID_SIZE) {
        list.push_back(QPoint(x, minY));
    }
    //down
    for(int x = minX; x < maxX; x += GRID_SIZE) {
        list.push_back(QPoint(x, maxY - GRID_SIZE));
    }
    //left
    for(int y = minY; y < maxY; y += GRID_SIZE) {
        list.push_back(QPoint(minX, y));
    }
    //right
    for(int y = minY; y < maxY; y += GRID_SIZE) {
        list.push_back(QPoint(maxX - GRID_SIZE, y));
    }
}
void Walls::add(QPoint pos) {
    if(list.contains(pos)) {
        return;
    }
    list.append(pos);
}
void Walls::checkHit(int snakeId, const QPoint& head) {
    if(list.contains(head)) {
        emit hitWall(snakeId);
    }
}
void Walls::checkOverwrite(QPoint& p, int index) {
    if(list.contains(p)) {
        emit overwritten(index);
    }
}
Walls::~Walls()
{

}
QDataStream& operator<<(QDataStream& out, const Walls& walls) {
    out<<walls.list;
    return out;
}
QDataStream& operator>>(QDataStream& in, Walls& walls) {
    in>>walls.list;
    return in;
}
