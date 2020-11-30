#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QtDebug>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    snake = new Snake();
    snake1 = new Snake(nullptr, LEFT, "blue");
//    snake1->slowDown();
    foods = new Foods();
    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::snakeMove));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::checkEat));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDER_SPEED);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Map::snakeMove() {
    snake->move();
    if(snake1 != nullptr) {
        snake1->move();
    }
}
void Map::checkEat() {
    if(foods->check(snake->head())) {
        snake->grow();
    }
    if(snake1 != nullptr) {
        if(foods->check(snake1->head())) {
            snake1->grow();
        }
    }
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

Map::~Map()
{
    delete snake;
    if(snake1 != nullptr) {
        delete snake1;
    }
    delete foods;
    delete ui;
}
