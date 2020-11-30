#include "snake.h"

#include <QPainter>
#include <QTimer>
#include <QtDebug>

Snake::Snake(QWidget *parent, Heading h, QString c)
    : QWidget(parent)
{
    for(int i = -direction[h][0]*SNAKE_SIZE; i != 0; i+=direction[h][0]) {
        body.push_back(QPoint(i,0));
    }
    heading = h;
    color = QColor(c);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Snake::move));
    timer->start(speed);
}
void Snake::slowDown() {
    speed += SPEED_STEP;
    timer->setInterval(speed);
}
void Snake::speedUp() {
    speed -= SPEED_STEP;
    timer->setInterval(speed);
}
void Snake::draw(QPainter *painter)
{
    QColor c = color;
    painter->setBrush(c);
    //draw head
    QPoint p = body.back();
    painter->drawRect(p.rx(), p.ry(), SNAKE_SIZE, SNAKE_SIZE);
    //draw body
    c.setAlpha(150);
    painter->setBrush(c);
    for(int i = body.size() - 2; i >= 0; --i) {
        QPoint p = body[i];
        painter->drawRect(p.rx(), p.ry(), SNAKE_SIZE, SNAKE_SIZE);
    }
}
void Snake::setHeading(Heading newHeading) {
    if(direction[heading][0] + direction[newHeading][0] == 0  || direction[heading][1] + direction[newHeading][1] == 0) {
        return;
    }
    heading = newHeading;
//    move(); // Temporary solution to turning around
}
void Snake::pause() {
    timer->stop();
}
void Snake::resume() {
    timer->start(speed);
}
void Snake::keyEvent1(int key) {
    switch(key) {
    case Qt::Key_Up:
        setHeading(UP);
        break;
    case Qt::Key_Down:
        setHeading(DOWN);
        break;
    case Qt::Key_Left:
        setHeading(LEFT);
        break;
    case Qt::Key_Right:
        setHeading(RIGHT);
        break;
    }
}
void Snake::keyEvent2(int key) {
    switch(key) {
    case Qt::Key_W:
        setHeading(UP);
        break;
    case Qt::Key_S:
        setHeading(DOWN);
        break;
    case Qt::Key_A:
        setHeading(LEFT);
        break;
    case Qt::Key_D:
        setHeading(RIGHT);
        break;
    }
}
void Snake::grow() {
    QPoint tail = body.front();
    int dx, dy;
    if(body.size() > 1) {
        QPoint beforeTail = body.at(1);
        dx = tail.rx() - beforeTail.rx();
        dy = tail.ry() - beforeTail.ry();

    } else {
        dx = direction[heading][0];
        dy = direction[heading][1];
    }
    tail.setX(tail.rx() + dx);
    tail.setY(tail.ry() + dy);
    body.push_front(tail);
}
void Snake::resize(int s) {
    scale = s;
}
void Snake::move() {
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
}
QPoint Snake::head() {
    return body.back();
}
