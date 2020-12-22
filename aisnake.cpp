#include "aisnake.h"
#include <QTimer>
#include <QDeadlineTimer>

AISnake::AISnake() :
    Snake()
{
    color = AI_SNAKE_COLOR;
}
QString AISnake::name() {
    return "AI";
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
void AISnake::move() {
    QPoint head = body.back();
    body.pop_front();
    int x = head.rx() + direction[heading][0];
    int y = head.ry() + direction[heading][1];
    int width = MAP_WIDTH;
    int height = MAP_HEIGHT;
    int w = width/2, h = height/2;
    if(x < -w) {
        x += width;
    }
    if(x >= w) {
        x -= width;
    }
    if(y < -h) {
        y += height;
    }
    if(y >= h) {
        y -= height;
    }
    head.setX(x);
    head.setY(y);
    body.push_back(head);
    checkHitSelf();
    decide();
    emit Snake::snakeMoved(id, head);
}
void AISnake::decide() {
    QPoint current = head();
    int dist = INT_MAX;
    int newHeading = heading;
    refreshTarget();
    for(int i = 0; i < 4; ++i) {
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
bool AISnake::isAI() {
    return true;
}
AISnake::~AISnake()
{

}
