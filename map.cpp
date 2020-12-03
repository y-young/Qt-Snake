#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QMessageBox>
#include <QtDebug>

Map::Map(QWidget *parent) :
    QWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
//    snake1->slowDown();
    foods = new Foods();
    timer = new QTimer(this);
    snake = new Snake(nullptr, foods);
    snake1 = new Snake(nullptr, foods, LEFT, "blue");
    connect(snake, &Snake::hitSelf, this, QOverload<>::of(&Map::gameOver));
    connect(snake1, &Snake::hitSelf, this, QOverload<>::of(&Map::gameOver));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDER_SPEED);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void Map::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    painter.scale(scale, scale);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("red"));
    snake->draw(&painter);
    if(snake1 != nullptr) {
        snake1->draw(&painter);
    }
    foods->draw(&painter);
}
void Map::resizeEvent(QResizeEvent *) {
    scale = qMin(width() / MAP_WIDTH, height() / MAP_HEIGHT);
    snake->resize(scale);
    foods->resize(scale);
    qDebug() << width() << height() << scale;
}
void Map::pause() {
    snake->pause();
    if(snake1 != nullptr) {
        snake1->pause();
    }
    timer->stop();
}
void Map::resume() {
    timer->start(RENDER_SPEED);
    snake->resume();
    if(snake1 != nullptr) {
        snake1->resume();
    }
}
void Map::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch(key) {
    case Qt::Key_P:
        pause();
        break;
    case Qt::Key_R:
        resume();
        break;
    default:
        snake->keyEvent1(key);
        if(snake1 != nullptr) {
            snake1->keyEvent2(key);
        }
    }
}
void Map::gameOver() {
    pause();
    QMessageBox msgBox;
    msgBox.setText("Game over!");
    msgBox.exec();
    QApplication::exit(0);
}
Map::~Map()
{
    delete snake;
    if(snake1 != nullptr) {
        delete snake1;
    }
    delete foods;
}
