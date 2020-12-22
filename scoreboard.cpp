#include "scoreboard.h"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(Snake* p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #f5f5f5");
    player = p;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ScoreBoard::updateUndefeatableTime);
    timer->start(1000);

    setName(player);
    updateLives(player->getLives());
    updateScore(player->getScore());
    updateUndefeatableTime();
    connect(player, &Snake::livesUpdated, this, &ScoreBoard::updateLives);
    connect(player, &Snake::scoreUpdated, this, &ScoreBoard::updateScore);
}
void ScoreBoard::setName(Snake* player) {
    ui->PlayerName->setText(player->name());
}
void ScoreBoard::setUndefeatableTime(int time) {
    ui->UndefeatableTime->setText(QString::number(time / 1000) + " s");
}
void ScoreBoard::updateLives(int lives) {
    ui->Lives->setText(QString::number(lives));
}
void ScoreBoard::updateScore(int score) {
    ui->Score->setText(QString::number(score));
}
void ScoreBoard::updateUndefeatableTime() {
    setUndefeatableTime(player->undefeatableTime());
}
ScoreBoard::~ScoreBoard()
{
    delete ui;
}
