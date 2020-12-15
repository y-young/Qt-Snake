#include "map.h"
#include "ui_map.h"
#include <QPainter>
#include <QMessageBox>
#include <QtDebug>

Map::Map(QWidget *parent) :
    QWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setStyleSheet("background-color: white");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
    timer->start(RENDER_SPEED);
    this->pause();
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void Map::paintEvent(QPaintEvent *)
{
    for(int i = 0; i < players.size(); ++i) {
        walls->checkHit(players[i]);
    }
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
void Map::showEvent(QShowEvent *) {
    this->resume();
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
        for(int i = 0; i < players.size(); ++i) {
            players[i]->keyEvent(key);
        }
    }
}
void Map::init() {
    foods = new Foods();
    initWalls();
    initPlayers();
}
void Map::initWalls() {
    walls = new Walls();
    if(wallType == SURROUNDING) {
        walls->generateSurroundingWalls();
    }
    connect(walls, &Walls::hitWall, this, QOverload<>::of(&Map::gameOver));
}
void Map::initPlayers() {
    qDebug() << playerNum;
    for(int i = 1; i <= playerNum; ++i) {
        Snake* player = new Snake(this, foods);
        players.push_back(player);
        connect(player, &Snake::hitSelf, this, QOverload<>::of(&Map::gameOver));
    }
}
void Map::noWalls() {
    wallType = NONE;
}
void Map::surroundingWalls() {
    wallType = SURROUNDING;
}
void Map::singlePlayer() {
    playerNum = 1;
}
void Map::doublePlayers() {
    playerNum = 2;
}
void Map::triplePlayers() {
    playerNum = 3;
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
    for(int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    delete foods;
}
