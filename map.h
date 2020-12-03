#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include "snake.h"
#include "foods.h"
#include "constants.h"

namespace Ui {
class Map;
}
class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Snake *snake;
    Snake *snake1 = nullptr;
    Foods *foods;
    QTimer *timer;
    int scale;
    void snakeMove();
    void checkEat();
    void pause();
    void resume();

public slots:
    void gameOver();
};

#endif // MAP_H
