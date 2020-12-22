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
    initFoodSelect();
    initControlPanel();
}
void GameBoard::init() {
    map->init();
    playersAlive = playerNum;
    initPlayers();
}
void GameBoard::initScoreboard(Snake* player) {
    ScoreBoard* scoreboard = new ScoreBoard(player, this);
    ui->ScoreBoardLayout->addWidget(scoreboard);
    scoreboards.push_back(scoreboard);
}
void GameBoard::initFoodSelect() {
    for(int i = 0; i < FOOD_TYPE_NUM; ++i) {
        ui->FoodSelect->addItem(FoodTypes[i].name);
    }
}
void GameBoard::initControlPanel() {
    connect(ui->PauseResumeButton, &QPushButton::clicked, this, &GameBoard::switchPauseResume);
    connect(ui->SaveGameButton, &QPushButton::clicked, this, &GameBoard::saveGame);
    connect(ui->QuitButton, &QPushButton::clicked, this, [=] { QApplication::exit(0);});
    connect(ui->EditButton, &QPushButton::clicked, this, &GameBoard::startEditing);
    connect(ui->SaveMapButton, &QPushButton::clicked, this, &GameBoard::finishEditing);
    connect(ui->WallsButton, &QRadioButton::clicked, this, &GameBoard::editWalls);
    connect(ui->FoodsButton, &QRadioButton::clicked, this, &GameBoard::editFoods);
    connect(ui->FoodSelect, QOverload<int>::of(&QComboBox::currentIndexChanged), map, &Map::changeFoodType);
}
void GameBoard::addPlayer(Snake* player) {
    players.push_back(player);
    map->addPlayer(player);
    initScoreboard(player);
    connect(player, &Snake::snakeDied, this, &GameBoard::snakeDied);
}
void GameBoard::initPlayers() {
    for(int i = 1; i <= playerNum - static_cast<int>(withAi); ++i) {
        Snake* player = new Snake(this);
        addPlayer(player);
    }
    if(withAi) {
        AISnake* ai = new AISnake();
        addPlayer(ai);
    }
}
void GameBoard::switchPauseResume() {
    if(ui->PauseResumeButton->text() == "Pause") {
        pause();
    } else {
        resume();
    }
}
void GameBoard::pause() {
    map->pause();
    ui->PauseResumeButton->setText("Resume");
    ui->SaveGameButton->setDisabled(false);
    ui->EditButton->setDisabled(false);
}
void GameBoard::resume() {
    map->resume();
    ui->PauseResumeButton->setText("Pause");
    ui->SaveGameButton->setDisabled(true);
    ui->EditButton->setDisabled(true);
}
void GameBoard::startEditing() {
    ui->GameControlWidget->setCurrentIndex(1);
    map->startEditing();
}
void GameBoard::finishEditing() {
    ui->GameControlWidget->setCurrentIndex(0);
    map->finishEditing();
}
void GameBoard::editWalls() {
    ui->FoodSelect->setDisabled(true);
    map->changeEditItem(WALLS);
}
void GameBoard::editFoods() {
    ui->FoodSelect->setDisabled(false);
    map->changeEditItem(FOODS);
}
void GameBoard::saveGame() {
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QString filename = currentTime + ".sav";
    filename = QFileDialog::getSaveFileName(this, "Open saved file", "./" + filename, tr("Saved Files (*.sav)"));
    if(filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QDataStream out(&file);
    out<<playerNum<<playersAlive<<withAi;
    out<<*map;
    for(int i = 0; i < playerNum; ++i) {
        out<<*(players[i]);
    }
    file.close();
    QMessageBox::information(this, "Save Game", "Game saved successfully.");
}
void GameBoard::loadGame(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QDataStream in(&file);
    in>>playerNum>>playersAlive>>withAi;
    in>>*map;
    for(int i = 0; i < playerNum - static_cast<int>(withAi); ++i) {
        Snake* player = new Snake(this);
        in>>(*player);
        addPlayer(player);
    }
    if(withAi) {
        AISnake* ai = new AISnake();
        in>>(*ai);
        addPlayer(ai);
    }
    file.close();
}
void GameBoard::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch(key) {
    case Qt::Key_P:
        pause();
        break;
    case Qt::Key_R:
        resume();
        break;
    case Qt::Key_Escape:
        QApplication::exit(0);
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
    playerNum = 1;
    withAi = true;
}
void GameBoard::playerAndAI() {
    playerNum = 2;
    withAi = true;
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
void GameBoard::snakeDied(int snakeId) {
    --playersAlive;
    if(playersAlive == 0) {
        gameOver(snakeId);
    }
}
void GameBoard::gameOver(int surviverId) {
    pause();
    QMessageBox msgBox;
    QString result = "Game over, ";
    msgBox.setWindowTitle("Game Over");
    // calculate the result
    if(playerNum == 1 && withAi == false) {
        result += "your final score: " + QString::number(players[0]->getScore());
    } else {
        // judge who is the winner
        int maxScore = -1;
        bool tie = false;
        QString winner;
        for(int i = 0; i < playerNum; ++i) {
            Snake* player = players[i];
            int score = player->getScore();
            if(score > maxScore) {
                winner = player->name();
                maxScore = score;
                tie = false;
            } else if(score == maxScore) { // may be a tie
                tie = true;
            }
        }
        if(tie) { // if scores are equal, the last surviver is the winner
            winner = players[surviverId]->name();
        }
        result += winner + " is the winner!";
    }
    msgBox.setText(result);
    msgBox.exec();
    QApplication::exit(0);
}
GameBoard::~GameBoard()
{
    for(int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    delete map;
    delete ui;
}
