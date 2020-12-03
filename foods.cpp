#include "foods.h"
#include <QPainter>
#include <QImage>

Foods::Foods(QWidget *parent) :
    QWidget(parent)
{
    generate(3);
}
void Foods::resize(int s) {
    scale = s;
}
void Foods::draw(QPainter *painter)
{
    for(int i = 0; i < list.size(); ++i) {
        QPoint p = list[i].pos;
        QImage img(":/foods/" + list[i].type);
        painter->drawImage(QRectF(p.rx()-FOOD_OFFSET, p.ry()-FOOD_OFFSET, FOOD_SIZE, FOOD_SIZE), img);
    }
}
Food Foods::newFood() {
    int width = MAP_WIDTH/FOOD_SIZE;
    int height = MAP_HEIGHT/FOOD_SIZE;
    int x = QRandomGenerator::global()->bounded(-width/2, width/2);
    int y = QRandomGenerator::global()->bounded(-height/2, height/2);
    return Food(QPoint(x*FOOD_SIZE,y*FOOD_SIZE));
}
void Foods::generate(int num) {
    for(int i = 1; i <= num; ++i) {
        list.push_back(newFood());
    }
}
bool Foods::check(const QPoint& p) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].pos == p) {
            list.remove(i);
            generate();
            return true;
        }
    }
    return false;
}
bool Foods::contains(QPoint p) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].pos == p) {
            return true;
        }
    }
    return false;
}
Foods::~Foods()
{

}
