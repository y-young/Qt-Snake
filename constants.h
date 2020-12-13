#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

#define GRID_SIZE 4

//snake
#define SNAKE_LENGTH 4
#define SNAKE_SPEED 40
#define SPEED_STEP 10

enum Heading {UP, DOWN, LEFT, RIGHT};
const int direction[4][2] = {
    {0,-GRID_SIZE}, {0,GRID_SIZE},{-GRID_SIZE,0}, {GRID_SIZE,0}
};
const QString SNAKE_COLORS[] = {"red", "blue", "green"};
const Heading SNAKE_HEADINGS[] = {RIGHT, LEFT, UP};

//map
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640
#define MAP_WIDTH 240
#define MAP_HEIGHT 160
#define RENDER_SPEED 30

//foods
#define FOOD_SIZE 4
#define FOOD_RENDER_SIZE 7
#define FOOD_RENDER_OFFSET 1.5
enum Effect {NONE, GROW, EXTEND, DIE, SPEED_UP, SLOW_DOWN, UNDEFEATABLE};
const QString FoodTypes[] = {
    "apple", "grape", "peach", "pear",
    "rocket", "snail",
    "heart", "bomb",
    "shield"
};
const Effect FoodEffects[] = {
    GROW, GROW, GROW, GROW,
    SPEED_UP, SLOW_DOWN,
    EXTEND, DIE,
    UNDEFEATABLE
};

//walls
const QString WALL_COLOR = "#e9e8e8";

#endif // CONSTANTS_H
