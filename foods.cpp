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
        painter->drawImage(QRectF(p.rx()-FOOD_RENDER_OFFSET, p.ry()-FOOD_RENDER_OFFSET, FOOD_RENDER_SIZE, FOOD_RENDER_SIZE), img);
    }
}
int Foods::randomFood() {
    int rand = QRandomGenerator::global()->bounded(101);
    if(rand <= 70) { // normal fruits
        return QRandomGenerator::global()->bounded(0, 4);
    } else {
        while(true) {
            int type = QRandomGenerator::global()->bounded(4, 8);
            if(FoodTypes[type] == "rocket") {
                if(rockets == 2) {
                    continue;
                } else {
                    ++rockets;
                    return type;
                }
            }
            if(FoodTypes[type] == "snail") {
                if(snails == 2) {
                    continue;
                } else {
                    ++snails;
                    return type;
                }
            }
            return type;
        }
    }
}
Food Foods::newFood() {
    int width = MAP_WIDTH/FOOD_SIZE;
    int height = MAP_HEIGHT/FOOD_SIZE;
    int x = QRandomGenerator::global()->bounded(-width/2, width/2);
    int y = QRandomGenerator::global()->bounded(-height/2, height/2);
    int type = randomFood();
    return Food(QPoint(x*FOOD_SIZE,y*FOOD_SIZE), type);
}
void Foods::generate(int num) {
    for(int i = 1; i <= num; ++i) {
        list.push_back(newFood());
    }
}
void Foods::checkEat(int snakeId, const QPoint& snakeHead) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].pos == snakeHead) {
            Food food = list[i];
            list.remove(i);
            if(food.type == "rocket") {
                --rockets;
            }
            if(food.type == "snail") {
                --snails;
            }
            generate();
            emit foodEaten(snakeId, food.effect);
            return;
        }
    }
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
