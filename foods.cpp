#include "foods.h"
#include <QPainter>

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
        painter->setBrush(list[i].color);
        QPoint p = list[i].pos;
        painter->drawRect(p.rx(), p.ry(), FOOD_SIZE, FOOD_SIZE);
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
