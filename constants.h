#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

//snake
#define SNAKE_SIZE 4
#define SNAKE_SPEED 40
#define SPEED_STEP 10

enum Heading {UP, DOWN, LEFT, RIGHT};
const int direction[4][2] = {
    {0,-SNAKE_SIZE}, {0,SNAKE_SIZE},{-SNAKE_SIZE,0}, {SNAKE_SIZE,0}
};

//map
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640
#define MAP_WIDTH 240
#define MAP_HEIGHT 160
#define RENDER_SPEED 30

//foods
#define FOOD_SIZE 4
const QString FoodColors[] = {
    "orange", "cyan", "green", "purple"
};

#endif // CONSTANTS_H
