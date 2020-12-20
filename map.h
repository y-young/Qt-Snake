#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include "snake.h"
#include "foods.h"
#include "walls.h"
#include "aisnake.h"
#include "constants.h"

class Map : public QWidget
{
    Q_OBJECT

    friend QDataStream& operator<<(QDataStream& out, const Map& map);
    friend QDataStream& operator>>(QDataStream& in, Map& map);
public:
    explicit Map(QWidget *parent = nullptr);
    void init();
    void addPlayer(Snake* player);
    void pause();
    void resume();
    void setWallType(WallType type);
    void startEditing();
    void finishEditing();
    void changeEditItem(MapItem item);
    void keyPressEvent(QKeyEvent *event) override;
    ~Map();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
private:
    QVector<Snake*> players;
    Foods *foods;
    Walls *walls;
    QTimer *timer;
    int scale;
    bool editing = false;
    MapItem editingItem = WALLS;
    WallType wallType = NONE;
    int selectedFoodIndex = 0;
    void initWalls();
    QPoint convert2MapPoint(int x, int y);

public slots:
    void changeFoodType(int foodIndex);
};

#endif // MAP_H
