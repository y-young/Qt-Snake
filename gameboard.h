#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include "snake.h"
#include "map.h"
#include "scoreboard.h"
#include "aisnake.h"
#include "constants.h"

namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    void init();
    void initPlayers();
    void loadGame(QString filename);
    ~GameBoard();

private:
    Ui::GameBoard *ui;
    int playerNum = 1;
    bool ai = false;
    QVector<Snake*> players;
    Map* map;
    QHBoxLayout* container;
    QHBoxLayout* mapContainer;
    QVBoxLayout* scoreContainer;
    QVector<ScoreBoard*> scores;
    void saveGame();
    void addPlayer(Snake* player);
    void showPausedDialog();
    void initScoreboard(Snake* player);

protected:
    void showEvent(QShowEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void noWalls();
    void surroundingWalls();
    void singlePlayer();
    void doublePlayers();
    void triplePlayers();
    void onlyAI();
    void playerAndAI();
    void snakeDied(int id, int lives);
};

#endif // GAMEBOARD_H
