#include "aisnake.h"

// public methods:

AISnake::AISnake() :
    Snake()
{
    color = AI_SNAKE_COLOR;
}
void AISnake::setFoods(Foods *f) {
    foods = &f->list;
    connect(f, &Foods::foodEaten, this, &AISnake::refreshTarget);
    refreshTarget();
}
void AISnake::setWalls(Walls *w) {
    walls = &w->list;
}
void AISnake::keyEvent(int) {}
bool AISnake::isAI() {
    return true;
}
QString AISnake::name() {
    return "AI";
}
AISnake::~AISnake()
{
}

// protected methods:

void AISnake::move() {
    Snake::move();
    autoMove();
}

// private methods:

void AISnake::autoMove() {
    QPoint current = head();
    int dist = INT_MAX;
    int newHeading = heading;
    refreshTarget();
    // check 3 possible directions
    for(int i = 0; i < 4; ++i) {
        // avoid turning around
        if(heading - i == 2 || heading - i == -2) {
            continue;
        }
        int x = current.rx() + direction[i][0];
        int y = current.ry() + direction[i][1];
        QPoint next(x,y);
        if(body.contains(next) || walls->contains(next)) {
            continue;
        }
        int newDist = (next - target).manhattanLength();
        if(newDist < dist) {
            dist = newDist;
            newHeading = i;
        }
    }
    setHeading(static_cast<Heading>(newHeading));
}

// slots:

// refresh target food
void AISnake::refreshTarget() {
    QPoint current = head();
    int dist = INT_MAX;
    for(int i = 0; i < foods->size(); ++i) {
        QPoint p = (*foods)[i].position;
        int newDist = (p - current).manhattanLength();
        if(newDist < dist) {
            dist = newDist;
            target = p;
        }
    }
}
