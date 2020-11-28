#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QtDebug>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    snake = new Snake();
    snake1 = new Snake(nullptr, LEFT, "blue");
    foods = new Foods();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::snakeMove));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::checkEat));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDERSPEED);
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
    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    snake->draw(&painter);
    if(snake1 != nullptr) {
        snake1->draw(&painter);
    }
    foods->draw(&painter);
}

void Map::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch(key) {
    case Qt::Key_P:
        timer->stop();
        break;
    case Qt::Key_R:
        timer->start(RENDERSPEED);
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
