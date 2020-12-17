#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include "snake.h"
#include "foods.h"
#include "walls.h"
#include "constants.h"

namespace Ui {
class Map;
}
class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    void init();
    void pause();
    void resume();
    void loadGame(QString filename);
    ~Map();
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *) override;
private:
    QVector<Snake*> players;
    Foods *foods;
    Walls *walls;
    QTimer *timer;
    int scale;
    int playerNum = 1;
    enum {NONE, SURROUNDING} wallType = NONE;
    void snakeMove();
    void checkEat();
    void initWalls();
    void initPlayers();
    void registerPlayer(Snake* player);
    void saveGame();
    void showPausedDialog();

public slots:
    void noWalls();
    void surroundingWalls();
    void singlePlayer();
    void doublePlayers();
    void triplePlayers();
    void snakeDied(int id, int lives);
};

#endif // MAP_H
