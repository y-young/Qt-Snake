#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include "snake.h"
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
    QTimer *timer;
    void snakeMove();
};

#endif // MAP_H
