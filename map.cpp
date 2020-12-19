#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QMessageBox>
#include <QtDebug>

Map::Map(QWidget *parent) :
    QWidget(parent)
{
//    this->setFocusPolicy(Qt::StrongFocus);
    this->setStyleSheet("background-color: white");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDER_SPEED);
    this->pause();
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void Map::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    painter.scale(scale, scale);

    painter.setPen(Qt::NoPen);
    for(int i = 0; i < players.size(); ++i) {
        players[i]->draw(&painter);
    }
    foods->draw(&painter);
    walls->draw(&painter);
}
void Map::resizeEvent(QResizeEvent *) {
    scale = qMin(width() / MAP_WIDTH, height() / MAP_HEIGHT);
    foods->resize(scale);
    qDebug() << width() << height() << scale;
}
void Map::pause() {
    for(int i = 0; i < players.size(); ++i) {
        players[i]->pause();
    }
    timer->stop();
}
void Map::resume() {
    timer->start(RENDER_SPEED);
    for(int i = 0; i < players.size(); ++i) {
        players[i]->resume();
    }
}
void Map::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if(editing) {
        changeEditingItem(key);
    }
    for(int i = 0; i < players.size(); ++i) {
        players[i]->keyEvent(key);
    }
}
void Map::changeEditingItem(int key) {
    switch (key) {
    case Qt::Key_W:
        editingItem = WALLS;
        break;
    case Qt::Key_F:
        editingItem = FOODS;
        break;
    }
}
void Map::init() {
    foods = new Foods();
    initWalls();
}
void Map::initWalls() {
    walls = new Walls();
    if(wallType == SURROUNDING) {
        walls->generateSurroundingWalls();
    }
    connect(foods, &Foods::foodGenerated, walls, &Walls::checkOverwrite);
    connect(walls, &Walls::overwritten, foods, &Foods::regenerate);
}
void Map::addPlayer(Snake *player) {
    players.push_back(player);
    connect(player, &Snake::snakeMoved, foods, &Foods::checkEat);
    connect(player, &Snake::snakeMoved, walls, &Walls::checkHit);
    connect(foods, &Foods::foodEaten, player, &Snake::applyEffect);
    connect(walls, &Walls::hitWall, player, &Snake::die);
    connect(foods, &Foods::foodGenerated, player, &Snake::checkOverwrite);
    connect(player, &Snake::overwritten, foods, &Foods::regenerate);
    if(player->isAI()) {
        ((AISnake* )player)->setFoods(foods);
    }
}
QDataStream& operator<<(QDataStream& out, const Map& map) {
    out<<*(map.foods)<<*(map.walls);
    return out;
}
QDataStream& operator>>(QDataStream& in, Map& map) {
    map.foods = new Foods();
    map.walls = new Walls();
    in>>*(map.foods)>>*(map.walls);
    return in;
}
void Map::setWallType(WallType type) {
    this->wallType = type;
}
void Map::editMap() {

}
void Map::mousePressEvent(QMouseEvent *event) {
    if(!editing) {
        return;
    }
    int x = event->x(), y = event->y();
    // translate
    x -= WINDOW_WIDTH / 2;
    y -= WINDOW_HEIGHT / 2;
    // scale
    x /= 4;
    y /= 4;
    // round to grid
    x -= x % GRID_SIZE;
    y -= y % GRID_SIZE;
    if(x < 0) {
        x -= GRID_SIZE;
    }
    if(y < 0) {
        y -= GRID_SIZE;
    }
//    qDebug() << x << y;
    if(event->button() == Qt::LeftButton) {
        walls->add(QPoint(x, y));
        this->update();
    }
}
Map::~Map()
{
    delete foods;
    delete walls;
}
