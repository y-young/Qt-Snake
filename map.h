#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include "snake.h"
#include "foods.h"
#define RENDERSPEED 40

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
private:
    Ui::Map *ui;
    Snake *snake;
    Snake *snake1 = nullptr;
    Foods *foods;
    QTimer *timer;
    void snakeMove();
    void checkEat();
};

#endif // MAP_H
