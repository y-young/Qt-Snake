#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include "settingsdialog.h"
#include "gameboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameBoard* game;
    SettingsDialog *settingsDialog;

protected:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void newGame();
    void load();
    void quit();
};
#endif // MAINWINDOW_H
