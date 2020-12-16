#include "snake.h"

#include <QPainter>
#include <QTimer>
#include <QtDebug>

int Snake::_id = 0;

Snake::Snake(QWidget *parent)
    : QWidget(parent), id(_id), lives(1)
{
    ++_id;
    heading = SNAKE_HEADINGS[id];
    color = SNAKE_COLORS[id];
    for(int i = -direction[heading][0]*SNAKE_LENGTH; i != 0; i+=direction[heading][0]) {
        body.push_back(QPoint(i,0));
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Snake::move));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Snake::decreaseUndefeatable));
    timer->start(speed);
}
void Snake::applyEffect(int snakeId, Effect effect) {
    if(snakeId != id) {
        return;
    }
    switch (effect) {
    case GROW:
        grow();
        break;
    case SPEED_UP:
        speedUp();
        break;
    case SLOW_DOWN:
        slowDown();
        break;
    case UNDEFEATABLE:
        increaseUndefeatable();
        break;
    case EXTEND:
        ++lives;
        break;
    default:
        break;
    }
}
void Snake::slowDown() {
    int newSpeed = speed + SPEED_STEP;
    undefeatableTime = undefeatableTime * speed / newSpeed;
    speed = newSpeed;
    timer->setInterval(speed);
}
void Snake::speedUp() {
    int newSpeed = speed - SPEED_STEP;
    undefeatableTime = undefeatableTime * speed / newSpeed;
    speed = newSpeed;
    timer->setInterval(speed);
}
void Snake::draw(QPainter *painter)
{
    QColor c = color;
    painter->setBrush(c);
    //draw head
    QPoint p = body.back();
    painter->drawRect(p.rx(), p.ry(), GRID_SIZE, GRID_SIZE);
    //draw body
    c.setAlpha(150);
    painter->setBrush(c);
    for(int i = body.size() - 2; i >= 0; --i) {
        QPoint p = body[i];
        painter->drawRect(p.rx(), p.ry(), GRID_SIZE, GRID_SIZE);
    }
}
void Snake::setHeading(Heading newHeading) {
    if(direction[heading][0] + direction[newHeading][0] == 0  || direction[heading][1] + direction[newHeading][1] == 0) {
        return;
    }
    heading = newHeading;
}
void Snake::pause() {
    timer->stop();
}
void Snake::resume() {
    timer->start(speed);
}
void Snake::keyEvent(int key) {
    switch (id) {
    case 0:
        keyEvent1(key);
        break;
    case 1:
        keyEvent2(key);
        break;
    case 2:
        keyEvent3(key);
        break;
    }
}
void Snake::keyEvent1(int key) {
    switch(key) {
    case Qt::Key_Up:
        userInputs.push(UP);
        break;
    case Qt::Key_Down:
        userInputs.push(DOWN);
        break;
    case Qt::Key_Left:
        userInputs.push(LEFT);
        break;
    case Qt::Key_Right:
        userInputs.push(RIGHT);
        break;
    }
}
void Snake::keyEvent2(int key) {
    switch(key) {
    case Qt::Key_W:
        userInputs.push(UP);
        break;
    case Qt::Key_S:
        userInputs.push(DOWN);
        break;
    case Qt::Key_A:
        userInputs.push(LEFT);
        break;
    case Qt::Key_D:
        userInputs.push(RIGHT);
        break;
    }
}
void Snake::keyEvent3(int key) {
    switch(key) {
    case Qt::Key_I:
        userInputs.push(UP);
        break;
    case Qt::Key_K:
        userInputs.push(DOWN);
        break;
    case Qt::Key_J:
        userInputs.push(LEFT);
        break;
    case Qt::Key_L:
        userInputs.push(RIGHT);
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
void Snake::handleUserInput() {
    if(userInputs.empty()) {
        return;
    }
    Heading newHeading = userInputs.front();
    userInputs.pop();
    setHeading(newHeading);
}
void Snake::move() {
    handleUserInput();
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
    emit snakeMoved(id, head);
}
void Snake::checkHitSelf() {
    if(body.indexOf(head()) != body.size() - 1) {
        die(id);
    }
}
void Snake::increaseUndefeatable() {
    undefeatableTime += 3000 / speed;
}
void Snake::decreaseUndefeatable() {
    if(undefeatableTime > 0) {
        undefeatableTime -= 1;
    }
}
QPoint Snake::head() {
    return body.back();
}
void Snake::die(int snakeId) {
    if(snakeId != id) {
        return;
    }
    if(undefeatableTime > 0) {
        return;
    }
    --lives;
    emit died(id, lives);
    if(lives > 0) {
        increaseUndefeatable();
    }
}
