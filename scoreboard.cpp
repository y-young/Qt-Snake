#include "scoreboard.h"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(Snake* player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #f5f5f5");
    setName(player);
    updateLives(player->lives);
    connect(player, &Snake::livesUpdated, this, &ScoreBoard::updateLives);
}
void ScoreBoard::setName(Snake* player) {
    if(player->isAI()) {
        ui->PlayerName->setText("AI");
    } else {
        ui->PlayerName->setText("Player " + QString::number(player->id));
    }
}
void ScoreBoard::updateLives(int lives) {
    ui->Lives->setText(QString::number(lives));
}
ScoreBoard::~ScoreBoard()
{
    delete ui;
}
