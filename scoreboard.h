#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
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

public slots:
    void updateLives(int lives);
};

#endif // SCOREBOARD_H
