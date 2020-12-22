#include "snake.h"
#include <QtDebug>

int Snake::_id = 0;

// public methods:

Snake::Snake(QWidget *parent)
    : QWidget(parent), id(_id)
{
    ++_id;
    heading = SNAKE_HEADINGS[id];
    color = SNAKE_COLORS[id];
    constructBody();
    initTimers();
}
void Snake::render(QPainter *painter)
{
    if(isDead()) {
        return;
    }
    QColor c = color;
    painter->setBrush(c);
    // draw head
    QPoint p = body.back();
    painter->drawRect(p.rx(), p.ry(), GRID_SIZE, GRID_SIZE);
    // draw body
    c.setAlpha(150);
    painter->setBrush(c);
    for(int i = body.size() - 2; i >= 0; --i) {
        QPoint p = body[i];
        painter->drawRect(p.rx(), p.ry(), GRID_SIZE, GRID_SIZE);
    }
}
void Snake::keyEvent(int key) {
    if(isDead()) {
        return;
    }
    // different key mappings for different players
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
void Snake::pause() {
    timer->stop();
}
void Snake::resume() {
    if(isDead()) {
        return;
    }
    timer->start(speed);
}
int Snake::getId() {
    return id;
}
QString Snake::name() {
    return "Player " + QString::number(id);
}
QPoint Snake::head() {
    return body.back();
}
int Snake::getLives() {
    return lives;
}
int Snake::getScore() {
    return score;
}
int Snake::undefeatableTime() {
    return undefeatable->remainingTime();
}
bool Snake::isAI() {
    return false;
}
bool Snake::isDead() {
    return lives == 0;
}
Snake::~Snake() {
    delete undefeatable;
}

// protected methods:

void Snake::setHeading(Heading newHeading) {
    // avoid turning around
    if(direction[heading][0] + direction[newHeading][0] == 0  || direction[heading][1] + direction[newHeading][1] == 0) {
        return;
    }
    heading = newHeading;
}
void Snake::move() {
    if(isDead()) {
        return;
    }
    handleUserInput();
    QPoint head = body.back();
    body.pop_front();
    int x = head.rx() + direction[heading][0];
    int y = head.ry() + direction[heading][1];
    processTeleport(x, y);
    head.setX(x);
    head.setY(y);
    body.push_back(head);
    checkHitSelf();
    emit snakeMoved(id, head);
}

// private methods:

void Snake::constructBody() {
    for(int i = -direction[heading][0]*SNAKE_LENGTH; i != 0; i+=direction[heading][0]) {
        body.push_back(QPoint(i,0));
    }
}
// if snake passes the border, teleport it to the other side
void Snake::processTeleport(int &x, int &y) {
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
}
void Snake::checkHitSelf() {
    if(body.indexOf(head()) != body.size() - 1) {
        die(id);
    }
}
// reset length & speed
void Snake::reset() {
    speed = SNAKE_SPEED;
    body.remove(0, body.size() - SNAKE_LENGTH);
}
void Snake::initTimers() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Snake::move));
    timer->start(speed);
    undefeatable = new QDeadlineTimer();
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
void Snake::accelerate() {
    int newSpeed = speed - SPEED_STEP;
    if(newSpeed >= SNAKE_MAX_SPEED) {
        speed = newSpeed;
        timer->setInterval(speed);
    }
}
void Snake::decelerate() {
    int newSpeed = speed + SPEED_STEP;
    if(newSpeed <= SNAKE_MIN_SPEED) {
        speed = newSpeed;
        timer->setInterval(speed);
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
void Snake::handleUserInput() {
    if(userInputs.empty()) {
        return;
    }
    Heading newHeading = userInputs.front();
    userInputs.pop();
    setHeading(newHeading);
}
void Snake::increaseUndefeatable(int secs) {
    if(undefeatable->hasExpired()) {
        delete undefeatable;
        undefeatable = new QDeadlineTimer(secs*1000);
    } else {
        *undefeatable += secs * 1000;
    }
}

// slots:

void Snake::eatFood(int snakeId, FoodType foodType) {
    if(snakeId != id) {
        return;
    }
    score += foodType.point;
    emit scoreUpdated(score);
    switch (foodType.effect) {
    case GROW:
        grow();
        break;
    case ACCELERATE:
        accelerate();
        break;
    case DECELERATE:
        decelerate();
        break;
    case UNDEFEATABLE:
        increaseUndefeatable();
        break;
    case EXTEND:
        ++lives;
        emit livesUpdated(lives);
        break;
    case RESET:
        reset();
        break;
    default:
        break;
    }
}
void Snake::die(int snakeId) {
    if(snakeId != id) {
        return;
    }
    if(!undefeatable->hasExpired()) {
        return;
    }
    --lives;
    emit livesUpdated(lives);
    reset();
    if(lives > 0) {
        increaseUndefeatable(RESURGE_COOLDOWN);
    } else {
        pause();
        emit snakeDied(id);
    }
}
void Snake::checkOverwrite(QPoint& p, int index) {
    if(body.contains(p)) {
        emit overwritten(index);
    }
}

// friends:

QDataStream& operator<<(QDataStream& out, const Snake& snake) {
    out<<snake.id
       <<snake.lives
       <<snake.score
       <<snake.speed
       <<snake.heading
       <<snake.undefeatable->remainingTime()
       <<snake.body;
    return out;
}
QDataStream& operator>>(QDataStream& in, Snake& snake) {
    qint64 remainingTime;
    in>>snake.id
      >>snake.lives
      >>snake.score
      >>snake.speed
      >>snake.heading
      >>remainingTime
      >>snake.body;
    snake.undefeatable = new QDeadlineTimer(remainingTime);
    return in;
}
