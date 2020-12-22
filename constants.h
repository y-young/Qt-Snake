#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QColor>

#define GRID_SIZE 4

//snake
#define SNAKE_LENGTH 4
#define SNAKE_SPEED 40
#define SNAKE_MAX_SPEED 30
#define SNAKE_MIN_SPEED 50
#define SPEED_STEP 5

enum Heading {UP, LEFT, DOWN, RIGHT};
const int direction[4][2] = {
    {0,-GRID_SIZE}, {-GRID_SIZE,0}, {0,GRID_SIZE}, {GRID_SIZE,0}
};
const QColor AI_SNAKE_COLOR = QColor("orange");
const QString SNAKE_COLORS[] = {"red", "blue", "green"};
const Heading SNAKE_HEADINGS[] = {RIGHT, LEFT, RIGHT};

//map
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640
#define MAP_WIDTH 240
#define MAP_HEIGHT 160
#define RENDER_SPEED 30
enum MapItem {WALLS, FOODS};
enum WallType {NONE, SURROUNDING};

//foods
#define FOOD_NUM 3
#define FOOD_SIZE 4
#define FOOD_RENDER_SIZE 7
#define FOOD_RENDER_OFFSET 1.5
#define FOOD_TYPE_NUM 9
enum Effect {GROW, EXTEND, DIE, ACCELERATE, DECELERATE, UNDEFEATABLE, RESET};
struct FoodType {
    friend QDataStream& operator<<(QDataStream& out, const FoodType& type);
    QString name;
    Effect effect = GROW;
    int point = 0;
    FoodType() {}
    FoodType(QString n, Effect e, int p = 0) {
        name = n;
        effect = e;
        point = p;
    }
};

const FoodType
    apple("apple", GROW, 15),
    grape("grape", GROW, 5),
    pear("pear", GROW, 10),
    peach("peach", GROW, 20),
    rocket("rocket", ACCELERATE),
    snail("snail", DECELERATE),
    shield("shield", UNDEFEATABLE),
    heart("heart", EXTEND),
    green_apple("green_apple", RESET)
;
const FoodType FoodTypes[] = {
    apple, grape, peach, pear,
    rocket, snail,
    shield,
    heart,
    green_apple
};

//walls
const QString WALL_COLOR = "#e9e8e8";

#endif // CONSTANTS_H
