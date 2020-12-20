#include "foods.h"
#include <QPainter>
#include <QImage>

Foods::Foods(QWidget *parent) :
    QWidget(parent)
{
    generate(FOOD_NUM);
}
void Foods::draw(QPainter *painter)
{
    for(int i = 0; i < list.size(); ++i) {
        QPoint p = list[i].position;
        QImage img(":/foods/" + list[i].type.name);
        painter->drawImage(QRectF(p.rx()-FOOD_RENDER_OFFSET, p.ry()-FOOD_RENDER_OFFSET, FOOD_RENDER_SIZE, FOOD_RENDER_SIZE), img);
    }
}
int Foods::randomFood() {
    int rand = QRandomGenerator::global()->bounded(101);
    if(rand <= 70) { // normal fruits
        return QRandomGenerator::global()->bounded(0, 4);
    } else {
        while(true) {
            int t = QRandomGenerator::global()->bounded(4, 8);
            if(FoodTypes[t].name == "rocket") {
                if(rockets == 2) {
                    continue;
                } else {
                    ++rockets;
                    return t;
                }
            }
            if(FoodTypes[t].name == "snail") {
                if(snails == 2) {
                    continue;
                } else {
                    ++snails;
                    return t;
                }
            }
            return t;
        }
    }
}
Food Foods::newFood() {
    int width = MAP_WIDTH/FOOD_SIZE;
    int height = MAP_HEIGHT/FOOD_SIZE;
    int x, y;
    do {
        x = FOOD_SIZE * QRandomGenerator::global()->bounded(-width/2, width/2);
        y = FOOD_SIZE * QRandomGenerator::global()->bounded(-height/2, height/2);
    } while(exists(QPoint(x,y)));
    int type = randomFood();
    return Food(QPoint(x,y), type);
}
void Foods::generate(int num) {
    for(int i = 1; i <= num; ++i) {
        Food food = newFood();
        list.push_back(food);
        emit foodGenerated(food.position, list.size() - 1);
    }
}
void Foods::add(QPoint pos, int foodIndex) {
    Food food(pos, foodIndex);
    list.push_back(food);
    emit foodGenerated(food.position, list.size() - 1);
}
void Foods::remove(QPoint pos) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].position == pos) {
            list.remove(i);
            return;
        }
    }
}
void Foods::regenerate(int index) {
    list.remove(index);
    generate();
}
void Foods::checkEat(int snakeId, const QPoint& snakeHead) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].position == snakeHead) {
            Food food = list[i];
            list.remove(i);
            if(food.type.name == "rocket") {
                --rockets;
            }
            if(food.type.name == "snail") {
                --snails;
            }
            generate();
            emit foodEaten(snakeId, food.type);
            return;
        }
    }
}
bool Foods::exists(QPoint p) {
    for(int i = 0; i < list.size(); ++i) {
        if(list[i].position == p) {
            return true;
        }
    }
    return false;
}
Foods::~Foods()
{

}
QDataStream& operator<<(QDataStream& out, const Food& food) {
    out<<food.typeIndex<<food.position;
    return out;
}
QDataStream& operator<<(QDataStream& out, const Foods& foods) {
    out<<foods.list<<foods.rockets<<foods.snails;
    return out;
}
QDataStream& operator>>(QDataStream& in, Food& food) {
    in>>food.typeIndex;
    in>>food.position;
    food.type = FoodTypes[food.typeIndex];
    return in;
}
QDataStream& operator>>(QDataStream& in, Foods& foods) {
    in>>foods.list;
    in>>foods.rockets>>foods.snails;
    return in;
}
