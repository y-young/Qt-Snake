#include "aisnake.h"
#include <QTimer>
#include <QDeadlineTimer>

AISnake::AISnake() :
    Snake()
{
    id = 3;
    color = AI_SNAKE_COLOR;
}
void AISnake::setFoods(Foods *f) {
    foods = &f->list;
    connect(f, &Foods::foodEaten, this, &AISnake::refreshTarget);
    refreshTarget();
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
        if(body.contains(QPoint(x,y))) {
            continue;
        }
        int newDist = (QPoint(x, y) - target).manhattanLength();
        if(newDist < dist) {
            qDebug() << dist<<newDist<< "choose " << i;
            dist = newDist;
            newHeading = i;
        }
    }
    qDebug() <<"heading: "<<heading<<"newheading: " <<static_cast<Heading>(newHeading)<<"\n";
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
    qDebug() << target;
}
bool AISnake::isAI() {
    return true;
}
AISnake::~AISnake()
{

}
