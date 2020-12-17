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
        showPausedDialog();
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
}
void Map::initPlayers() {
    for(int i = 1; i <= playerNum; ++i) {
        Snake* player = new Snake(this);
        players.push_back(player);
        registerPlayer(player);
    }
}
void Map::registerPlayer(Snake* player) {
    connect(player, &Snake::snakeMoved, foods, &Foods::checkEat);
    connect(player, &Snake::snakeMoved, walls, &Walls::checkHit);
    connect(foods, &Foods::foodEaten, player, &Snake::applyEffect);
    connect(walls, &Walls::hitWall, player, &Snake::die);
    connect(player, &Snake::died, this, &Map::snakeDied);
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
void Map::snakeDied(int id, int lives) {
    pause();
    QMessageBox msgBox;
    if(lives == 0) {
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("Game over!");
        msgBox.exec();
        QApplication::exit(0);
    } else {
        msgBox.setWindowTitle("Player Died");
        msgBox.setText("Player " + QString::number(id) + " died, " + QString::number(lives) + " live(s) remained.");
        msgBox.exec();
        resume();
    }
}
void Map::saveGame() {
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QFile file(currentTime + ".sav");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QDataStream out(&file);
    out<<playerNum;
    out<<(*foods)<<(*walls);
    for(int i = 0; i < playerNum; ++i) {
        out<<*(players[i]);
    }
    file.close();
}
void Map::loadGame(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QDataStream in(&file);
    in>>playerNum;
    foods = new Foods();
    walls = new Walls();
    in>>*foods>>*walls;
    for(int i = 0; i < playerNum; ++i) {
        Snake* player = new Snake(this);
        in>>(*player);
        players.push_back(player);
        registerPlayer(player);
    }
    file.close();
}
void Map::showPausedDialog() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Paused");
    msgBox.setText("Game paused.\nWhat would you like to do?");
    QPushButton *resumeButton = msgBox.addButton("Resume", QMessageBox::AcceptRole);
    QPushButton *saveButton = msgBox.addButton(QMessageBox::Save);
    QPushButton *quitButton = msgBox.addButton("Quit", QMessageBox::RejectRole);
    msgBox.exec();
    QPushButton* clicked = (QPushButton*) msgBox.clickedButton();
    if(clicked == resumeButton) {
        resume();
    } else if(clicked == saveButton) {
        saveGame();
    } else if(clicked == quitButton) {
        QApplication::exit(0);
    }
}
Map::~Map()
{
    for(int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    delete foods;
}
