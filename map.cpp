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
    foods = new Foods();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::snakeMove));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::checkEat));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDERSPEED);
}

void Map::snakeMove() {
    snake->move();
}
void Map::checkEat() {
    if(foods->check(snake->head())) {
        snake->grow();
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
    case Qt::Key_Up:
        snake->setHeading(UP);
        break;
    case Qt::Key_Down:
        snake->setHeading(DOWN);
        break;
    case Qt::Key_Left:
        snake->setHeading(LEFT);
        break;
    case Qt::Key_Right:
        snake->setHeading(RIGHT);
        break;
    }
}

Map::~Map()
{
    delete snake;
    delete foods;
    delete ui;
}
