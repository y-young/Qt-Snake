#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QTimer>
#include "snake.h"

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreBoard(Snake* player, QWidget *parent = nullptr);
    void setName(Snake* player);
    ~ScoreBoard();

private:
    Ui::ScoreBoard *ui;
    QTimer* timer;
    Snake* player;
    void setUndefeatableTime(int time);

public slots:
    void updateLives(int lives);
    void updateScore(int score);
    void updateUndefeatableTime();
};

#endif // SCOREBOARD_H
