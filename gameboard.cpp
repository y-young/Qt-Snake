#include "gameboard.h"
#include "ui_gameboard.h"
#include <QDebug>

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setStyleSheet("background-color: white");
    this->setFocusPolicy(Qt::StrongFocus);
    map = new Map(this);
    map->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    ui->MapLayout->addWidget(map);
    ui->SidebarLayout->setAlignment(Qt::AlignTop);
}
void GameBoard::init() {
    map->init();
    initPlayers();
}
void GameBoard::initScoreboard(Snake* player) {
    ScoreBoard* scoreboard = new ScoreBoard(player, this);
    ui->ScoreBoardLayout->addWidget(scoreboard);
    scores.push_back(scoreboard);
}
void GameBoard::addPlayer(Snake* player) {
    players.push_back(player);
    map->addPlayer(player);
    initScoreboard(player);
    connect(player, &Snake::died, this, &GameBoard::snakeDied);
}
void GameBoard::initPlayers() {
    for(int i = 1; i <= playerNum; ++i) {
        Snake* player = new Snake(this);
        addPlayer(player);
    }
    if(ai) {
        AISnake* ai = new AISnake();
        addPlayer(ai);
    }
}
void GameBoard::saveGame() {
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QFile file(currentTime + ".sav");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QDataStream out(&file);
    out<<playerNum;
    out<<*map;
    for(int i = 0; i < playerNum; ++i) {
        out<<*(players[i]);
    }
    out<<ai;
    if(ai) {
        out<<*(players[playerNum]);
    }
    file.close();
}
void GameBoard::loadGame(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QDataStream in(&file);
    in>>playerNum;
    in>>*map;
    for(int i = 0; i < playerNum; ++i) {
        Snake* player = new Snake(this);
        in>>(*player);
        addPlayer(player);
    }
    in>>ai;
    if(ai) {
        AISnake* ai = new AISnake();
        in>>(*ai);
        addPlayer(ai);
    }
    file.close();
}
void GameBoard::showPausedDialog() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Paused");
    msgBox.setText("Game paused.\nWhat would you like to do?");
    QPushButton *resumeButton = msgBox.addButton("Resume", QMessageBox::AcceptRole);
    QPushButton *saveButton = msgBox.addButton(QMessageBox::Save);
    msgBox.addButton("Edit map", QMessageBox::NoRole);
    QPushButton *quitButton = msgBox.addButton("Quit", QMessageBox::RejectRole);
    msgBox.exec();
    QPushButton* clicked = (QPushButton*) msgBox.clickedButton();
    if(clicked == resumeButton) {
        map->resume();
    } else if(clicked == saveButton) {
        saveGame();
    } else if(clicked == quitButton) {
        QApplication::exit(0);
    }
}
void GameBoard::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch(key) {
    case Qt::Key_P:
        map->pause();
        showPausedDialog();
        break;
    case Qt::Key_R:
        map->resume();
        break;
    default:
        map->keyPressEvent(event);
    }
}
void GameBoard::singlePlayer() {
    playerNum = 1;
}
void GameBoard::doublePlayers() {
    playerNum = 2;
}
void GameBoard::triplePlayers() {
    playerNum = 3;
}
void GameBoard::onlyAI() {
    playerNum = 0;
    ai = true;
}
void GameBoard::playerAndAI() {
    playerNum = 1;
    ai = true;
}
void GameBoard::noWalls() {
    map->setWallType(NONE);
}
void GameBoard::surroundingWalls() {
    map->setWallType(SURROUNDING);
}
void GameBoard::showEvent(QShowEvent *) {
    map->resume();
}
void GameBoard::snakeDied(int id, int lives) {
    map->pause();
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
        map->resume();
    }
}
GameBoard::~GameBoard()
{
    for(int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    delete map;
    delete ui;
}
