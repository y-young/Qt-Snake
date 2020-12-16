#include "walls.h"

#include <QPainter>

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
    for(int x = minX; x < maxX; ++x) {
        list.push_back(QPoint(x, minY));
    }
    //down
    for(int x = minX; x < maxX; ++x) {
        list.push_back(QPoint(x, maxY - GRID_SIZE));
    }
    //left
    for(int y = minY; y < maxY; ++y) {
        list.push_back(QPoint(minX, y));
    }
    //right
    for(int y = minY; y < maxY; ++y) {
        list.push_back(QPoint(maxX - GRID_SIZE, y));
    }
}
void Walls::checkHit(int snakeId, const QPoint& head) {
    if(list.contains(head)) {
        emit hitWall(snakeId);
    }
}
Walls::~Walls()
{

}
